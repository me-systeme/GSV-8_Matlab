/**********************************************************************************************
C or C++ Header-file for MEGSV86x64.DLL (Windows 64-Bit)
For using with GSV-8/BX8 or GSV-6/ITA measuring amplifiers with serial interface
Copyright 2017 ME-Messysteme GmbH H.Kabelitz
1. Data types, all little-endian style:
	int : signed integer of 32 bits size
	unsigned long : unsigned integer of 32 bits size
	double : IEEE754 floating-point value of 64 bits size

2. Calling conventions: w32: __stdcall x64: __fastcall

************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _M_X64
#define CALLTYP __fastcall
#else
#define CALLTYP __stdcall
#endif

/* Definition of error codes, as retrieved by GSV86getLastProtocollError and GSV86getLastErrorText */
#include "Errorcodes.h"

/************************************************************************************************
Definitions of constants.
Values can't be changed, since it won't have any effect on using the readily compiled library.
*************************************************************************************************/
/* Version of this DLL */
#define FILEVER_H                       1
#define FILEVER_L                       17

/* Return-codes for Simple errorcode */
#define GSV_OK 0	/*no error, without signalling information */
#define GSV_ERROR -1	/*an error occurred within the request */
#define GSV_TRUE 1	/*no error, with signalling information */
/* Device Model constants */
#define GSV6	6
#define GSV8	8

/*Constant values used by GSV86*actEx */
#define CONST_BAUDRATE	115200
#define CONST_BUFSIZE	48000

/* Flags for parameter "flags" in GSV86activateExtended */
#define ACTEX_FLAG_HANDSHAKE	4	/* enables HW-handshake in in GSV86activateExtended */
#define ACTEX_FLAG_WAIT_EXTENDED	0x0100	/* waits longer for device-answer in GSV86activateExtended */
#define ACTEX_FLAG_STOP_TX	0x0200	/* stops continious data transmission in GSV86activateExtended */

/* Constants for GSV86getLastProtocollError and GSV86getLastErrorText */
#define ERRTEXT_SIZE 256 /* Maximum size of error text */
#define ERR_MASK_ALL 0xFC000000 /* Mask for error code types */
#define OWN_ERR_MASK 0x20000000 /*Mask, which can be or-ed with one of the well-known Windows Systen Error Code , see: MSDN:GetLastError() */
#define ERR_MSK_DEVICE 0x38000000 /*Error given by GSV-8 device, errorcode in Bits<7:0>, see GSV-8 manual */
/* This application Errorcodes. Retrieve with GSV86getLastProtocollError. See file Errorcodes.h */

/* Hardware properties of GSV-8 device */
#define	IN_CHAN_NO	8 /* Number of analogue input channels */
#define SIX_AXIS_CHAN_NUM 6	/* Number of channels of the six-axis sensor */
#define NUM_INTYPES 6	/* Number of switchable input types */

/* Object Mapping, as for GSV86getValObjectInfo */
#define VALOBJ_NUM_MAX 16	/* Arraysize for ScaleFactors and ObjMapping */
/* 1. Value type in  Bits<15:8> of ObjMapping */
#define VALTYPE_NORMAL 0	/* actual measuring value */
#define VALTYPE_MAXVAL	1	/* Maximum value */
#define VALTYPE_MINVAL	2	/* Minimum value */
/* 2. Physical type in Bits<23:16> of ObjMapping */
#define VAL_PHYS_TYPE_NOTDEF 0	/* no physical type defined (unknown) */
#define VAL_PHYS_TYPE_FORCE_X 1	/* Force in X-direction */
#define VAL_PHYS_TYPE_FORCE_Y 2	/* Force in Y-direction */
#define VAL_PHYS_TYPE_FORCE_Z 3	/* Force in Z-direction */
#define VAL_PHYS_TYPE_TORQUE_X 4	/* Torque-moment in X-direction */
#define VAL_PHYS_TYPE_TORQUE_Y 5	/* Torque-moment in Y-direction */
#define VAL_PHYS_TYPE_TORQUE_Z 6	/* Torque-moment in Z-direction */
#define VAL_PHYS_TYPE_RAW	0x10	/* Raw value of six-axis sensor (before calculation) */
#define VAL_PHYS_TYPE_TEMP	0x20	/* Temperature */

/* 	Struct definitition for convenience. ObjMapping parameter can be type-casted to this
	after return from GSV86getValObjectInfo.
	Must be packed to total size of 32 Bits, so better use with C or C++ only. */

typedef struct
{
	unsigned char ChannelNo;	/* Channel-Numbers from 1 to 8 */
	unsigned char ValueType;	/* Value type as defined above */
	unsigned char PhysicType;	/* Physical type as defined above */
	unsigned char reserved;		/* not yet used */
} OBJECT_MAPPING;
/* 3. DataType enumeration definition for GSV86getValObjectInfo,GSV86getInterfaceIdent, GSV86setValDataType parameter */
#define DATATYP_INT16	1	/* Datatype sent by GSV-8 is 16-Bit value in binary offset format */
#define DATATYP_INT24	2	/* Datatype sent by GSV-8 is 24-Bit value in binary offset format */
#define DATATYP_FLOAT	3	/* Datatype sent by GSV-8 is 32-Bit Float (scaled in physical units) */

/* Parameter of GSV86getInterfaceIdentity */
#define SET_STOP_MV_TX	1	/* StopPermTX parameter: Disable permanent measuring value transmission */
#define SET_START_MV_TX	2	/* StopPermTX parameter: Enable permanent measuring value transmission */

/* Constants for GSV86getMode and GSV86setMode Flag-Parameter Mode*/
#define SIX_AXIS_SENSOR_ACTIVE 0x01 /* Six-axis sensor (=FT-sensor) calculation enabled */
#define SIX_AXIS_SENSOR_ACT_GSV6 0x400 /* same, but for GSV-6 */
#define ANALOG_FILTER_AUTO 0x02 /* Analog input filter's cut-off frequency set automatically according to data rate */
#define MODE_MAXIMUM 0x04 /* determine maximum- and minimum value */
#define MODE_MAXIMUM_GSV6 0x80  /* same, but for GSV-6 */
#define MODE_NOISECUT 0x08 /* if =1: values below noiseCutThreshold are set to 0 */
#define ALL_WRITES_BLOCKED 0x80 /* all write / set commands are blocked */

/* Constants for GSV86getTXmode and GSV86setTXmode Flag-Parameter*/
#define TX_OFF_VOLATILE 0x01 /* permanent measured value transmission actually off (not stored in EEPROM)*/
#define TX_OFF_NONVOLAT	0x02 /* permanent measured value transmission permanent off (stored in EEPROM)*/
#define TX_MAXVALUE 0x04 /* values in measured vals frame are maximum values */
#define TX_MINVALUE 0x08 /* values in measured vals frame are minimum values */
#define THRESH_VALTYPE_FLOAT 0x10 /* values for noiseCutThreshold and DoutThreshold are stored as float */

/*Type enums (constants) for GSV86readFTsensorCalValue */
#define SENSORCAL_TYP_SERNO 0 /* Sensor serial number. Type-exeption: u32 not float! */
#define SENSORCAL_TYP_MATRIX_NORM 1 /* scaling of values in matrix (=1 for normalized matrix values)*/
#define SENSORCAL_TYP_MATRIX 2 /* 6-axis sensor coefficients 6x6 =36 matrix */
#define SENSORCAL_TYP_OFFSET 3 /* mechanical offsets, 3 values Lx,Ly,Lz */
#define SENSORCAL_TYP_MAXVAL 4 /* sensor nominal maximum values, 6vals Fx,Fy,Fz,Mx,My,Mz */
#define SENSORCAL_TYP_INSENS 5 /* Input sensitivity of amp wich matrix vals were obtained (=1 for normalized matrix values)*/
#define SENSORCAL_TYP_ZEROVAL 6 /* Zero signal values of unloaded sensor */
#define SENSORCAL_MATRIX_NORM_DEF 5.0 /* default value for SENSORCAL_TYP_MATRIX_NORM */
#define SENSORCAL_INSENS_DEF 2.0 /* default value for SENSORCAL_TYP_INSENS */
#define SENSORCAL_ZEROVAL_DEF 0.0  /* default value for SENSORCAL_TYP_ZEROVAL */
#define SENSORCAL_OFFSET_DEF 0 /* default value for SENSORCAL_TYP_OFFSET */
#define SENSORCAL_TYP_TEDS_MEM 0x80	/*Memory type-offset for TEDS memory (reserved)*/
#define SENSORCAL_TYP_EEPROM_MEM 0 /*Memory type-offset for EEPROM memory*/
#define SENSORCAL_VECTOR_SIZE 6
#define SENSORCAL_MATRIX_SIZE	36
#define SENSORCAL_OFFSET_SIZE	3
#define SENSORCAL_MAXVAL_SIZE	6

/*serial number constants */
#define SER_NO_SIZE	8
#define SER_NO_CHAR_SIZE SER_NO_SIZE+1	/*inclusive termination */
#define SERNO_MIN 1
#define SERNO_MAX 99999999

/* Constants for GSV86getInTypeRange, GSV86getAllInTypesRanges and GSV86setInType */
#define MAX_INPUT_TYPES_NUM 10	/* Maximum possible number of input types.
	(bigger than max. existent type-num, for future compatibiliy) */
#define INTYP_BRIDGE_US875 0	/* Input-Type Bridge at Vexcitation= 8.75V */
#define INTYP_BRIDGE_US5 1	/* Input-Type Bridge at Vexcitation= 5V */
#define INTYP_BRIDGE_US25 2	/* Input-Type Bridge at Vexcitation= 2.5V */
#define INTYP_SE10 3		/* Input-Type single-endend +-10V */
#define INTYP_PT1000	4	/* Input-Type Temperature-Sensor PT1000 */
#define INTYP_TEMP_K	5	/* Input-Type Temperature-Sensor Type-K (reserved)*/

/* Constants for GSV86getUnitText and GSV86setUnitText */
#define UNIT_WIDTH 8	/* maximum width of unit text array incl. termination*/
/* Bits<7:0> of Code parameter. Can be ORed with Bit<23:8> constants */
#define ACTIVE_UNIT_ANY 0x00 /*GSV86getUnitText: Read active unit. GSV86setUnitText: Set and activate any unit */
#define USER_UNIT_1 0x01 /*GSV86getUnitText: Read user defined unit string 1. 
			GSV86setUnitText: Set and activate user defined unit string 1. */
#define USER_UNIT_2 0x02 /*GSV86getUnitText: Read user defined unit string 2. 
			GSV86setUnitText: Set and activate user defined unit string 2. */
#define SET_FIXED_UNIT	0x10 /*GSV86setUnitText: Set and activate fixed unit (UnitNo set) */
#define WRITE_USER_UNIT_1 0x11 /*GSV86setUnitText: Write user unit string 1 (not activated) */
#define WRITE_USER_UNIT_2 0x12 /*GSV86setUnitText: Write user unit string 2 (not activated) */
/* Bits<23:0> of Code parameter. Can be ORed with Bit<7:0> constants */
#define ANSI_CODEPAGE 0x00000000 /* ANSI 8-Bit coded */
#define ASCII_ONLY	0x00000100 /* Use ASCII 7-Bit only */
#define DOS_CODEPAGE_437 0x0001B500 /* DOS/Windows Codepage 437 */
#define WIN_CODEPAGE_1252 0x0004E400 /* Windows Codepage 1252 */

/* Constants for digital filters GSV86getDfilterOnOff and GSV86setDfilterOnOff */
#define FILT_TYPE_IIR	0	/* Mask or for IIR-Type. */
#define FILT_TYPE_FIR	0x80	/* Mask or for FIR-Type. See function description for details*/
#define FILT_TYPE_IIR_LP	0x04	/* IIR low pass, 4th order*/
#define FILT_TYPE_IIR_HP	0x14	/* IIR high pass, 4th order*/
#define FILT_TYPE_IIR_BP	0x24 	/* IIR band pass, 4th order*/
#define FILT_TYPE_IIR_BS	0x34 	/* IIR band stop, 4th order*/
#define FILT_TYPE_UNCONFIG	0x00	/* Filter has nor been configured */
#define FILT_ORDER_MSK		0x0F	/* Mask for filter order */
#define FILT_ORDER_IIR	4 /* As by now, filter order is constant for IIR filter */
#define FILT_MAXORDER_FIR 14 /* Maximum FIR filter Order */
#define FILT_MINORDER_FIR 4	/* Minimum FIR filter Order */
#define FILT_COEFFNUM_FIR 8 /* Because a0=a7, a1=a6... coeff. number is order/2 */
#define FILT_CHARACT_MSK	0x70	/* Mask for filter characteristic (LP,HP,BP,BS) */
#define FILT_CHARACT_LP	0x00	/* low pass */
#define FILT_CHARACT_HP	0x10	/* high pass */
#define FILT_CHARACT_BP	0x20	/* band pass */
#define FILT_CHARACT_BS	0x30	/* band stop */
#define FILT_CHARACT_COMB 0x40 /* comb filter (FIR only) */
#define FILT_IDX_MSK_B_COEFF 0x10 /*Mask for IIR index parameter for b coefficients */
#define FILT_FCUT_RATIO_MAX 0.5f	/* maximum ratio for Fcutoff/Fs */
/* Constants for GSV86simulateDfilter. May be ORed with FILT_TYPE_FIR */
#define SIMUL_DFILT_FREQ_RESPONSE 1 /* simulate frequency response (frequency domain)*/
#define SIMUL_DFILT_STEP_RESPONSE 2 /* simulate step response (time domain)*/

/* Constants for analogue filter */
#define FDATA_MAX_FG28HZ 80	/* With SetAnalogFilterAuto: Below this data rate filter is set to 28Hz cutoff */
#define FDATA_MAX_FG1KHZ 3000 /* With SetAnalogFilterAuto: Below this data rate filter is set to 850Hz cutoff */
#define ANAFILT_LOW	28	/* lowest cut-off frequency of analogue input filter (switchable) */
#define ANAFILT_MID	850	/* middle cut-off frequency of analogue input filter (switchable) */
#define ANAFILT_HIGH	12000 /* highest cut-off frequency of analogue input filter (fixed) */

/* Constants for analog output */
#define AOUT_TYPE_0_10V 0	/* 0..10V  */
#define AOUT_TYPE_10_10V 1	/* -10..10V */
#define AOUT_TYPE_0_5V 2	/* 0..5V */
#define AOUT_TYPE_5_5V 3	/* -5..5V */
#define AOUT_TYPE_4_20A 4	/* 4..20mA */
#define AOUT_TYPE_0_20A 6	/* 0..20mA */
/* Mode: Flag value as follows: */
#define AOUT_ACTIVE_M_VALUES 0 /* Output is on and follows the corresponding measuring value input. */
#define AOUT_MODE_DIRECT 1 /*Output is on, but does NOT react on measuring values,
				but is direcly settable with GSV86writeAoutDirect */
#define AOUT_MODE_OFF 2 /* Output is off and high-impedance. */
#define AOUT_IX_MAX 8	/* 8 Analogue Voltage/current outputs. */
#define AOUT_SCALE_IX_MAX 9 /* No. 9 for special-version (freq. output) */

/* Constants for GSV86getEquipment */
#define HAS_ADC 0x01
#define HAS_ETHERCAT 0x02
#define HAS_LCD 0x04
#define HAS_TEDS 0x08
#define HAS_DIGI_IO 0x10
#define HAS_ANALOG_OUT 0x40
#define HAS_SERIAL 0x80
#define HAS_FREQ_OUT 0x100
#define HAS_AIN_MCU 0x200
#define HAS_SIXAXIS 0x400
#define HAS_CANOPEN 0x800

