#ifndef __SED_OTP_H__
#define __SED_OTP_H__

int sed_cmd_otp_get_nuid (uint8 *ibuf, uint8 *obuf);
int sed_cmd_otp_set_stbcasn (uint8 *ibuf, uint8 *obuf);
int sed_cmd_otp_get_stbcasn (uint8 *ibuf, uint8 *obuf);
int sed_cmd_otp_set_msid (uint8 *ibuf, uint8 *obuf);
int sed_cmd_otp_get_msid (uint8 *ibuf, uint8 *obuf);
int sed_cmd_otp_dump (uint8 *ibuf, uint8 *obuf);
int sed_cmd_otp_read (uint8 *ibuf, uint8 *obuf);
int sed_cmd_otp_write (uint8 *ibuf, uint8 *obuf);

#endif
