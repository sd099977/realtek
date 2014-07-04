#define MD_MODE_OFFSET 4
#define INPUT_SEL_OFFSET 6
#define PICT_W_SCALE_OFFSET 17
#define H_BLK_OFFSET 21
#define W_BLK_OFFSET 6
#define Y_BLK_OFFSET 20
#define X_BLK_OFFSET 6


#define SEQ2SEQ 0x00
#define SEQ2BLK 0x01
#define BLK2SEQ 0x02
#define LEN_1M  0x00
#define NORMAL_MODE 0x05
#define MD_GO   0x07
#define WIDTH_UNIT 256
#define LEN_1MB 0x100000

typedef struct
{
	UINT32 dwCmd_addr;
	UINT32 dwMD_mode;
	UINT32 dwStr_addr;
	UINT32 dwDest_addr;
	UINT16 wLen;
}MD_PARA;