/* Constants for DIOtype */
#define DIO_IN_GENERALPURPOSE 0x04
#define DIO_IN_SYNC_SLAVE 0x02
#define DIO_IN_QEI_ANY 0x08
#define DIO_IN_TARE_SINGLE 0x10
#define DIO_IN_TARE_ALL 0x20
#define DIO_IN_RESET_MAXMIN 0x40
#define DIO_IN_TRIG_SEND_VAL 0x80
#define DIO_IN_TRIG_SEND_MAXVAL 0x100
#define DIO_IN_TRIG_SEND_MINVAL 0x200
#define DIO_IN_TRIG_SEND_AVGVAL 0x400
#define DIO_IN_TRIG_SEND_VAL_WHILE_HI 0x800
#define DIO_OUT_GENERALPURPOSE 0x1000
#define DIO_THRESHOLD_WINDOWCOMP_MASK 0x2000
#define DIO_OUT_THRESHOLD_MAXVAL 0x14000
#define DIO_OUT_THRESHOLD_MINVAL 0x18000
#define DIO_OUT_THRESHOLD_ANYVAL 0x10000
#define DIO_OUT_SYNC_MASTER 0x20000
#define DIO_INVERT_MASK	0x800000

/* Constants for GSV86readCANsettings / GSV86setCANsettings */
#define CAN_SER_CMD_ID 0
#define CAN_SER_ANSW_ID 1
#define CAN_SER_MV_ID 2
#define CAN_SER_MULTI_ID 3
#define CAN_BAUDRATE 4
#define CAN_FLAGS 5
#define CANOPEN_NODEID 6
#define CAN_FLAGMASK_ONOFF 1
#define CAN_FLAGVAL_ON 0
#define CAN_FLAGVAL_OFF 1
#define CAN_FLAGMASK_PROT 2
#define CAN_FLAGVAL_CANOPEN 2
#define CAN_FLAGVAL_CANSER 0

/* Constant macros for use with Communication interface descriptor functions:
	GSV86readInterfaceSetting
	GSV86writeInterfaceSetting
	GSV86readBasicInterfSettings
	GSV86readAllInterfSettings */
/* Interface Physical Layer protocol enumeration */
#define INTF_PHY_TYP_V24 1	/* RS232 with V24 voltage levels */
#define INTF_PHY_TYP_232TTL 2	/* RS232 with 3.3V / 0V voltage levels */
#define INTF_PHY_TYP_USB 3	/* USB (with CDC) */
#define INTF_PHY_TYP_CAN 4	/* CAN bus */
#define INTF_PHY_TYP_ETH 5	/* 100BaseT "Ethernet" */
/* Interface Application Layer protocol enumeration */
#define INTF_APP_TYP_GSV68 0x00000001L /* ME propretary "GSV6/8" interface, used by this DLL */
#define INTF_APP_TYP_CANOPEN 0x00000002L /* CANopen */
#define INTF_APP_TYP_ETCOE 0x00000003L /* EtherCAT CoE */
#define INTF_APP_TYP_MONI 0x00000004L /* Text-based commands "Monitor", GSV-6 only */
/* The flags-value of basic interface setting */
#define INTF_T1_FLG_ACT 1 /* Flag (-mask) indicating that interface is enabled */
#define INTF_T1_FLG_RXACT 1 /* Flag (-mask) indicating that receiving commands is enabled */
#define INTF_T1_FLG_TXACT 2 /* Flag (-mask) indicating that transmitting data is enabled */
#define INTF_T1_FLG_TXRX_ACT 3 /* Flag (-mask) indicating that transmit and receive is enabled */
#define INTF_T1_FLG_WRACC 4 /* Flag (-mask) indicating that write commands are allowed */
#define INTF_T1_MV_BINOFS 8 /* Flag (-mask) indicating that integer measuring values have binary offset formal (sign bit inverted) */
#define INTF_T1_FLG_SWITCHABLE 0x10000 /* Flag (-mask) indicating that interface can be disabled (then enabled) */
#define INTF_T1_FLG_ADRESSABLE 0x20000 /* Flag (-mask) indicating that interface uses device or service address/ID */
#define INTF_T1_FLG_ADRES_CHANGE 0x40000 /* Flag (-mask) indicating that device / service address/ID can be changes by command interface*/
/* Data/Setting type 2 meaning enumeration */
#define INTF_DSCTYP_FLAGS 0  /* Flag value of basic interface setting */
#define INTF_DSCTYP_FLG_SETMSK 1 /* Mask for setting a bit in the Flag value of the basic setting =1:Flag at this pos. can be set*/
#define INTF_DSCTYP_FLG_CLRMSK 2 /* Mask for clearing a bit in the Flag value of the basic setting =1:Flag at this pos. can be cleared*/
#define INTF_DSCTYP_MUTEXCLUSIV 3 /* Ordinal number of other interfaces, that this exist in a mutual exclusive manner. Upto 4 in 4 Bytes, beginning with LSByte*/
#define INTF_DSCTYP_ACTBAUD 4 /* Baud Rate actually set, in Bits/s */
#define INTF_DSCTYP_BAUD_AVAIL 5 /* Baud rate existent, in Bits/s */
#define INTF_DSCTYP_NUM_SERVID 6 /* Number of IDs of device or servicve, used with field bus interfaces */
#define INTF_DSCTYP_SERVID_CAN_IN 7 /* CAN-ID for Host->Device commands, used with "GSV68 CAN-serial" */
#define INTF_DSCTYP_SERVID_CAN_OUT 8 /* CAN-ID for Device->Host command answers, used with "GSV68 CAN-serial" */
#define INTF_DSCTYP_SERVID_CAN_CV 9  /* CAN-ID for Device->Host measuring value frames, used with "GSV68 CAN-serial" */
#define INTF_DSCTYP_SERVID_CAN_CAST 10 /* CAN-ID for Host->Devices multicast messages, used with "GSV68 CAN-serial" */
#define INTF_DSCTYP_SERVID_CANO_NODE 11 /* CANopen Node-ID, used with CANopen aplication protocol */
#define INTF_DSCTYP_DEVSTATE 16 /* Device state, used with fieldbus application protocols */
	#define INTF_FB_STAT_OFF 0 /* Data-value for INTF_DSCTYP_DEVSTATE if Interface is off */
	#define INTF_FB_STAT_INIT 2 /* Data-value for INTF_DSCTYP_DEVSTATE if device is in init or stopped state */
	#define INTF_FB_STAT_PO 4 /* Data-value for INTF_DSCTYP_DEVSTATE if device is in pre-operational state */
	#define INTF_FB_STAT_SO 8 /* Data-value for INTF_DSCTYP_DEVSTATE if device is in safe operational state (EtherCAT) */
	#define INTF_FB_STAT_O 12 /* Data-value for INTF_DSCTYP_DEVSTATE if device is in operational state */
#define INTF_DSCTYP_CANO_TX_TIME 17 /* CANopen Transmission Type (Bits<31:24>) and Event timer (Bits<15:0>) */
#define INTF_DSCTYP_CANO_INH_HB 18 /* CANopen Inhibit time (Bits<31:16>) and Heartbeat time (Bits<15:0>) */
#define INTFT2_WR 0x80 /* Flag value indicating that a value is writable. ORed with data type enum */

#pragma once


///////////////////////////////////////////////////////////////////////////////////
//// Exported functions Prototypes
//--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////





/**
	@brief Get DLL version Number
--------------------------------------------------------------------------------------
 @return Version Number High in Bits<31:16>, Version number Low in Bits<15:0><br>
 Example: Version 1.1.00.32: return value 0x00010001 = d65537<br>
 \note: 3rd and 4th number of version ressource NOT part of return value
*
 OrdinalNo: 1
 Device access: No
*
 \revision date: 10-31-2014
 ********************************************************************************** */
unsigned long CALLTYP GSV86dllVersion(void);

/*!  ****************************************************************************
	@brief Opens a GSV8 on a (V)COM-port, with all necessary ressources.
--------------------------------------------------------------------------------------
	Simplified Version of GSV86activeteExtended, with:
	Bitrate=CONST_BAUDRATE, BufSize=CONST_BUFSIZE, flags=0

 @param[in]	ComNo: 	Number of Comport to be opened
 	
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if ComPort could not be opened or device was not found.
 If =GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 2
 
 Device access: Yes, see GSV86activateExtended
*
 date: 10-31-2014
********************************************************************************** */
int CALLTYP GSV86actExt(int ComNo);

/*!  ****************************************************************************
	@brief Opens a GSV8 on COM-port, specified by parameters, with all necessary ressources.
--------------------------------------------------------------------------------------
 @param[in]	ComNo: 	Number of Comport to be opened
 @param[in]	Bitrate: Bits per second. Allowed values: 9600,19200,38400,57600,115200,230400,460800,921600<br>
 		Must match device setting with Ethernet-Xport, RS232 and RS422 only;<br>
 		but can be any of above values with USB-CDC - value will be discarded.
 @param[in]	BufSize: Size of the buffer, given in number of measuring values.
 		In this buffer measuring values are stored by the reading thread of this DLL<br>
 		and from where values are read by GSV86read/GSV86readMultiple.<br>
 		Size is in Measuring values per channel-object; e.g. with MappedObjectNum=8 and BufSize=30000,
 		8 buffers are allocated, and each has a capacity of 30000 measuring values.
 @param[in]	flags:	Openes with special settings, specified by this flags. Can be ORed together.<br>
 		ACTEX_FLAG_HANDSHAKE: if set, opens the port with hardware-handshake (RTS-CTS)<br>
		ACTEX_FLAG_WAIT_EXTENDED: waits longer for device-answer<br>
		ACTEX_FLAG_STOP_TX stops continious data transmission<br>
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if ComPort could not be opened or device was not found.
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
  OrdinalNo: 4
  
  Device access: Yes, CmdNo: 0x80, 0x01, 0x2B
  
  date: 10-31-2014
********************************************************************************** */
int CALLTYP GSV86activateExtended(int ComNo, unsigned long Bitrate, unsigned long BufSize, unsigned long flags);

/*!  ****************************************************************************
@brief	Get Last Error Code
--------------------------------------------------------------------------------------
	Can be called after another function returned GSV_ERROR.

 @param[in] ComNo: 	Number of Device Comport
 @return One of the following:<br>
 1. Direct System Error Codes (http://msdn.microsoft.com/en-us/library/ms681381%28VS.85%29.aspx),
 retrieved by GetLastError(), which was called by previously failed function.
 Only if GSV86actEx/GSV86activateExtended failed before hardware were accessed.<br>
 2. System Error Codes as above ORed with OWN_ERR_MASK (0x20000000)<br>
 3. Error code as defined above. Range: 0x30000001..0x3000FFFF<br>
 4. Error code thrown by GSV-8 device, ORed with 0x38000000. Range: 0x38000001..0x380000FF. See GSV-8 manual for details.<br>
*
 OrdinalNo: 6
 
 Device access: No
*
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86getLastProtocollError(int ComNo);

/*!  ****************************************************************************
@brief	Get Last Error Code from Device
--------------------------------------------------------------------------------------
	Can be called after another function returned GSV_ERROR.

 @param[in] ComNo: 	Number of Device Comport
 @param[in]   Async:	=0: Last error of measuring application or command interface
     		=1: Last error of protocol frames
 @return
 Error code thrown by GSV-8 device, See Annex for details.
*
 OrdinalNo: 127
 
 Device access: Yes, CmdNo: 0x42
*
  date: 23.02.2017
 ********************************************************************************** */
int CALLTYP GSV86getLastDeviceError(int ComNo, int Async);

/*!  ****************************************************************************
@brief	Get Last Error Code and error describing text
--------------------------------------------------------------------------------------
	Can be called after another function returned GSV_ERROR.

 @param[in] ComNo: 	Number of Device Comport
 @param[in] ErrText: pointer to ASCII coded 8-Bit char array of size 256 chars, where error text is written to.
 @return One of the following:
 1. Direct System Error Codes (http://msdn.microsoft.com/en-us/library/ms681381%28VS.85%29.aspx),
 retrieved by GetLastError(), which was called by previously failed function.
 Only if GSV86actEx/GSV86activateExtended failed before hardware were accessed.<br>
 2. System Error Codes as above ORed with OWN_ERR_MASK (0x20000000)<br>
 3. Error code as defined in Errorcodes.h. Range: 0x30000001..0x3000FFFF<br>
 4. Error code thrown by GSV-8 device, ORed with 0x38000000. Range: 0x38000001..0x380000FF. See GSV-8 manual for details.<br>
*
 OrdinalNo: 5
 
 Device access: No
*
  date: 27.04.2015 14:12
 ********************************************************************************** */
int CALLTYP GSV86getLastErrorText(int ComNo, char* ErrText);

/*!  ****************************************************************************
@brief	Clear and reset all DLL Buffers
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if an error occurred.
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 8
 
 Device access: No
*
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86clearDLLbuffer(int ComNo);

/*!  ****************************************************************************
@brief	Get device model and communication interface information
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] StopPermTX: if =1, The permanent mesuring data transmission will be stopped.
 		if =2, The permanent mesuring data transmission will be started.
 @param[out]	*NumOfIntfDescr: pointer to total number of communication interfaces and their descriptors
 @param[out]	*ThisInterfNo: pointer to Index of this communicating interface in the descriptor array
 @param[out]	*WriteProtection: pointer: =0: no write protection, =2: write protection enabled
 @param[out]	*MValDataType: pointer to Measuring value type: =1: DATATYP_INT16, =2: ~24, =3: DATATYP_FLOAT
 @param[out]	*MValPermanenTX: pointer: =1 permanent mesuring value transmission on, =0: no permanent val.tx
 @param[out]	*NumObjInMVframe: pointer to Number of objects in mesuring value frame
 @param[out]	*ThisDeviceModel: pointer to Model No of device attached. GSV-8: =8
 @param[out]	*ThisProtocol: pointer to General interface type. =1 for serial
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 7
 
 Device access: Yes, CndNo: 0x01
*
  date: 30.09.2015 12:02
 ********************************************************************************** */
int CALLTYP GSV86getInterfaceIdentity(int ComNo, int StopPermTX, int* NumOfIntfDescr, int* ThisInterfNo, int* WriteProtect,
		int* MValDataType, int* MValPermanenTX, int* NumObjInMVframe, int* ThisDeviceModel, int* ThisProtocol);

