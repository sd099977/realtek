/* 
 * fat_write.c 
 * 
 * R/W (V)FAT 12/16/32 filesystem implementation by Donggeun Kim 
 * 
 * See file CREDITS for list of people who contributed to this 
 * project. 
 * 
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation; either version 2 of 
 * the License, or (at your option) any later version. 
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, 
 * MA 02111-1307 USA 
 */ 
// #include <common.h>
// #include <config.h>
#include <common.h>
#include "linux/compat.h"
#include <asm/arch/system.h>
#include <rtd_types_qc.h>
//#include <rtd_system.h>
//#include <misc.h>
#include <fs/part.h>
#include <fs/fat.h>
#include <asm/byteorder.h>
//--#include <asm/addrspace.h>

#define KSEG1ADDR

 
static int total_sector; 
extern  block_dev_desc_t *cur_dev;
extern unsigned long part_offset;




#if 1
#if defined(CONFIG_USB_PATCH)
extern __u8	 get_vfatname_block[MAX_CLUSTSIZE] __attribute__ ((aligned (512)));
#else
extern __u8     get_vfatname_block[MAX_CLUSTSIZE];
#endif


#if defined(CONFIG_USB_PATCH)
extern __u8 get_dentfromdir_block[MAX_CLUSTSIZE] __attribute__ ((aligned (512)));
#else
extern __u8 get_dentfromdir_block[MAX_CLUSTSIZE];
#endif


#if defined(CONFIG_USB_PATCH)
extern __u8 do_fat_read_block[MAX_CLUSTSIZE] __attribute__ ((aligned (512))); /* Block buffer */
#else
extern __u8 do_fat_read_block[MAX_CLUSTSIZE];
#endif

#else

#if defined(CONFIG_USB_PATCH)
extern __u8	 get_vfatname_block[];
#else
extern __u8     get_vfatname_block[];
#endif


#if defined(CONFIG_USB_PATCH)
extern __u8 get_dentfromdir_block[];
#else
extern __u8 get_dentfromdir_block[];
#endif


#if defined(CONFIG_USB_PATCH)
extern __u8 do_fat_read_block[] ; /* Block buffer */
#else
extern __u8 do_fat_read_block[];
#endif


#endif



#define sys_dcache_flush_and_invalidate_all flush_dcache_all

extern void sys_dcache_hit_writeback_all(void);	
extern void sys_dcache_flush_and_invalidate_all(void);

extern int disk_read (__u32 startblock, __u32 getsize, __u8 * bufptr);
extern __u8 mkcksum(const char *str);

static void uppercase(char *str, int len) 
{ 
        int i; 
 
        for (i = 0; i < len; i++) { 
                TOUPPER(*str); 
                str++; 
        } 
} 

static int disk_write(__u32 startblock, __u32 getsize, __u8 *bufptr) 
{ 
        if (cur_dev == NULL) 
                return -1; 

	sys_dcache_flush_and_invalidate_all();

 
        if (startblock + getsize > total_sector) { 
                printk("error: overflow occurs\n"); 
                return -1; 
        } 
 
        startblock += part_offset; 
 
        if (cur_dev->block_read) { 
                return cur_dev->block_write(cur_dev->dev, startblock, getsize, 
                                           (unsigned long *) bufptr); 
        } 
        return -1; 
		
} 


static char * _strchr(const char * s, int c)
{
    for(; *s != (char) c; ++s)
        if (*s == '\0')
            return NULL;
    return (char *) s;
}
 
/* 
 * Set short name in directory entry 
 */ 
static void set_name(dir_entry *dirent, const char *filename) 
{ 
        char s_name[VFAT_MAXLEN_BYTES]; 
        char *period; 
        int period_location, len, i, ext_num; 
 
        if (filename == NULL) 
                return; 
 
        len = strlen(filename); 
        if (len == 0) 
                return; 
 
        memcpy(s_name, filename, len); 
        uppercase(s_name, len); 
 
        period = _strchr(s_name, '.'); 
        if (period == NULL) { 
                period_location = len; 
                ext_num = 0; 
        } else { 
                period_location = period - s_name; 
                ext_num = len - period_location - 1; 
        } 
 
        /* Pad spaces when the length of file name is shorter than eight */ 
        if (period_location < 8) { 
                memcpy(dirent->name, s_name, period_location); 
                for (i = period_location; i < 8; i++) 
                        dirent->name[i] = ' '; 
        } else if (period_location == 8) { 
                memcpy(dirent->name, s_name, period_location); 
        } else { 
                memcpy(dirent->name, s_name, 6); 
                dirent->name[6] = '~'; 
                dirent->name[7] = '1'; 
        } 
 
        if (ext_num < 3) { 
                memcpy(dirent->ext, s_name + period_location + 1, ext_num); 
                for (i = ext_num; i < 3; i++) 
                        dirent->ext[i] = ' '; 
        } else 
                memcpy(dirent->ext, s_name + period_location + 1, 3); 
 
        FAT_DPRINT("name : %s\n", dirent->name); 
        FAT_DPRINT("ext : %s\n", dirent->ext); 
} 
 
/* 
 * Write fat buffer into block device 
 */ 
