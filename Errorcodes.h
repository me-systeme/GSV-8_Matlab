/* Error codes of GSV-8 device */
#define ERR_OK			0x00	/* Ok, no error */
#define ERR_OK_CHANGED		0x01	/* OK und weitere Parameter geaendert */
#define ERR_OK_CHANGED_TXT "Device: No error, but further device parameters changed"
#define ERR_CMD_NOTKNOWN	0x40	/* unbekannte Befehls-Nr. */
#define ERR_CMD_NOTKNOWN_TXT "Device: Command number unknown"
#define ERR_CMD_NOTIMPL		0x41	/* Befehls-Nr. zwar bekannt, aber bei dieser Version nicht implementiert */
#define ERR_CMD_NOTIMPL_TXT "Device: Command not implemented"
#define ERR_FRAME_ERROR		0x42	/* Suffix falsch */
#define ERR_FRAME_ERROR_TXT "Device: Frame error: wrong suffix"

#define ERR_PAR		0x50		/* falscher Parameter */
#define ERR_PAR_TXT "Device: Parameter wrong"
#define ERR_PAR_ADR	0x51		/* falscher Adress- o. Indexparameter */
#define ERR_PAR_ADR_TXT "Device: Wrong index or adress parameter"
#define ERR_PAR_DAT	0x52		/* falscher Datenparameter */
#define ERR_PAR_DAT_TXT "Device: Wrong data parameter"
#define ERR_PAR_BITS	0x53		/* falsche(s) Bit(s) im Parameter */
#define ERR_PAR_BITS_TXT "Device: Wrong bits inside parameter"
#define ERR_PAR_ABSBIG	0x54		/* Parameter absolut zu gross */
#define ERR_PAR_ABSBIG_TXT "Device: Parameter abolutely too big"
#define ERR_PAR_ABSMALL	0x55		/* Parameter absolut zu klein */
#define ERR_PAR_ABSMALL_TXT "Device: Parameter abolutely too small"
#define ERR_PAR_COMBI	0x56		/* falsche Parameter-Kombination */
#define ERR_PAR_COMBI_TXT "Device: Wrong parameter / setting combination"
#define ERR_PAR_RELBIG	0x57		/* Parameter in Relation zu anderen zu gross */
#define ERR_PAR_RELBIG_TXT "Device: Parameter too big in relation to other parameters / Settings"
#define ERR_PAR_RELSMALL	0x58	/* Parameter in Relation zu anderen zu klein */
#define ERR_PAR_RELSMALL_TXT "Device: Parameter too small in relation to other parameters / Settings"
#define ERR_PAR_NOTIMPL	0x59		/* Durch Parameter angeforderte Funktion nicht implementiert */
#define ERR_PAR_NOTIMPL_TXT "Device: Function invoked by parameter is not implemented"
#define ERR_WRONG_PAR_NUM 0x5B		/* Uebergebene ParamNum stimmt nicht mit Erwartungswert ueberein */
#define ERR_WRONG_PAR_NUM_TXT "Device: Wrong number of parameters in frame"
#define ERR_PAR_NOFIT_SETTINGS	0x5C 
#define ERR_PAR_NOFIT_SETTINGS_TXT "Device: Parameter improper with respect to device's settings"
#define ERR_PAR_HW_COLLISION 0x5D	/* Durch Parameter angeforderte Funktion fueht zu Hardware-Kollision */
#define ERR_PAR_HW_COLLISION_TXT "Device: Function leads to hardware (connection) collision, e.g. short-circuit"
#define ERR_NO_DATA_AVAIL 0x60		/* Abgewiesen bei Leseanfrage, weil Daten nicht vorhanden */
#define ERR_NO_DATA_AVAIL_TXT "Device: Data reqested not available (e.g. not initiated)"
#define ERR_DATA_INCONSISTENT 0x61	/* Gespeicherte Daten falsch, bzw inkonsistent mit Zustandsanforderung */
#define ERR_DATA_INCONSISTENT_TXT "Device: Data stored not consistent in itself or with parameters"
#define ERR_WRONG_MOD_STATE 0x62	/* Befehl konnte nicht ausgeführt weren, weil Geraet bzw Modul im ungeeignetem Zustand */
#define ERR_WRONG_MOD_STATE_TXT "Device: Command could not be executed, because device or functionality in improper state"
#define ERR_NOT_SUPPORTED_D 0x63		/* Abgewiesen, weil angeforderte Funktionalitaet nicht unterstuetzt */
#define ERR_NOT_SUPPORTED_D_TXT "Device: Denied, because requested funcionality not supported"
#define ERR_FDATA_TOO_HIGH 0x64		/* Abgewiesen, weil Datenrate zu hoch, bzw Prozessor waere zu ausgelastet */
#define ERR_FDATA_TOO_HIGH_TXT "Device: Denied, because data rate too high for requested setting"
#define	ERR_MEMORY_WRONG_COND 0x6E	/* Abgewiesen bei Memory-Interface-write, weil Bed. nicht erf. */
#define	ERR_MEMORY_WRONG_COND_TXT "Device: Memory write denied, because condition(s) not satisfied"
#define	ERR_MEMORY_ACCESS_DENIED 0x6F	/* Abgewiesen bei Memory-Interface-write */
#define	ERR_MEMORY_ACCESS_DENIED_TXT "Device: Memory write: Access denied"

