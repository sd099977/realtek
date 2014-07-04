typedef enum  {
	IFD_DIG_DEMOD=0,
	IFD_ANA_DEMOD,
}IFD_IFADC_MUX;

//remove on sirius
typedef enum  {
	IFD_ADC_SHAGAIN_0P6X = 0,
	IFD_ADC_SHAGAIN_0P86X = 1,
	IFD_ADC_SHAGAIN_1P0X = 2,
	IFD_ADC_SHAGAIN_1P2X = 3,
}IFD_ADC_SHAGAIN;

typedef enum  {
	IFD_ADC_FULLSCALE_1P23V = 0,
	IFD_ADC_FULLSCALE_1P30V = 1,
	IFD_ADC_FULLSCALE_1P40V = 2,
	IFD_ADC_FULLSCALE_1P48V = 3,
}IFD_ADC_FULLSCALE;

typedef enum  {
	IFD_ADC_PGAFIX_CTRL_FROM_DIGITAL = 0,
	IFD_ADC_PGAFIX_CTRL_N1DB = 1,
	IFD_ADC_PGAFIX_CTRL_N2DB = 2,
	IFD_ADC_PGAFIX_CTRL_N3DB = 3,
	IFD_ADC_PGAFIX_CTRL_N4DB,
	IFD_ADC_PGAFIX_CTRL_N5DB,
	IFD_ADC_PGAFIX_CTRL_N6DB,
	IFD_ADC_PGAFIX_CTRL_N7DB,
}IFD_ADC_PGAFIX_CTRL;

typedef enum  {
	IFD_ADC_INPUT_SEL_IFPGA=0,
	IFD_ADC_INPUT_SEL_BYPASS,
}IFD_ADC_INPUT_SEL;

typedef enum  {
	IFD_CLK_RATE_108M = 0  ,
	IFD_CLK_RATE_54M,
	IFD_CLK_RATE_135M,
	IFD_CLK_RATE_162M,
}IFD_CLK_RATE;

void drv_ifd_analog_preset(void);
void drv_ifd_power_on(bool enable);
void drv_ifd_set_adcinput_swing(IFD_ADC_SHAGAIN setting1, IFD_ADC_FULLSCALE setting2);
void drv_ifd_adc_clock_source_set(IFD_IFADC_MUX value);
void drv_ifd_adc_input_sel(IFD_ADC_INPUT_SEL input_source);
void drv_ifd_adc_clock_default(void);
void drv_ifd_adc_clock(IFD_CLK_RATE adc_clock);
void drv_ifd_adc_pga_gain_fix(bool enable, IFD_ADC_PGAFIX_CTRL fix_pga_gain);