static int flush_fat_buffer(fsdata *mydata) 
{ 
        int getsize = FATBUFBLOCKS; 
        __u32 fatlength = mydata->fatlength; 
        __u8 *bufptr = mydata->fatbuf; 
        __u32 startblock = mydata->fatbufnum * FATBUFBLOCKS; 
 
        fatlength *= FS_BLOCK_SIZE; 
        startblock += mydata->fat_sect; 
 
        if (getsize > fatlength) 
                getsize = fatlength; 

	sys_dcache_flush_and_invalidate_all();

        /* Write FAT buf */ 
        if (disk_write(startblock, getsize, bufptr) < 0) { 
                FAT_DPRINT("error: writing FAT blocks\n"); 
                return -1; 
        } 
 
        return 0; 
} 
 
/* 
 * Get the entry at index 'entry' in a FAT (12/16/32) table. 
 * On failure 0x00 is returned. 
 * When bufnum is changed, write back the previous fatbuf to the disk. 
 */ 
static __u32 get_fatent_value(fsdata *mydata, __u32 entry) 
{ 
        __u32 bufnum; 
        __u32 offset; 
        __u32 ret = 0x00; 
      //  __u16 val1, val2; 
 
        switch (mydata->fatsize) { 
        case 32: 
                bufnum = entry / FAT32BUFSIZE; 
                offset = entry - bufnum * FAT32BUFSIZE; 
                break; 
        case 16: 
                bufnum = entry / FAT16BUFSIZE; 
                offset = entry - bufnum * FAT16BUFSIZE; 
                break; 
        case 12: 
                bufnum = entry / FAT12BUFSIZE; 
                offset = entry - bufnum * FAT12BUFSIZE; 
                break; 
 
        default: 
                /* Unsupported FAT size */ 
                return ret; 
        } 
 
        FAT_DPRINT("FAT%d: entry: 0x%04x = %d, offset: 0x%04x = %d\n", 
               mydata->fatsize, entry, entry, offset, offset); 
 
        /* Read a new block of FAT entries into the cache. */ 
        if (bufnum != mydata->fatbufnum) { 
                int getsize = FATBUFSIZE/FS_BLOCK_SIZE; 
                __u8 *bufptr = mydata->fatbuf; 
                __u32 fatlength = mydata->fatlength; 
                __u32 startblock = bufnum * FATBUFBLOCKS; 
 
 
                fatlength *= SECTOR_SIZE; /* We want it in bytes now */ 
                startblock += mydata->fat_sect; /* Offset from start of disk */ 

 
                if (getsize > fatlength) 
                        getsize = fatlength; 
				
                /* Write back the fatbuf to the disk */ 
                if (mydata->fatbufnum != -1) { 
                        if (flush_fat_buffer(mydata) < 0) 
                                return -1; 
                } 
 
                if (disk_read(startblock, getsize, bufptr) < 0) { 
                        FAT_DPRINT("Error reading FAT blocks\n"); 
                        return ret; 
                } 
                mydata->fatbufnum = bufnum; 
        } 
 
        /* Get the actual entry from the table */ 
        switch (mydata->fatsize) { 
        case 32: 
                ret = FAT2CPU32(((__u32 *) mydata->fatbuf)[offset]); 
                break; 
        case 16: 
                ret = FAT2CPU16(((__u16 *) mydata->fatbuf)[offset]); 
                break; 
        case 12: 
		{
               __u32 off16 = (offset*3)/4;
		__u16 val1, val2;
 
                switch (offset & 0x3) { 
                case 0: 
                        ret = FAT2CPU16(((__u16 *) mydata->fatbuf)[off16]); 
                        ret &= 0xfff; 
                        break; 
                case 1: 
                        val1 = FAT2CPU16(((__u16 *)mydata->fatbuf)[off16]); 
                        val1 &= 0xf000; 
                        val2 = FAT2CPU16(((__u16 *)mydata->fatbuf)[off16 + 1]); 
                        val2 &= 0x00ff; 
                        ret = (val2 << 4) | (val1 >> 12); 
                        break; 
                case 2: 
                        val1 = FAT2CPU16(((__u16 *)mydata->fatbuf)[off16]); 
                        val1 &= 0xff00; 
                        val2 = FAT2CPU16(((__u16 *)mydata->fatbuf)[off16 + 1]); 
                        val2 &= 0x000f; 
                        ret = (val2 << 8) | (val1 >> 8); 
                        break; 
                case 3: 
                        ret = FAT2CPU16(((__u16 *)mydata->fatbuf)[off16]); 
                        ret = (ret & 0xfff0) >> 4; 
                        break; 
                default: 
                        break; 
                } 
        	}
                break; 
        } 
        FAT_DPRINT("FAT%d: ret: %08x, entry: %08x, offset: %04x\n", 
               mydata->fatsize, ret, entry, offset); 
 
        return ret; 
} 
 
#ifdef CONFIG_SUPPORT_VFAT 
/* 
 * Set the file name information from 'name' into 'slotptr', 
 */ 
