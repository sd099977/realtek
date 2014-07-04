#include <rtd_types_qc.h>
#include <qc_verify.h>

#define KEYCODE_BS		0x08
#define KEYCODE_TAB		0x09
#define KEYCODE_ESC		0x1B
#define KEYCODE_SP		0x20
#define KEYCODE_CR		0x0D
#define KEYCODE_LF		0x0A
#define MAX_ARGV		20
#define TAB				8

#define U1_RX     0xb8000840
#define U1_TX     0xb8000844
#define U1_MUXPAD 0xb80008FC
#define U1RBR_THR_DLL 0xb801BC00
#define U1IIR_FCR 0xb801BC08
#define U1LCR     0xb801BC0C

#define GetChar()		UartDataRead()
#define PutChar(x)		UartDataWrite(x)
#define GetChar_uart1()	Uart1DataRead()
#define PutChar_uart1(x) Uart1DataWrite(x)
static char*			ArgvArray[MAX_ARGV];

/*-----------------------------------------------
	Lower case string to upper case string
-----------------------------------------------*/

char* StrUpr( char* string )
{
	char*		p ;
	const int	det = 'a' - 'A';

	p = string ;
	while( *p ){
		if( *p >= 'a'  &&  *p <= 'z' ){
			*p -= det ;
		}
		p++ ;
	}
	return string ;
}

/*
---------------------------------------------------------------------------
; void GetLine(char * buffer, const unsigned int size, int EchoFlag)
:   Description:
;	    Input line from stdio
;	    Function not return until a line input complete.
;	    End input line only by <ENTER> key (0x0d)
;   Input:
;	    buffer: pointer to buffer for getline
;	    size  : maximum buffer size
;			EchoFlag: 1: Echo character when get character
;					: 0: No Echo character
;   Output:
;	    buffer: pointer to input data, end by zero character
;	    none
;   Destroy:
---------------------------------------------------------------------------
*/
void GetLine( char * buffer, const unsigned int size, int EchoFlag )
{
	char		ch = 0 ;
	int		c;
	char*		p = buffer ;
	unsigned int	n = 0L ;
	int		i ;

	while( n < size )
	{
		c = GetChar() ;
		
		if( c == -1 )
		{
		    continue;
		}
		ch = c;
		if( ch == KEYCODE_LF )
		{
		    #ifdef USE_LF
		    *--p = 0 ;
		    n-- ;
		    #endif // USE_LF
		    break ;
		}
		else if( ch == KEYCODE_CR )
		{
		    *p = 0 ;
		    n-- ;
		    break ;
		}
		else if( ch == KEYCODE_BS )
		{
		    if( p != buffer )
		    {
			    p-- ;
			    n-- ;
							if(EchoFlag)
							{
								PutChar(KEYCODE_BS);
								PutChar(' ');
								PutChar(KEYCODE_BS);
							}
		    }
		}
		else if( ch == KEYCODE_TAB )
		{				
		    for( i=0 ; i < TAB ; i++ )
		    {
			    *p++ = ' ' ;
			    n++ ;
							if(EchoFlag) PutChar(' ');
		    }
		}
		else
		{
		    *p++ = ch ;
		    n++ ;
					if(EchoFlag) PutChar(ch);
		}
	}
}

/*
---------------------------------------------------------------------------
; int GetArgc(const char* string)
:   Description:
;			Get argument number for a input string
;			Input string separate by space key
;   Input:
;	    string : pointer to buffer
;   Output:
;			argument number
;   Destroy:
---------------------------------------------------------------------------
*/
int GetArgc( const char* string )
{
	int			argc;
	char*		p ;

	argc = 0 ;
	p = (char* )string ;
	while( *p )
	{
		if( *p != ' '  &&  *p )
		{
			argc++ ;
			while( *p != ' '  &&  *p ) p++ ;
			continue ;
		}
		p++ ;
	}
	if (argc >= MAX_ARGV) argc = MAX_ARGV - 1;
	return argc ;
}

