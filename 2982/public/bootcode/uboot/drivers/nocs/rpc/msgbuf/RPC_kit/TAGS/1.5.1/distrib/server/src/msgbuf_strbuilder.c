/**
 * File: $Id:$
 *
 *  This file implements string builder_utilily functions.
 *
 *  Copyright (c) 2013 Nagravision. All rights reserved.
 *  CH-1033 Cheseaux, Switzerland
 *  Tel: +41 21 7320311  Fax: +41 21 7320100
 *  http://www.nagra.com
 *
 *  All trademarks and registered trademarks are the property of their respective
 *  owners.
 *
 *  This document is supplied with an understanding that the notice(s) herein or
 *  any other contractual agreement(s) made that instigated the delivery of a
 *  hard copy, electronic copy, facsimile or file transfer of this document are
 *  strictly observed and maintained.
 *
 *  The information contained in this document is subject to change without notice.
 *
 *  Security Policy of Nagravision Kudelski Group
 *  Any recipient of this document, without exception, is subject to a
 *  Non-Disclosure Agreement (NDA) and access authorization.
 **/


/***************************************************************************/
/*                                                                         */
/*                               INCLUDE FILES                             */
/*                                                                         */
/***************************************************************************/

#include "inc/msgbuf_strbuilder.h"
#include "inc/msgbuf_sys_malloc.h"
#include "inc/msgbuf_sys_string.h"


/* If not specified at compilation time, fix the maximum number of bytes
 * to be reported for a buffer to a default value. */

#if !defined (NHT_TRACE_BUFFER_MAX_LEN)
#define NHT_TRACE_BUFFER_MAX_LEN 256
#endif

#define _NHT_TRACE_BUFFER_MAX_LEN_ ((NHT_TRACE_BUFFER_MAX_LEN + 15) & ~0x0F)


static const char gPrintoutChar[] =
{
  '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056',  /* 0x00-0x0F */
  '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056',  /* 0x10-0x1F */
  '\040', '\041', '\042', '\043', '\044', '\045', '\046', '\047', '\050', '\051', '\052', '\053', '\054', '\056', '\056', '\057',  /* 0x20-0x2F */
  '\060', '\061', '\062', '\063', '\064', '\065', '\066', '\067', '\070', '\071', '\072', '\073', '\074', '\075', '\076', '\077',  /* 0x30-0x3F */
  '\100', '\101', '\102', '\103', '\104', '\105', '\106', '\107', '\110', '\111', '\112', '\113', '\114', '\115', '\116', '\117',  /* 0x40-0x4F */
  '\120', '\121', '\122', '\123', '\124', '\125', '\126', '\127', '\130', '\131', '\132', '\133', '\134', '\135', '\136', '\137',  /* 0x50-0x5F */
  '\140', '\141', '\142', '\143', '\144', '\145', '\146', '\147', '\150', '\151', '\152', '\153', '\154', '\155', '\156', '\157',  /* 0x60-0x6F */
  '\160', '\161', '\162', '\163', '\164', '\165', '\166', '\167', '\170', '\171', '\172', '\173', '\174', '\175', '\176', '\056',  /* 0x70-0x7F */
  '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056',  /* 0x80-0x8F */
  '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056',  /* 0x90-0x9F */
  '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056',  /* 0xA0-0xAF */
  '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056',  /* 0xB0-0xBF */
  '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056',  /* 0xC0-0xCF */
  '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056',  /* 0xD0-0xDF */
  '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056',  /* 0xE0-0xEF */
  '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056', '\056'   /* 0xF0-0xFF */
};

#if 0

  '\200', '\056', '\222', '\203', '\204', '\205', '\206', '\207', '\210', '\211', '\212', '\213', '\214', '\056', '\216', '\056',  /* 0x80-0x8F */
  '\056', '\221', '\222', '\223', '\224', '\225', '\226', '\227', '\230', '\231', '\232', '\233', '\234', '\056', '\236', '\237',  /* 0x90-0x9F */
  '\056', '\241', '\242', '\243', '\244', '\245', '\246', '\247', '\250', '\251', '\252', '\253', '\254', '\056', '\256', '\257',  /* 0xA0-0xAF */
  '\260', '\261', '\262', '\263', '\264', '\265', '\266', '\267', '\270', '\271', '\272', '\273', '\274', '\275', '\276', '\277',  /* 0xB0-0xBF */
  '\260', '\261', '\262', '\263', '\264', '\265', '\266', '\267', '\270', '\271', '\272', '\273', '\274', '\275', '\276', '\277',  /* 0xB0-0xBF */
  '\300', '\301', '\302', '\303', '\304', '\305', '\306', '\307', '\310', '\311', '\312', '\313', '\314', '\315', '\316', '\317',  /* 0xC0-0xCF */
  '\320', '\321', '\322', '\323', '\324', '\325', '\326', '\327', '\330', '\331', '\332', '\333', '\334', '\335', '\336', '\337',  /* 0xD0-0xDF */
  '\340', '\341', '\342', '\343', '\344', '\345', '\346', '\347', '\350', '\351', '\352', '\353', '\354', '\355', '\356', '\357',  /* 0xE0-0xEF */
  '\360', '\361', '\362', '\363', '\364', '\365', '\366', '\367', '\370', '\371', '\372', '\373', '\374', '\375', '\376', '\377'   /* 0xF0-0xFF */
};

