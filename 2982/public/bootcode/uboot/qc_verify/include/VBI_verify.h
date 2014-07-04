

//=====================================================
void Display_Init(void);

#ifdef AV_Input
void AV_Init(void);
#endif
#ifdef IFD_Input
void IFD_Init(void);
#endif
#ifdef YPP_Input
void YPbPr_Init(void);
#endif

#ifdef CC_verify_test
void  CC_Init(void);
UINT8 CC_verify(void);
#endif

#ifdef TT_WSS_VPS_test
void TT_WSS_VPS_Init(void);
UINT8 TT_WSS_VPS_verify(void);
#ifdef TT_DMA_test
void DMA_Init(void);
#endif
#endif

#ifdef CGMS_test
void CGMS_Init(void);
UINT8 CGMS_verify(void);
#endif


