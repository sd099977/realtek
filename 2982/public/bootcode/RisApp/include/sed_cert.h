#ifndef __SED_CERT_H__
#define __SED_CERT_H__

int sed_cmd_cert_exchange (uint8 *ibuf, uint8 *obuf);
int sed_cmd_set_cert_enc_key (uint8 *ibuf, uint8 *obuf);
int sed_cmd_set_cert_dec_key (uint8 *ibuf, uint8 *obuf);

#endif
