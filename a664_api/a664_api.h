/**
* @file a664_api.h
* @brief Time-Triggered Ethernet and ARINC 664 End System Application Programmer's Interface
*
*  Created on: 12/15/2010
*   
*	- $HeadURL: https://internal.aviftech.com/svn/Ethernet_ES/Development_ES/HostSW/trunk/a664_api/include/a664_api.h $
*	- $Date: 2013-10-02 10:05:25 -0500 (Wed, 02 Oct 2013) $
*	- $Revision: 2585 $
*	- $Author: johnb $
*
* Copyright (c) 2010 by Avionics Interface Technologies
*  - Omaha, NE USA
*  - Beavercreek, OH USA
*  .
* All rights reserved.  No part of this software may
* be published, distributed, translated or otherwise
* reproduced by any means or for any purpose without
* the prior written consent of Avionics Interface Technologies. 
*/
#ifndef A664_API_H
#define A664_API_H
#include "a664_cdef.h"
#include "a664_error_def.h"

/** 
* @brief The Interface Version for this API
**/
#define A664_API_IO_VERSION 0x00000001

/**
*  @brief  Global variable to store the number of end systems.
**/
extern uint32_t  gNumEndSystems;

/**
* \defgroup a664ApiAdmin A664 API Administration Functions
* @{
*
* @section sec_oview Overview
* <p>
* This section contains the A664 Library Adminstration Functions that
* are used by the application program to Initialize the A664 API and
* to obtain Status and Version information about the API library
* </p>
*
*/

/**
* @brief Initializes the Application Interface and returns the number of 
*  End System Devices found.
* This must be the first function called in the application program.
* @param[in] aStructureIoVersion This input is required to be the value of 
*  A664_API_IO_VERSION. This defines how the internal library will interpret 
*  input and output structures to the exported interface functions. Each time
*  an input or output structure is changed, the definition will be incremented
*  and the library will be able to interpret previously compiled applications
*  correctly, without recompiling.
* @param[out] aNumEndSystems The number of compatible End System devices found 
*  in the system.
* @return @link error Error Code @endlink
*/
A664_API_FUNC a664Init(const uint32_t aStructureIoVersion, uint32_t* aNumEndSystems);

/** 
* @brief Software version number where the format is Major.Minor.Maintenance.Revision
**/
typedef struct 
{
	/**
	* @brief Major Version for Version Format Major.Minor.Maintenance.Revision
	*/
	uint32_t mVersionMajor;
	/**
	* @brief Minor Version for Version Format Major.Minor.Maintenance.Revision
	*/
	uint32_t mVersionMinor;
	/**
	* @brief Maintenance Version for Version Format Major.Minor.Maintenance.Revision
	*/
	uint32_t mVersionMaintenance;
	/**
	* @brief Revision for Version Format Major.Minor.Maintenance.Revision
	*/
	uint32_t mVersionRevision;
} A664Version;

/**
* @brief Returns the Version of the A664 API and Kernel Module Driver.
* @param[out] aApiVersion The version of the API Library
* @param[out] aDriverVersion The version of the device driver
* @return @link error Error Code @endlink
*/
A664_API_FUNC a664GetApiVersions(A664Version* aApiVersion, A664Version* aDriverVersion);

/** 
* @brief Closes the API and releases resources
**/
A664_API_FUNC a664Close(void);

/**@}	(end defgroup a664ApiAdmin)	*/

/**
* \defgroup a664ApiEs A664 API End System Functions
* @{
*
* @section sec_oview Overview
* <p>
* This section contains the A664 Library functions that
* are used by the application program to operate on End System
* devices
* </p>
*
*/
/**
* @brief Gets the number of End System Devices available in the system
* @param[out] aNumEndSystems The number of End System Devices available for use in the system
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664ESGetCount(uint32_t* aNumEndSystems);

/** 
* @brief Device Identification Structure
**/
typedef struct
{
	/** 
	* @brief Vendor ID
	**/
	uint16_t vid;
	/** 
	* @brief Device ID
	**/
	uint16_t did;
	/** 
	* Device name
	**/
	char name[64];
} A664DeviceIdent;

/** 
* @brief Status and Version Information for the End System
**/
typedef struct 
{
	/** 
	* @brief Unique Identifier for the End System Device (ES Hardware Serial Number)
	**/
	uint32_t aESId;
	/** 
	* @brief The part number identifying the end system
	**/
	uint32_t aESPartNumber;
	/**
	* @brief The number of Ethernet interfaces available at the End System
	**/
	uint32_t aNumNetworkInterfaces;
	/** 
	* @brief sNIC Version Information
	**/
	A664Version    sNicVersion;
	/** 
	* @brief Tx NIOS Software Version
	**/
	A664Version    txNIOSVersion;
	/** 
	* @brief Rx NIOS Software Version
	**/
	A664Version    rxNIOSVersion;
	/** 
	* @brief Tx Boot NIOS Software Version
	**/
	A664Version    txBootNIOSVersion;
	/** 
	* @brief Rx Boot NIOS Software Version
	**/
	A664Version    rxBootNIOSVersion;
	/**
	* @brief Hardware Device Identification
	**/
	A664DeviceIdent deviceIdent;
} A664EndSystemInfo;
/**
* @brief Returns information about an End System
* @param[in] aESIndex The index of the End System Device
* @param[out] aEndSystemInfo A block of information about the End System device
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664ESGetInfo(const uint32_t aESIndex, A664EndSystemInfo* aEndSystemInfo);


/**
* @brief The End System's Handle
**/
typedef struct a664EndSystemHandle
{
	void* handle;
} A664EndSystemHandle;

/**
* @brief Returns information about an End System given an End System handle.
* @param[in] aEndSystemHandle The End System handle.
* @param[out] aEndSystemInfo The retrieved information for the End System device.
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664ESGetInfoViaHandle(const A664EndSystemHandle aEndSystemHandle, A664EndSystemInfo* aEndSystemInfo);

/**
* @brief Phy status
**/
typedef struct a664PhyStatus
{
	/**
	* @brief Boolean link status for channel 0.
	**/
	uint32_t linkStatusCh0;
	/**
	* @brief Configured speed for channel 0 (?10? for 1 Gbit/s, ?01? for 100 Mbit/s, ?00? otherwise).
	**/
	uint32_t speedCh0;
	/**
	* @brief Boolean link status for channel 1.
	**/
	uint32_t linkStatusCh1;
	/**
	* @brief Configured speed for channel 1 (?10? for 1 Gbit/s, ?01? for 100 Mbit/s, ?00? otherwise).
	**/
	uint32_t speedCh1;
} A664PhyStatus;

/**
* @brief Returns information about an End System given an End System handle.
* @param[in] aEndSystemHandle The End System handle.
* @param[out] aPhyStatus The returned PHY status for End System.
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664ESGetPhyStatus(const A664EndSystemHandle aEndSystemHandle, A664PhyStatus* aPhyStatus);

/**
*  @brief  The types of the sNIC status registers.
**/
typedef enum
{
	A_STATE_G  =  1,
	A_STATE_P  =  2,
	A_STATE_C  =  3, 
} A664SnicStatusType;

/**
*  @brief  The number of 32-bit longwords comprising the A_STATE_G sNIC register.
**/
#define  A_STATE_G_SIZE  (14)
/**
*  @brief  The number of 32-bit longwords comprising the A_STATE_P sNIC register.
**/
#define  A_STATE_P_SIZE  ( 8)
/**
*  @brief  The number of 32-bit longwords comprising the A_STATE_C sNIC register.
**/
#define  A_STATE_C_SIZE  (19)

/**
*  @brief  An sNIC status register, an array of 32-bit words.
**/
typedef uint32_t A664SnicStatusRegister[20];

/**
*  @brief  Get a status register (as an array of 32-bit integers).
*  @param[in] aEndSystemHandle A handle of an end system.
*  @param[in] snicStatusType The type of status register that is to be read from the sNIC.
*  @param[out] snicStatusRegister The sNIC status register, as an array of unsigned, 32-bit integers.
*  @return @link error Error Code @endlink 
**/
A664_API_FUNC a664GetSnicStatus(const A664EndSystemHandle aEndSystemHandle, const A664SnicStatusType snicStatusType,
                                A664SnicStatusRegister snicStatusRegister);