#endif

/***************************************************************************/
/*                                                                         */
/*                   Function implementation                               */
/*                                                                         */
/***************************************************************************/


/* */
void msgbuf_strbuilder_buffer_init
(
  TMsgbufStrBuffer * pxNhtStrBuffer
)
{
  /* char tmpStr[2]; */
  /* *int  i; */

  pxNhtStrBuffer->pBuffer    = NULL;
  pxNhtStrBuffer->bufferSize = 0;
  pxNhtStrBuffer->curSize    = 0;

#if 0
  tmpStr[1]=0;
  for (i=0; i < 256; i++)
  {
    if (i%16 == 0) printf ("\n");
    tmpStr[0] = gPrintoutChar[i];
    printf ("%s", tmpStr);
  }
  printf ("\n");

#endif
}


/* */
void msgbuf_strbuilder_buffer_terminate
(
  TMsgbufStrBuffer * pxNhtStrBuffer
)
{
  if (pxNhtStrBuffer->pBuffer)
    MSGBUF_SYS_free (pxNhtStrBuffer->pBuffer);

  msgbuf_strbuilder_buffer_init (pxNhtStrBuffer);
}


/* */
void msgbuf_strbuilder_buffer_empty
(
  TMsgbufStrBuffer * pxNhtStrBuffer
)
{
  pxNhtStrBuffer->curSize = 0;
}


/* */
int msgbuf_strbuilder_buffer_extSize
(
  TMsgbufStrBuffer * pxNhtStrBuffer,
  int                xExtSize
)
{
  int newSize;

  newSize = pxNhtStrBuffer->curSize + xExtSize;

  if (newSize >= pxNhtStrBuffer->bufferSize)
  {
    char * pNewBuffer = NULL;

    newSize = (newSize/1024 + 1) * 1024;

    pNewBuffer = (char*)MSGBUF_SYS_malloc (newSize);

    if (pxNhtStrBuffer->pBuffer)
    {
      MSGBUF_SYS_strcpy (pNewBuffer, pxNhtStrBuffer->pBuffer);
      MSGBUF_SYS_free (pxNhtStrBuffer->pBuffer);
    }

    pxNhtStrBuffer->pBuffer = pNewBuffer;
    pxNhtStrBuffer->bufferSize = newSize;
  }

  return 0;
}


/* */
void msgbuf_strbuilder_add_string
(
  TMsgbufStrBuffer * pxNhtStrBuffer,
  const char       * pxString
)
{
  int addedLen;

  if (pxString) addedLen = (int)MSGBUF_SYS_strlen (pxString);
  else return;

  msgbuf_strbuilder_buffer_extSize (pxNhtStrBuffer, addedLen);

  MSGBUF_SYS_strcpy (&pxNhtStrBuffer->pBuffer[pxNhtStrBuffer->curSize], pxString);
  pxNhtStrBuffer->curSize += addedLen;
}


/* */
int msgbuf_strbuilder_add_hexchar_value
(
  TMsgbufStrBuffer * pxNhtStrBuffer,
  unsigned char      xByte
)
{
  char subStr[3];
  int  i;

  subStr[2]=0;

  for (i=0; i<2; i++)
  {
    unsigned char digit;

    digit = (xByte >> (4 -(i*4))) & 0x0F;
    if (digit < 10) subStr[i] = '0' + digit;
    else subStr[i] = 'A' + digit - 10;
  }

  msgbuf_strbuilder_add_string (pxNhtStrBuffer, subStr);
  return 0;
}


