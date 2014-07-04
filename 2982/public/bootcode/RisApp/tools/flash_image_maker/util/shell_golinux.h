#ifndef SHELL_GOLINUX_H
#define SHELL_GOLINUX_H


#define UNZIP_ADDRESS       0xa0100000
#define COPY_MERGE_ADDRESS  0xa1000000

typedef struct {
	UINT8	signature[8];
	UINT32	checksum;
	UINT8	version;
	UINT8	reserved[15];
	UINT32	length;
} __attribute__((packed)) fw_desc_table_t;


extern int Lzma_main(char *inAddr, char *outAddr, long length, char *rs, unsigned int *extract_len);


char *shell_golinux();



#endif