/*
---------------------------------------------------------------------------
; int GetArgv(const char* string)
:   Description:
;			Get argument for a input string
;			Input string separate by space key
;   Input:
;	    string : pointer to buffer
;   Output:
;			argument string array, argv[0], argv[1],...
;			argument string end by zero character
;   Destroy:
---------------------------------------------------------------------------
*/
char** GetArgv(const char* string)
{
	char*			p ;
	int				n;

	n = 0 ;
	memset( ArgvArray, 0, MAX_ARGV*sizeof(char *) );
	p = (char* )string ;
	while( *p )
	{
		ArgvArray[n] = p ;
		while( *p != ' '  &&  *p ) p++ ;
		*p++ = '\0';
		while( *p == ' '  &&  *p ) p++ ;
		n++ ;
		if (n == MAX_ARGV) break;
	}
	return (char** )&ArgvArray ;
}

int UART1_to_MAC(UINT8 item, UINT8 branch_num)
{
	UINT32 ch = 0;
	UINT8  flag = 0;
	UINT8  flag_end = 0;

	//input mux & pinshare
	rtd_maskl(U1_RX, 0xffffc1ff, 0x00000400); //RX:[13:9]=0x02
	rtd_maskl(U1_TX, 0x07ffffff, 0x10000000); //RX:[31:27]=0x02
	rtd_maskl(U1_MUXPAD, 0xff8fffff, 0x00000000); //RX:[22:20]=0
	//uart settings
	rtd_outl(U1LCR,0x83);		//Line CTRL: DLAB:1; Word length:8	
	rtd_outl(U1RBR_THR_DLL,0xf0);		//U1RBR_THR_DLL: (DLAB=1) --> Timing Setting(DLL), clock =432MHz
	rtd_outl(U1LCR,0x03);  	//Line CTRL: DLAB:0; DLL --> RX/TX FIFO
	rtd_outl(U1IIR_FCR,0xc6);		//FIFO CTRL: FIFO Reset:FIFO En; receiver line status
	rtd_outl(U1IIR_FCR,0xc1);		//FIFO CTRL: FIFO Enable:FIFO En; no interrupt pending;
	rtd_outl(U1LCR,0x03);		//Line CTRL: DLAB:0; DLL --> RX/TX FIFO
	
	//TEST uart1
	rtd_outl(U1RBR_THR_DLL,KEYCODE_LF); //enter key
	rtd_outl(U1RBR_THR_DLL,KEYCODE_LF); //enter key	
	rtd_outl(U1RBR_THR_DLL,0x71);	//q
	rtd_outl(U1RBR_THR_DLL,0x63);	//c
	rtd_outl(U1RBR_THR_DLL,KEYCODE_LF); //enter key	
	udelay(1000);

	rtd_outl(U1RBR_THR_DLL, (0x30+item)); //item number
	rtd_outl(U1RBR_THR_DLL,KEYCODE_LF); //enter key	

	udelay(1000);	
	rtd_outl(U1RBR_THR_DLL, (0x30+branch_num)); //branch number	
	rtd_outl(U1RBR_THR_DLL,KEYCODE_LF); //enter key	
	
	while(TRUE)
	{
		ch = GetChar_uart1();
		PutChar(ch);

		//fail check	
		if (ch == 0x52) //R
			flag = 1;
		else if ((flag == 1) && (ch == 0x58)) //X
			flag = 2;
		else if ((flag == 2) && (ch == 0x5F)) //_
			flag = 3;
		else if ((flag == 3) && (ch == 0x46)) //F
			flag = 4;
		else if ((flag == 4) && (ch == 0x41)) //A
			flag = 5;
		else if ((flag == 5) && (ch == 0x49)) //I
			flag = 6;
		else if ((flag == 6) && (ch == 0x4C)) //L
			flag = 7;
		else if (flag != 7)
			flag = 0;					

		//test finish
		if (ch == 0x3C) //<
			flag_end = 1;
		else if ((flag_end == 1) && (ch == 0x65)) //e
			flag_end = 2;
		else if ((flag_end == 2) && (ch == 0x6E)) //n
			flag_end = 3;
		else if ((flag_end == 3) && (ch == 0x64)) //d
			flag_end = 4;		
		else if ((flag_end == 4) && (ch == 0x3E)) //>
			flag_end = 5;		
		else if (flag_end != 5)
			flag_end = 0;

		if (flag_end == 5)
		{				
			rtd_outl(U1RBR_THR_DLL,0x36); //6
			rtd_outl(U1RBR_THR_DLL,KEYCODE_LF); //enter key
			udelay(1000);	
			
			if (flag == 7)  
				return FAILED;		 
			else 
				return SUCCESS; 
			break;
		}			
	}
}