/** 
* @brief Open an End System and get an End System Handle to use for subsequent operations on the End System. The End System will be reset.
* @param[in] aESIndex The index of the End System Device
* @param[out] aEndSystemHandle A handle for the End System. To be used as input to API functions executing operations on the End System
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESOpen(const uint32_t aESIndex, A664EndSystemHandle* aEndSystemHandle);

#ifdef VISA
/** 
* @brief Open an End System with the VISA Device Name and get an End System Handle to use for subsequent operations on the End System. The End System will be reset.
* @param[in] aVisaDeviceName A pointer to the VISA Device Name of the End System, for example: "PXI5::12::INSTR"
* @param[out] aEndSystemHandle A handle for the End System. To be used as input to API functions executing operations on the End System
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESOpenVisaName(const char* aVisaDeviceName, A664EndSystemHandle* aEndSystemHandle);
#endif

/**
* @brief Close an End System and release the End System Handle
* @param[in] aEndSystemHandle The handle for the End System Device.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESClose(const A664EndSystemHandle aEndSystemHandle);

/** 
* @brief Enumeration of possible Network Interfaces at the End System
**/
typedef enum
{
	/** 
	* @brief Base Address Register 0
	**/
	A664_BAR_0 = 0,
	/** 
	* @brief Base Address Register 1
	**/
	A664_BAR_1 = 1,
	/** 
	* @brief Base Address Register 2
	**/
	A664_BAR_2 = 2,
	/** 
	* @brief Base Address Register 3
	**/
	A664_BAR_3 = 3,
} A664Bar;

/**
* @brief Read data dWords directly from the End System
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[in] aBar The Base Address Register to read from.
* @param[in] aByteOffset The byte offset into the bar to start reading at.
* @param[in] aLength The number of dWords to read.
* @param[out] aData32 A pointer to the memory to write the data to.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESRead32(A664EndSystemHandle aEndSystemHandle, A664Bar aBar, uint32_t aByteOffset, uint32_t aLength, uint32_t* aData32);

/**
* @brief Write data dWords directly to the End System
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[in] aBar The Base Address Register to write to.
* @param[in] aByteOffset The byte offset into the bar to start writing at.
* @param[in] aLength The number of dWords to write.
* @param[out] aData32 A pointer to the memory holding the data to be written.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESWrite32(A664EndSystemHandle aEndSystemHandle, A664Bar aBar, uint32_t aByteOffset, uint32_t aLength, uint32_t* aData32);

/**
* @brief Reset an End System 
* @param[in] aEndSystemHandle The handle for the End System Device.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESReset(const A664EndSystemHandle aEndSystemHandle);

/** 
* @brief End System Configuration Information
**/
typedef struct  
{
	/** 
	* @brief Pointer to the binary device specific Intel Hex formatted configuration Data for the sNIC 
	**/
	void* aSnicConf;
	/** 
	* @brief Pointer to the binary device specific Intel Hex formatted configuration data for the upper layer protocols (Tx)
	**/
	void* aTxUlpConf;
	/** 
	* @brief Pointer to the binary device specific Intel Hex formatted configuration data for the upper layer protocols (Rx)
	**/
	void* aRxUlpConf;
} A664Configuration;

/** 
* @brief Configure an End System using a TTE-Tools compiled device-specific configuration.
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[in] aEndSystemConfiguration Device-specific binary configuration data produced by TTE-Tools.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESConfigure(const A664EndSystemHandle aEndSystemHandle, const A664Configuration* aEndSystemConfiguration);

/** 
* @brief Configure an End System using three Intel HEX configuration files.
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[in] aSnicConfig sNIC configuration filepath
* @param[in] aTxConfig   Tx configuration filepath
* @param[in] anRxConfig  Rx configuration filepath
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESConfigureFromHexPaths(const A664EndSystemHandle aEndSystemHandle, const char* aSnicConfig ,
                                          const char* aTxConfig, const char* anRxConfig);

/** 
* @brief Configure an End System using a AIT-Tools compiled device-specific configuration.
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[in] aEndSystemConfiguration Pointer to the device-specific binary configuration data produced by AIT-Tools.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESConfigureEx(const A664EndSystemHandle aEndSystemHandle, const void* aEndSystemConfiguration);

/** 
* @brief Timestamp in DAY::HOUR::MIN::SEC::NANOSEC format
**/
typedef struct
{
	/** 
	* @brief The number of days
	**/
	uint32_t	mDay;
	/** 
	* @brief The number of hours
	**/
	uint32_t	mHour;
	/** 
	* @brief The number of minutes
	**/
	uint32_t	mMinute;
	/** 
	* @brief The number of seconds
	**/
	uint32_t	mSecond;
	/** 
	* @brief The number of nanoseconds
	**/
	uint32_t	mNanosecond;
}A664Timestamp;

/** 
* @brief Sets the timestamping clock for the end system.
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[in] aTime The time to set to the end system timestamping clock.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESSetTime(const A664EndSystemHandle aEndSystemHandle, const A664Timestamp* aTime);

/** 
* @brief Gets the current time from the end system timstamping clock.
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[out] aTime The current time from the timestamping clock.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESGetTime(const A664EndSystemHandle aEndSystemHandle, A664Timestamp* aTime);

/** 
* @brief Gets the time of the last External Event.  The Event Timestamp will be cleared during a664ESReset() and a664ESSetTime().
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[out] aTime The time of the last occurance of the External Event.
* @param[out] aNewEvent, returns TRUE if this is the first time the event timestamp was returned for the event.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESGetExternalEventTime(const A664EndSystemHandle aEndSystemHandle, A664Timestamp* aTime, uint32_t* aNewEvent);

/** 
* @brief MAC Interface Status Information
**/
typedef struct  
{
	/** 
	* @brief Indicates if the MAC Interface is enabled (TRUE) or not (FALSE)
	**/
	int      mInterfaceEnabled;
	/** 
	* @brief The number of bytes (including preamble and SOF delimiters)
	*        received at the MAC port
	**/
	uint32_t  mRxBytes;
	/** 
	* @brief The number of bytes (including preamble and SOF delimiters)
	*        transmitted at the MAC port
	**/
	uint32_t  mTxBytes;
	/** 
	* @brief The number of frames with MII Errors
	**/
	uint32_t  mMIIErrors;
	/** 
	* @brief The number of frames received with CRC Errors
	**/
	uint32_t  mCRCErrors;
	/** 
	* @brief The number of frames received with Allignment Errors
	**/
	uint32_t  mAlignmentErrors;
	/** 
	* @brief The number of frames received with Start of Frame Delimiter Errors
	**/
	uint32_t  mSOFErrors;
	/** 
	* @brief The number of frames received that are larger than 1518 bytes or less than 64 bytes
	**/
	uint32_t  mSizeErrors;
} A664MacStatus;

/** 
* @brief Enumeration of possible Network Interfaces at the End System
**/
typedef enum
{
	/** 
	* @brief Network A Interface
	**/
	A664_NETWORK_A  =  0,
	/** 
	* @brief Network B Interface
	**/
	A664_NETWORK_B  =  1,
} A664NetworkInterface;

/** 
*  @brief  Gets status information for the MAC Protocol Layer.
*          The counters returned via aMacStatus are re-set to zero
*          with each invocation of this function, and
*          at both power-on and board re-set.
*  @param[in]   aEndSystemHandle  A handle to an End System.
*  @param[in]   aNetwork          A Network Interface (A or B).
*  @param[out]  aMacStatus        A structure containing MAC Layer Status information.
*  @return @link error Error Code@endlink
**/
A664_API_FUNC  a664ESGetMacStatus(const A664EndSystemHandle aEndSystemHandle, const A664NetworkInterface  aNetwork,
								  A664MacStatus* aMacStatus);

/** 
*  @brief MAC Interface Control Settings
**/
typedef struct
{
	/** 
	*  @brief  Enables (true) or Disables (false) the Mac Interface
	**/
	uint32_t  mInterfaceEnabled;
} A664MacControl;
/**
*  @brief  Sets the control settings for a MAC interface (Net A or Net B) of the End System
*  @param[in]   aEndSystemHandle  A handle to an End System.
*  @param[in]   aNetwork          A Network Interface (A or B).
*  @param[in]   aMacControl       The structure containing the MAC Interface Control settings
*  @return @link error Error Code@endlink
**/
A664_API_FUNC a664ESSetMacControl(const A664EndSystemHandle  aEndSystemHandle,
								  const A664NetworkInterface aNetwork,
								  A664MacControl* aMacControl);

