/************************************************************
*	SYSTEM GLOBAL OPTIONS
*************************************************************/
//#define USE_AUTO_FREQ
//#define AC209_28PIN		//28 PIN IC GPIO CONFIG


#if 1
//#define UART_ENABLE
#ifdef UART_ENABLE
#define USE_UART_P24_P25
#endif

#define MUTE_CTRL_LEVEL_NORMAL
//#define REC_PLAY_KEY_BREAK_POINT
//#define DEFAULT_VOL		0

//#define IIC_GPIO_USE_P00_P01
//#define IIC_GPIO_USE_P02_P03
//#define EXCHANGE_AUX_CHANNEL
//#define CUSTOM_DEFINED_FOLDER
//#define NO_LED_DISPLAY
//#define NEW_DH_228_LCD_MODULE_SM5901
//#define NEW_DH_289_LCD_MODULE_SM5858

#define JK_FT_780_MODULE
//#define JK_FP_211_MODULE
//#define JK_HT_998_MODULE
//#define JK_SZ_S900_MODULE
//#define JK_JF_933_MODULE
//#define JK_JF_689_MODULE
//#define JK_JF_168_MODULE
//#define JK_DH_105_104_MODULE
//#define JK_DH_289_MODULE
//#define K129_MODULE
//#define JK299_MODULE



#if defined(JK_JF_933_MODULE)

#define DISP_VER		2

#define ADKEY_PORT_P02
#define IIC_GPIO_USE_P00_P07

#define LCD_BACK_LIGHT_USE_P03

#define LCD_GPIO_DRV
//#define JF_168_LCD_MODULE_NEW_BOARD
#define LCD_DRV_5_COM_8_SEG
#define JK_JF_933_LCD_MODULE
#define DISP_PAU_STR

#define RADIO_BAND_SWITCH_AD_PORT_P05
#define FUNCTION_SWITCH_AD_PORT_P04

#define SW_TWO_BAND_RANGE_FOR_CUSTOMER_JIN_FENG

#define REC_PLAY_KEY_BREAK_POINT

#define SAVE_BAND_FREQ_INFO

#define REPEAT_MODE_USE_ONE_ALL

#define EXCHANGE_AUX_CHANNEL
#define DEFAULT_VOL		MAX_MAIN_VOL
#define NO_AUX_CHANNEL

#define JOG_STICK_FUNC
#define FAST_STICK_TUNE_FUNC


#define USE_BAT_MANAGEMENT
#define CHARGER_DETECT_INDICATOR

#define DC_CHARGER_DET_SHARE_IIC_P07
#define USE_GPIO_MEASURE_VOLT_AT_P06

#define PLAY_MODE_IN_USE
#define REPEAT_MODE_USE_ONE_ALL
#define DISP_PLAY_MODE_STR


#define AUTO_PLAY_RADIO_REC_FILE
#define DISP_REC_ICON_WHEN_RECORDING
#define DISP_ACTIVE_REC_DEVICE_AT_RADIO_MODE
#endif


#if defined(JK_FT_780_MODULE)

#define DISP_VER		1

#define ADKEY_PORT_P02
#define IIC_GPIO_USE_P00_P07

#define LCD_BACK_LIGHT_USE_P03

#define LCD_GPIO_DRV

#define MCU_ADC_VOL_TUNER

//#define NEW_DH_289_LCD_MODULE_SM5858
#if 1
#define NEW_FT_LCD_780_MODULE
#define DISP_PLAY_ICON
#define DISP_PAUSE_ICON
#define DISP_SW2_ICON
//#define DISP_PAU_STR
#endif

#define RADIO_BAND_SWITCH_AD_PORT_P04
#define FUNCTION_SWITCH_AD_PORT_P05

//#define SW_TWO_BAND_RANGE
#define SAVE_BAND_FREQ_INFO

#define REC_PLAY_KEY_BREAK_POINT
//#define FM_FREQ_NUM_KEY_INPUT