/* */
void msgbuf_strbuilder_add_buffer_value
(
  TMsgbufStrBuffer * pxNhtStrBuffer,
  const void       * pxLineHeaderStr,
  const void       * pxByteArray,
  int                xSize
)
{
  if (pxByteArray)
  {
    int          counter = 0;
    int          effSize;
    char         tmpStr[2];
    int          i;
    char const * pMyPtr = NULL;

    tmpStr[1] = 0;
    pMyPtr  = (char const *)pxByteArray;

    if (xSize > _NHT_TRACE_BUFFER_MAX_LEN_) effSize = _NHT_TRACE_BUFFER_MAX_LEN_;
    else effSize = xSize;

    if (effSize == 0) return;
    msgbuf_strbuilder_add_string (pxNhtStrBuffer, pxLineHeaderStr);

    while (counter < effSize)
    {
      msgbuf_strbuilder_add_string (pxNhtStrBuffer, " ");
      msgbuf_strbuilder_add_hexchar_value (pxNhtStrBuffer, (unsigned char)*pMyPtr++);
      counter++;

      if ((counter%16) == 0)
      {
        char const * pVal = &pMyPtr[-16];

        msgbuf_strbuilder_add_string (pxNhtStrBuffer, " : ");
        for (i=0; i<16; i++)
        {
          tmpStr[0] = gPrintoutChar[(const unsigned char)*pVal++];
          msgbuf_strbuilder_add_string (pxNhtStrBuffer, tmpStr);
        }

        if (counter < xSize)
        {
          msgbuf_strbuilder_add_string (pxNhtStrBuffer, "\n");
          msgbuf_strbuilder_add_string (pxNhtStrBuffer, pxLineHeaderStr);
        }
      }
    }

    if (counter%16)
    {
      char const * pVal = (char const*)&pMyPtr[-(counter & 0x0F)];

      for (i=counter; (i%16 != 0); i++)
        msgbuf_strbuilder_add_string (pxNhtStrBuffer, "   ");
      msgbuf_strbuilder_add_string (pxNhtStrBuffer, " : ");

      for (i=(counter & ~0x0F); i < counter; i++)
      {
        tmpStr[0] = gPrintoutChar[(const unsigned char)*pVal++];
        msgbuf_strbuilder_add_string (pxNhtStrBuffer, tmpStr);
      }

      if (effSize < xSize)
        msgbuf_strbuilder_add_string (pxNhtStrBuffer, "\n");
    }

    if (effSize < xSize)
      msgbuf_strbuilder_add_string (pxNhtStrBuffer, "...");
  }
}


/* */
void msgbuf_strbuilder_add_uchar
(
  TMsgbufStrBuffer * pxNhtStrBuffer,
  unsigned char      xNumber
)
{
  msgbuf_strbuilder_add_string  (pxNhtStrBuffer, "0x");
  msgbuf_strbuilder_add_hexchar_value (pxNhtStrBuffer, xNumber);
}


/* */
void msgbuf_strbuilder_add_hex_value
(
  TMsgbufStrBuffer * pxNhtStrBuffer,
  size_t             xNumber,
  size_t             xNumberSize
)
{
  int i;
  int shift = ((int)xNumberSize - 1) * 8;

  msgbuf_strbuilder_add_string (pxNhtStrBuffer, "0x");

  for (i=0; i < (int)xNumberSize; i++)
  {
    unsigned char digit;

    digit = (unsigned char)(xNumber >> shift);
    msgbuf_strbuilder_add_hexchar_value (pxNhtStrBuffer, digit);
    shift -= 8;
  }
}


/* */
void msgbuf_strbuilder_add_dec_value
(
  TMsgbufStrBuffer * pxNhtStrBuffer,
  size_t             xNumber
)
{
  size_t absValue;
  size_t tmpValue;
  size_t div = 1;
  char   decChar[2];

  if (xNumber < 0)
  {
    msgbuf_strbuilder_add_string (pxNhtStrBuffer, "-");
    absValue = -xNumber;
  }
  else absValue = xNumber;

  if (absValue == 0)
  {
    msgbuf_strbuilder_add_string (pxNhtStrBuffer, "0");
    return;
  }

  tmpValue = absValue;
  while ((tmpValue / 10) > 0)
  {
    tmpValue /= 10;
    div *= 10;
  }

  tmpValue = absValue;
  decChar[1] = 0;
  while (div)
  {
    decChar[0] = (char)(tmpValue / div) + '0';
    msgbuf_strbuilder_add_string (pxNhtStrBuffer, decChar);
    tmpValue %= div;
    div /= 10;
  }
}


/* */
void msgbuf_strbuilder_add_pointer
(
  TMsgbufStrBuffer * pxNhtStrBuffer,
  const void       * pxPointer
)
{
  if (pxPointer == NULL)
  {
    msgbuf_strbuilder_add_string (pxNhtStrBuffer, "<NULL>");
  }
  else
  {
    msgbuf_strbuilder_add_hex_value (pxNhtStrBuffer, (size_t)pxPointer, sizeof(void*));
  }
}