/**
*  @brief Type of ES Event
**/
typedef enum 
{
	/** 
	*   @brief Tx Event Queue overflow on the ES hardware. This event indicates that the event queue of the ES hardware has overflowed 
	*          and that one or more events has been dropped by the embedded Tx Processor (txNIOS). This event indicates that events are
	*          occurring faster than the host is processing events.
	**/
	A664_EVENT_TX_EVENT_QUEUE_OVERFLOW,
	/** 
	*   @brief Indicates a Tx Message Port Event
	**/
	A664_EVENT_TX_MESSAGE_PORT,
	/** 
	*   @brief Rx Event Queue overflow on the ES hardware. This event indicates that the event queue of the ES hardware has overflowed
	*          and that one or more events have been dropped by the embedded Rx Processor (rxNIOS). This event indicates taht the events are
	*          occurring faster than the host is processing events.
	**/
	A664_EVENT_RX_EVENT_QUEUE_OVERFLOW,
	/** 
	*   @brief Indicates an Rx Critical Traffic Message Port Event
	**/
	A664_EVENT_RX_CT_MESSAGE_PORT,
	/** 
	*   @brief Indicates an Rx Best Effort/COTS Message Port Event
	**/
	A664_EVENT_RX_BE_MESSAGE_PORT,
	/** 
	*   @brief Indicates a Loopback Message Port Event
	**/
	A664_EVENT_LOOPBACK_MESSAGE_PORT
} A664EventType;
/** 
* @brief End System Event Information. Holds information about the ES Event
**/
typedef struct  
{
	/** 
	* @brief Specifies the type of Event 
	**/
	A664EventType		mEventType;
	/** 
	* @brief Specifies the Event type specific source. The actual information contained 
	*        is dependent on the event type as specified below <BR>
	*        A664_EVENT_TX_EVENT_QUEUE_OVERFLOW :   N/A <BR>
	*        A664_EVENT_TX_MESSAGE_PORT         :   Tx Message Port Handle <BR>
	*        A664_EVENT_RX_EVENT_QUEUE_OVERFLOW :   N/A <BR>
	*        A664_EVENT_RX_CT_MESSAGE_PORT      :   Rx CT Message Port Handle <BR>
	*        A664_EVENT_RX_BE_MESSAGE_PORT      :   Rx BE/COTS Message Port Handle <BR>
	*		 A664_EVENT_LOOPBACK_MESSAGE_PORT	:	Loopback Message Port Handle <BR>
	**/
	void*				mEventSource;
	/** 
	* @brief Specifies the Event Type specific data. The actual information contained is 
	*        dependent on the event type as specified below <BR>
	*        A664_EVENT_TX_EVENT_QUEUE_OVERFLOW :   N/A <BR>
	*        A664_EVENT_TX_MESSAGE_PORT         :   See A664TxMessagePortEventData <BR>
	*        A664_EVENT_RX_EVENT_QUEUE_OVERFLOW :   N/A <BR>
	*        A664_EVENT_RX_CT_MESSAGE_PORT      :   See A664RxMessagePortEventData <BR>
	*        A664_EVENT_RX_BE_MESSAGE_PORT      :   See A664RxMessagePortEventData <BR>
	*        A664_EVENT_LOOPBACK_MESSAGE_PORT	:	See A664RxMessagePortEventData <BR>
	**/
	uint32_t            mEventData[2];
} A664EventInfo;

/** 
* @brief Tx Message Port Event Data
**/
typedef struct 
{
#ifndef __VXWORKS__
	/** 
	* @brief Indicates if the event is a Tx Message Port Invalid Message Event
	**/
	unsigned int 		mInvalidMessageEvent	: 1;
	/** 
	* @brief Indicates if the event is a Tx Message Port Buffer Overflow Event
	**/
	unsigned int		mBufferOverflowEvent	: 1;
	/** 
	* @brief Indicates if the event is a Tx Message Port Message Sent Event
	**/
	unsigned int		mMessageSentEvent		: 1;
	unsigned int		mReserved				: 29;
#else
	unsigned int		mReserved				: 29;
	unsigned int		mMessageSentEvent		: 1;
	unsigned int		mBufferOverflowEvent	: 1;
	unsigned int 		mInvalidMessageEvent	: 1;
#endif
} A664TxMessagePortEventData;


/** 
*  @brief Rx (CT and BE) Message Port Event Data
**/
typedef struct 
{
#ifndef __VXWORKS__
	/** 
	* @brief Indicates if the event is an Rx Message Port Invalid Message Event
	**/
	unsigned int		mInvalidMessageEvent	: 1;
	/** 
	* @brief Indicates if the event is a Rx Message Port Buffer Overflow Event
	**/
	unsigned int		mBufferOverflowEvent	: 1;
	/** 
	* @brief Indicates if the event is a Rx Message Port Message Sent Event
	**/
	unsigned int		mMessageReceivedEvent	: 1;
	/** 
	* @brief reserved
	**/
	unsigned int		mReserved				: 27;
	/** 
	* @brief Indicates if the port is a loopback port
	**/
	unsigned int		mLoopbackPort			: 1;
	/** 
	* @brief Indicates if the port is a critical traffic port
	**/
	unsigned int		mCtPort					: 1;
#else
	unsigned int		mCtPort					: 1;
	unsigned int		mLoopbackPort			: 1;
	unsigned int		mReserved				: 27;
	unsigned int		mMessageReceivedEvent	: 1;
	unsigned int		mBufferOverflowEvent	: 1;
	unsigned int		mInvalidMessageEvent	: 1;
#endif
} A664RxMessagePortEventData;

/** 
* @brief Interrupt handler callback function pointer
* @param[in] apEventInfo Event Information specifying the type, source, and other information about the event
* @param[in] apUserData  Pointer to the user application data. This is the pointer to the user data provided when the Event handler is registered.
**/
typedef void (A664EventFunc(A664EventInfo* apEventInfo, void* apUserData));

/** 
* @brief Registers the Event handler function which is to be used for Events originating from the End System.
* @param[in] aEndSystemHandle The handle for the End System Device.
* @param[in] apEventFunc A pointer to the user defined event handler function. This is the user application function that is
*            invoked for each ES event.
* @param[in] apUserData A pointer to user/application controlled data. This pointer will be passed into the Event callback.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664ESRegisterEventHandler(A664EndSystemHandle aEndSystemHandle, A664EventFunc* apEventFunc, void* apUserData);



/**@}	(end defgroup a664ApiEs)	*/

/**
* \defgroup a664ApiTxMessages A664 API Transmit Functions
* @{
*
* @section Overview
* <p>
* This section contains the A664 Library functions that
* are used by the application program to perform Transmit
* operations on the End System.
* </p>
*/

/**
* @brief General Container for Tx Message Port Handles. This type is used for input parameters to functions
* not requiring a Tx Message Port Type specific handle.
*/
typedef void* A664TxMessagePortHandle;

/** 
* @brief Handle for Tx COM_UDP  type message ports
**/
typedef struct a664TxComUdpHandle
{
	A664TxMessagePortHandle handle;
} A664TxComUdpHandle;
/**
* @brief Open a COM_UDP (UDP COMMUNICATIONS) Type of message port for communications. A handle to be used for subsequent
* functions operating on the message port is returned.
* @param[in] aEndSystemHandle The handle to the End System Device
* @param[in] aPortId The ID of the Port as defined in the End System Configuration. Valid values are 0 - 1023.
* @param[out] aTxComUdpHandle The handle to the COM_UDP port.
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxComUdpOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId ,
							   A664TxComUdpHandle* aTxComUdpHandle);

/** 
* @brief Writes Data to the COM_UDP (Sampling or Queuing) type message port
* @param[in] aTxComUdpHandle The handle to the COM_UDP port
* @param[in] aDataLength The number of bytes of data in aTxComUdpData to write. 
                         Max Value: 1471 (sampling, limited by port configuration and sequence numbering)
						 8192 (queuing, limited by port configuration)
* @param[in] aTxComUdpData The data to write to the port
* @param[out] aBytesWritten The number of bytes successfully written to the message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxComUdpWrite(const A664TxComUdpHandle aTxComUdpHandle, const uint16_t aDataLength, 
							    const void* aTxComUdpData, uint16_t* aBytesWritten);

/** 
* @brief Closes the COM_UDP type port
* @param[in] aTxComUdpHandle The handle to the COM_UDP port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxComUdpClose(const A664TxComUdpHandle aTxComUdpHandle);

/** 
* @brief Handle for a SAP_UDP Type Tx Message Port
**/
typedef struct a664TxSapUdpHandle
{
	A664TxMessagePortHandle handle;
} A664TxSapUdpHandle;