/*!  ****************************************************************************
@brief	Clear and reset device measuring values buffer
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 9
 
 Device access: Yes, CndNo: 0x25
*
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86clearDeviceBuf(int ComNo);

/*!  ****************************************************************************
@brief	Get number of measuring values in DLL buffer(s)
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in]	Chan: =0: get lowest buffer filling<br>
 		=1..NumMappedObjects: get buffer filling for specified object<br>
 		=NumMappedObjects+1: get highest buffer filling<br>
 	Remark: Different buffer fillings can only occur, if GSV86read or
 		GSV86readMultiple with parameter Chan >0 is used.<br>
 		If GSV86readMultiple with parameter Chan=0 is used only, all buffers have the
 		same filling.
 @return: Number of values in specified buffer, or
 		GSV_ERROR if an error occurred.
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 10
 
 Device access: No
*
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86received(int ComNo, int Chan);

/*!  ****************************************************************************
@brief	Read one measuring value of one (channel-) object
--------------------------------------------------------------------------------------
 @param[in]	ComNo: 	Number of Device Comport
 @param[in]	Chan: Number of Object (channel, respectively) to read. Range: 1..NumMappedObjects
 @param[out]	out: Pointer to one double value, were the measuring value is written to
 @return: 	GSV_OK,if no value was read (buffer empty), or <br>
 		GSV_TRUE if a value was read, or<br>
 		GSV_ERROR if an error occurred
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 12
 
 Device access: No
*
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86read(int ComNo, int Chan, double* out);

/*!  ****************************************************************************
@brief	Reads whole Array of values in dll-value-buffer(s)
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in]	Chan:	=0: Read all existent (channel-)objects <br>
 		=1..NumMappedObjects: Read values of specified object
 @param[out]	*out:	Pointer to (one-dimensional) array of double, where mesuring values 
 		are be written to (if return-value =GSV_TRUE). <br>
 		Important: Array size must be greater or equal <count>!
 @param[in]	count:	Total maximum number of values to read. <br>
 		If Chan=0, count must be dividible by NumMappedObjects.
 @param[out]	*valsread: Pointer to int value, where the actual number of values written into *out is stored.
 @param[out]	*ErrFlags: Pointer to int value, where measuring-value-related error flags given by device are stored. 
 		May be set to NULL, if not used.
 @return Simple errorcode: GSV_OK, if (at least one) buffer is emty and no values were read, or 
 	GSV_TRUE if value(s) were read, or  <br>
 	GSV_ERROR if an (internal) error occurred. <br>
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText(). <br>
  \note: Value-related error flags set by device have no impact on the return value (i.e. *ErrFlags !=0 : return GSV_TRUE)
*
Reads whole array of measuring values in dll-value-buffer(s), if returned GSV_TRUE.  <br>
Reads up to <count> values and writes number of values, which were really read, into <valsread>. <count> must be >0. 
If resulting <valsread> is smaller than <count>, the whole buffer (the smallest, if Chan=0) was read. <br>
If Chan=0: Reads whole Array of all channel-objects into the array of double-type, 
where <out> points to. <count> must be dividible by <NumMappedObjects> (determine NumMappedObjects with GSV86getValObjectInfo). <br>
Assuming Chan=0 and NumMappedObjects=8, <out> is sorted as follows: <br>
Obj1 in n*8, Obj2 in (n*8)+1, Obj3 in (n*8)+2, and so on, Obj8 in (n*8)+7; with n= {0...(<valsread> /8)-1} <br>
Example: Assumed, Chan=0, count >=16 and NumMappedObjects=8, and <valsread> results =16, 
the content of <out> is, beginning with index 0: <br>
oldObj1,oldObj2,...,oldObj8,newObj1,newObj2,...,newObj8 <br>
If Chan={1..NumMappedObjects}: Reads whole Array of specified object. <br>
Oldest value is at index 0 (base) of <out>-array, newest at <valsread>-1.
*
 OrdinalNo: 14
 
 Device access: No

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86readMultiple(int ComNo, int Chan, double *out, int count, int* valsread, int* ErrFlags);

/*!  ****************************************************************************
@brief	Starts GSV-4 value transmission, if stopped before.
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 Remark: starts GSV-4 value transmission. State not saved in device non-volatile memory.
*
 OrdinalNo: 16
 
 Device access: Yes, CmdNo: 0x24

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86startTX(int ComNo);

/*!  ****************************************************************************
@brief	Stopps GSV-4 value transmission, if started before.
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 Remark: stops GSV-4 value transmission. State not saved in device non-volatile memory.
*
 OrdinalNo: 18
 
 Device access: Yes, CmdNo: 0x23

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86stopTX(int ComNo);

/*!  ****************************************************************************
@brief	Close COMport and free all associated dll-ressources
--------------------------------------------------------------------------------------
	Should be called at program (i.e. dll caller'd trmination;
	Must be called before re-opening a GSV-8 at the same COMport

 @param[in] ComNo: 	Number of Device Comport
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 20
 
 Device access: No

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86release(int ComNo);

 
 /*!  ****************************************************************************
@brief	Read device serial number
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return Serial-No or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 70
 
 Device access: Yes, CmdNo: 0x1F

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86getSerialNo(int ComNo);
 
/*!  ****************************************************************************
@brief	Get information Flags on value transmission and command communication
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in]	Index:	=0: Read TXmode-flags. Return value defined as follows:
 			Bit0: =1: Measuring value transmission is temorarily stopped (by GSV86stopTX)
 			      =0: Permanent measuring value transmission active
 			Bit1: =1: Measuring value transmission is stopped (stored in non-volatile memory)
 			    =0: By parameterization (non-volatile memory), permanent value transmission is active
 			Remark: Get this information simplier by calling GSV86isValTXpermanent
 			Bit 6: =1: Serial Port (Ethernet) has no write access
 			       =0: Serial Port (Ethernet) may have write access (depending on other settings)
 			Bit 7: =1: USB Port has no write access
 			       =0: USB Port may have write access (depending on other settings)
 			Remark: Get this information simplier and reliably by calling GSV86getWriteAccess
 		=1: Read measuring value type. Return value defined as follows:
 			=1: Measuring value is a 16-Bit integer in binary offset format, unscaled raw value
 			=2: Measuring value is a 24-Bit integer in binary offset format, unscaled raw value
 			=3: Measuring value is a IEEE754 float, 32 bit size, scaled in physical units
 			Remark: Value type can also be determined with GSV86getValObjectInfo
 		=2: Read input channel numbering information. Return value defined as follows:
 			Bits<7:0>: lowest input channel number (constant =1 for GSV-8 by now)
 			Bits<15:8>: highest input channel number (constant =8 for GSV-8 by now)
 @return Informational value as defined above, or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 22
 
 Device access: Yes, CmdNo: 0x80

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86getTXmode(int ComNo, int Index);

/*!  ****************************************************************************
@brief	Set Value transmission type and flags
--------------------------------------------------------------------------------------
 @param[in] 	ComNo: 	Number of Device Comport
 @param[in]	Index:	=0: Set TXmode-flags.
 		=1: Set measuring value type.
 @param[in]	TXmode: If Index=0 (set TXmode-flags), defined as follows:<br>
 		Bit0: =1: Measuring value transmission is temorarily stopped (not stored in non-volatile memory)<br>
 			Remark: Set this easier by calling GSV86stopTX.<br>
 		      =0: Permanent measuring value transmission active (stored in non-volatile memory).<br>
 		      Remark: Set this easier by calling GSV86startTX.<br>
 		Bit1: =1: Measuring value transmission is stopped (stored in non-volatile memory)<br>
 		      =0: Permanent value transmission is active (stored in non-volatile memory)<br>
 		Remark: Write access bits are read-only.<br>
 		If Index=1 (set measuring value type), defined as follows:<br>
 			=1: Measuring value is a 16-Bit integer in binary offset format, unscaled raw value<br>
 			Remark: Set this easier by calling GSV86setValDataType<br>
 			=2: Measuring value is a 24-Bit integer in binary offset format, unscaled raw value<br>
 			=3: Measuring value is a IEEE754 float, 32 bit size, scaled in physical units<br>
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 24
 
 Device access: Yes, CmdNo: 0x81

  date: 11-19-2014
 ********************************************************************************** */
int CALLTYP GSV86setTXmode(int ComNo, int Index, unsigned long TXmode);

/*!  ****************************************************************************
@brief	Get information on permanent measuring value transmission
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return GSV_OK, if permanet value transmission is actually stopped<br>
 	GSV_TRUE, if permanet value transmission is actually active<br>
 	or GSV_ERROR if function failed<br>
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 28
 
 Device access: Yes, CmdNo: 0x80

  date: 11-19-2014
 ********************************************************************************** */
int CALLTYP GSV86isValTXpermanent(int ComNo);

/*!  ****************************************************************************
@brief	Get information on device parameter write access via this interface
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return GSV_OK, if this interface doesn't have write access<br>
 	GSV_TRUE, if this interface has write access<br>
 	or GSV_ERROR if function failed<br>
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 60
 
 Device access: Yes, CmdNo: 0x26

  date: 11-19-2014
 ********************************************************************************** */
int CALLTYP GSV86getWriteAccess(int ComNo);

/*!  ****************************************************************************
@brief	Set measuring value data type sent by device
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in]	Datatype: Data type enumeration, defines as follows:
 	 DATATYP_INT16	1 Datatype sent by GSV-8 is 16-Bit raw value in binary offset format<br>
	 DATATYP_INT24	2 Datatype sent by GSV-8 is 24-Bit raw value in binary offset format<br>
	 DATATYP_FLOAT	3 Datatype sent by GSV-8 is 32-Bit Float, scaled in physical units<br>
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 62
 
 Device access: Yes, CmdNo: 0x81

  date: 11-19-2014
 ********************************************************************************** */
int CALLTYP GSV86setValDataType(int ComNo, int Datatype);

/*!  ****************************************************************************
@brief	Get GSV-8 firmware version
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return Firmware version:
 	Bits<31:16>: Higher number of firmware version<br>
 	Bits<15:0>: Lower number of firmware version<br>
 	or GSV_ERROR if function failed<br>
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 26
 
 Device access: Yes, CmdNo: 0x2B

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86firmwareVersion(int ComNo);

/*!  ****************************************************************************
@brief	Get measuring value scaling factor
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
  @param[in]   Chan: Number of input channel to get scaling factor. Range: 1..8
  @param[out]   *Norm: Pointer to one variable of type double, where scaling factor is written to.
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed<br>
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().<br>
 \note: Scaling factor and raw measuring value is the float measuring value product,
 	if six-axis sensor is not used.
*
 OrdinalNo: 28
 
 Device access: Yes, CmdNo: 0x14

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86readUserScale(int ComNo, int Chan, double* Norm);

/*!  ****************************************************************************
@brief	Set measuring value scaling factor
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in]	Chan: Number of input channel to set scaling factor. Range: 0..8. 0: set all channels.
 @param[in]	Norm: Scaling factor.
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed<br>
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 30
 
 Device access: Yes, CmdNo: 0x15
 
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86writeUserScale(int ComNo, int Chan, double Norm);

/*!  ****************************************************************************
@brief	Get Mode flags
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return Mode-Flags:
 	 SIX_AXIS_SENSOR_ACTIVE 0x01 Multi-axis sensor used<br>
	 ANALOG_FILTER_AUTO 0x02 Analog input filter cutoff frequency switched automatically<br>
	 MODE_MAXIMUM 0x04 Maximum and minimum values are determined<br>
	 MODE_NOISECUT 0x08 Values around 0 (Noisecut-threshold dependend) are set to 0<br>
	Bit 4: Absolute measuring value used for maximum- and minimum checking<br>
	 ALL_WRITES_BLOCKED 0x80 All write functions are rejected<br>
	Bits <15:8>: Use TEDS for scaling of corresponding channel 8..1<br>
	Bit 16: Set Unit from TEDS (if channel-corresponding Bit in <15:8> set)<br>
	Bit 17: Set Input type from TEDS (if channel-corresponding Bit in <15:8> set)<br>
	Bit 18: Set Output scaling according to TEDS physical range (if channel-corresponding Bit in <15:8> set)<br>
 or GSV_ERROR if function failed<br>
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 32
 
 Device access: Yes, CmdNo: 0x26
 
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86getMode(int ComNo);

/*!  ****************************************************************************
@brief	Set Mode flags
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Mode: Flags for device operation (channel independent or valid for all channels)
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed<br>
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 34
 
 Device access: Yes, CmdNo: 0x27
 
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86setMode(int ComNo, unsigned long Mode);

/*!  ****************************************************************************
@brief	Get Mode: Six-Axis sensor active
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return: GSV_OK,if Six-axis sensor disabled, GSV_TRUE if enabled, or
 GSV_ERROR if function failed<br>
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 134
 
 Device access: Yes, CmdNo: 0x26
 
  date: 30.04.2015 14:14
 ********************************************************************************** */
int CALLTYP GSV86getFTsensorActive(int ComNo);

/*!  ****************************************************************************
@brief	Set Mode: Six-Axis sensor active
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] OnOff: =1 to enable Six-axis sensor, =0 to disable it
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed<br>
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 135 <br>
 Device access: Yes (Cmd. 0x26, 0x27) <br>
  date: 30.04.2015 14:14
 ********************************************************************************** */
int CALLTYP GSV86setFTsensorActive(int ComNo, int OnOff);

/*!  ****************************************************************************
@brief	Get Mode: Automatic selection of Analog filter
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return: GSV_OK,if Analog-filter-auto is disabled, GSV_TRUE if enabled, or<br>
 GSV_ERROR if function failed<br>
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 136
 
 Device access: Yes (Cmd. 0x26)
 
  date: 30.04.2015 14:14
 ********************************************************************************** */
int CALLTYP GSV86getModeAfilterAuto(int ComNo);

/*!  ****************************************************************************
@brief	Set Mode: Automatic selection of Analog filter
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] OnOff: =1 to enable Automatic selection of Analog (anti-aliasing-) filter according to
 	the configured data rate, =0 to disable it
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 137
 
 Device access: Yes (Cmd. 0x26, 0x27)
 
  date: 30.04.2015 14:14
 ********************************************************************************** */
int CALLTYP GSV86setModeAfilterAuto(int ComNo, int OnOff);

/*!  ****************************************************************************
@brief	Get Mode: Noise-cut threshold active
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return: GSV_OK,if Noise-cut threshold disabled, GSV_TRUE if enabled, or<br>
 GSV_ERROR if function failed<br>
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 138
 
 Device access: Yes (Cmd. 0x26)
 
  date: 30.04.2015 14:14
 ********************************************************************************** */
int CALLTYP GSV86getModeNoiseCut(int ComNo);

/*!  ****************************************************************************
@brief	Set Mode: Noise-cut threshold active
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] OnOff: =1 to enable Six-axis sensor, so that measuring values between NoiseCutThreshold 
 	and -NoiseCutThreshold are set to 0.<br>
 	=0: to disable Noise-cut threshold
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed<br>
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 139
 

 Device access: Yes (Cmd. 0x26, 0x27)
 
  date: 30.04.2015 14:14
 ********************************************************************************** */
int CALLTYP GSV86setModeNoiseCut(int ComNo, int OnOff);

/*!  ****************************************************************************
@brief	Get Mode: Maximum / Minimum measuring value determination active
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return: GSV_OK,if Maximum / Minimum mode disabled, GSV_TRUE if enabled, or 
 GSV_ERROR if function failed<br>
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 145
 
 Device access: Yes (Cmd. 0x26)
 
  date: 19.05.2015 22:02
 ********************************************************************************** */
int CALLTYP GSV86getModeMaxMin(int ComNo);

/*!  ****************************************************************************
@brief	Set Mode: Enable Maximum / Minimum measuring value determination
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
@param[in]  OnOff: =1 to enable Maximum / Minimum measuring value determination.<br>
 	Result can be retrieved with GSV86getMaxMinValue. <br>
 	=0: to disable Maximum / Minimum mode
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 146
 
 Device access: Yes (Cmd. 0x26, 0x27)
 
  date: 19.05.2015 22:04
 ********************************************************************************** */
int CALLTYP GSV86setModeMaxMin(int ComNo, int OnOff);