static int str2slot(dir_slot *slotptr, const char *name, int *idx) 
{ 
        int j, end_idx = 0; 
 
        for (j = 0; j <= 8; j += 2) { 
                if (name[*idx] == 0x00) { 
                        slotptr->name0_4[j] = 0; 
                        slotptr->name0_4[j + 1] = 0; 
                        end_idx++; 
                        goto name0_4; 
                } 
                slotptr->name0_4[j] = name[*idx]; 
                (*idx)++; 
                end_idx++; 
        } 
        for (j = 0; j <= 10; j += 2) { 
                if (name[*idx] == 0x00) { 
                        slotptr->name5_10[j] = 0; 
                        slotptr->name5_10[j + 1] = 0; 
                        end_idx++; 
                        goto name5_10; 
                } 
                slotptr->name5_10[j] = name[*idx]; 
                (*idx)++; 
                end_idx++; 
        } 
        for (j = 0; j <= 2; j += 2) { 
                if (name[*idx] == 0x00) { 
                        slotptr->name11_12[j] = 0; 
                        slotptr->name11_12[j + 1] = 0; 
                        end_idx++; 
                        goto name11_12; 
                } 
                slotptr->name11_12[j] = name[*idx]; 
                (*idx)++; 
                end_idx++; 
        } 
 
        if (name[*idx] == 0x00) 
                return 1; 
 
        return 0; 
/* Not used characters are filled with 0xff 0xff */ 
name0_4: 
        for (; end_idx < 5; end_idx++) { 
                slotptr->name0_4[end_idx * 2] = 0xff; 
                slotptr->name0_4[end_idx * 2 + 1] = 0xff; 
        } 
        end_idx = 5; 
name5_10: 
        end_idx -= 5; 
        for (; end_idx < 6; end_idx++) { 
                slotptr->name5_10[end_idx * 2] = 0xff; 
                slotptr->name5_10[end_idx * 2 + 1] = 0xff; 
        } 
        end_idx = 11; 
name11_12: 
        end_idx -= 11; 
        for (; end_idx < 2; end_idx++) { 
                slotptr->name11_12[end_idx * 2] = 0xff; 
                slotptr->name11_12[end_idx * 2 + 1] = 0xff; 
        } 
 
        return 1; 
} 
 
static int is_next_clust(fsdata *mydata, dir_entry *dentptr); 
static void flush_dir_table(fsdata *mydata, dir_entry **dentptr); 
 
/* 
 * Fill dir_slot entries with appropriate name, id, and attr 
 * The real directory entry is returned by 'dentptr' 
 */ 
static void 
fill_dir_slot(fsdata *mydata, dir_entry **dentptr, const char *l_name) 
{ 
        dir_slot *slotptr = (dir_slot *)get_vfatname_block; 
        __u8 counter = 0, checksum = 0; 
        int idx = 0, ret = 0; 
        char s_name[16]; 
 
        /* Get short file name and checksum value */ 
        memcpy(s_name, (*dentptr)->name, 16); 
        checksum = mkcksum(s_name); 
 
        do { 
                memset(slotptr, 0x00, sizeof(dir_slot)); 
                ret = str2slot(slotptr, l_name, &idx); 
                slotptr->id = ++counter; 
                slotptr->attr = ATTR_VFAT; 
                slotptr->alias_checksum = checksum; 
                slotptr++; 
        } while (ret == 0); 
 
        slotptr--; 
        slotptr->id |= LAST_LONG_ENTRY_MASK; 

	
        while (counter >= 1) { 
                if (is_next_clust(mydata, *dentptr)) { 
                        /* A new cluster is allocated for directory table */ 
                        flush_dir_table(mydata, dentptr); 
                } 

                memcpy(*dentptr, slotptr, sizeof(dir_slot)); 

			
                (*dentptr)++; 
                slotptr--; 
                counter--; 
        } 
 
        if (is_next_clust(mydata, *dentptr)) { 
                /* A new cluster is allocated for directory table */ 
                flush_dir_table(mydata, dentptr); 
        } 
} 
 
static __u32 dir_curclust; 
 
/* 
 * Extract the full long filename starting at 'retdent' (which is really 
 * a slot) into 'l_name'. If successful also copy the real directory entry 
 * into 'retdent' 
 * If additional adjacent cluster for directory entries is read into memory, 
 * then 'get_vfatname_block' is copied into 'get_dentfromdir_block' and 
 * the location of the real directory entry is returned by 'retdent' 
 * Return 0 on success, -1 otherwise. 
 */ 