/** 
*  @brief  An IP Address represented as a raw 32-bit value.
**/
typedef  uint32_t  A664IpAddress;

/** 
* @brief A User Datagram Protocol (UDP) port address
**/
typedef  uint16_t       A664UdpAddress;
/** 
* @brief Opens an SAP_UDP type Tx Message Port and returns a port handle to be used
*        as input for subsequent functions performing operations on the Tx Message Port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The Port ID of the message port to be opened. This is the Port ID specified in the 
*                    configuration created by the TTE-Tools. Valid values are 0 - 1023.
* @param[out] aTxSapUdpHandle The handle to the SAP_UDP Tx Message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxSapUdpOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
								A664TxSapUdpHandle* aTxSapUdpHandle);
/** 
* @brief Writes a message to an SAP_UDP type Tx Message Port
* @param[in] aTxSapUdpHandle The handle to the SAP_UDP Tx Message port
* @param[in] aDestIpAddress The Destination IP Address to which this message should be sent
* @param[in] aDestUdpAddress The Destination UDP Port to which this message should be sent
* @param[in] aDataLength The length (in bytes) of the message data (pointed to by aTxSapUdpData).
*                        Max Value: 8192 (Limited by port configuration)
* @param[in] aTxSapUdpData Pointer to the message data to be transmitted
* @param[out] aBytesWritten The number of bytes successfully written to the message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxSapUdpWrite(const A664TxSapUdpHandle  aTxSapUdpHandle, const A664IpAddress aDestIpAddress,
								const A664UdpAddress aDestUdpAddress, const uint16_t aDataLength,
								const void* aTxSapUdpData, uint16_t* aBytesWritten);
/** 
* @brief Closes a SAP_UDP Tx Message port and releases the port handle
* @param[in] aTxSapUdpHandle The handle to the associated Tx SAP_UDP message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxSapUdpClose(const A664TxSapUdpHandle aTxSapUdpHandle);

/** 
* UNDOCUMENTED FUNCTION
* Changes the source UDP port.
* param[in] aTxSapUdpHandle The handle to the associated Tx SAP_UDP port.
* param[out] aUdpSrcPort The UDP source port to be set.
* returns A664_API_OK upon successful completion.
**/
A664_API_FUNC  a664TxSapUdpChgSrcPort(	const A664TxSapUdpHandle  aTxSapUdpHandle,
									  const A664UdpAddress      aUdpSrcPort);
/** 
* @brief Handle for an SAP_IP type Tx Message Port
**/
typedef struct a664TxSapIpHandle
{
	A664TxMessagePortHandle handle;
} A664TxSapIpHandle;
/** 
* @brief Opens a Tx SAP_IP type message port and returns the port handle to be used in subsequent operation
*        on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The Port ID as specified in the input to the TTE-Tools ES configuration. Valid values are 0 - 1023.
* @param[out] aTxSapIpHandle The handle to the associated Tx SAP_IP message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxSapIpOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
							   A664TxSapIpHandle* aTxSapIpHandle);
/** 
* @brief Writes a message to a Tx SAP_IP type message port
* @param[in] aTxSapIpHandle The handle to the associated Tx SAP_IP message port
* @param[in] aDestIpAddress The Destination IP Address to which this message should be sent
* @param[in] aDataLength The length (in bytes) of the message data (pointed to by aTxSapIpData).
*                        Max Value: 8200 (Limited by port configuration)
* @param[in] aTxSapIpData Pointer to the message data to be transmitted
* @param[out] aBytesWritten The number of bytes successfully written to the message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxSapIpWrite(const A664TxSapIpHandle aTxSapIpHandle, const A664IpAddress aDestIpAddress, 
								const uint16_t aDataLength, const void* aTxSapIpData, uint16_t* aBytesWritten);
/** 
* @brief Closes a SAP_IP Tx Message port and releases the port handle
* @param[in] aTxSapIpHandle The handle to the associated Tx SAP_IP message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxSapIpClose(const A664TxSapIpHandle aTxSapIpHandle);

/** 
* @brief Handle for a TX SAP_MAC Type Message port
**/
typedef struct a664TxSapMacHandle
{
	A664TxMessagePortHandle handle;
} A664TxSapMacHandle;
/** 
* @brief Opens a Tx SAP_MAC type port and returns a port handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The Port ID as specified in the input to the TTE-Tools ES configuration. Valid values are 0 - 1023.
* @param[out] aTxSapMacHandle The handle to the associated Tx SAP_MAC message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxSapMacOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId, A664TxSapMacHandle* aTxSapMacHandle);
/** 
* @brief Writes a message to a Tx SAP_MAC type message port
* @param[in] aTxSapMacHandle The handle to the associated Tx SAP_MAC message port
* @param[in] aDataLength The length (in bytes) of the message data (pointed to by aTxSapMacData).
*                        Max Value: 1500 (Limited by port configuration and sequence numbering)
* @param[in] aTxSapMacData Pointer to the message data to be transmitted
* @param[out] aBytesWritten The number of bytes successfully written to the message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxSapMacWrite(const A664TxSapMacHandle aTxSapMacHandle, const uint16_t aDataLength, 
								const void* aTxSapMacData, uint16_t* aBytesWritten);
/** 
* @brief Closes a SAP_MAC Tx Message port and releases the port handle
* @param[in] aTxSapMacHandle The handle to the associated Tx SAP_MAC message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxSapMacClose(const A664TxSapMacHandle aTxSapMacHandle);

/** 
* @brief Handle for a COTS_MAC type Tx Message port
**/
typedef struct a664TxCotsMacHandle
{
	A664TxMessagePortHandle handle;
} A664TxCotsMacHandle;
/** 
* @brief Opens a Tx COTS_MAC type port and returns a port handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The Port ID as specified in the input to the TTE-Tools ES configuration. Valid values are 0 - 1023.
* @param[out] aTxCotsMacHandle The handle to the associated Tx COTS_MAC message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxCotsMacOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
								 A664TxCotsMacHandle* aTxCotsMacHandle);
/** 
* @brief A MAC/Ethernet Address
**/
typedef struct  
{
	/** 
	* @brief The upper (high order) 16 bits of the MAC Address
	**/
	uint16_t     mMacAddressHigh;
	/** 
	* @brief The lower (low order) 32 bits of the MAC Address
	**/
	uint32_t     mMacAddressLow;
} A664MacAddress;
/** 
* @brief MAC Type Length Field
**/
typedef  uint16_t     A664MacTypeLen;

/** 
* @brief Writes a message to a Tx COTS_MAC type message port
* @param[in] aTxCotsMacHandle The handle to the associated Tx COTS_MAC message port
*.@param[in] aDestMacAddress The destination MAC Address to which the message shall be sent
* @param[in] aMacTypeLen The value to be inserted into the MAC Type/Len field of the outgoing message. If set to 0
*                        the End System will automatically fill this field with the correct length value.
* @param[in] aDataLength The length (in bytes) of the message data (pointed to by aTxCotsMacData).
*                        Max Value: 1500 (1518 - MacDest - MacSrc - MacType - CRC).
* @param[in] aTxCotsMacData Pointer to the message data to be transmitted
* @param[out] aBytesWritten The number of bytes successfully written to the message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxCotsMacWrite(const A664TxCotsMacHandle  aTxCotsMacHandle, const A664MacAddress aDestMacAddress,
								  const A664MacTypeLen aMacTypeLen, const uint16_t aDataLength,
								  const void* aTxCotsMacData, uint16_t* aBytesWritten);
/** 
* @brief Closes a COTS_MAC Tx Message port and releases the port handle
* @param[in] aTxCotsMacHandle The handle to the associated Tx COTS_MAC message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxCotsMacClose(const A664TxCotsMacHandle aTxCotsMacHandle);

/** 
* @brief Handle for a COTS_MAC_RAW type Tx Message port
**/
typedef struct a664TxCotsMacRawHandle
{
	A664TxMessagePortHandle handle;
} A664TxCotsMacRawHandle;

