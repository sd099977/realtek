#ifndef __SED_CHAR_H__
#define __SED_CHAR_H__

int sed_cmd_char_host_read (uint8 *ibuf, uint8 *obuf);
int sed_cmd_char_host_write (uint8 *ibuf, uint8 *obuf);
int sed_cmd_char_host_read_iter (uint8 *ibuf, uint8 *obuf);
int sed_cmd_char_host_linear (uint8 *ibuf, uint8 *obuf);
int sed_cmd_char_read_infinite (uint8 *ibuf, uint8 *obuf);
int sed_cmd_char_host_cond (uint8 *ibuf, uint8 *obuf);
int sed_cmd_char_get_rand (uint8 *ibuf, uint8 *obuf);
int sed_cmd_char_host_rng (uint8 *ibuf, uint8 *obuf);

#endif
