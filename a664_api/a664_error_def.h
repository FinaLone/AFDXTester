
/**
 * @file a664_error_def.h
 * @brief	Defines, constants, structures and function prototypes required to support
 *			the error handling interface to the API.
 *
 *  Created on: 12/21/2010
 *   
 *	- $HeadURL: https://internal.aviftech.com/svn/Ethernet_ES/Development_ES/HostSW/trunk/a664_api/include/a664_error_def.h $
 *	- $Date: 2014-02-06 11:47:43 -0600 (Thu, 06 Feb 2014) $
 *	- $Revision: 2728 $
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

#ifndef _A664_ERROR_DEF_H_
#define _A664_ERROR_DEF_H_

/**
 * \defgroup error Error: Error codes
 * @{
 *
 * @section sec_oview Overview
 * <p>
 * Each callable function in the A664 API will provide a return code upon 
 *  completion. Upon successful completion of the defined function, it 
 *  should always return with a zero value of A664_API_OK.
 *  If a function is unsuccessful at accomplishing it's defined behavior, it
 *  will return with a negative integer. A A664_API_ERROR return value of -1 is
 *  used to indicate a general error occurred that does not yet have a 
 *  unique negative error code defined.  In all other cases, unique negative 
 *  error codes are defined to describe the specific reason for the failure.  
 *  The file ( a664_error_def.h ) provides a list of all of the possible 
 *  error code return value definitions and a brief description for each.
 * </p>
 *
 */

/**
 * \defgroup generr General A664 API Library error return codes -1 to -99
 * @{
 */

/** Success	*/
#define	A664_API_OK								0
/** Generic error	*/
#define	A664_API_ERROR							-1
/** Pointer is NULL	*/
#define A664_API_ERROR_NULL_POINTER				-2
/** Parameter is invalid	*/
#define A664_API_ERROR_PARAM_INVALID			-3
/** Value is invalid	*/
#define A664_API_ERROR_VALUE_INVALID			-4
/** Function is not implemented	*/
#define A664_API_ERROR_NOT_IMPLEMENTED			-5
/** General Operating System Driver Error*/
#define A664_API_DRIVER_ERROR                   -6
/** Checksum is Invalid */
#define A664_API_ERROR_INVALID_CHECKSUM			-7
/** Tx Configuration Invalid */
#define A664_API_ERROR_INVALID_CONFIG_TX		-8
/** Rx Configuration Invalid */
#define A664_API_ERROR_INVALID_CONFIG_RX		-9
/** sNIC Configuration Invalid */
#define A664_API_ERROR_INVALID_CONFIG_SNIC		-10
/** Tx Configuration Timeout */
#define A664_API_ERROR_TIMEOUT_CONFIG_TX		-11
/** Rx Configuration Timeout */
#define A664_API_ERROR_TIMEOUT_CONFIG_RX		-12
/** sNIC Configuration Timeout */
#define A664_API_ERROR_TIMEOUT_CONFIG_SNIC		-13
/** Invalid port type */
#define A664_API_ERROR_INVALID_PORT_TYPE		-14
/** Port ID not found */
#define A664_API_ERROR_PORT_NOT_FOUND			-15
/** Queue underflow */
#define A664_API_QUEUE_UNDERFLOW                -16
/** Line exceeds maximum length */
#define A664_API_ERROR_LINE_LENGTH				-17
/** Configuration Invalid */
#define A664_API_ERROR_INVALID_CONFIG			-18
/** Invalid handle */
#define A664_API_ERROR_INVALID_HANDLE           -19
/** ES Not Found */
#define A664_API_ERROR_ES_NOT_FOUND				-20
/** Queue Header Invalid */
#define A664_API_ERROR_QUEUE_HEADER_INVALID		-21
/** Hardware needs to be updates */
#define A664_API_ERROR_UPDATE_HARDWARE			-22
/**@}	(end defgroup generr)	*/

/**
 * \defgroup adminerr Library Administration error return codes -100 to -199
 * @{
 */

/** Generic device error							*/
#define	A664_ADMIN_ERROR_GENERIC					-100
/** Buffer Full */
#define A664_ADMIN_ERROR_BUFFER_FULL				-101
/** Message Length Exceeds Buffer Entry Size */
#define A664_ADMIN_ERROR_MSG_LENGTH_EXCEEDS_BUFF_ENTRY_SIZE	-102
/** Unsupported API IO Structure Version **/
#define A664_ADMIN_UNSUPPORTED_API_IO_VERSION       -103
/**@}	(end defgroup adminerr)	*/

/**
 * \defgroup endsyserr End System error return codes  -200 to -299
 * @{
 */
/** Generic channel error	*/
#define	A664_ES_ERROR_GENERIC				-200
/**@}	(end defgroup endsyserr)	*/

/**
 * \defgroup a664txerr ES Transmit error return codes  -300 to -399
 * @{
 */

/** The specified buffer size exceeds the max transmit size */
#define A664_TX_BUFFER_SIZE_ERROR				    -300
/**@}	(end defgroup a664txerr)	*/

/**
* \defgroup a664rxerr ES Receive error return codes  -400 to -499
* @{
*/

/** The specified buffer size is not large enough for the data */
#define A664_RX_BUFFER_SIZE_ERROR                   -400
/**@}	(end defgroup a664rxerr)	*/

/**@}	(end defgroup error)	*/

#endif	/* _A664_ERROR_DEF_H_ */