/** 
* @brief Opens a Tx COTS_MAC_RAW type port and returns a port handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The Port ID as specified in the input to the TTE-Tools ES configuration. Valid values are 0 - 1023.
* @param[out] aTxCotsMacRawHandle The handle to the associated Tx COTS_MAC_RAW message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxCotsMacRawOpen(const A664EndSystemHandle aEndSystemHandle, 
									const uint32_t aPortId,
									A664TxCotsMacRawHandle* aTxCotsMacHandle);

/** 
* @brief Writes a message to a Tx COTS_MAC_RAW type message port
* @param[in] aTxCotsMacRawHandle The handle to the associated Tx COTS_MAC_RAW message port which can be used for timed playback
* @param[in] aDataLength The length (in bytes) of the data (pointed to by aTxCotsMacRawData).
*                        Max Value: 1514 (1518 - CRC).
* @param[in] aTxCotsMacData Pointer to the message data to be transmitted, this included the Mac header and payload
* @param[in] aTime Pointer to the timestamp for the frame, the frame will be sent out at this time minus time zero
* @param[in] aSetBaseTime If this is non zero then aTime + (nanoseconds)aSetBaseTime will be set as time zero for the COTS_MAC_RAW Tx ports on the ES, other than the first frame in the sequence it should be set to 0
* @param[out] aBytesWritten The number of bytes successfully written to the message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxCotsMacRawWrite(const A664TxCotsMacRawHandle  aTxCotsMacRawHandle, 
									 const uint16_t aDataLength, 
									 const void* aTxCotsMacRawData, 
									 const A664Timestamp* aTime, 
									 const uint32_t aSetBaseTime,
									 uint16_t* aBytesWritten);

/** 
* @brief Closes a COTS_MAC_RAW Tx Message port and releases the port handle
* @param[in] aTxCotsMacRawHandle The handle to the associated Tx COTS_MAC_RAW message port
* @return @link error Error Code @endlink 
**/
A664_API_FUNC  a664TxCotsMacRawClose(const A664TxCotsMacRawHandle aTxCotsMacRawHandle);

/** 
* @brief Specifier of Tx Message Port Type
**/
typedef enum
{
	/** 
	* @brief Disabled Tx Message Port
	**/
	A664_TX_DISABLED         = 0,
	/**
	* @brief SAP_UDP Type Tx Message Port
	**/
	A664_TX_SAP_UDP          = 1,
	/**
	* @brief SAP_IP Type Tx Message Port
	**/
	A664_TX_SAP_IP           = 2,
	/**
	* @brief SAP_MAC Type Tx Message Port
	**/
	A664_TX_SAP_MAC          = 3,
	/**
	* @brief COM_UDP (Sampling) Type Tx Message Port
	**/
	A664_TX_COM_UDP_SAMPLING = 4,
	/**
	* @brief COM_UDP (Queuing) Type Tx Message Port
	**/
	A664_TX_COM_UDP_QUEUING  = 5,
	/**
	* @brief COTS_MAC_RAW Type Tx Message Port
	**/
	A664_TX_COTS_MAC_RAW     = 6,
	/**
	* @brief COTS_MAC Type Tx Message Port
	**/
	A664_TX_COTS_MAC         = 7
} A664TxMessagePortType;
/** 
* @brief Tx Message Port Control Data
**/
typedef struct 
{
#ifndef __VXWORKS__
	/** 
	* @brief Enables (True) or Disables (False) Events on invalid messages for the message port
	**/
	unsigned int mInvalidMessageEventEnable		: 1;
	/** 
	* @brief Enables (True) or Disables (False) Events on message port buffer overflows for the message port. 
	*        The message port buffer overflow events occur when VL buffer associated to the message port overflows.
	**/
	unsigned int mBufferOverflowEventEnable		: 1;
	/** 
	* @brief Enables (True) or Disables (False) Events on valid messages sent for the message port
	**/
	unsigned int mMessageSentEventEnable		: 1;
	unsigned int	mReserved					: 28;
	/** 
	* @brief Enables (True) or Disables (False) the message port for sending messages
	**/
	unsigned int mMessagePortEnable				: 1;
#else
	unsigned int mMessagePortEnable				: 1;
	unsigned int	mReserved					: 28;
	unsigned int mMessageSentEventEnable		: 1;
	unsigned int mBufferOverflowEventEnable		: 1;
	unsigned int mInvalidMessageEventEnable		: 1;
#endif
} A664TxMessagePortControl;
/** 
* @brief Sets the control settings for a Tx Message Port
* @param[in] aTxMessagePortHandle The handle of the Tx Message Port for which the control settings
*            shall be set
* @param[in] apTxMessagePortControl The structure containing the Tx Message Port control settings
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664TxSetMessagePortControl(const A664TxMessagePortHandle aTxMessagePortHandle, A664TxMessagePortControl* apTxMessagePortControl);


/** 
* @brief Tx Message Port Status Information
**/
typedef struct  
{
	/** 
	* @brief The Type of Tx Message Port
	**/
	A664TxMessagePortType mTxMessagePortType;
	/**
	* @brief The Port ID
	**/
	uint32_t			mPortId;
	/** 
	* @brief The ES Index
	**/
	uint32_t			mEsIndex;
	/** 
	* @brief Count of valid messages transmitted from the Tx Message Port
	**/
	uint32_t              mValidMessageCount;
	/** 
	* @brief Count of invalid messages submitted to the Tx Message Port for transmission. 
	*        Messages may be invalid due to containing more data than the maximum message size
	*        configured for the port or due to the message written to the port being of the incorrect
	*        type (that is not matching the Tx Message Port Type)
	**/
	uint32_t              mInvalidMessageCount;
	/** 
	* @brief Count of messages not transmitted from the Tx Message Port due to no buffer resources 
	*        being available in the lower layer Sub Virtual Link associated to the Tx Message Port
	**/
	uint32_t              mNoBufferAvailableErrorCount;
	/** 
	* @brief Count of full buffers in the CT or BE Queue
	**/
	uint32_t              mNumFullBuffers;
	/** 
	* @brief Count of empty buffers in the CT or BE Queue
	**/
	uint32_t              mNumEmptyBuffers;
	/** 
	* @brief Indicates the control bits for the port
	**/
	A664TxMessagePortControl	mMessagePortControl;
} A664TxMessagePortStatus;
/**
* @brief Gets the status information for a Tx Message Port
* @param[in]  aTxMessagePortHandle The handle of the Tx Message Port from which the status information 
*             shall be retrieved
* @param[out] aTxMessagePortStatus The structure containing the Tx Message Port Status data
* @return @link error Error Code @endlink 
**/
A664_API_FUNC a664TxGetMessagePortStatus(const A664TxMessagePortHandle aTxMessagePortHandle, A664TxMessagePortStatus* aTxMessagePortStatus);
/** 
* @brief Tx UDP Layer Status Information
**/
typedef struct  
{
	/** 
	* @brief Count of the total number of messages processed by the Tx UDP layer
	**/
	uint32_t             mTotalMessageCount;
	/** 
	* @brief Count of the number of invalid messages received at the Tx UDP layer for transmission
	*        This field is the sum of all of the Invalid Message Counts of the Tx Message Ports
	**/
	uint32_t             mInvalidMessageCount;
	/** 
	* @brief Count of the number of messages submitted for transmission by the host for which 
	*        no configured Tx Message port is defined. 
	**/
	uint32_t             mNoPortCount;
} A664TxUdpStatus;
/** 
* @brief Gets the status information for the Tx UDP Protocol Layer
* @param[in]  aEndSystemHandle The handle to the End System Device
* @param[out]  aTxUdpStatus The structure containing the Tx UDP Layer Status Information
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxGetUdpStatus(const A664EndSystemHandle aEndSystemHandle, A664TxUdpStatus* aTxUdpStatus);
/** 
* @brief Tx IP Layer Status Information
**/
typedef struct  
{
	/** 
	* @brief Count of the total number of packets processed by the Tx IP layer
	**/
	uint32_t            mTotalPacketCount;
	/** 
	* @brief Count of the number of invalid packets processed by the Tx IP layer
	**/
	uint32_t            mInvalidPacketCount;
	/** 
	* @brief Count of the number of packets discarded by the Tx IP layer. Packets can
	*        be discarded for example if there are no available resources in the MAC
	*        layer for transmission of the packet
	**/
	uint32_t            mDicardCount;
} A664TxIpStatus;
/** 
* @brief Gets the status information for the Tx IP Protocol Layer
* @param[in]   aEndSystemHandle The handle to the End System Device
* @param[out]  aTxIpStatus The structure containing the Tx IP Layer Status Information
* @return @link error Error Code@endlink
**/
A664_API_FUNC  a664TxGetIpStatus(const A664EndSystemHandle aEndSystemHandle, A664TxIpStatus* aTxIpStatus);