static int 
get_long_file_name(fsdata *mydata, int curclust, __u8 *cluster, 
              dir_entry **retdent, char *l_name) 
{ 
        dir_entry *realdent; 
        dir_slot *slotptr = (dir_slot *)(*retdent); 
        dir_slot *slotptr2 = NULL; 
        __u8 *nextclust = cluster + FS_BLOCK_SIZE * mydata->clust_size; 

														
        __u8 counter = (slotptr->id & ~LAST_LONG_ENTRY_MASK) & 0xff; 
        int idx = 0, cur_position = 0; 

#if 0 
        if (counter > VFAT_MAXSEQ) { 
                FAT_DPRINT("Error: VFAT name is too long\n"); 
                return -1; 
        } 
 #endif

 
        while ((__u8 *)slotptr < nextclust) { 
                if (counter == 0) 
                        break; 
                if (((slotptr->id & ~LAST_LONG_ENTRY_MASK) & 0xff) != counter) 
                        return -1; 
                slotptr++; 
                counter--; 
        } 
 
        if ((__u8 *)slotptr >= nextclust) { 
                if (curclust == 0) 
                        return -1; 

			slotptr--;
                curclust = get_fatent_value(mydata, dir_curclust); 

		if (curclust <= 0x0001 || curclust >= 0xfff0) {
			FAT_DPRINT("curclust: 0x%x\n", curclust);
			FAT_ERROR("Invalid FAT entry\n");
			return -1;
		}

		#if 0
                if (CHECK_CLUST(curclust, mydata->fatsize)) { 
                        FAT_DPRINT("curclust: 0x%x\n", curclust); 
                        printk("Invalid FAT entry\n"); 
                        return -1; 
                } 
 		#endif
		
                dir_curclust = curclust; 
 
                if (get_cluster(mydata, curclust, get_vfatname_block, 
                                mydata->clust_size * SECTOR_SIZE) != 0) { 
                        FAT_DPRINT("Error: reading directory block\n"); 
                        return -1; 
                } 
 
                slotptr2 = (dir_slot *)get_vfatname_block; 
                while (slotptr2->id > 0x01) { 
				#if 0
                        if (((slotptr2->id & ~LAST_LONG_ENTRY_MASK) 
                            & 0xff) != counter) 
                                return -1; 
				#endif
                        slotptr2++;
				#if 0
                        counter--;
				#endif
                } 
 
                /* Save the real directory entry */ 
                realdent = (dir_entry *)slotptr2 + 1; 
                while ((__u8 *)slotptr2 >= get_vfatname_block) { 
                        
                        slot2str(slotptr2, l_name, &idx); 
			   slotptr2--; 
                } 
        } else { 
                /* Save the real directory entry */ 
                realdent = (dir_entry *)slotptr; 
        } 
 
        do { 
                slotptr--; 
                if (slot2str(slotptr, l_name, &idx)) 
                        break; 
        } while (!(slotptr->id & LAST_LONG_ENTRY_MASK)); 
 
        l_name[idx] = '\0'; 
        if (*l_name == DELETED_FLAG) 
                *l_name = '\0'; 
        else if (*l_name == aRING) 
                *l_name = '?'; 
        downcase(l_name); 
 
        /* Return the real directory entry */ 
        *retdent = realdent; 
 
        if (slotptr2) { 
                memcpy(get_dentfromdir_block, get_vfatname_block, 
                        mydata->clust_size * FS_BLOCK_SIZE); 
                cur_position = (__u8 *)realdent - get_vfatname_block; 
                *retdent = (dir_entry *) &get_dentfromdir_block[cur_position]; 
        } 
 
        return 0; 
} 
 
#endif 
 
/* 
 * Set the entry at index 'entry' in a FAT (16/32) table. 
 */ 
static int set_fatent_value(fsdata *mydata, __u32 entry, __u32 entry_value) 
{ 
        __u32 bufnum, offset; 
 
        switch (mydata->fatsize) { 
        case 32: 
                bufnum = entry / FAT32BUFSIZE; 
                offset = entry - bufnum * FAT32BUFSIZE; 
                break; 
        case 16: 
                bufnum = entry / FAT16BUFSIZE; 
                offset = entry - bufnum * FAT16BUFSIZE; 
                break; 
        default: 
                /* Unsupported FAT size */ 
                return -1; 
        } 
 
        /* Read a new block of FAT entries into the cache. */ 
        if (bufnum != mydata->fatbufnum) { 
                int getsize = FATBUFSIZE/FS_BLOCK_SIZE; 
                __u8 *bufptr = mydata->fatbuf; 
                __u32 fatlength = mydata->fatlength; 
                __u32 startblock = bufnum * FATBUFBLOCKS; 
 
                fatlength *= SECTOR_SIZE; 
                startblock += mydata->fat_sect; 
 
                if (getsize > fatlength) 
                        getsize = fatlength; 
 
                if (mydata->fatbufnum != -1) { 
                        if (flush_fat_buffer(mydata) < 0) 
                                return -1; 
                } 
 
                if (disk_read(startblock, getsize, bufptr) < 0) { 
                        FAT_DPRINT("Error reading FAT blocks\n"); 
                        return -1; 
                } 
                mydata->fatbufnum = bufnum; 
        } 
 
        /* Set the actual entry */ 
        switch (mydata->fatsize) { 
        case 32: 
                ((__u32 *) mydata->fatbuf)[offset] = cpu_to_le32(entry_value); 
                break; 
        case 16: 
                ((__u16 *) mydata->fatbuf)[offset] = cpu_to_le16(entry_value); 
                break; 
        default: 
                return -1; 
        } 
 
        return 0; 
} 
 
/* 
 * Determine the entry value at index 'entry' in a FAT (16/32) table 
 */ 
static __u32 determine_fatent(fsdata *mydata, __u32 entry) 
{ 
        __u32 next_fat, next_entry = entry + 1; 
 
        while (1) { 
                next_fat = get_fatent_value(mydata, next_entry); 
                if (next_fat == 0) { 
                        set_fatent_value(mydata, entry, next_entry); 
                        break; 
                } 
                next_entry++; 
        } 
        FAT_DPRINT("FAT%d: entry: %08x, entry_value: %04x\n", 
               mydata->fatsize, entry, next_entry); 
 
        return next_entry; 
} 
 