//#define RADIO_VAR_VOL_TUNE

#define REPEAT_MODE_USE_ONE_ALL

#define EXCHANGE_AUX_CHANNEL
#define DEFAULT_VOL		MAX_MAIN_VOL
#define NO_AUX_CHANNEL
//#define JOG_STICK_FUNC
//#define FAST_STICK_TUNE_FUNC

#if 0
#define BLUE_TOOTH_UART_FUNC
#define USE_BLUE_TOOTH_FUNC
#endif

//#define USE_BAT_MANAGEMENT
//#define CHARGER_DETECT_INDICATOR

//#define DC_CHARGER_DET_SHARE_IIC_P07
//#define USE_GPIO_MEASURE_VOLT_AT_P03

#define PLAY_MODE_IN_USE
#define REPEAT_MODE_USE_ONE_ALL
#define DISP_PLAY_MODE_STR
#endif


#if defined(JK_FP_211_MODULE)

#define NEW_FP_LCD_211_MODULE

#define SW_TWO_BAND_RANGE

#define DISP_PAU_STR
#define LCD_DRV_5_COM_8_SEG

#define REC_PLAY_KEY_BREAK_POINT
#define FM_FREQ_NUM_KEY_INPUT

#define IIC_GPIO_USE_P00_P01


#define REPEAT_MODE_USE_ONE_ALL

#define EXCHANGE_AUX_CHANNEL
#define USE_BAT_MANAGEMENT
#define DEFAULT_VOL		MAX_MAIN_VOL
#define LCD_GPIO_DRV
#define NO_AUX_CHANNEL
#define SAVE_BAND_FREQ_INFO
#define JOG_STICK_FUNC
#define FAST_STICK_TUNE_FUNC


#define CHARGER_DETECT_INDICATOR

#define DC_CHARGER_DET_SHARE_IIC_P01
#define USE_GPIO_MEASURE_VOLT_AT_P03

#define PLAY_MODE_IN_USE
#define REPEAT_MODE_USE_ONE_ALL
#define DISP_PLAY_MODE_STR
#endif

#if defined(JK_HT_998_MODULE)

#define DISP_VER		3

#define JK_HT_998_LCD_MODULE
//#define NEW_DH_228_LCD_MODULE_SM5901

#define DISP_PAU_STR

#define SW_TWO_BAND_RANGE

#define REC_PLAY_KEY_BREAK_POINT
#define FM_FREQ_NUM_KEY_INPUT

#define IIC_GPIO_USE_P00_P01

#define REPEAT_MODE_USE_ONE_ALL

#define EXCHANGE_AUX_CHANNEL
#define USE_BAT_MANAGEMENT
#define DEFAULT_VOL		MAX_MAIN_VOL
#define LCD_GPIO_DRV
#define NO_AUX_CHANNEL
#define SAVE_BAND_FREQ_INFO
#define JOG_STICK_FUNC
#define FAST_STICK_TUNE_FUNC


#define CHARGER_DETECT_INDICATOR

#define DC_CHARGER_DET_SHARE_IIC_P01
#define USE_GPIO_MEASURE_VOLT_AT_P03

#define PLAY_MODE_IN_USE
#define REPEAT_MODE_USE_ONE_ALL
#define DISP_PLAY_MODE_STR

#define AUTO_PLAY_RADIO_REC_FILE
#define DISP_REC_ICON_WHEN_RECORDING
#define DISP_ACTIVE_REC_DEVICE_AT_RADIO_MODE
#endif

#if defined(JK_JF_689_MODULE)

#define DISP_VER		2

//#define JF_168_LCD_MODULE
#define JK_JF_689_LCD_MODULE
#define LCD_DRV_5_COM_8_SEG

#define SW_TWO_BAND_RANGE_FOR_CUSTOMER_JIN_FENG
#define REC_PLAY_KEY_BREAK_POINT
#define FM_FREQ_NUM_KEY_INPUT

#define IIC_GPIO_USE_P00_P01

#define DISP_PAU_STR