typedef struct a664TxLoopbackError
{
	/** 
	* @brief Start of Frame Error (e.g. invalid preamble)
	**/
	unsigned int mSofError				: 1;
	/** 
	* @brief Frame Size Error (smaller than 64 or larger than 2047)
	**/
	unsigned int mFrameSizeError		: 1;
	/** 
	* @brief Alignment Error (symbols not coming in at correct intervals)
	**/
	unsigned int mAlignmentError		: 1;
	/**
	* @brief MII Error (the TX MAC aborted the transmission)
	**/
	unsigned int mMiiError				: 1;
	/**
	* @Brief CRC Error (the final checksum is not correct)
	**/
	unsigned int mCrcError				: 1;
	unsigned int mReserved				: 27;
} A664TxLoopbackError;

/**
* @brief **Deprecated** use a664RxLoopbackRead() instead. 
* Reads a message from a Tx Loopback frame interface
* @param[in] aEndSystemHandle The handle to the ES Device
* @param[in] aNetwork The network interface from which to read a frame
* @param[in] aMaxDataBytes The maximum number of data bytes that can be read. This is the size of the 
*                          buffer allocated by the application to store the read data (pointed to by aRxLoopbackMacDataBuffer)
* @param[in] aTxLoopbackMacDataBuffer Pointer to the data buffer that is to hold the read message port data. The data stored in 
*                                 this buffer will be the entire MAC frame.
* @param[out] aBytesRead The actual number of message payload bytes read from the port.
* @param[out] aTime The time at which the frame was received
* @param[out] aLoopbackError Errors detected on the transmission
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664TxLoopbackMacRead(const A664EndSystemHandle aEndSystemHandle, 
									const A664NetworkInterface aNetwork,  
									const uint16_t aMaxDataBytes, 
									void* aTxLoopbackMacDataBuffer, 
									uint16_t* aBytesRead, 
									A664Timestamp* aTime,
									A664TxLoopbackError* aLoopbackError);

/**@}	(end defgroup a664ApiTxMessages)	*/

/**
* \defgroup a664ApiRxMessages A664 API Receive Functions
* @{
*
* @section Overview
* <p>
* This section contains the A664 Library functions that
* are used by the application program to perform Receiver/Read
* operations on the End System.
* </p>
*/

/** 
* @brief General Container for Rx Message Port Handle
**/
typedef void* A664RxMessagePortHandle;

/** 
* @brief Handle for an Rx COM_UDP type message port
**/
typedef struct a664RxComUdpHandle
{
	A664RxMessagePortHandle handle;
} A664RxComUdpHandle;

/** 
* @brief Opens an Rx COM_UDP type message port and returns a handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The ID of the Port to be opened as defined in the End System Configuration. Valid values are 0 - 4095.
* @param[out] aRxComUdpHandle The handle to the associated Rx COM_UDP port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxComUdpOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
							   A664RxComUdpHandle* aRxComUdpHandle);

/** 
* @brief Closes a COM_UDP Rx Message port and releases the port handle
* @param[in] aRxComUdpHandle The handle to the associated Rx COM_UDP port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxComUdpClose(const A664RxComUdpHandle aRxComUdpHandle);

/** 
* @brief Reads a message from an Rx COM_UDP message port
* @param[in] aRxComUdpHandle The handle to the associated Rx COM_UDP port.
* @param[in] aMaxDataBytes The maximum number of data bytes that can be read. This is the size of the 
*                          buffer allocated by the application to store the read data (pointed to by aRxComUdpDataBuffer)
* @param[in] aRxComUdpDataBuffer Pointer to the data buffer that is to hold the read message port data. The data stored
*                                in this buffer will be the UDP payload data.
* @param[out] aBytesRead The actual number of message payload bytes read from the port.
* @param[out] aNetwork The channel (network) from which the data was received.
* @param[out] aTime The time at which the message was received
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxComUdpRead(const A664RxComUdpHandle aRxComUdpHandle, const uint16_t aMaxDataBytes,
							   void* aRxComUdpDataBuffer, uint16_t* aBytesRead, A664NetworkInterface* aNetwork,
							   A664Timestamp* aTime);

/** 
* @brief Handle for an Rx SAP_UDP type message port
**/
typedef struct a664RxSapUdpHandle
{
	A664RxMessagePortHandle handle;
} A664RxSapUdpHandle;

/** 
* @brief Opens an Rx SAP_UDP type message port and returns a handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The ID of the Port to be opened as defined in the End System Configuration. Valid values are 0 - 4095.
* @param[out] aRxSapUdpHandle The handle to the associated Rx SAP_UDP port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxSapUdpOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
							   A664RxSapUdpHandle* aRxSapUdpHandle);

/** 
* @brief Closes a SAP_UDP Rx Message port and releases the port handle
* @param[in] aRxSapUdpHandle The handle to the associated Rx SAP_UDP port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC  a664RxSapUdpClose(const A664RxSapUdpHandle aRxSapUdpHandle);

/** 
* @brief Reads a message from an Rx SAP_UDP message port
* @param[in] aRxSapUdpHandle The handle to the associated Rx SAP_UDP port.
* @param[in] aMaxDataBytes The maximum number of data bytes that can be read. This is the size of the 
*                          buffer allocated by the application to store the read data (pointed to by aRxSapUdpDataBuffer)
* @param[in] aRxSapUdpDataBuffer Pointer to the data buffer that is to hold the read message port data. The data stored in
*                                this buffer will be the UDP payload data.
* @param[out] aBytesRead The actual number of message payload bytes read from the port.
* @param[out] aNetwork The channel (network) from which the data was received.
* @param[out] aIpSourceAddress The IP Source address of the read message.
* @param[out] aUdpSourcePort The UDP Source port of the read message.
* @param[out] aTime The time at which the message was received
* @return @link error Error Code@endlink
**/
A664_API_FUNC  a664RxSapUdpRead(const A664RxSapUdpHandle aRxSapUdpHandle, const uint16_t aMaxDataBytes,
							    void* aRxSapUdpDataBuffer, uint16_t* aBytesRead, A664NetworkInterface* aNetwork ,
								A664IpAddress* aIpSourceAddress, A664UdpAddress* aUdpSourcePort,
								A664Timestamp* aTime);

/** 
* UNDOCUMENTED FUNCTION
* Changes the destination UDP port and clears out the queue.
* param[in] aRxSapUdpHandle The handle to the associated Rx SAP_UDP port.
* param[out] aUdpDestPort The UDP destination port to be set.
* returns A664_API_OK upon successful completion.
**/
A664_API_FUNC  a664RxSapUdpChgDestPort(	const A664RxSapUdpHandle		aRxSapUdpHandle,
									   A664UdpAddress					aUdpDestPort);

/** 
* @brief Handle for an Rx SAP_IP type message port
**/
typedef struct a664RxSapIpHandle
{
	A664RxMessagePortHandle handle;
} A664RxSapIpHandle;