/*!  ****************************************************************************
@brief	Get Information about the masuring value frame
-------------------------------------------------------------------------------------
	Get also info about the measuring value's (read by GSV86read/GSV86readMultiple) interpretation.<br>
	Typically used once before mesuring loop has started and after NormFactor(s)
	or Mode-States had changed.<br>
*
 @param[in] ComNo: 	Number of Device Comport
 @param[out] ScaleFactors: Pointer to array of double with size = 16.<br>
 		If pointer-value is not NULL, the functions writes Factors into 
 		indices 0.. (NumberOfMappedObjects-1), with which 
 		the corresponding measuring value-objects should be multiplied in order to get 
 		values that are scaled in physical units.
 @param[out] ObjMapping: Pointer to array of concatenated enumerations with size = 16.<br>
 		If pointer-value is not NULL, the functions writes into indices 0.. (NumberOfMappedObjects-1)
 		the mapping information of the corresponding measuring-value-objects.<br>
 		This Mapping Info is a quasi-struct and defined as follows:<br>
 		LowByte, Bits<7:0>: Amplifiers input channel-Number of corresponding value-object. 
 			Range is 1 to 8.<br>
 		Bits<15:8>: Value-Type of corresponding value-object, defined as follows:<br>
	 		NORMAL=0x00: The value-object is an actual value<br>
	 		MAX_VAL=0x01:  The value-object is a maximum value<br>
	 		MIN_VAL=0x02:  The value-object is a minimum value<br>
 		Bits<23:16>:<br>
 			Physical type corresponding value-object, defined as follows:<br>
 			0x00: No physical type defined<br>
 			0x01: Force in X direction (mainly with Six-axis sensors)<br>
 			0x02: Force in Y direction (mainly with Six-axis sensors)<br>
 			0x03: Force in Z direction (mainly with Six-axis sensors)<br>
 			0x04: Torque in X direction (mainly with Six-axis sensors)<br>
 			0x05: Torque in Y direction (mainly with Six-axis sensors)<br>
 			0x06: Torque in Z direction (mainly with Six-axis sensors)<br>
 			0x10: Raw value of six-axis sensor (before calculation)<br>
 			0x20: Temparature<br>
 @param[out] DataType: Pointer to one 32-Bit enumeration value.<br>
 		If pointer-value is not NULL, the function writes one of the following 
 		codes for the data type of the measuring values in the value frame sent 
 		by the GSV-8 (the values in the frame have all the same data type):<br>
 		0x01: Data type sent by device is 16-Bit integer value in binary offset format (raw value)<br>
 		0x02: Data type sent by device is 24-Bit integer value in binary offset format (raw value)<br>
 		0x03: Data type sent by device is 32-Bit float value (IEEE754), scaled in physical units<br>
 @return NumberOfMappedObjects: Number of value-objects in the measuring frame, Range: 1 to 16. 
 	Or GSV_ERROR if function failed. 
 If =GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 36
 
 Device access: Yes, CmdNo: 0x26, 0x80, eventually 0x14
 
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86getValObjectInfo(int ComNo, double* ScaleFactors, unsigned long* ObjMapping, int* DataType);

/*!  ****************************************************************************
@brief	Get Value Mapping Info
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Index:	0: number of mapped objects.<br>
 		1..NumberOfMappedObjects: Get Info of corresponding Object in Value-Frame, 
 		whereby 1: first Object in device value frame, which is at Object Index 0 of GSVread
 @return 	if Index=0: number of mapped objects (1..16) or =0: Mapping not present or not supported by device 
 		else if Index= 1..NumberOfMappedObjects:<br>
 		ObjMapping: See description for GSV86getValObjectInfo()<br>
 	 or GSV_ERROR if function failed 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 38
 
 Device access: Yes, CmdNo: 0x49
 
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86getValMapping(int ComNo, int Index);


/*!  ****************************************************************************
@brief	Select FT sensor calibration data array for reading
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] ArrNo: Index of array to select for reading with GSV86readFTsensorCalValue. Range: 0 to 4
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 164
 
 Device access: Yes, CmdNo: 0x7D
 
  date: 05.10.2015 16:07
 ********************************************************************************** */
int CALLTYP GSV86setFTarrayToRead(int ComNo, int ArrNo);

/*!  ****************************************************************************
@brief	Get single calibration value of six-axis sensor calibration
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] typ: One of theses:
 SENSORCAL_TYP_MATRIX_NORM 1 Scaling of calibration matrix. ix must be =0
 SENSORCAL_TYP_MATRIX 2 calibration matrix. ix: 0..35
 SENSORCAL_TYP_OFFSET 3 mechanical offsets of sensor installation. ix: 0:X,1:Y,2:Z, in metres
 SENSORCAL_TYP_MAXVAL 4 maximum values for the 6 outputs. ix:0..5:Fx,Fy,Fz,Mx,My,Mz
 SENSORCAL_TYP_INSENS 5 input sensitivity of origin if calibration matrix. ix must be =0
 SENSORCAL_TYP_ZEROVAL 6 No-load sensor deviations of the 6 inputs. ix: 0..5
 @param[in] ix: Index, if array value, see typ.
 @param[out] val: Pointer to value, where value is written to
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 40 <br>
 Device access: Yes, CmdNo: 0x47 <br>
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86readFTsensorCalValue(int ComNo, int typ, int ix, double* val);
 
/*!  ****************************************************************************
@brief	Get all calibration values for six-axis sensor calibration
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] ArrNo: 0x80: TEDS storage (coming hardware versions), Bits <6:0>: Calibrations structs index, if several
 sensors/calibration data sets are supported
 @param[out] SensorSerNo: pointer to String of 8 number digits: Sensor serial number will be written here
 @param[out] MatrixNorm: ptr to single double value: Scaling of calibration matrix will be written here
 @param[out] InSens: ptr to single double value: input sensitivity of origin if calibration matrix ill be written here
 @param[out] Matrix: ptr to array of 36 double values: Calibration matrix will be written, order: first row 0..5, 2nd row 6..11...
 @param[out] Offsets: ptr to array of 3 double values: mechanical offsets of sensor installation in mmetres. 0..2:Ox,Oy,Oz
 @param[out] MaxVals: ptr to array of 6 double values: maximum values for the 6 outputs. Order: 0..5: Fx,Fy,Fz,Mx,My,Mz
 @param[out] Zvals: ptr to array of 6 double values: No-load sensor deviations of the 6 inputs. Order: 0..5: Fx,Fy,Fz,Mx,My,Mz
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 42
 
 Device access: Yes, CmdNo: 0x47
 
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86readFTsensorCalArray(int ComNo,int ArrNo, char* SensorSerNo,
		double* MatrixNorm, double* InSens,double* Matrix,double* Offsets,double* MaxVals,double* Zvals);

/*!  ****************************************************************************
@brief	Set all calibration values for six-axis sensor calibration
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] ArrNo: Bits <6:0>: Calibrations struct index for storing several sensors/calibration data sets
 @param[in] SensorSerNo: pointer to String of 8 number digits: Sensor serial number read from here
 @param[in] MatrixNorm: single double value: Scaling of calibration matrix
 @param[in] InSens: single double value: input sensitivity of origin if calibration matrix
 @param[in] Matrix: ptr to array of 36 double values: Calibration matrix will be written, order: first row 0..5, 2nd row 6..11...
 @param[in] Offsets: ptr to array of 3 double values: mechanical offsets of sensor installation in mmetres. 0..2:Ox,Oy,Oz
 @param[in] MaxVals: ptr to array of 6 double values: maximum values for the 6 outputs. Order: 0..5: Fx,Fy,Fz,Mx,My,Mz
 @param[in] Zvals: ptr to array of 6 double values: No-load sensor deviations of the 6 inputs. Order: 0..5: Fx,Fy,Fz,Mx,My,Mz
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
Pre-condition: User-Password set (see GSV86setPassword() ) <br>
 OrdinalNo: 44 <br>
 Device access: Yes, CmdNo: 0x48, 0x7F <br>
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86writeFTsensorCalArray(int ComNo, int ArrNo, const char* SensorSerNo,
		double MatrixNorm, double InSens, double* Matrix,double* Offsets,double* MaxVals, double* Zvals);
		
/*!  ****************************************************************************
@brief	Set mechanical offset values for six-axis sensor calibration
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] ArrNo: Bits <6:0>: Calibrations structs index for storing several sensors/calibration data sets
 @param[in] offsets: pointer to double array, which contain the three offsets values, 
 	whereby at index 0: offset in metres in X directin,<br>
 	index 1: offset in metres in Y direction,<br>
 	index 2: offset in metres in X directin.<br>
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
Pre-condition: User-Password set (see GSV86setPassword() ) <br>
 OrdinalNo: 45 <br>
 Device access: Yes, CmdNo: 0x48, 0x7F <br>
  date: 25.04.2015 16:24
 ********************************************************************************** */
int CALLTYP GSV86writeFTsensorGeoOffsets(int ComNo, int ArrNo, double* offsets);

/*!  ****************************************************************************
@brief	Read sensor serial number of six-axis sensor
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] ArrNo: Bits <6:0>: Calibrations structs index for storing several sensors/calibration data sets
 @param[out] SensorSerNo: pointer to String of 8 number digits: Sensor serial number will be written here
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 46 <br>
 Device access: Yes, CmdNo: 0x47 <br>
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86readFTsensorSerNo(int ComNo, int ArrNo, char* SensorSerNo);

/*!  ****************************************************************************
@brief	Set all calibration values for six-axis sensor calibration
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] ArrNo: 0x80: TEDS storage (coming hardware versions), Bits <6:0>: Calibrations structs index for
 storing several sensors/calibration data sets
 @param[in] DatFilePath: String (ptr) to full path of sensor calibration file: "<drive>:\\<path\\<name>.dat"
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 100
 
 Device access: Yes, CmdNo: 0x48, 0x7F
 
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86writeFTsensorFromFile(int ComNo, int ArrNo, const char* DatFilePath);

/*!  ****************************************************************************
@brief	Get Information about Six-axis calibration array data sets
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[out]   *MaxNumSupp: Pointer to int value, where the maximum number of storable six-axis arrays are written
 @param[out]   *ArrNumStored: Pointer to int value, where the number of stored six-axis-arrays are written
 @return: index of active six-axis calibration array (beginning with 0) or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 162
 
 Device access: Yes, CmdNo: 0x54
 
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86getFTsensorCalArrayInfo(int ComNo, int* MaxNumSupp, int* ArrNumStored);

/*!  ****************************************************************************
@brief	Set active Six-axis calibration array
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] ArrNo: Index of six-axis calibration array (beginning with 0) to activate. Range: 0 to 4.
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 163
 
 Device access: Yes, CmdNo: 0x55
 
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86setFTsensorActiveCalArray(int ComNo, int ArrNo);

/*!  ****************************************************************************
@brief	Erase last Six-axis calibration array
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 \note: The 1st array (ArrNo=0) can't be erased,
 	so the minimum number of stored calibration arrays is 2
*
 OrdinalNo: 166
 
 Device access: Yes, CmdNo: 0x7F
 
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86eraseFTsensorCalArray(int ComNo);

/*!  ****************************************************************************
@brief	Get Data rate
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return Measuring data rate or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 48
 
 Device access: Yes, CmdNo: 0x8A
 
  date: 10-31-2014
 ********************************************************************************** */
double CALLTYP GSV86getFrequency(int ComNo);

/*!  ****************************************************************************
@brief	Set Data rate
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] frequency Number of measuringg value frames per second, that the device shall transmit 
            equidistant and permanently
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 50
 
 Device access: Yes, CmdNo: 0x8B
 
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86setFrequency(int ComNo, double frequency);

/*!  ****************************************************************************
@brief	Set Zero. Adjust internal offset values, so that measuring value becomes Zero.
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: if =0: Set all channels to zero. 1..8: Set specified channel to zero.
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 56
 
 Device access: Yes, CmdNo: 0x0C
 
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86setZero(int ComNo, int Chan);

/*!  ****************************************************************************
@brief	Get input type and range, as actually active
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: Number of input channel, 1..8
 @param[out] Range: if not NULL: pointer to one variable of double, where the input range 
 		(sensitivity) is written to. Physical unit of range depends on the  
 		Input Type: Bridge inputs (0..2): mV/V. Single ended (3): V<br>
 		Temperature (4..5): range is meaningless (not applicable)<br>
 @return Input Type, defined as follows:<br>
 	 INTYP_BRIDGE_US875 	0	Input-Type Bridge at Vexcitation=8.75V<br>
	 INTYP_BRIDGE_US5 	1	Input-Type Bridge at Vexcitation=5V<br>
	 INTYP_BRIDGE_US25 	2	Input-Type Bridge at Vexcitation=2.5V<br>
	 INTYP_SE10 		3	Input-Type single-endend +-10V<br>
	 INTYP_PT1000		4	Input-Type Temperature-Sensor PT1000<br>
	 INTYP_TEMP_K		5	Input-Type Temperature-Sensor Type-K<br>
 	or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 64
 
 Device access: Yes, CmdNo: 0xA2
 
  date: 11-18-2014
 ********************************************************************************** */
int CALLTYP GSV86getInTypeRange(int ComNo, int Chan, double* Range);

/*!  ****************************************************************************
@brief	Get all available input types and ranges
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan:	Number of input channel, 1..8
 @param[out] Types: 	If not NULL: pointer to array of int, where the existent input types 
 		are written to. Type definition: see GSV86setInType() (InType)
 @param[out] Ranges: If not NULL: pointer to array of double, where the existent input ranges 
 		(sensitivities) are written to. Meaning depends on corresponding InType, 
 		which has the same index in InTypes array.
 		Array sizes should be #MAX_INPUT_TYPES_NUM
 @return Number of existent input types or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 66
 
 Device access: Yes, CmdNo: 0xA2
 
  date: 11-18-2014
 ********************************************************************************** */
int CALLTYP GSV86getAllInTypesRanges(int ComNo, int Chan, int* InTypes, double* Ranges);

/*!  ****************************************************************************
@brief	Set input type
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: Number of input channel, 1..8
 @param[in] InType: Input type, defined as follows:<br>
 	 INTYP_BRIDGE_US875 	0	Input-Type Bridge at Vexcitation=8,75V<br>
	 INTYP_BRIDGE_US5 	1	Input-Type Bridge at Vexcitation=5V<br>
	 INTYP_BRIDGE_US25 	2	Input-Type Bridge at Vexcitation=2,5V<br>
	 INTYP_SE10 		3	Input-Type single-endend +-10V<br>
	 INTYP_PT1000		4	Input-Type Temperature-Sensor PT1000<br>
  @return 
 	Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 68
 
 Device access: Yes, CmdNo: 0xA3
 
  date: 11-18-2014
 ********************************************************************************** */
int CALLTYP GSV86setInType(int ComNo, int Chan, int InType);