#define REPEAT_MODE_USE_ONE_ALL

#define EXCHANGE_AUX_CHANNEL
#define DEFAULT_VOL		MAX_MAIN_VOL
#define LCD_GPIO_DRV
#define NO_AUX_CHANNEL
#define SAVE_BAND_FREQ_INFO
#define JOG_STICK_FUNC
#define FAST_STICK_TUNE_FUNC

#define USE_BAT_MANAGEMENT
#define CHARGER_DETECT_INDICATOR
#define DC_CHARGER_DET_SHARE_IIC_P01
#define USE_GPIO_MEASURE_VOLT_AT_P03
#define PLAY_STATUS_LED_FUNC
#define LCD_BACK_LIGHT_DUMMY


#define PLAY_MODE_IN_USE
#define REPEAT_MODE_USE_ONE_ALL
#define DISP_PLAY_MODE_STR

#define AUTO_PLAY_RADIO_REC_FILE
#define DISP_REC_ICON_WHEN_RECORDING
#define DISP_ACTIVE_REC_DEVICE_AT_RADIO_MODE

#endif

#if defined(JK_JF_168_MODULE)

#define JF_168_LCD_MODULE

#define SW_TWO_BAND_RANGE
#define REC_PLAY_KEY_BREAK_POINT
#define FM_FREQ_NUM_KEY_INPUT

#define IIC_GPIO_USE_P00_P01


#define REPEAT_MODE_USE_ONE_ALL

#define EXCHANGE_AUX_CHANNEL
#define DEFAULT_VOL		MAX_MAIN_VOL
#define LCD_GPIO_DRV
#define NO_AUX_CHANNEL
#define SAVE_BAND_FREQ_INFO
#define JOG_STICK_FUNC
#define FAST_STICK_TUNE_FUNC

//#define USE_BAT_MANAGEMENT
//#define CHARGER_DETECT_INDICATOR
//#define DC_CHARGER_DET_SHARE_IIC_P01
//#define USE_GPIO_MEASURE_VOLT_AT_P03
#define PLAY_STATUS_LED_FUNC


#define PLAY_MODE_IN_USE
#define REPEAT_MODE_USE_ONE_ALL
#define DISP_PLAY_MODE_STR
#endif



#if defined(JK_DH_105_104_MODULE)

#define NEW_DH_107_105_104_LCD_MODULE

#define SW_TWO_BAND_RANGE
#define REC_PLAY_KEY_BREAK_POINT
#define FM_FREQ_NUM_KEY_INPUT

#define IIC_GPIO_USE_P00_P01


#define REPEAT_MODE_USE_ONE_ALL

#define EXCHANGE_AUX_CHANNEL
#define DEFAULT_VOL		MAX_MAIN_VOL
#define LCD_GPIO_DRV
#define NO_AUX_CHANNEL
#define SAVE_BAND_FREQ_INFO
#define JOG_STICK_FUNC
#define FAST_STICK_TUNE_FUNC


//#define USE_BAT_MANAGEMENT
//#define CHARGER_DETECT_INDICATOR
//#define DC_CHARGER_DET_SHARE_IIC_P01
//#define USE_GPIO_MEASURE_VOLT_AT_P03

#define PLAY_MODE_IN_USE
#define REPEAT_MODE_USE_ONE_ALL
#define DISP_PLAY_MODE_STR
#endif


#if defined(JK_SZ_S900_MODULE)

#define NEW_DH_289_LCD_MODULE_SM5858

#ifdef NEW_DH_289_LCD_MODULE_SM5858
#define DISP_PAU_STR
#endif

#define SW_TWO_BAND_RANGE
#define REC_PLAY_KEY_BREAK_POINT
#define FM_FREQ_NUM_KEY_INPUT

#define IIC_GPIO_USE_P00_P01


#define REPEAT_MODE_USE_ONE_ALL