/* */
void msgbuf_strbuilder_setparam_buffer
(
  TMsgbufStrBuffer * pxNhtStrBuffer,
  const char       * pxParamName,
  const void       * pxByteArray,
  int                xSize
)
{
  msgbuf_strbuilder_add_string  (pxNhtStrBuffer, "  ");
  msgbuf_strbuilder_add_string  (pxNhtStrBuffer, pxParamName);
  msgbuf_strbuilder_add_string  (pxNhtStrBuffer, " (buffer ptr=");
  msgbuf_strbuilder_add_pointer (pxNhtStrBuffer, (void*)pxByteArray);

  if (pxByteArray == NULL)
  {
    msgbuf_strbuilder_add_string (pxNhtStrBuffer, ")");
  }
  else
  {
    msgbuf_strbuilder_add_string       (pxNhtStrBuffer, ", size=");
    msgbuf_strbuilder_add_hex_value    (pxNhtStrBuffer, (int)xSize, sizeof(int));

    if (xSize > 0)
    {
      msgbuf_strbuilder_add_string       (pxNhtStrBuffer, ") =\n");
      msgbuf_strbuilder_add_buffer_value (pxNhtStrBuffer, "   ", pxByteArray, xSize);
    }
    else msgbuf_strbuilder_add_string       (pxNhtStrBuffer, ")");
  }
}


/* */
void msgbuf_strbuilder_setparam_string
(
  TMsgbufStrBuffer * pxNhtStrBuffer,
  const char       * pxParamName,
  const char       * pxString
)
{
  msgbuf_strbuilder_add_string  (pxNhtStrBuffer, "  ");
  msgbuf_strbuilder_add_string  (pxNhtStrBuffer, pxParamName);
  msgbuf_strbuilder_add_string  (pxNhtStrBuffer, " (string ptr=");
  msgbuf_strbuilder_add_pointer (pxNhtStrBuffer, (void*)pxString);

  if (pxString == NULL)
  {
    msgbuf_strbuilder_add_string  (pxNhtStrBuffer, ")");
  }
  else
  {
    int strSize = (int)MSGBUF_SYS_strlen(pxString);

    msgbuf_strbuilder_add_string  (pxNhtStrBuffer, ", size=");
    msgbuf_strbuilder_add_hex_value (pxNhtStrBuffer, strSize, sizeof(int));
    if (strSize > 0)
    {
      msgbuf_strbuilder_add_string  (pxNhtStrBuffer, ") =\n    ");
      msgbuf_strbuilder_add_string  (pxNhtStrBuffer, pxString);
    }
    else msgbuf_strbuilder_add_string  (pxNhtStrBuffer, ")");
  }
}


/* */
void msgbuf_strbuilder_setparam_uchar
(
  TMsgbufStrBuffer * pxNhtStrBuffer,
  const char       * pxParamName,
  unsigned char      xNumber
)
{
  msgbuf_strbuilder_add_string        (pxNhtStrBuffer, "  ");
  msgbuf_strbuilder_add_string        (pxNhtStrBuffer, pxParamName);
  msgbuf_strbuilder_add_string        (pxNhtStrBuffer, " = ");
  msgbuf_strbuilder_add_hexchar_value (pxNhtStrBuffer, xNumber);
  msgbuf_strbuilder_add_string        (pxNhtStrBuffer, " (");
  msgbuf_strbuilder_add_dec_value     (pxNhtStrBuffer, (size_t)xNumber);
  msgbuf_strbuilder_add_string        (pxNhtStrBuffer, ")");
}


/* */
void msgbuf_strbuilder_setparam_pointer
(
  TMsgbufStrBuffer * pxNhtStrBuffer,
  const char       * pxParamName,
  const void       * pxPointer
)
{
  msgbuf_strbuilder_add_string  (pxNhtStrBuffer, "  ");
  msgbuf_strbuilder_add_string  (pxNhtStrBuffer, pxParamName);
  msgbuf_strbuilder_add_string  (pxNhtStrBuffer, " (ptr=");
  msgbuf_strbuilder_add_pointer (pxNhtStrBuffer, pxPointer);
  msgbuf_strbuilder_add_string  (pxNhtStrBuffer, ")");
}


/* */
void msgbuf_strbuilder_setparam_hex_value
(
  TMsgbufStrBuffer * pxNhtStrBuffer,
  const char       * pxParamName,
  size_t             xNumber,
  size_t             xNumberSize
)
{
  msgbuf_strbuilder_add_string    (pxNhtStrBuffer, "  ");
  msgbuf_strbuilder_add_string    (pxNhtStrBuffer, pxParamName);
  msgbuf_strbuilder_add_string    (pxNhtStrBuffer, " = ");
  msgbuf_strbuilder_add_hex_value (pxNhtStrBuffer, xNumber, xNumberSize);
  msgbuf_strbuilder_add_string    (pxNhtStrBuffer, " (");
  msgbuf_strbuilder_add_dec_value (pxNhtStrBuffer, (size_t)xNumber);
  msgbuf_strbuilder_add_string    (pxNhtStrBuffer, ")");
}
