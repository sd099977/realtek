/************************************************************************
 *  Include files
 ************************************************************************/
#include <common.h>
#include <environment.h>
#include <platform_lib/board/pcb_mgr.h>

/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  Static function prototypes
 ************************************************************************/

/************************************************************************
 *  Implementation : Static functions
 ************************************************************************/

/************************************************************************
 *
 *                          env_setup_env_pcb
 *  Description :
 *  -------------
 *
 *  Create pcb specific system environment variables
 *
 *  Return values :
 *  ---------------
 *
 *  TRUE -> OK, else FALSE
 *
 ************************************************************************/
unsigned int env_setup_env_pcb(void)
{
	#define PCB_PARAMETER_MAX_LEVEL 32

	char raw0[101]={0}, tmp[20];
	char buffer_area[(SYS_USER_ENVIRONMENT_MAX_INDEX + 2) * 100];	// max 99 env items (each data has 100 bytes)
	char *raw, *buffer;
	unsigned int rc = 1;
	int buffer_len, para_no=0;
	int i = 0;
	int clear_env_num = 0;

	buffer = buffer_area;
	pcb_gen_kernel_cmd_line(buffer, NULL);

	buffer_len = strlen(buffer);

	while(buffer_len > 0) {

		strncpy(raw0, buffer, (buffer_len > 100) ? 100 : buffer_len);
		raw0[(buffer_len > 100) ? 100 : buffer_len]='\0';
		buffer += 100;
		buffer_len -=100;
		para_no++;

		sprintf(tmp, "pcb_parameter_%d", para_no);

		/* pcb_parameter */
		//if(!env_get( tmp, &raw, NULL, 0 ) )
		raw = raw0 ; /* Create new */

		// printf("%s \n", raw0);

		if(setenv(tmp, raw)) {
			printf("%s ERROR at setenv()\n", __func__);
			rc = 0;
			break;
		}

	}

	if (para_no > PCB_PARAMETER_MAX_LEVEL)
	{
		printf("[WARN] para_no is %d > %d. Clear more pcb_parameter env.\n", para_no, PCB_PARAMETER_MAX_LEVEL);

		clear_env_num = PCB_PARAMETER_MAX_LEVEL * 2;
	}
	else
	{
		clear_env_num = PCB_PARAMETER_MAX_LEVEL;
	}

	para_no++; /* clear the pcb_parameter_xxx env after para_no */

	for(i = para_no;i <= clear_env_num;i++)
	{
		sprintf(tmp, "pcb_parameter_%d", i);

		setenv(tmp, NULL);
	}

	return rc;
}