#define ERR_ACC_DEN		0x70	/* Zugriff verboten (ohne Nennung des Grundes) */
#define ERR_ACC_DEN_TXT "Device: Access denied"
#define ERR_ACC_BLK		0x71	/* Zugriff verboten, weil Blocking gesetzt */
#define ERR_ACC_BLK_TXT "Device: Access denied, because write functions are blocked"
#define ERR_ACC_PWD		0x72	/* Zugriff verboten, weil fehlendes o. falsches Passwort */
#define ERR_ACC_PWD_TXT "Device: Access denied: Missing password/PIN"
#define ERR_ACC_MAXWR		0x74	/* Zugriff verboten, weil maximale Ausfuehrungsanzahl erreicht */
#define ERR_ACC_MAXWR_TXT "Device: Access denied: Maximum executions reched"
#define ERR_ACC_PORT		0x75	/* Zugriff verboten, weil dieser Port (z.Zt.) kein Schreibrecht hat */
#define ERR_ACC_PORT_TXT "Device: Access from this port denied (other port seems to have write access)"

#define	ERR_INTERNAL	0x80		/* interner Ausnahmefehler */
#define	ERR_INTERNAL_TXT "Internal exception in device. Please contact manufacturer"
#define	ERR_ARITH	0x81		/* interner arithmetischer Fehler */
#define	ERR_ARITH_TXT "Internal arithmetic exception in device. Please contact manufacturer"
#define	ERR_INTER_ADC	0x82		/* Fehlerhaftes Verhalten des AD-Umsetzers */
#define	ERR_INTER_ADC_TXT "Device: Erratic behaviour of AD converter. Please contact manufacturer"
#define	ERR_MWERT_ERR	0x83		/* Zur Befehlsausfuehrung ungeeigneter Messwert */
#define	ERR_MWERT_ERR_TXT "Device: Actual measuring value inappropriate to fulfil request"
#define	ERR_EEPROM	0x84		/* neu 12.00 ;Fehlerhaftes Verhalten des EEPROMs */
#define	ERR_EEPROM_TXT "Device: Erratic behaviour of EEPROM memory. Please contact manufacturer"