/** 
* @brief Opens an Rx SAP_IP type message port and returns a handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The ID of the Port to be opened as defined in the End System Configuration. Valid values are 0 - 4095.
* @param[out] aRxSapIpHandle The handle to the associated Rx SAP_IP port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxSapIpOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
							  A664RxSapIpHandle* aRxSapIpHandle);

/** 
* @brief Closes a SAP_IP Rx Message port and releases the port handle
* @param[in] aRxSapIpHandle The handle to the associated Rx SAP_IP port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxSapIpClose(const A664RxSapIpHandle aRxSapIpHandle);

/** 
* @brief Reads a message from an Rx SAP_IP message port
* @param[in] aRxSapIpHandle The handle to the associated Rx SAP_IP port.
* @param[in] aMaxDataBytes The maximum number of data bytes that can be read. This is the size of the 
*                          buffer allocated by the application to store the read data (pointed to by aRxSapIpDataBuffer)
* @param[in] aRxSapIpDataBuffer Pointer to the data buffer that is to hold the read message port data. The data stored in
*                               this buffer will be the IP Packet Payload.
* @param[out] aBytesRead The actual number of message payload bytes read from the port.
* @param[out] aNetwork The channel (network) from which the data was received.
* @param[out] aIpSourceAddress The IP Source address of the read message.
* @param[out] aTime The time at which the message was received
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxSapIpRead(const A664RxSapIpHandle aRxSapIpHandle, const uint16_t aMaxDataBytes ,
							  void* aRxSapIpDataBuffer, uint16_t* aBytesRead, A664NetworkInterface* aNetwork,
							  A664IpAddress* aIpSourceAddress, A664Timestamp* aTime);

/** 
* @brief Handle for an Rx SAP_MAC type message port
**/
typedef struct a664RxSapMacHandle
{
	A664RxMessagePortHandle handle;
} A664RxSapMacHandle;

/** 
* @brief Opens an Rx SAP_MAC type message port and returns a handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The ID of the Port to be opened as defined in the End System Configuration. Valid values are 0 - 4095.
* @param[out] aRxSapMacHandle The handle to the associated Rx SAP_MAC port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxSapMacOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
							   A664RxSapMacHandle* aRxSapMacHandle);

/** 
* @brief Closes a SAP_MAC Rx Message port and releases the port handle
* @param[in] aRxSapMacHandle The handle to the associated Rx SAP_MAC port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxSapMacClose(const A664RxSapMacHandle aRxSapMacHandle);

/** 
* @brief Reads a message from an Rx SAP_MAC message port
* @param[in] aRxSapMacHandle The handle to the associated Rx SAP_MAC port.
* @param[in] aMaxDataBytes The maximum number of data bytes that can be read. This is the size of the 
*                          buffer allocated by the application to store the read data (pointed to by aRxSapMacDataBuffer)
* @param[in] aRxSapMacDataBuffer Pointer to the data buffer that is to hold the read message port data. The data stored
*                                in this buffer will be the MAC Frame payload data (Does not include the MAC header,
*                                VL Sequence Number or MAC CRC).
* @param[out] aBytesRead The actual number of message payload bytes read from the port.
* @param[out] aNetwork The channel (network) from which the data was received
* @param[out] aTime The time at which the frame was received
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxSapMacRead(const A664RxSapMacHandle aRxSapMacHandle, const uint16_t aMaxDataBytes,
							   void* aRxSapMacDataBuffer, uint16_t* aBytesRead, A664NetworkInterface* aNetwork,
							   A664Timestamp* aTime);

/** 
* @brief Handle for an Rx COTS_MAC type message port
**/
typedef struct a664RxCotsMacHandle
{
	A664RxMessagePortHandle handle;
} A664RxCotsMacHandle;

/** 
* @brief Opens an Rx COTS_MAC type message port and returns a handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aPortId The ID of the Port to be opened as defined in the End System Configuration. Valid values are 0 - 31.
* @param[out] aRxCotsMacHandle The handle to the associated Rx COTS_MAC port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxCotsMacOpen(const A664EndSystemHandle aEndSystemHandle, const uint32_t aPortId,
								A664RxCotsMacHandle* aRxCotsMacHandle);

/** 
* @brief Closes a COTS_MAC Rx Message port and releases the port handle
* @param[in] aRxCotsMacHandle The handle to the associated Rx COTS_MAC port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxCotsMacClose(const A664RxCotsMacHandle aRxCotsMacHandle);

/** 
* @brief Reads a message from an Rx COTS_MAC message port
* @param[in] aRxCotsMacHandle The handle to the associated Rx COTS_MAC port.
* @param[in] aMaxDataBytes The maximum number of data bytes that can be read. This is the size of the 
*                          buffer allocated by the application to store the read data (pointed to by aRxCotsMacDataBuffer)
* @param[in] aRxCotsMacDataBuffer Pointer to the data buffer that is to hold the read message port data. The data stored in 
*                                 this buffer will be the entire MAC frame (excluding the 4 byte MAC CRC).
* @param[out] aBytesRead The actual number of message payload bytes read from the port.
* @param[out] aNetwork The channel (network) from which the data was received.
* @param[out] aTime The time at which the frame was received
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxCotsMacRead(const A664RxCotsMacHandle aRxCotsMacHandle, const uint16_t aMaxDataBytes,
							    void* aRxCotsMacDataBuffer, uint16_t* aBytesRead, A664NetworkInterface* aNetwork,
								A664Timestamp* aTime);

/** 
* @brief Handle for a Loopback type message port
**/
typedef struct a664RxLoopbackHandle
{
	A664RxMessagePortHandle handle;
} A664RxLoopbackHandle;

typedef struct a664RxLoopbackError
{
#ifndef __VXWORKS__
	/** 
	* @brief Start of Frame Error (e.g. invalid preamble)
	**/
	unsigned int mSofError				: 1;
	/** 
	* @brief Frame Size Error (smaller than 64 or larger than 2047)
	**/
	unsigned int mFrameSizeError		: 1;
	/** 
	* @brief Alignment Error (symbols not coming in at correct intervals)
	**/
	unsigned int mAlignmentError		: 1;
	/**
	* @brief MII Error (the TX MAC aborted the transmission)
	**/
	unsigned int mMiiError				: 1;
	/**
	* @Brief CRC Error (the final checksum is not correct)
	**/
	unsigned int mCrcError				: 1;
	unsigned int mReserved				: 27;
#else
	unsigned int mReserved				: 27;
	unsigned int mCrcError				: 1;
	unsigned int mMiiError				: 1;
	unsigned int mAlignmentError		: 1;
	unsigned int mFrameSizeError		: 1;
	unsigned int mSofError				: 1;
#endif
} A664RxLoopbackError;

/** 
* @brief Opens a Loopback type message port and returns a handle to be used for subsequent operations on the port
* @param[in] aEndSystemHandle The handle to the associated End System device
* @param[in] aNetwork The the network of the loopback port to open.
* @param[out] aLoopbackHandle The handle to the associated Loopback port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxLoopbackOpen(const A664EndSystemHandle aEndSystemHandle, A664NetworkInterface aNetwork,
								A664RxLoopbackHandle* aLoopbackHandle);

/** 
* @brief Closes a Loopback Message port and releases the port handle
* @param[in] aLoopbackHandle The handle to the associated Loopback port.
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxLoopbackClose(const A664RxLoopbackHandle aLoopbackHandle);

/** 
* @brief Reads a message from an Rx Loopback message port
* @param[in] aLoopbackHandle The handle to the associated Loopback port.
* @param[in] aMaxDataBytes The maximum number of data bytes that can be read. This is the size of the 
*                          buffer allocated by the application to store the read data (pointed to by aRxCotsMacDataBuffer)
* @param[in] aLoopbackDataBuffer Pointer to the data buffer that is to hold the read message port data. The data stored in 
*                                 this buffer will be the entire MAC frame (excluding the 4 byte MAC CRC).
* @param[out] aBytesRead The actual number of message payload bytes read from the port.
* @param[out] aLoopbackError Error information for the port.
* @param[out] aTime The time at which the frame was received
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxLoopbackRead(const A664RxLoopbackHandle aLoopbackHandle, const uint16_t aMaxDataBytes,
								void* aLoopbackDataBuffer, uint16_t* aBytesRead, A664Timestamp* aTime,
								A664RxLoopbackError* aLoopbackError);

/** 
* @brief Status information for a Receive VL
**/
typedef struct  
{
	/** 
	* @brief Count of the number of frames that have been discarded by Redundancy Management due to the VL
	*        sequence number being outside of the acceptable range.
	**/
	uint32_t rmFailCount;
	/** 
	* @brief Count of the number of frames on the VL that have failed integrity checking on network interface A
	**/
	uint32_t icFailNetworkACount;
	/** 
	* @brief Count of the number of frames on the VL that have failed integrity checking on network interface B
	**/
	uint32_t icFailNetworkBCount;
} A664RxVLStatus;