/*!  ****************************************************************************
@brief	Read Offset Value defined by user
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: 1..8: Read offset of specified channel
 @param[out] *Offset: Pointer to double value, where the user offset is wriiten to, if returned GSV_OK. 
 	This value is added by the device to every measuring value, if the device's 
 	measuring value data type is DATATYP_FLOAT
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 72
 
 Device access: Yes, CmdNo: 0x9A
*
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86readUserOffset(int ComNo, int Chan, double* Offset);

/*!  ****************************************************************************
@brief	Write Offset Value
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: if =0: Set offset of all channels to the same value. 1..8: Read offset of specified channel
 @param[in] Offset: Offset value, which is added by the device to every measuring value, if the device's 
 	measuring value data type is DATATYP_FLOAT
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 74
 
 Device access: Yes, CmdNo: 0x9B
*
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86writeUserOffset(int ComNo, int Chan, double Offset);

/*!  ****************************************************************************
@brief	Load Parameters from non-volatile memory
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] DataSetNo: =0: Load settings from previous power-on session
 		=1: Load factory default settings
 		=2..6: Load settings, which were previously stored by user
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

Load all device configuration parameters, previously stored by user (DataSetNo 2..6) 
Exept the following settings, which are NOT part of the user parameter array:<br>

- Interface Communication settings<br>
- Measuring value Type<br>
- Digital FIR/IIR filter configuration itself (but Filter On/Off state is part of user parameter)<br>
- Six-Axis-Sensor configuration itself (but en-/disabled state and active FT-Array-No is part of user parameter)<br>

 OrdinalNo: 76
 
 Device access: Yes, CmdNo: 0x09

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86loadSettings(int ComNo, int DataSetNo);

/*!  ****************************************************************************
@brief	Store Parameters in non-volatile memory
--------------------------------------------------------------------------------------

Saves all device configuration parameters, exept those mentioned in description for GSV86loadSettings()

 @param[in] ComNo: 	Number of Device Comport
 @param[in] DataSetNo: 2..6: Store settings at specified dataset
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
*
 OrdinalNo: 78
 
 Device access: Yes, CmdNo: 0x0A
*
  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86storeSettings(int ComNo, int DataSetNo);

/*!  ****************************************************************************
@brief	Get Analog output type and mode
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: 1..8: Channel number of analog output to read type and mode.
 @param[out] Type: Pointer, where Analog output type enum (@see GSV86setAnalogOutType) is written to.
 @return: Mode as defined above or GSV_ERROR if function failed 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 112
 
 Device access: Yes, CmdNo: 0x0D

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86getAnalogOutType(int ComNo, int Chan, int *Type);

/*!  ****************************************************************************
@brief	Set Analog output type and mode
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
@param[in] Chan: 0..8: Channel number of analog output to change type and mode.<br>
		A value of 0 means that all outputs are set to the same type/mode.
@param[in] Type: Analog output type enum as follows:<br>
		 AOUT_TYPE_0_10V 0	 0..10V <br>
		 AOUT_TYPE_10_10V 1	 -10..10V <br>
		 AOUT_TYPE_0_5V 2	 0..5V <br>
		 AOUT_TYPE_5_5V 3	 -5..5V <br>
		 AOUT_TYPE_4_20A 4	 4..20mA <br>
		 AOUT_TYPE_0_20A 6	 0..20mA <br>
@param[in] Mode: Flag value as follows: <br>
		 AOUT_ACTIVE_M_VALUES 0 Output is on and follows the corresponding 
				measuring value input. <br>
		 AOUT_MODE_DIRECT 1 Output is on, but does NOT react on measuring values, 
			but is direcly settable with GSV86writeAoutDirect <br>
		 AOUT_MODE_OFF 2 Output is off and high-impedance. <br>
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 114
 
 Device access: Yes, CmdNo: 0x0E

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86setAnalogOutType(int ComNo, int Chan, int Type, int Mode);


/*!  ****************************************************************************
@brief	Write Analog output offset value
--------------------------------------------------------------------------------------
Write Offset value of analog output. 
This voltage (or current) then represents a measuring value =0. <br>
The analog output scaling value is adjusted as follows: Scaling= FSval*(1-(Offset/100))

 @param[in] ComNo: 	Number of Device Comport
@param[in] Chan: 1..8: Channel number of analog output to change offset
@param[in] Offset: Value in percentage of positive full-scale value FSval. Range: -60%..60% 
	FSval is:  Output type:	0 & 1: 	10V
				2 & 3: 	5V
				4:	12mA
				6:	10 mA
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 104
 
 Device access: Yes, CmdNo: 0x05

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86writeAnalogOutOffset(int ComNo, int Chan, double Offset);

/*!  ****************************************************************************
@brief	Read Analog output offset value
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
@param[in] Chan: 1..8: Channel number of offset value to read
@param[out] Offset: Pointer, where function will write the Offset value in percentage of
	positive full-scale value. See above.
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 102
 
 Device access: Yes, CmdNo: 0x04

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86readAnalogOutOffset(int ComNo, int Chan, double *Offset);


/*!  ****************************************************************************
@brief	Read Analog output scaling value
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
@param[in] Chan: 1..8: Channel number of scale value to read
@param[out] Scale: Pointer, where function will write the scaling value. <br>
	This is a factor representing the deviation of the output range based on the type. 
	A scaling value of 1.0 will result in the positive full-scale voltage or current 
	at the output if the Offset is =0 and the measuring value is either 
	the input full range value (based on the input type) or the sensor maximum value 
	(with six-axis sensors).
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 106
 
 Device access: Yes, CmdNo: 0x06

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86readAnalogOutScale(int ComNo, int Chan, double *Scale);

/*!  ****************************************************************************
@brief	Write Analog output scaling value
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
@param[in] Chan: 1..8: Channel number of scale value to write
@param[in] Scale: Desired scaling value. 
	This is a factor representing the deviation of the output range based on the type.
	See GSV86readAnalogOutScale(). 
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 108
 
 Device access: Yes, CmdNo: 0x07

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86writeAnalogOutScale(int ComNo, int Chan, double Scale);

/*!  *****************************************************************************
@brief	Set Analog output voltage / current directly by DAC code
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
@param[in] Chan: 1..8: Channel number of analog output to set
@param[in] Code: 16-Bit DAC code, nominally as follows: <br>
	0x0000: -11 V for -10..10 and 0..10 V output type <br>
		0 mA for current output <br>
	0x8000: 0V for voltage output <br>
	0xFFFF: 11 V or 5.5V for voltage, 24mA for current output <br>
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 \note: Corresponding analog output must be in direct mode. See GSV86setAnalogOutType

 OrdinalNo: 110
 
 Device access: Yes, CmdNo: 0x08

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86writeAoutDirect(int ComNo, int Chan, int Code);

/*!  ****************************************************************************
@brief	Get fixed unit number
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
@param[in] Chan: 1..8: Channel number of unit number to read
 @return Unit-number. For assignment of codes 0..UNIT_NO_MAX to unit itself, see manual / annex. <br>
 	special codes: 0x000000FF: User definable unit text 1 active <br>
 			0x000000FE: User definable unit text 2 active <br>
 	or GSV_ERROR if function failed 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 80
 
 Device access: Yes, CmdNo: 0x0F

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86getUnitNo(int ComNo, int Chan);

/*!  ****************************************************************************
@brief	Set fixed unit number
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: If =0: Set unit-no. of all channels to the same value. 1..8: Set Unit-no specified channel
@param[in] UnitNo: Number of unit to set. <br>
 	For assignment of codes 0..UNIT_NO_MAX to unit itself, see manual/annex. <br>
 	special codes: 0x000000FF: User definable unit text 1 active <br>
 			0x000000FE: User definable unit text 2 active
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed
 	or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 82
 
 Device access: Yes, CmdNo: 0x10

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86setUnitNo(int ComNo, int Chan, int UnitNo);

/* Constants for GSV86getUnitText and GSV86setUnitText */
#define UNIT_WIDTH 8	/* maximum width of unit text array incl. termination*/
/* Bits<7:0> of Code parameter. Can be ORed with Bit<23:8> constants */
#define ACTIVE_UNIT_ANY 0x00 /*GSV86getUnitText: Read active unit. GSV86setUnitText: Set and activate any unit */
#define USER_UNIT_1 0x01 /*GSV86getUnitText: Read user defined unit string 1. 
			GSV86setUnitText: Set and activate user defined unit string 1. */
#define USER_UNIT_2 0x02 /*GSV86getUnitText: Read user defined unit string 2. 
			GSV86setUnitText: Set and activate user defined unit string 2. */
#define SET_FIXED_UNIT	0x10 /*GSV86setUnitText: Set and activate fixed unit (UnitNo set) */
#define WRITE_USER_UNIT_1 0x11 /*GSV86setUnitText: Write user unit string 1 (not activated) */
#define WRITE_USER_UNIT_2 0x12 /*GSV86setUnitText: Write user unit string 2 (not activated) */
/*!  ****************************************************************************
@brief	Get unit text string
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: 1..8: Channel number of active unit text to read
 @param[in] code: Control value, consisting of unit type (Bits <7:0> and code page value (Bits <23:8>) <br>
		Bits <23:8>: Code page. Only used if unit set by UnitNo (Bits<7:0>=0). Supported values: <br>
		ANSI_CODEPAGE =0x0000: ANSI 8-bit <br>
		ASCII_ONLY 0x0001: Strictly 7-Bit ASCII only (micro sign ->'u', degree sign left away, per mille->0/00)  <br>
		DOS_CODEPAGE_437 0x01B5 (437d): Windows/DOS codepage 437 <br>
		WIN_CODEPAGE_1252 0x04E4 (1252d): Windows codepage 1252 <br>
		Bits<7:0>: Unit type to read: <br>
		ACTIVE_UNIT_ANY =0: Read active unit (as set by unit-no, see GSV86getUnitNo) <br>
	      	USER_UNIT_1 =1: Read user-defined unit string number 1 (Chan ignored) <br>
	      	USER_UNIT_2 =2: Read user-defined unit string number 2 (Chan ignored) <br>
@param[out] UnitText: Poiner to char array: Unit-Text to read, ANSI-coded. 
	Must be at least 8 chars in length
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed 
 	or GSV_ERROR if function failed
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 84
 
 Device access: Yes, CmdNo: 0x0F and eventually 0x11

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86getUnitText(int ComNo, int Chan, int Code, char* UnitText);

/*!  ****************************************************************************
@brief	Set unit text string
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
@param[in]     Chan: If =0: Set unit of all channels to the same value. 1..8: Set Unit of specified channel
@param[in]     code: Control value, consisting of unit type (Bits <7:0> and code page value (Bits <23:8>) <br>
	Bits <23:8>: Code page for interpreting UnitText. Only used if Bits<3:0>=0. Supported values: <br>
	ANSI_CODEPAGE =0x0000: ANSI 8-bit <br>
	ASCII_ONLY 0x0001: Strictly 7-Bit ASCII only (micro sign ->'u', degree sign left away or ^, per mille->0/00)  <br>
	DOS_CODEPAGE_437 0x01B5 (437d): Windows/DOS codepage 437 <br>
	WIN_CODEPAGE_1252 0x04E4 (1252d): Windows codepage 1252 <br>
	Bits<7:0>: Storing method: <br>
	ACTIVE_UNIT_ANY =0x00: If unit text corresponds to an available fixed unit, that one is activated (UnitNo set accordingly). <br>
	Otherwise, user-defined unit string is written to the device at Unit-Text 1 and activated (UnitNo set to 0xFF) <br>
	USER_UNIT_1 =0x01: User-defined unit string is written to the device at Unit-Text 1 and activated (UnitNo set to 0xFF) <br>
	USER_UNIT_2 =0x02: User-defined unit string is written to the device at Unit-Text 2 and activated (UnitNo set to 0xFE) <br>
	SET_FIXED_UNIT =0x10: If unit text corresponds to an available fixed unit, that one is activated (UnitNo set accordingly). <br>
	Otherwise, nothing is set and an error is triggered. <br>
	WRITE_USER_UNIT_1 =0x11: User-defined unit string is written to the device at Unit-Text 1, but not activated (UnitNo not set) <br>
	WRITE_USER_UNIT_2 =0x12: User-defined unit string is written to the device at Unit-Text 2 but not activated (UnitNo not set) <br>
 @param[in] UnitText: Poiner to string with Unit-Text to set. 
		Maximum text-length is 7 chars
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 \remark: There're only two user-defined unit strings avaliable on the device (length is up to 7 chars each),
 	 while the UnitNo is stored for each of the 8 input channels individually.

 OrdinalNo: 86
 
 Device access: Yes, CmdNo: 0x0F, 0x10 or 0x12

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86setUnitText(int ComNo, int Chan, int Code, char* UnitText);

/*!  ****************************************************************************
@brief	Get Digital Filter enabled / disabled
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: If =0: Get Filter On/Off of all channels. 1..8: Get Filter On/Off of specified channel
 @param[in] Type: 	=0=FILT_TYPE_IIR: Get on/off state for the IIR filter. <br>
 		=0x80=FILT_TYPE_FIR: Get on/off state for the FIR filter.
 @return On/Off state(s): If Chan=0: On/Off state in Bits<7:0>, Bit=1: Filter enabled, =0: disabled;  <br>
 				   while bit 0 corresponds to channel 1, ..., bit 7 to channel 8
 			  If Chan = 1..8: Get Filter on/off state of specified channel: <br>
 			  	=1=GSV_TRUE: Filter enabled, =0=GSV_OK: Filter disabled <br>
 	or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 88
 
 Device access: Yes, CmdNo: 0x51

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86getDfilterOnOff(int ComNo, int Chan, int Type);

/*!  ****************************************************************************
@brief	Enable / disable Digital Filter
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: If =0: Set Filter On/Off for all channels. 1..8: Set Filter On/Off for specified channel
 @param[in] Type: 	=0=FILT_TYPE_IIR: Set on/off state for the IIR filter. <br>
 		=0x80=FILT_TYPE_FIR: Set on/off state for the FIR filter.
@param[in] OnOff: If Chan=0: On/Off state in Bits<7:0>, Bit=1: Filter enabled, =0: disabled; <br>
 				   while bit 0 corresponds to channel 1, ..., bit 7 to channel 8 <br>
 		If Chan = 1..8: Set Filter on/off state for specified channel: <br>
 			  	=1=GSV_TRUE: Filter enabled, =0=GSV_OK: Filter disabled <br>
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 90
 
 Device access: Yes, CmdNo: 0x52

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86setDfilterOnOff(int ComNo, int Chan, int Type, int OnOff);

/*!  ****************************************************************************
@brief	Get Digital Filter Information
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: 1..8: Get Filter Info for specified channel
 @param[in] TypeIn: =0=FILT_TYPE_IIR: Get Filter Info for the IIR filter. <br>
 		=0x80=FILT_TYPE_FIR: Get Filter Info for the FIR filter.
 @param[out] TypeOut: Type of filter. Bit7: =0: IIR, =1: FIR <br>
 		Bits<6:4>: =0: Low pass, =1: high pass, =2: band pass, =3: band stop <br>
 		Bits<3:0>: Filter order (as by now, 4 for IIR, 4..14 for FIR) <br>
 		See constant macros above (FILT_TYPE_<I/F>IR_<LP/HP/BP/BS>)
@param[out] CutOff*: Pointer to double array of min. size=2. At array index 0, the lower -3dB Cutoff <br>
		frequency will be written. With filter types Band pass and band stop, <br>
		at array index 1, the higher -3dB Cutoff frequency will be written. <br>
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
@note CutOff frequencies depend on data frequency. They are internally stored as ratio FcutOff/Fdata

 OrdinalNo: 92
 
 Device access: Yes, CmdNo: 0x8A, 0x4B, 0x4D

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86getDfilterInfo(int ComNo, int Chan, int TypeIn, int* TypeOut, double* CutOff);

/*!  ****************************************************************************
@brief	Get Digital Filter Type and order
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: 1..8: Get Filter Type for specified channel
 @param[in] TypeIn: =0=FILT_TYPE_IIR: Get Filter Type for the IIR filter. <br>
 		=0x80=FILT_TYPE_FIR: Get Filter Type for the FIR filter.
 @return
 	Type of filter. Bit7: =0: IIR, =1: FIR <br>
 		Bits<6:4>: =0: Low pass, =1: high pass, =2: band pass, =3: band stop <br>
 		Bits<3:0>: Filter order (as by now, 4 for IIR, 4..14 for FIR) <br>
 		See constant macros above (FILT_TYPE_<I/F>IR_<LP/HP/BP/BS>) <br>
 	or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 93
 
 Device access: Yes, CmdNo: 0x4B

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86getDfilterType(int ComNo, int Chan, int TypeIn);

/*!  ****************************************************************************
@brief	Get Digital Filter Coefficients
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: 1..8: Get Filter Coefficients for specified channel
 @param[in] Type: =0=FILT_TYPE_IIR: Get Filter Coefficients for the IIR filter. <br>
 		=0x80=FILT_TYPE_FIR: Get Filter Coefficients for the FIR filter.
 @param[out] Coeff*: Pointer to double array of min. size =8. With IIR filter, at the first 5 places 
 		the a coefficients a0..a4 will be stored, with a0 at index 0. <br>
 		With FIR filter, the 8 FIR coefficients will be stored.
 @param[out] CoeffB*: Pointer to double array of min. size =4. Only with IIR filter, at the first 4 places 
 		the b coefficients b0..b3 will be stored, with b0 at index 0. Can be NULL with FIR filter.
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 94
 
 Device access: Yes, CmdNo: 0x4F

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86getDfilterCoeff(int ComNo, int Chan, int Type, double* Coeff, double* CoeffB);

/*!  ****************************************************************************
@brief	Set Digital Filter Parameters
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: 0..8: If =0: Set Filter Params for all channels. Else: Set Filter Params for specified channel
 @param[in] Type: 	Type of filter. Bit7: =0: IIR, =1: FIR <br>
 		Bits<6:4>: =0: Low pass, =1: high pass, =2: band pass, =3: band stop <br>
 		Bits<3:0>: Filter order (as by now, 4 for IIR, 7 for FIR allowed) <br>
 		See constant macros (FILT_TYPE_<I/F>IR_<LP/HP/BP/BS>)
 @param[in] CutRatio*: Pointer to double array of min. size=2. At array index 0, the (lower) -3dB Cutoff 
		frequency ratio FcutOff,low/Fdata is expected. With filter types Band pass and Band stop, 
		at array index 1, the higher -3dB Cutoff frequency ratio FcutOff,up/Fdata is expected.
 @param[in] Coeff*: Pointer to double array of min. size =5. With IIR filter, 
 		the a coefficients a0..a4 are expected, with a0 at index 0. <br>
 		With FIR filter, the first 4 FIR coefficients are expected, with a0=a7 at index 0, a1=a6 at ix.2 .. a3=a4 at ix.3.
 @param[in] CoeffB*: Pointer to double array of min. size =4. Only with IIR filter, at the first 4 places 
 		the b coefficients b0..b3 are expected, with b0 at index 0. Can be NULL with FIR filter.
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 \note: The effectivity and quality of the filter is NOT tested! The user is expected to have calculated 
 	the coefficients appropriately in regard to the required cutoff frequency and filter type. 
 	Wrong coeefficients can result in instable and unpredictable bahaviour of the filter, i.e. 
 	erratic measuring values! <br>
 	In order to get safe results, use GSV86calcSetDfilterParams instead!

 OrdinalNo: 96
 
 Device access: Yes, CmdNo: 0x4E, 0x50, 0x7E

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86setDfilterParams(int ComNo, int Chan, int Type, double* CutRatio, double* Coeff, double* CoeffB);

/*!  ****************************************************************************
@brief	Calculate and set Digital Filter Parameters
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: -1,0..8: If =0: Set Filter On/Off for all channels. Else: get Filter Coefficients for specified channel <br>
 		If =-1: Do not write filter parameters to device. DLL stores Coefficients internally, e.g. for analysis (coming dll version)
 @param[in] Type: 	Type of filter. Bit7: =0: IIR, =1: FIR <br>
 		Bits<6:4>: =0: Low pass, =1: high pass, =2: band pass, =3: band stop <br>
 		Bits<3:0>: Filter order (as by now, 4 for IIR, 7 for FIR allowed) <br>
 		See constant macros above (FILT_TYPE_<I/F>IR_<LP/HP/BP/BS>)
 @param[in] CutOff: -3dB cutoff frequency. With types band pass and band stop, this is the lower cut off frequency.
 @param[in] CutOffHi: Higher -3dB cutoff frequency. Only used for types band pass and band stop.
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 Additional possible error codes: <br>
  DF_ERR_NO_CONVERGENCE 0x30000203 coefficient calculation failed to converge <br>
  DF_ERR_COEFF_SUM_TOOBIG 0x30000208 coefficients are too big <br>

 OrdinalNo: 98
 
 Device access: Yes, if Chan > -1, CmdNo: 0x4E, 0x50, 0x7E

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86calcSetDfilterParams(int ComNo, int Chan, int Type, double CutOff, double CutOffHi);

/*!  ****************************************************************************
	Digital Filter time-domain simulation
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Analyze_Ftyp: one of <br>
 		SIMUL_DFILT_FREQ_RESPONSE get Frequency response <br>
 		SIMUL_DFILT_STEP_RESPONSE get step response <br>
 		To simulate FIR filter, OR with FILT_TYPE_FIR
 @param[in] StartVal: First frequency if Analyze_Ftyp=SIMUL_DFILT_FREQ_RESPONSE <br>
 		Start value (before step) if Analyze_Ftyp=SIMUL_DFILT_STEP_RESPONSE (standard step: =0)
 @param[in] EndVal: Last frequency if Analyze_Ftyp=SIMUL_DFILT_FREQ_RESPONSE <br>
 		Step value (after step) if Analyze_Ftyp=SIMUL_DFILT_STEP_RESPONSE (standard step: =1)
 @param[in] Fa:	Sampling frequency = Data rate
 @param[in] Points: Number of simulated points (frequencies or samples, respective)
 @param[in] Filepath: Full path to file, where results are written to. File should not exist before;
 		otherwise, it will be overwritten.
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 Additional possible error codes: <br>
  DF_ERR_NOT_INIT 0x30000201 GSV86calcSetDfilterParams not called before <br>
  DF_ERR_OPT_WRONG 0x30000202 wrong parameters <br>
  DF_ERR_NO_CONVERGENCE 0x30000203 coefficient calculation failed to converge <br>
  DF_ERR_COEFF_SUM_TOOBIG 0x30000208 coefficients are too big <br>

 \note: GSV86calcSetDfilterParams must be called before.
 	There, Chan can be set to -1 for simulation only (no device access).

 OrdinalNo: 99
 
 Device access: No

  date: 3-6-2015
 ********************************************************************************** */
