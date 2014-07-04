#ifndef _ROM_SYMBOL_H_
#define _ROM_SYMBOL_H_

#define ROM__D__UartReg		0x90000000
#define ROM__b__emmc_card		0x90000008
#define ROM__B__sys_flash_current_pos		0x9000007c
#define ROM__B__sys_errno		0x90000080
#define ROM__B__sys_boot_flash_type		0x90000084
#define ROM__B__g_Aux_Code_Tail		0x90000088
#define ROM__B__g_NOCS_Certificate		0x9000019c
#define ROM__B__g_Params_Area		0x900003b8
#define ROM__B__g_SEC_FW_NOCS_Certificate		0x9000050c
#define ROM__B__s_PageSize		0x90000720
#define ROM__B__s_BlockSize		0x90000724
#define ROM__B__s_PagePerBlock		0x90000728
#define ROM__B__s_FlashID4Bytes		0x9000072c
#define ROM__B__alloc_count		0xb8079000
#define ROM__b__memory_pool		0xb8079004
#define ROM__b__alloc_current		0xb807a404
#define ROM__B__mcp_hash_result		0xb807a408
#define ROM__B__mcp_tmp_buffer		0xb807a428
#define ROM__b__mcp_dscpt		0xb807a448
#define ROM__T____reset_vector		0xbfc00000
#define ROM__T__func_nop		0xbfc00460
#define ROM__T__print_str		0xbfc00470
#define ROM__T__copy_data		0xbfc00508
#define ROM__T__clear_memory		0xbfc00558
#define ROM__T__sys_dcache_flush_all		0xbfc00574
#define ROM__T__enable_uart_tx		0xbfc005a8
#define ROM__T__go_acpu_for_recovery_mode		0xbfc005e4
#define ROM__T__empty		0xbfc0066d
#define ROM__T__my_malloc		0xbfc00671
#define ROM__T__my_free		0xbfc006c1
#define ROM__T__my_freeAll		0xbfc006e9
#define ROM__T__strlen		0xbfc00705
#define ROM__T__set_memory		0xbfc00719
#define ROM__T__RSA_prints		0xbfc0075d
#define ROM__T__RSA_print_hex		0xbfc007ad
#define ROM__T__get_RSA_memory_pool		0xbfc007fd
#define ROM__T__skip_pkcs_v1_5_padding		0xbfc00809
#define ROM__T__do_RSA		0xbfc009a9
#define ROM__T__Cmp		0xbfc00a65
#define ROM__T__isZero		0xbfc00ab9
#define ROM__T__Sub_p		0xbfc00acd
#define ROM__T__Add_p		0xbfc00b4d
#define ROM__T__Mul_p		0xbfc00b75
#define ROM__T__Div_p		0xbfc00bdc
#define ROM__T__Mod_p		0xbfc00dbc
#define ROM__T__OutPutToAddr		0xbfc00ead
#define ROM__T__BI_setbit		0xbfc00f09
#define ROM__T__BI_chkmsbbit		0xbfc00f21
#define ROM__T__BI_is_bit_set		0xbfc00f7d
#define ROM__T__Sub		0xbfc00fa1
#define ROM__T__Add		0xbfc0109d
#define ROM__T__init		0xbfc01121
#define ROM__T__InPutFromAddr		0xbfc0114d
#define ROM__T__Mul		0xbfc011c1
#define ROM__T__move_p		0xbfc01301
#define ROM__T__Mod		0xbfc01338
#define ROM__T__Div		0xbfc01580
#define ROM__T__move		0xbfc0180d
#define ROM__T__Exp_Mod		0xbfc01839
#define ROM__T__RCP_WRITE_SRAM		0xbfc018c5
#define ROM__T__RCP_SET_CW		0xbfc018ed
#define ROM__T__check_key_already_in_cw		0xbfc01955
#define ROM__t__do_k_mcp		0xbfc01979
#define ROM__T__AES_decrypt_key_in_CW		0xbfc01a39
#define ROM__T__SHA256_hash		0xbfc01aed
#define ROM__T__AES_ECB_decrypt		0xbfc01cd1
#define ROM__T__AES_CBC_decrypt		0xbfc01d75
#define ROM__T__do_kcpu_bisr		0xbfc01e18
#define ROM__T__do_acpu_bisr		0xbfc01efc
#define ROM__T__st_enable_clock		0xbfc01fd8
#define ROM__T__enable_PLL		0xbfc02050
#define ROM__T__init_crt		0xbfc020bc
#define ROM__T__do_cp42k_bisr		0xbfc02281
#define ROM__T__mmccr_print_buffer		0xbfc02355
#define ROM__t__mmccr_read_rsp		0xbfc02359
#define ROM__T__mmc_get_rsp_len		0xbfc0245d
#define ROM__T__mmc_get_rsp_type		0xbfc02479
#define ROM__T__endian_chg		0xbfc02519
#define ROM__t__mmccr_reset_cr_state		0xbfc0256d
#define ROM__t__mmccr_TriggerXferCmd		0xbfc025c9
#define ROM__t__mmccr_SendCmd		0xbfc02641
#define ROM__t__mmccr_Stream_Cmd		0xbfc026d5
#define ROM__t__mmc_read_ext_csd		0xbfc0287d
#define ROM__T__init_emmc		0xbfc0292d
#define ROM__T__mmc_select_part		0xbfc02b2d
#define ROM__T__mmc_blk_read		0xbfc02ba9
#define ROM__T__get_nocs_aux_code_emmc		0xbfc02cc1
#define ROM__T__get_nocs_params_emmc		0xbfc02d11
#define ROM__T__get_nocs_certificate_emmc		0xbfc02d61
#define ROM__T__enable_clock		0xbfc02d98
#define ROM__T__c_entry		0xbfc02e39
#define ROM__T__memcpy		0xbfc02ff8
#define ROM__T__get_nand_boot_type		0xbfc0315d
#define ROM__T__get_secure_boot_type		0xbfc03275
#define ROM__T__is_mem_obfus_enabled		0xbfc032dd
#define ROM__T__is_bootcode_encrypted		0xbfc03311
#define ROM__T__is_scs_flash_protection_activation		0xbfc03325
#define ROM__T__get_boot_flash_type		0xbfc03355
#define ROM__T__get_tv176_others_check_value		0xbfc03461
#define ROM__T__get_nand_emmc_type_select		0xbfc0349d
#define ROM__T__set_recovery_uart		0xbfc03515
#define ROM__T__set_uart_rx_pin_mux		0xbfc03590
#define ROM__T__set_pin_mux		0xbfc035f9
#define ROM__T__decrypt_aux_code		0xbfc039fd
#define ROM__T__process_aux_code		0xbfc03a1d
#define ROM__T__process_certificate		0xbfc03b39
#define ROM__T__restore_flash_protection_key		0xbfc03bd9
#define ROM__T__process_params		0xbfc03c55
#define ROM__T__check_recovery		0xbfc03d4d
#define ROM__T__init_spi		0xbfc03e49
#define ROM__T__get_nocs_aux_code_spi		0xbfc03e4d
#define ROM__T__get_nocs_params_spi		0xbfc03e7d
#define ROM__T__get_nocs_certificate_spi		0xbfc03eb1
#define ROM__T__InitTimer		0xbfc03f0d
#define ROM__T__mdelay		0xbfc03f4d
#define ROM__T__udelay		0xbfc03f8d
#define ROM__T__SystemTimeout		0xbfc03fc9
#define ROM__T__read_byte		0xbfc03fe9
#define ROM__T__read_word		0xbfc04005
#define ROM__T__serial_read		0xbfc04075
#define ROM__T__serial_write		0xbfc04091
#define ROM__T__prints		0xbfc040a9
#define ROM__T__print_val		0xbfc040e9
#define ROM__T__print_hex		0xbfc04139
#define ROM__T__check_uart0_tx_gpi_toggled		0xbfc04189
#define ROM__T__check_uart1_tx_gpi_toggled		0xbfc041b1
#define ROM__T__set_focus_uart		0xbfc041d9
#define ROM__T__init_uart		0xbfc0427c
#define ROM__T__polling_done		0xbfc04309
#define ROM__T__polling_timeout		0xbfc04315
#define ROM__T__wait_loop		0xbfc04340
#define ROM__T__mask_register		0xbfc04364
#define ROM__T__sync		0xbfc04381
#define ROM__T__not_valid_address		0xbfc0438d
#define ROM__T__compare_memory		0xbfc043ad
#define ROM__T__copy_memory		0xbfc043d5
#define ROM__T__memset		0xbfc04421
#define ROM__T__calculate_image_checksum		0xbfc0443d
#define ROM__T__watchdog_reset		0xbfc04461
#define ROM__T__swap_endian		0xbfc04489
#define ROM__T__print_error		0xbfc044ad
#define ROM__t__append_padding		0xbfc044ed
#define ROM__T__verify_image_signature		0xbfc04569
#define ROM__T__check_image_hash		0xbfc04615
#define ROM__T__scs_validate_controlling_data		0xbfc06001
#define ROM__T__scs_verify_aux_code		0xbfc06059
#define ROM__T__scs_verify_params		0xbfc06105
#define ROM__T__scs_verify_nocs_certificate		0xbfc06195
#define ROM__T__is_scs_enabled		0xbfc061f9
#define ROM__T__get_scs_market_segment_ID		0xbfc06229
#define ROM__T__get_scs_versioning		0xbfc06235

#endif /* _ROM_SYMBOL_H_ */