/* 
 * Write at most 'size' bytes from 'buffer' into the specified cluster. 
 * Return 0 on success, -1 otherwise. 
 */ 
static int 
set_cluster(fsdata *mydata, __u32 clustnum, __u8 *buffer, 
             unsigned long size) 
{ 
        int idx = 0; 
        __u32 startsect; 
 
        if (clustnum > 0) 
                startsect = mydata->data_begin + 
                                clustnum * mydata->clust_size; 
        else 
                startsect = mydata->rootdir_sect; 
 
       FAT_DPRINT("begin: %x clustnum: %d, startsect: %d  clust_size=%d\n",mydata->data_begin,clustnum, startsect,mydata->clust_size); 

//	printk("set_size=%d\n",mydata->sect_size);
//	printk("write size=%x\n",size);

	


        if (disk_write(startsect, size / FS_BLOCK_SIZE, buffer) < 0) { 
                FAT_DPRINT("Error writing data\n"); 
                return -1; 
        } 

        if (size % FS_BLOCK_SIZE) { 
                __u8 tmpbuf[FS_BLOCK_SIZE]; 
		  __u8 *ptr;
		  
		  ptr = (__u8*) KSEG1ADDR((unsigned int)tmpbuf);
		  
	//	p_qtd = (struct ehci_qtd *) KSEG1ADDR((unsigned long)tmpbuf);				
 
                idx = size / FS_BLOCK_SIZE; 
                buffer += idx * FS_BLOCK_SIZE; 
                memcpy(ptr, buffer, size % FS_BLOCK_SIZE); 

		
 
                if (disk_write(startsect + idx, 1, ptr) < 0) { 
                        FAT_DPRINT("Error writing data\n"); 
                        return -1; 
                } 
 
                return 0; 
        } 
 
        return 0; 
} 
 
/* 
 * Find the first empty cluster 
 */ 
static int find_empty_cluster(fsdata *mydata) 
{ 
        __u32 fat_val, entry = 3; 
 
        while (1) { 
                fat_val = get_fatent_value(mydata, entry); 
                if (fat_val == 0) 
                        break; 
                entry++; 
        } 
 
        return entry; 
} 
 
/* 
 * Write directory entries in 'get_dentfromdir_block' to block device 
 */ 
static void flush_dir_table(fsdata *mydata, dir_entry **dentptr) 
{ 
        int dir_newclust = 0; 
 
        if (set_cluster(mydata, dir_curclust, 
                    get_dentfromdir_block, 
                    mydata->clust_size * FS_BLOCK_SIZE) != 0) { 
                printk("error: wrinting directory entry\n"); 
                return; 
        } 
        dir_newclust = find_empty_cluster(mydata); 
        set_fatent_value(mydata, dir_curclust, dir_newclust); 
        if (mydata->fatsize == 32) 
                set_fatent_value(mydata, dir_newclust, 0xffffff8); 
        else if (mydata->fatsize == 16) 
                set_fatent_value(mydata, dir_newclust, 0xfff8); 
 
        dir_curclust = dir_newclust; 
 
        if (flush_fat_buffer(mydata) < 0) 
                return; 
 
        memset(get_dentfromdir_block, 0x00, 
                mydata->clust_size * FS_BLOCK_SIZE); 
 
        *dentptr = (dir_entry *) get_dentfromdir_block; 
} 
 
/* 
 * Set empty cluster from 'entry' to the end of a file 
 */ 
static int clear_fatent(fsdata *mydata, __u32 entry) 
{ 
        __u32 fat_val; 
 
        while (1) { 
                fat_val = get_fatent_value(mydata, entry); 
                if (fat_val != 0) 
                        set_fatent_value(mydata, entry, 0); 
                else 
                        break; 
 
                if (fat_val == 0xfffffff || fat_val == 0xffff) 
                        break; 
 
                entry = fat_val; 
        } 
 
        /* Flush fat buffer */ 
        if (flush_fat_buffer(mydata) < 0) 
                return -1; 
 
        return 0; 
} 
 
/* 
 * Write at most 'maxsize' bytes from 'buffer' into 
 * the file associated with 'dentptr' 
 * Return the number of bytes read or -1 on fatal errors. 
 */ 