int CALLTYP GSV86simulateDfilter(int ComNo, int Analyze_Ftyp, double StartVal, double EndVal, double Fa, int Points, char* Filepath);

/*!  ****************************************************************************
@brief	Get device working hours
--------------------------------------------------------------------------------------
 @param[in] 	ComNo: 	Number of Device Comport
 @param[in]	Index: =0: Get absolute Device working hours (not resettable) <br>
 		=1: Get relative (settable) device working hours
 @return: Hours, which the device was switched on or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 116
 
 Device access: Yes, CmdNo: 0x56

  date: 26-02-2015
 ********************************************************************************** */
double CALLTYP GSV86readDeviceHours(int ComNo, int Index);

/*!  ****************************************************************************
@brief	Set device hours
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Hours: Hours to set. Device will increment value by minutes and store in non-volatile memory.
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 117
 
 Device access: Yes, CmdNo: 0x57

  date: 26-02-2015 
 ********************************************************************************** */
int CALLTYP GSV86writeDeviceHours(int ComNo, double Hours);

/*!  ****************************************************************************
@brief	Get Threshold for the noise cut
--------------------------------------------------------------------------------------
 If corresponding flag in Mode is set (see GSV86setMode() ), the device will set measuring values below this threshold 
	(but above -1*threshold) to the zero value.

 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: 1..8: Get noise cut thershold for specified channel
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 118
 
 Device access: Yes, CmdNo: 0x94

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86getNoiseCutThreshold(int ComNo, int Chan, double* Thres);
 
/*!  ****************************************************************************
@brief	Set Threshold for the noise cut
--------------------------------------------------------------------------------------
 If corresponding flag in Mode is set (@see GSV86setMode), the device will set measuring values below this threshold 
	(but above -1*threshold) to the zero value.
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: 0..8: Set noise cut thershold for specified channel.
 		0 means: all channels to the same value
 @param[in] Thres: Noise cut thershold in percentage of the full scale range.
 		Value range is: 0.001% to 20%
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 120
 
 Device access: Yes, CmdNo: 0x95

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86setNoiseCutThreshold(int ComNo, int Chan, double Thres);

/*!  ****************************************************************************
@brief	Get Flag value of device capabilities
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return: Flags: <br>
 	Bit 0: HAS_ADC Has analog-digital converter <br>
 	Bit 1: HAS_ETHERCAT Has EtherCat fieldbus <br>
 	Bit 2: HAS_LCD Has LC-Display <br>
 	Bit 3: HAS_TEDS Has TEDS sensor reading capability <br>
 	Bit 4: HAS_DIGI_IO Has digital inputs and outputs <br>
 	Bit 5: HAS_ETH_TWOLEDS Ethercat with separated status-LED (DS housing) <br>
 	Bit 6: HAS_ANALOG_OUT Has analog output(s) <br>
 	Bit 7: HAS_SERIAL Has serial interface <br>
 	Bit 8: HAS_FREQ_OUT Has frequency output <br>
 	Bit 9: HAS_AIN_MCU Has Coprocessor for analog input <br>
 	Bit 10: HAS_SIXAXIS Supports six-axis sensor <br>
 	Bit 11: HAS_CANOPEN Has CANopen fieldbus <br>
 	or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 122
 
 Device access: Yes, CmdNo: 0x2A

  date: 10-31-2014
 ********************************************************************************** */
int CALLTYP GSV86getSoftwareConfiguration(int ComNo);

/*!  ****************************************************************************
@brief	Set special property for measuring values
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] PropType: =0: Set special value properties off, so that normal mesuring mode is enabled again <br>
	=1: Set simulated value on, so that all readouts of all channels 
	become equal to half of the full-scale value ("calibration jump") <br>
	Remark: This state is volatile (not saved in EEPROM memory) <br>
	=2: Load Zero calibration values, so that measuring values give the 
	no-load sensor deviation. <br>
	=3: Load Zero calibration values of first six-axis sensor, so that measuring values give the 
	(no-load) sensor deviation.
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 124
 
 Device access: Yes (Cmd. 0x35)

  date: 3-9-2015 war GSV86setSimulatedValue
 ********************************************************************************** */
int CALLTYP GSV86setMeasValProperty(int ComNo, int PropType);

/*!  ****************************************************************************
@brief	Get value error information
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Ix: =0: Get number of Error events stored in Memory as return value. <br>
 		If >=1: First Error (number) is a recent one, stored in memory, accessible by index 1. <br>
 		>=2: Error(s) stored in memory, accessible from index 2 on, up to <Number of Errors< + 1. <br>
 	Ix=1: Get recent Error: Writes error flags to *ErrInfo and device hours, when error occurred to *ErrTime. <br>
 	Ix= 2..<Number of errors +1>: get Error(s) stored in memory (see annex)
 @param[out] *ErrInfo: Pointer to Int value, where Error Flags are written to 
 @param[out] *ErrTime Pointer to Double value, where device hours, when error occurred is written to .
 @return Number of errors stored, if Ix =0, otherwise: <br>
 	Errortype: <br>
 	 VALERR_TYPE_SATURATED 1 Measuring value saturated <br>
	 VALERR_TYPE_MAX_EXCEED 2 For 6-axis sensors: Maximum exceedance <br>
	 VALERR_TYPE_SENSOR_BROKEN 3 Sensor or sensor cable broken <br>
	HWERR_TYPE_ANA_OUT 4 Analog output connection error (e.g. current output open) <br>
	HWERR_TYPE_DIO 5 Digital output error (shorted) <br>
 	or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
\note: refer to Manual Appendix for Error Flag coding

 OrdinalNo: 126
 
 Device access: Yes, CmdNo: 0x43

  date: 09.04.2015 16:15
 ********************************************************************************** */
int CALLTYP GSV86getValueError(int ComNo, int Ix, int* ErrInfo, double *ErrTime);

/*!  ****************************************************************************
@brief	Erase value error memory
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 128
 
 Device access: Yes, CmdNo: 0x44

  date: 09.04.2015 16:15
 ********************************************************************************** */
int CALLTYP GSV86eraseValueErrMemory(int ComNo);

/*!  ****************************************************************************
@brief	Reset Error state
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

\note: resets volatile (temporary) error state. Does not erase fault memory.
 OrdinalNo: 140
 
 Device access: Yes (Cmd. 0x00)

  date: 09.04.2015 16:15
 ********************************************************************************** */
int CALLTYP GSV86resetErrorState(int ComNo);

/*!  ****************************************************************************
@brief	Get analog filter cutoff frequency
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[out] CutOffFreq* pointer to double value where cutoff frequency of analog input filter is written to
 @return GSV_TRUE, if cutoff frequency is set by device automatically, according to the 
 data rate (see device manual). 
 GSV_OK, if automatic filter setting is disabled or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 128
 
 Device access: Yes, CmdNo: 0x90

  date: 16.04.2015 12:12
 ********************************************************************************** */
int CALLTYP GSV86readAnalogFilterCutOff(int ComNo, double* CutOffFreq);

/*!  ****************************************************************************
@brief	Set analog filter cutoff frequency
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] CutOffFreq Desired cutoff frequency of analog input filter. <br>
 	Set to 0, to enable automatic cutoff frequency setting (accoring to data rate). <br>
 	Otherwise, only 3 fixed cutoff frequency values will be set, closest to parameter CutOffFreq: <br>
 	If CutOffFreq <= FDATA_MAX_FG28HZ: ANAFILT_LOW will be set, otherwise: <br>
 	If CutOffFreq <= FDATA_MAX_FG1KHZ: ANAFILT_MID will be set. See macros above. <br>
@return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 @return GSV_TRUE, if cutoff frequency is set by device automatically, according to the 
 data rate (see below).
 GSV_OK, if automatic filter setting is disabled or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 128
 
 Device access: Yes, CmdNo: 0x26, 0x27 or 0x91

  date: 16.04.2015 12:12
 ********************************************************************************** */
int CALLTYP GSV86writeAnalogFilterCutOff(int ComNo, double CutOffFreq);

/*!  ****************************************************************************
@brief	Read digital zero raw value
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in]  Chan: 1..8: channel to read zero value
 @return Offset-zero raw value or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 141
 
 Device access: Yes, CmdNo: 0x02

  date: 16.04.2015 12:12
 ********************************************************************************** */
int CALLTYP GSV86readZeroValue(int ComNo, int Chan);

/*!  ****************************************************************************
@brief	Write digital zero raw value
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: 1..8: channel to write zero value
 @param[in] zero: Zero raw value, represented as a signed integer value of 16 or 24 bits magnitude, 
 	depending on the measuring value type
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 
 OrdinalNo: 142
 
 Device access: Yes, CmdNo: 0x03

  date: 16.04.2015 12:12
 ********************************************************************************** */
int CALLTYP GSV86writeZeroValue(int ComNo, int Chan, int zero);

/*!  ****************************************************************************
@brief	Get ID level, according to password / PIN set
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return ID level: 0: no password set <br>
 		   >=8: User password set <br>
 		   or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 143
 
 Device access: Yes, CmdNo: 0x1A

  date: 16.04.2015 12:12
 ********************************************************************************** */
int CALLTYP GSV86getIDlevel(int ComNo);

/*!  ****************************************************************************
@brief	Trigger sending of one measuring value frame
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 \note: Retrieve measuring value frame with GSVread

 OrdinalNo: 144
 
 Device access: Yes, CmdNo: 0x3B

  date: 16.04.2015 12:12
 ********************************************************************************** */
int CALLTYP GSV86triggerValue(int ComNo);