#define EXCHANGE_AUX_CHANNEL
#define USE_BAT_MANAGEMENT
#define DEFAULT_VOL		MAX_MAIN_VOL
#define LCD_GPIO_DRV
#define NO_AUX_CHANNEL
#define CHARGER_DETECT_INDICATOR
#define SAVE_BAND_FREQ_INFO
#define JOG_STICK_FUNC
#define FAST_STICK_TUNE_FUNC

#define DC_CHARGER_DET_SHARE_IIC_P01
#define USE_GPIO_MEASURE_VOLT_AT_P03

#define PLAY_MODE_IN_USE
#define REPEAT_MODE_USE_ONE_ALL
#define DISP_PLAY_MODE_STR
#endif

#if defined(JK_KN_299_MODULE)

#define USE_LCD_DRV_HT1621
#define DISP_REC_ICON_WHEN_RECORDING
#define REC_PLAY_KEY_BREAK_POINT
#define FM_FREQ_NUM_KEY_INPUT

#define IIC_GPIO_USE_P00_P01


#define EXCHANGE_AUX_CHANNEL

#define DEFAULT_VOL		MAX_MAIN_VOL
#define NO_AUX_CHANNEL
#define SAVE_BAND_FREQ_INFO
#define JOG_STICK_FUNC
#define FAST_STICK_TUNE_FUNC


#define REPEAT_MODE_USE_ONE_ALL
#define PLAY_MODE_IN_USE

#define USE_BAT_MANAGEMENT
#define DC_CHARGER_DET_SHARE_IIC_P01
#define USE_GPIO_MEASURE_VOLT_AT_P03
#define CHARGER_DETECT_INDICATOR

#endif

#if defined(K129_MODULE)

#define NEW_DH_228_LCD_MODULE_SM5901

#define DISP_PAU_STR

#define SW_TWO_BAND_RANGE

#define REC_PLAY_KEY_BREAK_POINT
#define FM_FREQ_NUM_KEY_INPUT

#define IIC_GPIO_USE_P00_P01


#define REPEAT_MODE_USE_ONE_ALL

#define EXCHANGE_AUX_CHANNEL
#define USE_BAT_MANAGEMENT
#define DEFAULT_VOL		MAX_MAIN_VOL
#define LCD_GPIO_DRV
#define NO_AUX_CHANNEL
#define SAVE_BAND_FREQ_INFO
#define JOG_STICK_FUNC
#define FAST_STICK_TUNE_FUNC


#define CHARGER_DETECT_INDICATOR

#define DC_CHARGER_DET_SHARE_IIC_P01
#define USE_GPIO_MEASURE_VOLT_AT_P03

#define PLAY_MODE_IN_USE
#define REPEAT_MODE_USE_ONE_ALL
#define DISP_PLAY_MODE_STR
#endif

#if defined(JK_DH_289_MODULE)

#define DISP_VER		2

#define NEW_DH_289_LCD_MODULE_SM5858

#ifdef NEW_DH_289_LCD_MODULE_SM5858
#define DISP_PAU_STR
#endif

#define REC_PLAY_KEY_BREAK_POINT
#define FM_FREQ_NUM_KEY_INPUT

#define IIC_GPIO_USE_P00_P01

#define AM_SHARE_SW_FM_LONG_ANT

#define REPEAT_MODE_USE_ONE_ALL

#define EXCHANGE_AUX_CHANNEL
#define USE_BAT_MANAGEMENT
#define DEFAULT_VOL		MAX_MAIN_VOL
#define LCD_GPIO_DRV
#define NO_AUX_CHANNEL
#define SAVE_BAND_FREQ_INFO
#define JOG_STICK_FUNC
#define FAST_STICK_TUNE_FUNC


#define CHARGER_DETECT_INDICATOR

#define DC_CHARGER_DET_SHARE_IIC_P01
#define USE_GPIO_MEASURE_VOLT_AT_P03

#define PLAY_MODE_IN_USE
#define REPEAT_MODE_USE_ONE_ALL
#define DISP_PLAY_MODE_STR
#endif



#endif