static int 
set_contents(fsdata *mydata, dir_entry *dentptr, __u8 *buffer, 
              unsigned long maxsize) 
{ 
        unsigned long filesize = FAT2CPU32(dentptr->size), gotsize = 0; 
        unsigned int bytesperclust = mydata->clust_size * FS_BLOCK_SIZE; 
        __u32 curclust = START(dentptr); 
        __u32 endclust = 0, newclust = 0; 
        unsigned long actsize; 
 
//      printk("Filesize: %d bytes\n", filesize); 
 
        if (maxsize > 0 && filesize > maxsize) 
                filesize = maxsize; 
 
  //      printk("%d bytes\n", filesize); 
//	 printk("bytesperclust = %d\n",bytesperclust);
 
        actsize = bytesperclust; 
        endclust = curclust; 
        do { 
                /* search for consecutive clusters */ 
				
                while (actsize < filesize) { 

				
                        newclust = determine_fatent(mydata, endclust); 
 
                        if ((newclust - 1) != endclust) 
                                goto getit; 

 			#if 0
                        if (CHECK_CLUST(newclust, mydata->fatsize)) { 
                                FAT_DPRINT("curclust: 0x%x\n", newclust); 
                                FAT_DPRINT("Invalid FAT entry\n"); 
                                return gotsize; 
                        } 
			#else
			if (newclust <= 0x0001 || newclust >= 0xffff0000) {
				printk("curclust: 0x%x\n", newclust);
				printk("Invalid FAT entry\n");
				return gotsize;
			}
			#endif
						
                        endclust = newclust; 
                        actsize += bytesperclust; 
                } 
				
                /* actsize >= file size */ 
                actsize -= bytesperclust; 

	//	  printk("actsize=%d\n",actsize);

					
                /* set remaining clusters */ 
                if (set_cluster(mydata, curclust, buffer, (int)actsize) != 0) { 
                        printk("error: writing cluster\n"); 
                        return -1; 
                } 
 
                /* set remaining bytes */ 
                gotsize += (int)actsize; 
                filesize -= actsize; 
                buffer += actsize; 
                actsize = filesize; 

	//	printk("[0]gotsize=%d\n",gotsize);
 
                if (set_cluster(mydata, endclust, buffer, (int)actsize) != 0) { 
                        printk("error: writing cluster\n"); 
                        return -1; 
                } 
                gotsize += actsize; 
 
                /* Mark end of file in FAT */ 
                if (mydata->fatsize == 16) 
                        newclust = 0xffff; 
                else if (mydata->fatsize == 32) 
                        newclust = 0xfffffff; 

               set_fatent_value(mydata, endclust, newclust); 

                return gotsize; 
getit: 
                if (set_cluster(mydata, curclust, buffer, (int)actsize) != 0) { 
                        printk("error: writing cluster\n"); 
                        return -1; 
                } 
                gotsize += (int)actsize; 
                filesize -= actsize; 
                buffer += actsize; 

 		  #if 1
		if (curclust <= 0x0001 || curclust >= 0xfff0) {
			FAT_DPRINT("curclust: 0x%x\n", curclust);
			printk("Invalid FAT entry\n");
			return gotsize;
		}

		  #else
                if (CHECK_CLUST(curclust, mydata->fatsize)) { 
                        FAT_DPRINT("curclust: 0x%x\n", curclust); 
                        FAT_DPRINT("Invalid FAT entry\n"); 
                        return gotsize; 
                } 
		  #endif
                actsize = bytesperclust; 
                curclust = endclust = newclust; 
        } while (1); 


	printk("end write............\n");
		
} 
 
/* 
 * Fill dir_entry 
 */ 
static void fill_dentry(fsdata *mydata, dir_entry *dentptr, 
        const char *filename, __u32 start_cluster, __u32 size, __u8 attr) 
{ 
        if (mydata->fatsize == 32) 
                dentptr->starthi = 
                        cpu_to_le16((start_cluster & 0xffff0000) >> 16); 
        dentptr->start = cpu_to_le16(start_cluster & 0xffff); 
        dentptr->size = cpu_to_le32(size); 
 
        dentptr->attr = attr; 
 
        set_name(dentptr, filename); 
} 
 
/* 
 * Check whether adding a file makes the file system to 
 * exceed the size of the block device 
 * Return -1 when overflow occurs, otherwise return 0 
 */ 
static int check_overflow(fsdata *mydata, __u32 clustnum, unsigned long size) 
{ 
        __u32 startsect, sect_num; 
 
        if (clustnum > 0) { 
                startsect = mydata->data_begin + 
                                clustnum * mydata->clust_size; 
        } else { 
                startsect = mydata->rootdir_sect; 
        } 
 
        sect_num = size / FS_BLOCK_SIZE; 
        if (size % FS_BLOCK_SIZE) 
                sect_num++; 
 
        if (startsect + sect_num > total_sector) 
                return -1; 
 
        return 0; 
} 
 
/* 
 * Check if adding several entries exceed one cluster boundary 
 */ 
static int is_next_clust(fsdata *mydata, dir_entry *dentptr) 
{ 
        int cur_position; 
 
        cur_position = (__u8 *)dentptr - get_dentfromdir_block; 
 
        if (cur_position >= mydata->clust_size * FS_BLOCK_SIZE) 
                return 1; 
        else 
                return 0; 
} 
 
static dir_entry *empty_dentptr; 
/* 
 * Find a directory entry based on filename or start cluster number 
 * If the directory entry is not found, 
 * the new position for writing a directory entry will be returned 
 */ 