/** 
* @brief Gets status information for an Rx Virtual Link.  The counters rmFailCount,
* icFailNetworkACount, and icFailNetworkBCount are reset to zero at power-on and
* whenever this function is invoked.  Also, none of these counters wrap-around.
* @param[in] aEndSystemHandle The handle to the End System Device
* @param[in] aVLId The Virtual Link ID
* @param[out] aRxVLStatus The VL Status Information
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxGetVLStatus(const A664EndSystemHandle aEndSystemHandle, const uint16_t aVLId,
								A664RxVLStatus* aRxVLStatus);

/** 
* @brief Rx UDP Layer Status Information
**/
typedef struct  
{
	/** 
	* @brief Count of the total number of messages processed by the Rx UDP Layer
	*        inlcudes both valid and invalid message processed
	**/
	uint32_t    mTotalMessageCount;
	/** 
	* @brief Count of the total number of invalid messages processed by the Rx UDP Layer
	*        A message may be counted as invalid if for instance it does not have a valid
	*        UDP CRC or UDP Length field
	**/
	uint32_t    mInvalidMessageCount;
	/** 
	* @brief Count of the total number of messages received at the UDP layer for which no
	*        configured message port is defined to receive.
	**/
	uint32_t    mNoPortCount;
} A664RxUdpStatus;

/** 
* @brief Gets the status information for the Rx UDP Protocol Layer
* @param[in] aEndSystemHandle The handle to the End System Device
* @param[out] aRxUdpStatus The structure containing the Rx UDP Layer Status Information
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxGetUdpStatus(const A664EndSystemHandle aEndSystemHandle, A664RxUdpStatus* aRxUdpStatus);

/** 
* @brief The Rx IP Protocol Layer status information
**/
typedef struct  
{
	/** 
	* @brief The total number of IP packets processed. Includes both valid and invalid packets
	**/
	uint32_t    mTotalPacketCount;
	/** 
	* @brief The total number of IP packet errors detected. Errors can be due to 
	*        badly formed packets, IP Checksum errors, etc.
	**/
	uint32_t    mPacketErrorCount;
	/** 
	* @brief The total number of IP packets that have been detected to have invalid IP Checksums
	**/
	uint32_t    mChecksumErrorCount;
	/** 
	* @brief The total number of IP packets that have been detected to have an unknown IP protocol. Only
	*        packets with protocol indicating UDP (17) or ICMP (1) are considered valid.
	**/
	uint32_t    mUnknownProtocolCount;
	/** 
	* @brief The total number of IP packets that have been discarded due to either detected errors
	*        or due to unavailable resorces in the IP layer
	**/
	uint32_t    mDiscardCount;
	/** 
	* @brief The total number of IP Reassembly errors that have occured in the IP layer. Reasembly errors
	*        can occur for instance if fragments are received out of order or with invalid fragment offsets
	**/
	uint32_t    mReassemblyErrorCount;
	/** 
	* @brief The total number of fragmented IP packets that are not processed (dropped) due to no resources
	*        available in the IP layer for processing the reassembly
	**/
	uint32_t    mReassemblyNoResourcesCount;
} A664RxIpStatus;

/** 
* @brief Gets the status information for the Rx IP Protocol Layer
* @param[in] aEndSystemHandle The handle to the End System Device
* @param[out] aRxIpStatus The structure containing the Rx IP Layer Status Information
* @return @link error Error Code@endlink
**/
A664_API_FUNC a664RxGetIpStatus(const A664EndSystemHandle aEndSystemHandle, A664RxIpStatus* aRxIpStatus);

/** 
* @brief Specifier of Rx Message Port Type
**/
typedef enum
{
	/** 
	* @brief Disabled Rx Message Port
	**/
	A664_RX_DISABLED         = 0,
	/** 
	* @brief SAP_UDP Type Rx Message Port
	**/
	A664_RX_SAP_UDP          = 1,
	/** 
	* @brief SAP_IP Type Rx Message Port
	**/
	A664_RX_SAP_IP           = 2,
	/** 
	* @brief SAP_MAC Type Rx Message Port
	**/
	A664_RX_SAP_MAC          = 3,
	/** 
	* @brief COM_UDP (Sampling) Type Rx Message Port
	**/
	A664_RX_COM_UDP_SAMPLING = 4,
	/** 
	* @brief COM_UDP (Queuing) Type Rx Message Port
	**/
	A664_RX_COM_UDP_QUEUING  = 5,
	/** 
	* @brief COTS_MAC Type Rx Message Port
	**/
	A664_RX_COTS_MAC         = 7,
} A664RxMessagePortType;

/** 
* @brief Rx Message Port Control Data
**/

typedef struct 
{
#ifndef __VXWORKS__
	/** 
	* @brief Enables (True) or Disables (False) Events on invalid messages received at the message port
	**/
	unsigned int mInvalidMessageEventEnable		: 1;
	/** 
	* @brief Enables (True) or Disables (False) Events on message port buffer overflows for the message port. 
	*        Port buffer overflow events occur when incoming message cannot be delivered to the message port due to a full buffer.
	**/
	unsigned int mBufferOverflowEventEnable		: 1;
	/** 
	* @brief Enables (True) or Disables (False) Events on valid messages received to the message port
	**/
	unsigned int mMessageReceivedEventEnable	: 1;
	unsigned int mReserved						: 28;
	/** 
	* @brief Enables (True) or Disables (False) the message port for receiving messages
	**/
	unsigned int mMessagePortEnable				: 1;
#else
	unsigned int mMessagePortEnable				: 1;
	unsigned int mReserved						: 28;
	unsigned int mMessageReceivedEventEnable	: 1;
	unsigned int mBufferOverflowEventEnable		: 1;
	unsigned int mInvalidMessageEventEnable		: 1;
#endif
} A664RxMessagePortControl;
/** 
* @brief Sets the control settings for a Rx Message Port
* @param[in] aRxMessagePortHandle The handle of the Rx Message Port for which the control settings
*            shall be set
* @param[in] apRxMessagePortControl The structure containing the Rx Message Port control settings
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664RxSetMessagePortControl(const A664RxMessagePortHandle aRxMessagePortHandle, A664RxMessagePortControl* apRxMessagePortControl);

/** 
* @brief Rx Message Port Status Information
**/
typedef struct  
{
	/** 
	* @brief The type of Rx Message Port
	**/
	A664RxMessagePortType   mRxMessagePortType;
	/**
	* @brief The Port ID
	**/
	uint32_t			mPortId;
	/** 
	* @brief The ES Index
	**/
	uint32_t			mEsIndex;
	/** 
	* @brief Count of valid messages received at the Rx Message Port
	**/
	uint32_t                mValidMessageCount;
	/** 
	* @brief Count of invalid messages destined the Rx Message Port but
	*         no delivered due to being invalid
	**/
	uint32_t                mInvalidMessageCount;
	/** 
	* @brief Count of valid messages not delivered to the Rx Message Port
	*         due to no available space in the port's buffer queue
	**/
	uint32_t                mNoBufferAvailableErrorCount;
	/**
	* @brief Number of full buffers in the queue
	**/
	uint16_t				mNumFullBuffers;
	/** 
	* @brief Number of empty buffers in the queue
	**/
	uint16_t				mNumEmptyBuffers;
	/** 
	* @brief Indicates the control bits for the port
	**/
	A664RxMessagePortControl	mMessagePortControl;
	
} A664RxMessagePortStatus;

/** 
* @brief Gets the status information for an Rx Message Port
* @param[in] aRxMessagePortHandle The handle to the associated Rx Message Port
* @param[out] aRxMessagePortStatus The structure containing the Rx Message Port Status Information
* @return @link error Error Code @endlink
**/
A664_API_FUNC a664RxGetMessagePortStatus(const A664RxMessagePortHandle aRxMessagePortHandle, A664RxMessagePortStatus* aRxMessagePortStatus);

/**
* UNDOCUMENTED FUNCTION
* brief Extracts a device configuration from a End System Configuration
* param[in] apEndSystemConfig The combined configuration hex data
* param[in] aDeviceType The device type of the configuration to be returned
* param[out] apConfigBufer The buffer for the configuration to be placed in
* param[in] aBufferLength The length of the user buffer provided in bytes
* return link error Error Code endlink
**/
A664_API_FUNC a664ESExtractDevice(	const void*	apEndSystemConfig, 
									uint8_t		aDeviceType, 
									void*		apConfigBufer, 
									uint32_t	aBufferLength);

/**@}	(end defgroup a664ApiRxMessages)	*/

#endif /* A664_API_H */