#define ERR_RET_TXBUF	0x91		/* Transmit-Buffer voll */
#define ERR_RET_TXBUF_TXT "Device transmission buffer full"
#define ERR_RET_BUSY	0x92		/* Prozessor temporaer zu ausgelastet, um Befehl auszufueren */
#define ERR_RET_BUSY_TXT "Device too busy to execute request"
#define ERR_RET_RXBUF	0x99		/* Receive-Buffer voll */
#define ERR_RET_RXBUF_TXT "Device receive buffer full"
/* TEDS errors */
#define TEDS_ERR_MASK 0x30000300
#define GETTEDS_ERR_NOSENSOR 0xB0
#define GETTEDS_ERR_NOSENSOR_TXT "Device (TEDS): No sensor connected at all"
#define GETTEDS_ERR_NOTEDSEE 0xB1	//kein TEDS angeschlossen
#define GETTEDS_ERR_NOTEDSEE_TXT "Device (TEDS): No TEDS memory connected"
#define GETTEDS_ERR_BASICONLY 0xB2 //nur Basic template vorhanden
#define GETTEDS_ERR_BASICONLY_TXT "Device (TEDS): Only Basic TEDS data found"
#define GETTEDS_ERR_NOTEDSDAT 0xB3 // Datensatz nicht normgemaess (ENTRY_NOT_EXIST 0xFF nur ExeCmdTEDS->GetTEDSentry)
#define GETTEDS_ERR_NOTEDSDAT_TXT "Device (TEDS): Data not in conformance with IEEE1541.4"
#define GETTEDS_ERR_ENTRY_INVALID 0xB4 // ENTRY_NOT_SET | ENTRY_NOT_SET
#define GETTEDS_ERR_ENTRY_INVALID_TXT "Device (TEDS): Data entry not set"
#define GETTEDS_ERR_TOUT 0xB5	//CoMCU antwortet nicht
#define GETTEDS_ERR_TOUT_TXT "Device (TEDS): 1-wire EEPROM driver timed out"
#define GETTEDS_ERR_CHKSUM 0xB6 
#define GETTEDS_ERR_CHKSUM_TXT "Device (TEDS): Data checksum error"
#define GETTEDS_ERR_UNKNOWN_TEMPL 0xB7
#define GETTEDS_ERR_UNKNOWN_TEMPL_TXT "Device (TEDS): TEDS template not supported"
#define GETTEDS_ERR_VERIFY_FAIL 0xB8
#define GETTEDS_ERR_VERIFY_FAIL_TXT "Device (TEDS): Data write-verify failed"

/* Measuring value Error */
#define VALERR_NONE 0
#define VALERR_TYPE_SATURATED 1
#define VALERR_TYPE_MAX_EXCEED 2
#define VALERR_TYPE_SENSOR_BROKEN 3
#define ERR_TYPE_ANALOG_OUTPUT 4
#define ERR_TYPE_DIGITAL_OUTPUT 5