static dir_entry *find_directory_entry(fsdata *mydata, int startsect, 
        char *filename, dir_entry *retdent, __u32 start) 
{ 
        __u16 prevcksum = 0xffff; 
        __u32 curclust = (startsect - mydata->data_begin) / mydata->clust_size; 
 
        FAT_DPRINT("get_dentfromdir: %s\n", filename); 
 
        while (1) { 
                dir_entry *dentptr; 
 
                int i; 
 
                if (get_cluster(mydata, curclust, get_dentfromdir_block, 
                            mydata->clust_size * FS_BLOCK_SIZE) != 0) { 
                        printk("Error: reading directory block\n"); 
                        return NULL; 
                } 
 
                dentptr = (dir_entry *)get_dentfromdir_block; 

 
                dir_curclust = curclust; 
 
                for (i = 0; i < DIRENTSPERCLUST; i++) { 
                        char s_name[14], l_name[VFAT_MAXLEN_BYTES]; 

                        l_name[0] = '\0'; 
                        if (dentptr->name[0] == DELETED_FLAG) { 
                                dentptr++; 
                                if (is_next_clust(mydata, dentptr)) 
                                        break; 
                                continue; 
                        } 
                        if ((dentptr->attr & ATTR_VOLUME)) { 
#ifdef CONFIG_SUPPORT_VFAT 
                                if ((dentptr->attr & ATTR_VFAT) && 
                                    (dentptr->name[0] & LAST_LONG_ENTRY_MASK)) { 
                                        prevcksum =  ((dir_slot *)dentptr)->alias_checksum; 
                                        get_long_file_name(mydata, curclust, 
                                                     get_dentfromdir_block, 
                                                     &dentptr, l_name); 
					
                                        FAT_DPRINT("vfatname: |%s|\n", l_name); 
					 //    printk("prevcksum: |%d|\n", prevcksum); 
                                } else 
#endif 
                                { 
                                        /* Volume label or VFAT entry */ 
                                        dentptr++; 
                                        if (is_next_clust(mydata, dentptr)) 
                                                break; 
                                        continue; 
                                } 
                        } 
                        if (dentptr->name[0] == 0) { 
                                FAT_DPRINT("Dentname == NULL - %d\n", i); 
                                empty_dentptr = dentptr; 
                                return NULL; 
                        } 
 
                        get_name(dentptr, s_name); 

			 
                        if (strcmp(filename, s_name) 
                            && strcmp(filename, l_name)) { 
                       
                                FAT_DPRINT("Mismatch: |%s|%s|\n", 
                                        s_name, l_name); 
                                dentptr++; 
                                if (is_next_clust(mydata, dentptr)) 
                                        break; 
                                continue; 
                        } 
 
                        memcpy(retdent, dentptr, sizeof(dir_entry)); 
 
         //               FAT_DPRINT("DentName: %s", s_name); 
          //              FAT_DPRINT(", start: 0x%x", START(dentptr)); 
          //              FAT_DPRINT(", size:  0x%x %s\n", 
         //                     FAT2CPU32(dentptr->size), 
          //                    (dentptr->attr & ATTR_DIR) ? 
            //                  "(DIR)" : ""); 
 
                        return dentptr; 
                } 
 
                curclust = get_fatent_value(mydata, dir_curclust); 
                if ((curclust >= 0xffffff8) || (curclust >= 0xfff8)) { 
                        empty_dentptr = dentptr; 
			   printk("return NULL\n");
                        return NULL; 
                } 

		 #if 0
                if (CHECK_CLUST(curclust, mydata->fatsize)) { 
                        FAT_DPRINT("curclust: 0x%x\n", curclust); 
                        FAT_DPRINT("Invalid FAT entry\n"); 
                        return NULL; 
                } 

		#else
			if (curclust <= 0x0001 || curclust >= 0xfff0) {
			FAT_DPRINT("curclust: 0x%x\n", curclust);
			FAT_ERROR("Invalid FAT entry\n");
			return NULL;
			}
		#endif
				
        } 
 
        return NULL; 
} 
 