/*!  ****************************************************************************
@brief	Get maximum and Minimum value
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: 0..8: Get maximum and Minimum value of specified channel <br>
 		0 means: Get values of all measuring objects (8 channels, respective): <br>
 		If =0: *MaxValue and *MinValue must point to array of (at least) 
 		double[8] size
 @param[out] *MaxValue: pointer to single value of double type (Chan>0), where maximum measuring 
 	value will be written to.
 @param[out] *MinValue: pointer to single value of double type (Chan>0), where minimum measuring 
 	value will be written to.
@return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 \note: Precondition: Maximum/Minimum Mode activated in device: GSV86getModeMaxMin must
 	return GSV_TRUE

 OrdinalNo: 142
 
 Device access: Yes (Cmd 0x53)

  date: 16.04.2015 12:12
 ********************************************************************************** */
int CALLTYP GSV86getMaxMinValue(int ComNo, int Chan, double* MaxValue, double* MinValue);

/*!  ****************************************************************************
@brief	Clear maximum and Minimum value
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] Chan: 0..8: Channel to clear maximum and minimum value. 0: clear for all channels
 @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 148
 
 Device access: Yes (Cmd 0x3C)

  date: 16.04.2015 12:12
 ********************************************************************************** */
int CALLTYP GSV86clearMaxMinValue(int ComNo, int Chan);

/*!  ****************************************************************************
@brief	See, if command number (range) is available
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] CmdUp: Higher command number of command number range to check 
 	(may be equal to CmdLo, if only one command is to be checked)
 @param[in] CmdLo: Lower command number of command number range to check
  @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 146
 
 Device access: Yes, CmdNo: 0x93

  date: 16.04.2015 12:12
 ********************************************************************************** */
int CALLTYP GSV86getIsCmdAvailable(int ComNo, int CmdUp, int CmdLo);

/*!  ****************************************************************************
@brief	Enable / disable write protection of device
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] OnOff: =0: Disable write protection, =1: Enable  write protection
  @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
\note: Pre-condition: User-Password set (see GSV86setPassword() ) <br>
 OrdinalNo: 150
 
 Device access: Yes, CmdNo: 0x92

  date: 16.04.2015 12:12
 ********************************************************************************** */
int CALLTYP GSV86switchBlocking(int ComNo, int OnOff);

/*!  ****************************************************************************
@brief	Change User password
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] NewPW: Char-String to new user password. Must be 4 chars long.
  @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 \note: Pre-condition: Old user password given with GSV86setPassword

 OrdinalNo: 151
 
 Device access: Yes, CmdNo: 0x58

  date: 16.04.2015 12:12
 ********************************************************************************** */
int CALLTYP GSV86changePassword(int ComNo, char* NewPW);

/*!  ****************************************************************************
@brief	Set User password
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] NewPW: Char-String to user password. Default is: "Beln"
  @return Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 
 OrdinalNo: 52
 
 Device access: Yes, CmdNo: 0x19

  date: 18.06.2015 11:29
 ********************************************************************************** */
int CALLTYP GSV86setPassword(int ComNo, char* password);

/*!  ****************************************************************************
@brief	Get digital IO direction
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] 	DIOgroup: The 16 digital IO lines are assigned to 4 groups, whose data direction 
 		can only be changed for that group of 4 IO lines. <br>
 		Assignment is as follows: <br>
 		GroupNo		DIOno	BitNo in returnVal, if DIOgroup=0 <br>
 		1		1..4	0 <br>
 		2		5..8	1 <br>
 		3		9..12	2 <br>
 		4		13..16	3 <br>
 		If DIOgroup is =0, all 4 direchtions are returned in Bits>3:0>.
  @return: Data direction: GSV_TRUE (=1) for Input and GSV_OK (=0) for output <br>
  or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 
 OrdinalNo: 152
 
 Device access: Yes, CmdNo: 0x59

  date: 18.06.2015 11:29
 ********************************************************************************** */
int CALLTYP GSV86getDIOdirection(int ComNo, int DIOgroup);

/*!  ****************************************************************************
@brief	Set digital IO direction
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] DIOgroup: See GSV86getDIOdirection(). <br>
 		If DIOgroup is =0, all 4 directions are set according to Bits<3:0> of Direction
 @param[in] Direction: =0 for output or =1 for input
  @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 153
 
 Device access: Yes, CmdNo: 0x5A

  date: 18.06.2015 11:29
 ********************************************************************************** */
int CALLTYP GSV86setDIOdirection(int ComNo, int DIOgroup, int Direction);

/*!  ****************************************************************************
@brief	Get digital IO type
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] DIOno: Number of digital IO line 1..16.
 @param[out] *AssignedChan: Pointer to int value, where the assigned channel 1..8 is written to, but only 
 	if DIOtype= ThresholdSwitch (DIO_OUT_THRESHOLD_ANYVAL Bit set) or DIO_IN_TARE_SINGLE.
  @return DIOtype: <br>
  	 DIO_IN_GENERALPURPOSE 0x04 <br>
  	 DIO_IN_SYNC_SLAVE 0x02 <br>
	 DIO_IN_QEI_ANY 0x08 <br>
	 DIO_IN_TARE_SINGLE 0x10 <br>
	 DIO_IN_TARE_ALL 0x20 <br>
	 DIO_IN_RESET_MAXMIN 0x40 <br>
	 DIO_IN_TRIG_SEND_VAL 0x80 <br>
	 DIO_IN_TRIG_SEND_MAXVAL 0x100 <br>
	 DIO_IN_TRIG_SEND_MINVAL 0x200 <br>
	 DIO_IN_TRIG_SEND_AVGVAL 0x400 <br>
	 DIO_IN_TRIG_SEND_VAL_WHILE_HI 0x800 <br>
	 DIO_OUT_GENERALPURPOSE 0x1000 <br>
	 DIO_OUT_THRESHOLD_ANYVAL 0x10000 <br>
	 DIO_OUT_THRESHOLD_MAXVAL 0x14000 <br>
	 DIO_OUT_THRESHOLD_MINVAL 0x18000 <br>
	 DIO_OUT_SYNC_MASTER 0x20000 <br>
	 DIO_THRESHOLD_WINDOWCOMP_MASK 0x2000 <br>
	 DIO_INVERT_MASK	0x800000 <br>
   or GSV_ERROR if function failed.  <br>
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 153
 
 Device access: Yes, CmdNo: 0x5B

  date: 18.06.2015 11:29
 ********************************************************************************** */
int CALLTYP GSV86getDIOtype(int ComNo, int DIOno, int* AssignedChan);

/*!  ****************************************************************************
@brief	Set digital IO type
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] DIOno: Number of digital IO line 0..16. 0: Set all DIO-no to the same type
 @param[in] DIOtype: See definition in GSV86getDIOtype()
 @param[in] AssignedChan: Analog input channel to apply DIO functionality, if 
 	DIOtype= ThresholdSwitch (DIO_OUT_THRESHOLD_ANYVAL Bit set) or DIO_IN_TARE_SINGLE.
  @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 154
 
 Device access: Yes, CmdNo: 0x5C

  date: 21.06.2015 10:53
 ********************************************************************************** */
int CALLTYP GSV86setDIOtype(int ComNo, int DIOno, int DIOtype, int AssignedChan);

/*!  ****************************************************************************
@brief	Get digital IO level
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] DIOno: Number of digital IO line 1..16. Or 0=: Get all 16 DIO levels in Bits<15:0> of return value, 
 whereby bit0 = DIOno 1.. Bit15= DIOno 16 
  @return: DIO level: GSV_TRUE, if DIO level = high. GSV_OK, if level = low, <br>
  or Bits<15:0> = all levels if DIOno=0 or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 /note: DIO level is read independently of DIOtype or DIOdirection.

 OrdinalNo: 155
 
 Device access: Yes, CmdNo: 0x5D

  date: 21.06.2015 10:53
 ********************************************************************************** */
int CALLTYP GSV86getDIOlevel(int ComNo, int DIOno);

/*!  ****************************************************************************
@brief	Set digital out level
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] DIOno: Number of digital IO line 0..16. 0: Set all 16 DIO levels, whereby 
 		Bit0 of DIOlevel = DIOno 1.. Bit15= DIOno 16
 @param[in] DIOlevel: IO level to set: 1= high, 0=low or all 16 lines in Bits<15:0>
  @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 /note: DIO level is set only if corresponding DIOtype= DIO_OUT_GENERALPURPOSE. 
 Otherwise, if DIOno>0, the function returns GSV_ERROR (LastError=ERR_PAR_NOFIT_SETTINGS)

 OrdinalNo: 156
 
 Device access: Yes, CmdNo: 0x5E

  date: 21.06.2015 10:53
 ********************************************************************************** */
int CALLTYP GSV86setDoutLevel(int ComNo, int DIOno, int DIOlevel);

/*!  ****************************************************************************
@brief	Get digital-out threshold of threshold switch
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] DIOno: Number of digital IO line 1..16.
 @param[out] *ThresUp: Pointer to double value, whrere upper threshold is written to
 @param[out] *ThresDown: Pointer to double value, whrere lower threshold is written to
  @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 157
 Device access: Yes, CmdNo: 0x5F

  date: 21.06.2015 10:53
 ********************************************************************************** */
int CALLTYP GSV86getDoutThreshold(int ComNo, int DIOno, double* ThresUp, double* ThresDown);

/*!  ****************************************************************************
@brief	Set digital-out threshold of threshold switch
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] DIOno: Number of digital IO line 1..16.
 @param[in] ThresUp: Upper threshold of thershold switch
 @param[in] ThresDown: Lower threshold of thershold switch
  @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 \note: ThresUp must be greater or equal than ThresDown

 OrdinalNo: 158
 
 Device access: Yes, CmdNo: 0x60

  date: 21.06.2015 10:53
 ********************************************************************************** */
int CALLTYP GSV86setDoutThreshold(int ComNo, int DIOno, double ThresUp, double ThresDown);

/*!  ****************************************************************************
@brief	Get initial digital out level
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] DIOno: Number of digital IO line 0..16. 0: Get all 16 DO init levels, whereby 
 	Bit0 of return value = DIOno 1.. Bit15= DIOno 16
  @return: DO init level: GSV_TRUE, if DO init level = high, GSV_OK, if level = low, 
  or Bits<15:0> = all levels if DIOno=0 or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 160
 
 Device access: Yes, CmdNo: 0x61

  date: 01.07.2015 18:39
 ********************************************************************************** */
int CALLTYP GSV86getDoutInitLevel(int ComNo, int DIOno);

/*!  ****************************************************************************
@brief	Set initial digital out level
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[in] DIOno: Number of digital IO line 0..16. 0: Set all 16 DIO levels, whereby 
 		Bit0 of DIOlevel = DIOno 1.. Bit15= DIOno 16
 @param[in] DOInitLevel: Default out level to set: 1= high, 0=low or all 16 lines in Bits<15:0>
  @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 /note: Default out level is stored for corresponding DIOno(s), regardless of its type or invert state. <br>
 This level is set to the corresponding DIO output if: <br>
 1. The corresponding DIOtype is an output type <br>
 2. DIO initialization is called. That happens at boot-up, at type or direction changing 
 and at parameter loading

 OrdinalNo: 161
 
 Device access: Yes, CmdNo: 0x62

  date: 21.06.2015 10:53
 ********************************************************************************** */
int CALLTYP GSV86setDoutInitLevel(int ComNo, int DIOno, int DOInitLevel);

/*!  ****************************************************************************
@brief	Get maximum and minimum possible data frequency
--------------------------------------------------------------------------------------
 @param[in] ComNo: 	Number of Device Comport
 @param[out] *DrateMax: pointer to double value, where maximum data frequency is written to
 @param[out] *DrateMin: pointer to double value, where minimum data frequency is written to
  @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 164
 
 Device access: Yes, CmdNo: 0x63

  date: 18.08.2015 14:10
 ********************************************************************************** */
int CALLTYP GSV86getDataRateRange(int ComNo, double* DrateMax, double* DrateMin);

/*!  ***********************************************************************************
@brief	Get CAN / CANopen settings
---------------------------------------------------------------------------------------------
	@param[in] ComNo: 	Number of Device Comport
	@param[in] Index:  =0: Command ID GSV86-CAN protocol <br>
		=1: Command-Answer ID GSV86-CAN protocol <br>
		=2: Value-Frame ID GSV86-CAN protocol <br>
		=3: Multicast ID GSV86-CAN protocol <br>
		=4: CAN-Baudrate in Bits/s (both CAN protocols) <br>
		=5: Flags: Bit 1: CAN appl. layer protocol: =0: GSV86-CAN protocol. =1: CANopen protocol <br>
			   Bit 0: =0: CAN interface is switched on. =1: CAN interface is switched off <br>
		Index =6: CANopen NodeID (range: 1..0x7F)
	@param[out]  *setting. Pointer to value, where setting (according to Index) is written to
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 167
 
 Device access: Yes, CmdNo: 0x8C

  date: 24.11.2015 12:45
 ********************************************************************************** */
int CALLTYP GSV86readCANsettings(int ComNo, int Index, int* setting);

/*!  ***********************************************************************************
@brief	Set CAN / CANopen settings
---------------------------------------------------------------------------------------------
	@param[in] ComNo: 	Number of Device Comport
	@param[in] Index:  =0: Command ID GSV86-CAN protocol (reserved) <br>
		Index:  =1: Command-Answer ID GSV86-CAN protocol (reserved) <br>
		Index:  =2: Value-Frame ID GSV86-CAN protocol (reserved) <br>
		Index:  =3: Multicast ID GSV86-CAN protocol (reserved) <br>
		Index:  =4: CAN-Baudrate in Bits/s (both CAN protocols) <br>
		Index:	=5: Flags. Bit 1: CAN appl. layer protocol: =0: GSV86-CAN protocol. <br>							=1: CANopen
				Bit 0: =0: CAN interface is switched on.	=1: CAN interface is switched off. <br>
		Index: =6:	CANopen NodeID (range: 1..0x7F) <br>
	@param[in] setting value, according to Index
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 168
 
 Device access: Yes, CmdNo: 0x8D

  date: 24.11.2015 12:45
 ********************************************************************************** */
int CALLTYP GSV86setCANsettings(int ComNo, int Index, int setting);

/*!  ***********************************************************************************
@brief	Get CAN / CANopen On / Off state
---------------------------------------------------------------------------------------------
	@param[in] ComNo: 	Number of Device Comport
	@param[out]  *CANappProt. Pointer to value, where application protocol info is written to: <br>
		=0 for proprietary (ME-Systeme) CAN "serial" protokol <br>
		=1 for stadartized CANopen protocol <br>
 @return: GSV_TRUE if CAN/CANopen is on (enabled), GSV_OK is it is off (disabled)
	 or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 169
 
 Device access: Yes, CmdNo: 0x8C

  date: 02.12.2015 12:32
 ********************************************************************************** */
int CALLTYP GSV86getCANonOff(int ComNo, int* CANappProt);

/*!  ***********************************************************************************
@brief Switch CAN / CANopen on or off
---------------------------------------------------------------------------------------------
	@param[in] ComNo: 	Number of Device Comport
	@param[in] OnOff: =0: Switch CAN/CANopen off. =1: Switch CAN/CANopen on
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 170
 
 Device access: Yes, CmdNo: 0x8C, 0x8D

  date: 02.12.2015 12:32
 ********************************************************************************** */
int CALLTYP GSV86setCANonOff(int ComNo, int OnOff);

