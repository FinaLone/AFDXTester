/**
 * @file a664_cdef.h
 * @brief C type definitions for A664 API use
 *
 *  Created on: 12/22/2010
 *
 *  - $HeadURL: https://internal.aviftech.com/svn/Ethernet_ES/Development_ES/HostSW/trunk/a664_api/include/a664_cdef.h $
 *  - $Date: 2013-05-09 16:31:30 -0500 (Thu, 09 May 2013) $
 *  - $Revision: 2415 $
 *  - $Author: jcole $
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

#ifndef A664_CDEF_H
#define A664_CDEF_H

#ifndef  __VXWORKS__
    #include  <stdint.h>
#endif  /* __VXWORKS__ */

/* ===============================  _WIN32  ================================ */
#ifdef  _WIN32

    #ifdef __cplusplus
        /**
        * @brief API extern declarations for C++
        */
        #define _A664_EXTERN extern "C" __declspec( dllexport )
    #else /* __cplusplus */
        /**
        * @brief API extern declarations for C++
        */
        #define _A664_EXTERN __declspec( dllexport )
    #endif /* __cplusplus */

    /**
    * @brief Prototype calling conventions for standard DLL functions
    */
    #define _A664_DLL_FUNC __cdecl

    /**
    * @brief Define the endianness of the host
    */
    #define HOST_ENDIAN_LITTLE

    /**
    *  @brief  Symbol for the currently executing function's name.
    */
    #define  __func__  __FUNCTION__
#endif /* _WIN32 */


/* ============================  __VXWORKS__  ============================== */
#ifdef __VXWORKS__
    #include "vxWorks.h"
    #define  _A664_EXTERN
    #define _A664_DLL_FUNC
    #define __stdcall

#endif /* __VXWORKS__ */


/* ========================  __linux__ || __QNX__ ========================== */
#if defined(__linux__) || defined(__QNX__)
    #ifdef __cplusplus
        #define _A664_EXTERN extern "C" __attribute__ ((visibility ("default")))
    #else
        #define _A664_EXTERN __attribute__ ((visibility ("default")))
    #endif
    #define _A664_DLL_FUNC
#endif /* __linux__ */

#ifdef LYNXOS
    #ifdef __cplusplus
        #define _A664_EXTERN extern "C"
    #else
        #define _A664_EXTERN
    #endif
    #define _A664_DLL_FUNC
    #define __stdcall
#endif /* LYNXOS */

/**
 * @brief Function return value
 */
typedef int              A664Return;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/**
* @brief Full prototype information
*/
#define A664_API_FUNC _A664_EXTERN A664Return  _A664_DLL_FUNC

#endif /* A664_CDEF_H */
