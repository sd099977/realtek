#ifndef _ROM_SYMBOL_H_
#define _ROM_SYMBOL_H_

#define ROM__D__UartReg		0x90000000
#define ROM__b__emmc_card		0x90000008
#define ROM__B__sys_boot_type		0x9000007c
#define ROM__B__sys_flash_current_pos		0x90000080
#define ROM__B__sys_errno		0x90000084
#define ROM__B__sys_boot_flash_type		0x90000088
#define ROM__B__g_Aux_Code_Tail		0x9000008c
#define ROM__B__g_NOCS_Certificate		0x900001a0
#define ROM__B__g_Params_Area		0x900004bc
#define ROM__B__g_SEC_FW_NOCS_Certificate		0x90000610
#define ROM__B__s_PageSize		0x90000824
#define ROM__B__s_BlockSize		0x90000828
#define ROM__B__s_PagePerBlock		0x9000082c
#define ROM__B__s_FlashID4Bytes		0x90000830
#define ROM__B__memory_pool		0xb8079000
#define ROM__b__alloc_count		0xb807a400
#define ROM__b__alloc_current		0xb807a404
#define ROM__B__mcp_hash_result		0xb807a408
#define ROM__B__mcp_tmp_buffer		0xb807a428
#define ROM__b__mcp_dscpt		0xb807a448
#define ROM__T____reset_vector		0xbfc00000
#define ROM__T__func_nop		0xbfc00438
#define ROM__T__print_str		0xbfc00448
#define ROM__T__copy_data		0xbfc004e0
#define ROM__T__clear_memory		0xbfc00530
#define ROM__T__sys_dcache_flush_all		0xbfc0054c
#define ROM__T__enable_uart_tx		0xbfc00580
#define ROM__T__go_acpu_for_recovery_mode		0xbfc005bc
#define ROM__T__empty		0xbfc00645
#define ROM__T__my_malloc		0xbfc00649
#define ROM__T__my_free		0xbfc00699
#define ROM__T__my_freeAll		0xbfc006c1
#define ROM__T__strlen		0xbfc006dd
#define ROM__T__set_memory		0xbfc006f1
#define ROM__T__get_RSA_memory_pool		0xbfc00735
#define ROM__T__skip_pkcs_v1_5_padding		0xbfc00741
#define ROM__T__do_RSA		0xbfc008e1
#define ROM__T__Cmp		0xbfc009b9
#define ROM__T__isZero		0xbfc00a0d
#define ROM__T__Sub_p		0xbfc00a21
#define ROM__T__Add_p		0xbfc00aa1
#define ROM__T__Mul_p		0xbfc00ac9
#define ROM__T__Div_p		0xbfc00b30
#define ROM__T__Mod_p		0xbfc00d10
#define ROM__T__OutPutToAddr		0xbfc00e01
#define ROM__T__BI_setbit		0xbfc00e5d
#define ROM__T__BI_chkmsbbit		0xbfc00e75
#define ROM__T__BI_is_bit_set		0xbfc00ed1
#define ROM__T__Sub		0xbfc00ef5
#define ROM__T__Add		0xbfc00ff1
#define ROM__T__init		0xbfc01075
#define ROM__T__InPutFromAddr		0xbfc010a1
#define ROM__T__Mul		0xbfc01115
#define ROM__T__move_p		0xbfc01255
#define ROM__T__Mod		0xbfc0128c
#define ROM__T__Div		0xbfc014d4
#define ROM__T__move		0xbfc01761
#define ROM__T__Exp_Mod		0xbfc0178d
#define ROM__T__RCP_WRITE_SRAM		0xbfc01819
#define ROM__T__RCP_SET_CW		0xbfc01841
#define ROM__T__check_key_already_in_cw		0xbfc018a9
#define ROM__t__do_k_mcp		0xbfc018cd
#define ROM__T__AES_decrypt_key_in_CW		0xbfc0198d
#define ROM__T__SHA256_hash		0xbfc01a5d
#define ROM__T__AES_CBC_decrypt		0xbfc01b69
#define ROM__T__do_kcpu_bisr		0xbfc01c98
#define ROM__T__do_acpu_bisr		0xbfc01d7c
#define ROM__T__st_enable_clock		0xbfc01e58
#define ROM__T__enable_PLL		0xbfc01ed0
#define ROM__T__init_crt		0xbfc01f3c
#define ROM__T__do_cp42k_bisr		0xbfc02101
#define ROM__T__mmccr_print_buffer		0xbfc021d5
#define ROM__t__mmccr_read_rsp		0xbfc021d9
#define ROM__T__mmc_get_rsp_len		0xbfc022dd
#define ROM__T__mmc_get_rsp_type		0xbfc022f9
#define ROM__T__endian_chg		0xbfc02399
#define ROM__t__mmccr_reset_cr_state		0xbfc023ed
#define ROM__t__mmccr_TriggerXferCmd		0xbfc02449
#define ROM__t__mmccr_SendCmd		0xbfc024c1
#define ROM__t__mmccr_Stream_Cmd		0xbfc02555
#define ROM__t__mmc_read_ext_csd		0xbfc026fd
#define ROM__T__init_emmc		0xbfc027ad
#define ROM__T__mmc_select_part		0xbfc029ad
#define ROM__T__mmc_blk_read		0xbfc02a29
#define ROM__T__get_nocs_aux_code_emmc		0xbfc02b41
#define ROM__T__get_nocs_params_emmc		0xbfc02c25
#define ROM__T__get_nocs_certificate_emmc		0xbfc02c75
#define ROM__T__enable_clock		0xbfc02cac
#define ROM__T__c_entry		0xbfc02d4d
#define ROM__T__memcpy		0xbfc02e48
#define ROM__T__nf_read_image		0xbfc02fad
#define ROM__T__get_nocs_aux_code_nand		0xbfc0306d
#define ROM__T__get_nocs_params_nand		0xbfc03185
#define ROM__T__get_nocs_certificate_nand		0xbfc031c5
#define ROM__T__init_nand		0xbfc03301
#define ROM__t__nand_op_xfer_mode_read		0xbfc034d9
#define ROM__T__nand_op_is_6bit_ecc		0xbfc03619
#define ROM__T__nand_op_is_12bit_ecc		0xbfc03629
#define ROM__T__nand_op_spare_ddr_enabled		0xbfc03639
#define ROM__T__nand_op_get_sram		0xbfc0364d
#define ROM__T__nand_op_is_random_mode		0xbfc036a5
#define ROM__T__nand_op_set_random_col_addr		0xbfc036b5
#define ROM__T__nand_op_set_timing		0xbfc036d9
#define ROM__T__nand_op_reset		0xbfc036fd
#define ROM__T__nand_op_read_id		0xbfc03761
#define ROM__T__nand_op_read_onfi_params		0xbfc03781
#define ROM__T__nand_op_read_to_PP_first		0xbfc03799
#define ROM__T__nand_op_read_page		0xbfc038cd
#define ROM__T__get_nand_boot_type		0xbfc03a31
#define ROM__T__get_secure_boot_type		0xbfc03b49
#define ROM__T__is_mem_obfus_enabled		0xbfc03bb1
#define ROM__T__is_bootcode_encrypted		0xbfc03be5
#define ROM__T__is_scs_flash_protection_activation		0xbfc03bf9
#define ROM__T__get_boot_flash_type		0xbfc03c29
#define ROM__T__get_tv176_others_check_value		0xbfc03d35
#define ROM__T__get_nand_emmc_type_select		0xbfc03d71
#define ROM__T__set_recovery_uart		0xbfc03de9
#define ROM__T__set_uart_rx_pin_mux		0xbfc03e64
#define ROM__T__set_pin_mux		0xbfc03ecd
#define ROM__T__process_aux_code		0xbfc042d9
#define ROM__T__decrypt_aux_code		0xbfc043b5
#define ROM__T__process_certificate		0xbfc043d5
#define ROM__T__restore_flash_protection_key		0xbfc04495
#define ROM__T__process_params		0xbfc04511
#define ROM__T__check_recovery		0xbfc0463d
#define ROM__T__init_spi		0xbfc04739
#define ROM__T__get_nocs_params_spi		0xbfc0473d
#define ROM__T__get_nocs_aux_code_spi		0xbfc04771
#define ROM__T__get_nocs_certificate_spi		0xbfc04851
#define ROM__T__init_spi_n		0xbfc048ad
#define ROM__T__spi_n_read_image		0xbfc048f1
#define ROM__T__get_nocs_aux_code_spi_n		0xbfc049e5
#define ROM__T__get_nocs_params_spi_n		0xbfc04afd
#define ROM__T__get_nocs_certificate_spi_n		0xbfc04b3d
#define ROM__T__sfc_get_cache_data		0xbfc04b75
#define ROM__T__sfc_get_cache_data_p		0xbfc04ba9
#define ROM__T__sfc_get_cache_tag_p		0xbfc04bd1
#define ROM__T__sfc_read_id		0xbfc04bf1
#define ROM__t__sfc_read_page_to_cache_b		0xbfc04c25
#define ROM__T__sfc_read_page_to_cache		0xbfc04cd5
#define ROM__T__sfc_read_page_b		0xbfc04cf5
#define ROM__T__sfc_reset		0xbfc04d71
#define ROM__T__sfc_read_page_c		0xbfc04da1
#define ROM__T__sfc_read_page		0xbfc04e41
#define ROM__T__InitTimer		0xbfc04e7d
#define ROM__T__mdelay		0xbfc04ebd
#define ROM__T__udelay		0xbfc04efd
#define ROM__T__SystemTimeout		0xbfc04f39
#define ROM__T__read_byte		0xbfc04f59
#define ROM__T__read_word		0xbfc04f75
#define ROM__T__serial_read		0xbfc04fe5
#define ROM__T__serial_write		0xbfc05001
#define ROM__T__prints		0xbfc05019
#define ROM__T__print_val		0xbfc05059
#define ROM__T__print_hex		0xbfc050a9
#define ROM__T__check_uart0_tx_gpi_toggled		0xbfc050f9
#define ROM__T__check_uart1_tx_gpi_toggled		0xbfc05121
#define ROM__T__set_focus_uart		0xbfc05149
#define ROM__T__init_uart		0xbfc051ec
#define ROM__T__polling_done		0xbfc05279
#define ROM__T__polling_timeout		0xbfc05285
#define ROM__T__wait_loop		0xbfc052b0
#define ROM__T__mask_register		0xbfc052d4
#define ROM__T__sync		0xbfc052f1
#define ROM__T__not_valid_address		0xbfc052fd
#define ROM__T__compare_memory		0xbfc0531d
#define ROM__T__copy_memory		0xbfc05345
#define ROM__T__memset		0xbfc05391
#define ROM__T__calculate_image_checksum		0xbfc053ad
#define ROM__T__watchdog_reset		0xbfc053d1
#define ROM__T__swap_endian		0xbfc053f5
#define ROM__T__print_error		0xbfc05419
#define ROM__t__append_padding		0xbfc05459
#define ROM__T__verify_image_signature		0xbfc054d5
#define ROM__T__check_image_hash		0xbfc05591
#define ROM__T__scs_validate_controlling_data		0xbfc06001
#define ROM__T__scs_verify_aux_code		0xbfc06059
#define ROM__T__scs_verify_params		0xbfc060c5
#define ROM__T__scs_verify_nocs_certificate		0xbfc06161
#define ROM__T__is_scs_enabled		0xbfc061bd
#define ROM__T__get_scs_market_segment_ID		0xbfc061ed
#define ROM__T__get_scs_versioning		0xbfc061f9

#endif /* _ROM_SYMBOL_H_ */