/*!  ***********************************************************************************
@brief Get Interface Setting Value
---------------------------------------------------------------------------------------------
	@param[in] ComNo: 	Number of Device Comport
	 @param[in]   Ix: index in linked list of interface descriptors/settings. <br>
	    	if Ix = 0..(Number of interfaces - 1) =Interface Number: Basic settings, ApplEnum set
	 @param[out]  Next: Next index in linked list of interface descriptors/settings of the same interface. <br>
	 	if =0: End of list
	 @param[out] Data: Data read. if Ix= Interface Number: Flag value. Else: Interpretation according to return value
	 @param[out] ApplEnum: If Index < (Number of interfaces): Enumerator of application interface
	 @param[out] Writable: Function writes 1, if value is writable (with GSV86writeInterfaceSetting), otherwise 0
 @return: if Ix= Interface Number: Enumerator of physical interface:
 
 	 \note: Refer to device manual appendix for details on interpretation of data
 	         
 or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 172
 
 Device access: Yes, CmdNo: 0x01, 0x7B

  date: 24.01.2016 18:39
 ********************************************************************************** */
int CALLTYP GSV86readInterfaceSetting(int ComNo, int Ix, int* Next, unsigned long* Data, int* ApplEnum, int* Writable);

/*!  ***********************************************************************************
@brief Get basic Interface Settings of all Interfaces or of interface actually communicating
---------------------------------------------------------------------------------------------
	@param[in] ComNo: 	Number of Device Comport
	@param[in] ActIntf: =0 get List of all Interfaces, =1: Get Actual Interface settings
	@param[out] PhysEnums: ActIntf=1: IntfNo values written, else 1 value: Physical type enum, Index= Inteface-No <- OK? BESSER INTNO_USB=0 setzen?! Klären!
	@param[out] ApplEnums: IntfNo values written, else 1 value: Application Protocol Enum
	@param[out] Flags: IntfNo values written, else 1 value: 
	
 @return: if ActIntf=1: Number of acual Interface <br>
 	if ActIntf=0: Number of Interfaces present =Number of values written in Flags, PhysEnums and ApplEnums Arrays
 or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 173
 
 Device access: Yes, CmdNo: 0x01, 0x7B

  date: 24.01.2016 18:40
 ********************************************************************************** */
int CALLTYP GSV86readBasicInterfSettings(int ComNo, int ActIntf, int* PhysEnums, int* ApplEnums, int* Flags);

/*!  ***********************************************************************************
@brief Get all Interface Settings of a particular interface
---------------------------------------------------------------------------------------------
	@param[in] ComNo: 	Number of Device Comport
	 @param[in] IntfNo: : Interface number: 0..Number of interfaces-1
	@param[out] IntfEnums: Always 2 values written: IntfEnums[0]: Physical type enum, 
	 					IntfEnums[1]: Application type enum
	@param[out] Dtypes: Array with all extended settings written, except baud rates.  =0 basic flag value <br>
	 			>0: Type enumerator for Data meaning
	 @param[out] Data: Data content array. Interpretation according to Dtypes at same index.
	 @param[out] BdList: Array with all baudrates settings written [Bits/s]. bdList[0]: actual baud rate set.
	 @param[out] BdNum: value that holds number of baud rates written to bdList. bdNum-1 =Number of available baud rates
	\note: Array size for Dtypes, dat and bdList won't ever exceed 256 Bytes. Just allocate 256 values.
 @return: Number of values written to dat and Dtypes 
 or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 174
 
 Device access: Yes, CmdNo: 0x01, 0x7B

  date: 24.01.2016 18:40
 ********************************************************************************** */
int CALLTYP GSV86readAllInterfSettings(int ComNo, int IntNo, int* IntfEnums, int* Dtypes, int* Data, int* BdList, int* BdNum);

/*!  ***********************************************************************************
@brief Write Interface Setting Value
---------------------------------------------------------------------------------------------
	@param[in] ComNo: 	Number of Device Comport
	@param[in] Ix: index in linked list of interface descriptors/settings: <br>
	    	if Ix = 0..(Number of interfaces - 1) =Interface Number: Basic settings
	@param[in]  Data: if Ix = 0..(Number of interfaces - 1): Flag value <br>
	    		Else: Value, according to Type of Data (e.g. read with GSV86readInterfaceSetting)
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed.  or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 176
 
 Device access: Yes, CmdNo: 0x7C

  date: 24.01.2016 18:40
 ********************************************************************************** */
int CALLTYP GSV86writeInterfaceSetting(int ComNo, int Ix, unsigned long Data);

/*!  ***********************************************************************************
@brief Switch interface on or off
---------------------------------------------------------------------------------------------
	@param[in] ComNo: 	Number of Device Comport
	@param[in] IntfNo: Number of Interface 
	@param[in] OnOff: =1 switch on, =0: switch off
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed.  or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 177
 
 Device access: Yes, CmdNo: 0x01, 0x7B, 0x7C

  date: 24.01.2016 18:41
 ********************************************************************************** */
int CALLTYP GSV86setInterfaceOnOff(int ComNo, int IntNo, int OnOff);

/*!  ***********************************************************************************
@brief Write baud rate
---------------------------------------------------------------------------------------------
	@param[in] ComNo: 	Number of Device Comport
	@param[in] IntfNo: Number of Interface 
	@param[in] Baud: baud rate in Bits/s
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed.  or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 178
 
 Device access: Yes, CmdNo: 0x01, 0x7B, 0x7C

  date: 24.01.2016 18:41
 ********************************************************************************** */
int CALLTYP GSV86writeInterfaceBaud(int ComNo, int IntNo, int Baud);

/*!  ***********************************************************************************
@brief Read Hardware Version
---------------------------------------------------------------------------------------------
@param[in] ComNo: 	Number of Device Comport
 @param[out]  *MainHW: Version of Devices mainboard. Pointer required
 @param[out] *ExtHW: Version of peripheral board(s), if relevant.
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed.  or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 179
 Device access: Yes, CmdNo: 0x36

  date: 05.07.2016 11:05
 ********************************************************************************** */
int CALLTYP GSV86readHWversion(int ComNo, int* MainHW, int* ExtHW);

#define TEDS_ANSW_IS_FLT 1
#define TEDS_IS_PACKED_CHR5 2
#define TEDS_IS_DATE_DAYS 4
#define TEDS_ENTRY_HAS_ERROR 0x80
#define TEDS_ENTRY_NOT_EXIST 0xFF
#define TEDS_ENTRY_NOT_SET 0xFE
#define TEDS_ENTRY_INVALID 0xFD
/*!  ***********************************************************************************
@brief Read TEDS sensor entry
---------------------------------------------------------------------------------------------
	@param[in] ComNo: 	Number of Device Comport
	@param[in] Chan: Input channel No (1..8) with TEDS sensor connected
	@param[in] TemplID: Template ID. BasicTEDS (incl. ID main template): =0
	@param[in] PropID: Property-ID of entry. 124 IDs exist so far. Property-ID =0: Get first valid entry
	@param[out] *Next: Property-ID of next entry in list. If=0: last entry
	@param[in] No: Array index for same Property-ID beginning with 0 (reserved). Else =0
	@param[out]  *Udata: Data of unsigned long type, if Flags written =0
	@param[out]  *DblData: Data of double type, if Flags written =ANSW_IS_FLT =1
	@param[out]  *Flags: 0..7F (Bit7 =0): Read fully successful. Bits<6:0>: Flag values: <br>
		 TEDS_ANSW_IS_FLT 1 Data type of answer is float. Data written to *DblData. <br>
		 TEDS_IS_PACKED_CHR5 2 Data type of answer is packed 5-Byte Char (Defined in IEEE1451.4 7.4.5.2.5) <br>
		 TEDS_IS_DATE_DAYS 4 Data type of answer is date in days (Defined in IEEE1451.4 7.4.5.2.1) <br>
		0x80..FF (Bit7 =1): Special Error-Code, no value written <br>
		 TEDS_ENTRY_NOT_EXIST 0xFF Entry-Request / PropID doesn't exist in the Template <br>
		 TEDS_ENTRY_NOT_SET 0xFE Entry exists, but is flagged as "don't care", i.e. all Bits=1 <br>
		 TEDS_ENTRY_INVALID 0xFD Entry invalid, eg NaN with Float <br>
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed.  or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 180
 
 Device access: Yes, CmdNo: 0x64

 ********************************************************************************** */
int CALLTYP GSV86readTEDSentry(int ComNo, int Chan, int TemplID, int PropID, int* Next, int No, unsigned long* Udata, double* DblData, int* Flags);


#define TEDSLISTFLG_BASICONLY 1 /* List Basic template only */
#define TEDSLISTFLG_MAINONLY 2 /* List Main template only*/
#define TEDSLISTFLG_COLUMN_NUM_VAR 4 /* Empty field left away, so that column number is variable*/
#define TEDSLISTFLG_FILL_EMPTY_SPACE 8 /* Insert space in empty field */
#define TEDSLISTFLG_PIPE_SEPARA 16 /*Field separator inside line is | otherwise TAB */
/*!  ***********************************************************************************
@brief Read TEDS formatted String
---------------------------------------------------------------------------------------------
	@param[in] ComNo: 	Number of Device Comport
	@param[in] Chan: Input channel No (1..8) with TEDS sensor connected
	@param[in] *TEDSfilePath: Full Path to TEDSdictionary.ini file
	@param[out]  *ListOut: String list. One line per entry, ending with LF CR. Format: <br>
	1			2		3 <br>
	Name			Value		Unit <br>
	@param[in] ListSize: Size of ListOut String in Bytes. Minimum recommended: 16384
	@param[in] Code: Bits<7:0>: Flags: see #TEDSLISTFLG_ above
	Bits<23:0> of Code parameter. Can be ORed with Bit<7:0> constants <br>
	 ANSI_CODEPAGE 0x00000000 ANSI 8-Bit coded  <br>
	 ASCII_ONLY	0x00000100 Use ASCII 7-Bit only <br>
	 DOS_CODEPAGE_437 0x0001B500 DOS/Windows Codepage 437 <br>
	 WIN_CODEPAGE_1252 0x0004E400 Windows Codepage 1252
	@param[out]  *ExtListOut: String list with additional information. One line per entry, ending with LF CR. Format: <br>
	1			2		3		4 <br>
	Extended Text		(Enum-)Value	Property-Name	Property-ID <br>
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed.  or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().

 OrdinalNo: 182
 
 Device access: Yes, CmdNo: 0x64
 ********************************************************************************** */
int CALLTYP GSV86readFormattedTEDSList(int ComNo, int Chan, const char* TEDSfilePath, char* ListOut, int ListSize, int Code, char* ExtListOut);

/*!  ***********************************************************************************
@brief Read TEDS raw data array
---------------------------------------------------------------------------------------------
	@param[in] ComNo: 	Number of Device Comport
	@param[in] Chan: Input channel No (1..8) with TEDS sensor connected
	 @param[out]  *DataOut: Array where data is written to. Size must be =NumBytes
	 @param[in] NumBytes Number of Bytes to read
	 @param[in] StartByteAdr Byte adress of 1-wire EEPROM. Must be dividible by 4. TEDS-checksum not included.
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed.  or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 Remark: DataOut doesn't contain the Checksum Byte(s); the function itself will check that.

 OrdinalNo: 183
 
 Device access: Yes, CmdNo: 0x65

  date: 05.07.2016 11:05
 ********************************************************************************** */
int CALLTYP GSV86readTEDSrawData(int ComNo, int Chan, unsigned char* DataOut, int NumBytes, int StartByteAdr);

/*!  ***********************************************************************************
@brief Write TEDS raw data
---------------------------------------------------------------------------------------------
	@param[in] ComNo: 	Number of Device Comport
	@param[in] Chan: Input channel No (1..8) with TEDS sensor connected
	 @param[in] *DataIn: Array with data to write. Must be byte-aligned at base. Size=NumBits/8, rounded up.
	 @param[in] NumBits Number of Bits to write
	 @param[in] StartBitAdr Start Bit adress of 1-wire EEPROM. TEDS-checksum not included.
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed.  or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 \note: 1. DataIn must not contain the Checksum Byte(s); the function itself will generate it/them. <br>
 	2. UserPassword must be set (see GSV86setPassword() ) <br>

 OrdinalNo: 184
 Device access: Yes, CmdNo: 0x66, 0x67

  date: 06.07.2016 15:29
 ********************************************************************************** */
int CALLTYP GSV86writeTEDSrawData(int ComNo, int Chan, const unsigned char* DataIn, int NumBits, int StartBitAdr);

/*!  ***********************************************************************************
@brief Determine Properties of plugged sensor
---------------------------------------------------------------------------------------------
	@param[in] ComNo: 	Number of Device Comport
	@param[in] Chan: Input channel No (0..8)
	@param[out] *BridgeSensor Flag value indicating, if a bridge sensor is connected (Flag=1) or not (Flag=0). <br>
	 	if Chan=0: Bits<7:0> correspond to bridge-sensor at input channels: Bit7: Input 8..bit0: Input 1 <br>
	 	if Chan =1..8: Value=1 indicated a connected bridge sensor. =0: No bridge sensor connected.
	@param[out] *TEDScapable: Indicates, if a 1-wire EEPROM is connected and if it is writable <br>
	 if Chan=0: Bits<7:0> indicate present 1-wire EEPROM of all input channels 8..1 (Bit7: chan. 8...Bit0: chan 1) <br>
	 	    Bits<15:8> indicate if the corresponding input channel is capable of writing to 1-wire TEDS EEPROM <br>
	 	                Bit15: Input chan. 8 writable ... Bit0: Input chan. 1 writable <br>
	 if Chan =1..8: Bit 0 indicates if TEDS is present at specified input channel <br>
	                Bit 1 indicates if specified input channel is capable of writing TEDS <br>
 @return: Simple errorcode: GSV_OK,if successful or GSV_ERROR if function failed.  or GSV_ERROR if function failed. 
 If GSV_ERROR, more detailed error information ca be retrieved with GSV86getLastProtocollError() or GSV86getLastErrorText().
 \note: The "1-wire EEPROM" flags indicate if a TEDS-capable memory is connected; it doesn't indicate 
           if it contains valid TEDS data and if they are used for scaling. To determine the latter, 
           use GSV86getTEDSactive instead.

 OrdinalNo: 186
 
 Device access: Yes, CmdNo: 0x45

  date: 06.07.2016 15:29
 ********************************************************************************** */
int CALLTYP GSV86getSensorPlugged(int ComNo, int Chan, int* BridgeSensor, int* TEDScapable);

/*!  ***********************************************************************************
@brief Determine, if TEDS data are actually used for scaling (i.e. as user scale value)
---------------------------------------------------------------------------------------------
	@param[in] ComNo: 	Number of Device Comport
	@param[in] Chan: Input channel No (0..8) if =0: TEDS active flags in Bity<7:0> for input channels 8..1
 @return: if Chan=0: TEDS active flags in Bity<7:0> for input channels 8..1 <br>
 	  if Chan= 1..8: TEDS active flag in Bit 0, whereby Bit=1: TEDS are actually used for scaling. <br>
 	  Bit=0: no TEDS data used for scaling, scaling used from GSV-8 memory
 \remark: Pre-conditions for used TEDS data: <br>
 	- Mode-Flags<15:8> of corresponding channel =1 (see GSV86getMode) <br>
 	- TEDS with valid and known template connected <br>
 	- Suitable input-Type set (see GSV86getInTypeRange)

 OrdinalNo: 188
 
 Device access: Yes, CmdNo: 0x68

  date: 06.07.2016 15:29
 ********************************************************************************** */
int CALLTYP GSV86getTEDSactive(int ComNo, int Chan);

int CALLTYP GSV86MEwriteCal(int ComNo, int Chan, int ix, double cal);
int CALLTYP GSV86readCal(int ComNo, int Chan, int ix, double* cal);
int CALLTYP GSV86MEwriteInputRange(int ComNo, int Chan, int type, double range);
int CALLTYP MEgsv86setSerialNo(int ComNo, int SerNo);

#ifdef __cplusplus
}
#endif