/* Dll error codes */
#define ERR_MUTEXFAILED 0x300000F0	/*d805306608 Mutex request refused by OS */
#define ERR_MUTEXFAILED_TXT "MEGSV86xx.DLL: Mutex request refused by OS"
#define ERR_EVENTFAILED 0x300000F1	/*d805306609 Event request refused by OS */
#define ERR_EVENTFAILED_TXT "MEGSV86xx.DLL: Event request refused by OS"
#define ERR_MEM_ALLOC	0x300000F3	/*d805306611 Memory allocation request refused by OS */
#define ERR_MEM_ALLOC_TXT "MEGSV86xx.DLL: Memory allocation request refused by OS"
#define ERR_NO_GSV_FOUND 0x300000F4	/*d805306612 Comport could be opened, but no GSV answered */
#define ERR_NO_GSV_FOUND_TXT "MEGSV86xx.DLL: Com port could be opened, but no GSV answered"
#define ERR_BYTES_WRITTEN 0x300000F5	/*d805306613 Could not write enough bytes to the port */
#define ERR_BYTES_WRITTEN_TXT "MEGSV86xx.DLL: Could not write enough bytes to the port"
#define ERR_WRONG_PARAMETER 0x30000100	/*d805306624 Function parameter exceedance */
#define ERR_WRONG_PARAMETER_TXT "MEGSV86xx.DLL: Function parameter exceedance"
#define ERR_NO_GSV_ANSWER 0x30000058	/*d805306456 Command response from device timed out */
#define ERR_NO_GSV_ANSWER_TXT "MEGSV86xx.DLL: Command response from device timed out"
#define ERR_WRONG_ANSWER_NUM 0x30000059	/*d805306457 Parameter number in command answer frame not as expected */
#define ERR_WRONG_ANSWER_NUM_TXT "MEGSV86xx.DLL: Parameter number in command answer frame not as expected"
#define ERR_WRONG_ANSWER 0x30000060	/*d805306458 GSV-8 sended wrong command answer */
#define ERR_WRONG_ANSWER_TXT "MEGSV86xx.DLL: GSV-8 sended wrong command answer"
#define ERR_WRONG_FRAME_SUFFIX	0x30000061 /*d805306465 Frame suffix wrong */
#define ERR_WRONG_FRAME_SUFFIX_TXT "MEGSV86xx.DLL: Frame suffix from device wrong"
#define ERR_NOT_SUPPORTED 0x30000062	/*GSV-8 Firmware doesn't support the request */
#define ERR_NOT_SUPPORTED_TXT "MEGSV86xx.DLL: Device firmware doesn't support the request"
#define ERR_WRONG_COMNO 0x30000101	/*d805306625 ComNo parameter wrong */
#define ERR_WRONG_COMNO_TXT "MEGSV86xx.DLL: ComNo parameter wrong"
#define ERR_COM_ALREADY_OPEN	0x300000F6	/*d805306614 Comport requested for opening (GSV86activateExtended) is already open */
#define ERR_COM_ALREADY_OPEN_TXT "MEGSV86xx.DLL: Comport requested for opening is already open"
#define ERR_COM_GEN_FAILURE 0x3000001F /*hardware-or driver-error of COMport. See: ERROR_GEN_FAILURE @msdn.microsoft.com/en-us/library/ms681382(VS.85).aspx */
#define ERR_COM_GEN_FAILURE_TXT "MEGSV86xx.DLL: Hardware-or driver-error of COMport (Generic error: System Error 0x1F)"
#define ERR_INTERNAL_FUNC 0x30000105	/*internal function call failed */
#define ERR_INTERNAL_FUNC_TXT "MEGSV86xx.DLL: Internal function call failed"
#define ERR_PARAM_NOT_STORED 0x30000065	/*Parameter is not stored (correctly) in the device memory */
#define ERR_PARAM_NOT_STORED_TXT "MEGSV86xx.DLL: Parameter is not stored (correctly) in the device memory"
#define ERR_FILE_CONTENT 0x30000108	/* File passed by user has error in content */
#define ERR_FILE_CONTENT_TXT "MEGSV86xx.DLL: File passed by user has error in its content"
#define ERR_UNKNOWN_VALUE 0x3000010A	/* Value read from device can not be deocded */
#define ERR_UNKNOWN_VALUE_TXT "MEGSV86xx.DLL: Value read from device can not be deocded"
/* Digital filter dll functions error codes */
#define NO_ERR 0
#define DF_ERR_MASK 0x31000000
#define DF_ERR_NOT_INIT 0x30000201
#define DF_ERR_NOT_INIT_TXT "DLL.Dfilter: Digital filter function could not be executed, because digital filter not initialized"
#define DF_ERR_OPT_WRONG 0x30000202
#define DF_ERR_OPT_WRONG_TXT "DLL.Dfilter: Wrong or incompatible filter options"
#define DF_ERR_NO_CONVERGENCE 0x30000203
#define DF_ERR_NO_CONVERGENCE_TXT "DLL.Dfilter: Digital filter calculation failed to converge"
#define DF_ERR_CHEB_RIB_WRONG 0x30000204
#define DF_ERR_CHEB_BUG_Y 0x30000205
#define DF_ERR_ZERO_NUM_HIGH 0x30000206
#define DF_ERR_POLE_ZERO_NOT_CONJ 0x30000207
#define DF_ERR_COEFF_SUM_TOOBIG 0x30000208
#define DF_ERR_COEFF_SUM_TOOBIG_TXT "DLL.Dfilter: Resulting coefficients discarded, because they may limit measuring precision (sum too big)"
#define DF_ERR_INTERN_GAIN_TOO_BIG 0x30000209
#define DF_ERR_INTERN_GAIN_TOO_BIG_TXT "DLL.Dfilter: Resulting coefficients discarded, because they may limit measuring precision (gain too big)"
#define DF_ERR_FIR_ODD_ORDER_NOTALLOWED  0x3000020A
#define DF_ERR_FIR_ODD_ORDER_NOTALLOWED_TXT "DLL.Dfilter: Odd filter order not allowed with this release"