static int do_fat_write(const char *filename, void *buffer, 
        unsigned long size) 
{ 
        dir_entry *retdent; 
#if 0
        dir_slot *slotptr;
#endif
        __u32 startsect; 
        __u32 start_cluster; 
        boot_sector bs; 
        volume_info volinfo; 

#if defined(CONFIG_USB_PATCH)
	 static fsdata datablock  __attribute__ ((aligned (512)));
	  fsdata *mydata = (fsdata *) (&datablock);
	 static dir_entry *dentptr;
#else
	 fsdata datablock;
	  fsdata *mydata = (fsdata *) (&datablock);
	  dir_entry *dentptr;
#endif
		

        int cursect; 
        //int root_cluster,
	 int ret = -1, name_len; 
        char l_filename[VFAT_MAXLEN_BYTES]; 

		
        dir_curclust = 0; 


    /* fox for cache invalid */
	sys_dcache_flush_and_invalidate_all();

        if (read_bootsectandvi(&bs, &volinfo, &mydata->fatsize)) { 
                FAT_DPRINT("error: reading boot sector\n"); 
                return -1; 
        } 
 
        total_sector = bs.total_sect; 
        if (total_sector == 0) 
        {
        	printk("total_sector = 0\n");
          //      total_sector = part_size; 
        }
//	printk("write size=%d\n",size);

//	 printk("[debug fat] %d %d %d %d %d %d %d %d\n",bs.root_cluster, bs.fat32_length,mydata->fatsize,bs.reserved,bs.cluster_size, bs.fat32_length,bs.fat_length,bs.fats);

		
 
        //--   root_cluster = bs.root_cluster; // 2
 
        if (mydata->fatsize == 32)  //32
                mydata->fatlength = bs.fat32_length;  //7637
        else 
                mydata->fatlength = bs.fat_length; 
 
        mydata->fat_sect = bs.reserved; 

 	 // find root_dir sector
        cursect = mydata->rootdir_sect 
                = mydata->fat_sect + mydata->fatlength * bs.fats; 
 
     //   FS_BLOCK_SIZE = (bs.sector_size[1] << 8) + bs.sector_size[0]; 


//	printk("@@@@@@@@@@@@@@my sector size=%d\n",(bs.sector_size[1] << 8) + bs.sector_size[0]); 

	 
        mydata->clust_size = bs.cluster_size; 
 
        if (mydata->fatsize == 32) { 
                mydata->data_begin = mydata->rootdir_sect - 
                                        (mydata->clust_size * 2); 
        } else { 
                int rootdir_size; 
 
                rootdir_size = ((bs.dir_entries[1]  * (int)256 + 
                                 bs.dir_entries[0]) * 
                                 sizeof(dir_entry)) / 
                                 SECTOR_SIZE; 
                mydata->data_begin = mydata->rootdir_sect + 
                                        rootdir_size - 
                                        (mydata->clust_size * 2); 
        } 
 
        mydata->fatbufnum = -1; 

#if 0
        mydata->fatbuf = malloc(FATBUFSIZE); 
        if (mydata->fatbuf == NULL) { 
                FAT_DPRINT("Error: allocating memory\n"); 
                return -1; 
        } 
#endif
 
        if (disk_read(cursect, (mydata->clust_size) , do_fat_read_block) < 0) { 
                printk("Error: reading rootdir block\n"); 
                goto exit; 
        } 
        dentptr = (dir_entry *) do_fat_read_block; 

	
 
        name_len = strlen(filename); 
        memcpy(l_filename, filename, name_len); 
	 l_filename[name_len] = 0; /* terminate the string */  	
        downcase(l_filename); 

//	printk("debug filename=%s\n",filename);
//	printk("debug l_filename=%s\n",l_filename);
 
        startsect = mydata->rootdir_sect; 
        retdent = find_directory_entry(mydata, startsect, l_filename, dentptr, 0); 
        if (retdent) { 

                /* Update file size and start_cluster in a directory entry */ 
                retdent->size = cpu_to_le32(size); 
                start_cluster = FAT2CPU16(retdent->start); 
                if (mydata->fatsize == 32) 
                        start_cluster |= 
                                (FAT2CPU16(retdent->starthi) << 16); 
 
                ret = check_overflow(mydata, start_cluster, size); 
                if (ret) { 
                        printk("Error: %ld overflow\n", size); 
                        goto exit; 
                } 
 
                ret = clear_fatent(mydata, start_cluster); 
                if (ret) { 
                        printk("Error: clearing FAT entries\n"); 
                        goto exit; 
                } 

                ret = set_contents(mydata, retdent, buffer, size); 
                if (ret < 0) { 
                        printk("Error: writing contents\n"); 
                        goto exit; 
                } 

//		printk("attempt to write 0x%x bytes\n", ret); 
 
                /* Flush fat buffer */ 
                ret = flush_fat_buffer(mydata); 
                if (ret) { 
                        printk("Error: flush fat buffer\n"); 
                        goto exit; 
                } 
 
                /* Write directory table to device */ 
                ret = set_cluster(mydata, dir_curclust, 
                            get_dentfromdir_block, 
                            mydata->clust_size * FS_BLOCK_SIZE); 
                if (ret) { 
                        printk("Error: wrinting directory entry\n"); 
                        goto exit; 
                } 
        } else { 
#if 0
                slotptr = (dir_slot *)empty_dentptr; 
 #endif
                /* Set short name to set alias checksum field in dir_slot */ 
                set_name(empty_dentptr, filename); 
                fill_dir_slot(mydata, &empty_dentptr, filename); 
		
                ret = start_cluster = find_empty_cluster(mydata); 
                if (ret < 0) { 
                        printk("Error: finding empty cluster\n"); 
                        goto exit; 
                } 
 
                ret = check_overflow(mydata, start_cluster, size); 
                if (ret) { 
                        printk("Error: %ld overflow\n", size); 
                        goto exit; 
                } 
 
                /* Set attribute as archieve for regular file */ 
                fill_dentry(mydata, empty_dentptr, filename, 
                        start_cluster, size, 0x20); 

                ret = set_contents(mydata, empty_dentptr, buffer, size); 
                if (ret < 0) { 
                        printk("Error: writing contents\n"); 
                        goto exit; 
                } 

		 printk("attempt to write 0x%x bytes\n", ret); 

	
                /* Flush fat buffer */ 
                ret = flush_fat_buffer(mydata); 
                if (ret) { 
                        printk("Error: flush fat buffer\n"); 
                        goto exit; 
                } 

                /* Write directory table to device */ 
                ret = set_cluster(mydata, dir_curclust, 
                            get_dentfromdir_block, 
                            mydata->clust_size * FS_BLOCK_SIZE); 
                if (ret) { 
                        printk("Error: writing directory entry\n"); 
                        goto exit; 
                } 
        } 
 
exit:

#if 0
       free(mydata->fatbuf); 
#endif

        return ret; 
} 
 
int file_fat_write(const char *filename, void *buffer, unsigned long maxsize) 
{ 
        printk("writing %s\n", filename); 
        return do_fat_write(filename, buffer, maxsize); 
} 


