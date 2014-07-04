#ifndef __SED_RST_H__
#define __SED_RST_H__

void sed_cmd_chip_rst (uint8 *ibuf, uint8 *obuf);
void sed_cmd_chip_rst_post (void);
int sed_cmd_set_config (uint8 *ibuf, uint8 *obuf);
int sed_cmd_get_config (uint8 *ibuf, uint8 *obuf);
// add this function for reset CERT ip only
void sed_cert_reset(void);
// add this for r2r test
void sed_ddr_init(void);

#endif
