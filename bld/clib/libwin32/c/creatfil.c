/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
*               DESCRIBE IT HERE!
*
****************************************************************************/


#include "variety.h"
#include <stddef.h>
#include <mbstring.h>
#include <windows.h>
#include "liballoc.h"
#include "libwin32.h"
#include "osver.h"

HANDLE __lib_CreateFileW( LPCWSTR lpFileName,
                          DWORD dwDesiredAccess,
                          DWORD dwShareMode,
                          LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                          DWORD dwCreationDisposition,
                          DWORD dwFlagsAndAttributes,
                          HANDLE hTemplateFile )
/*******************************************************************/
{
    if( WIN32_IS_NT ) {                                 /* NT */
        return( CreateFileW( lpFileName, dwDesiredAccess, dwShareMode,
                             lpSecurityAttributes, dwCreationDisposition,
                             dwFlagsAndAttributes, hTemplateFile ) );
    } else {                                            /* Win95 or Win32s */
        char *          mbFileName;
        HANDLE          osrc;
        size_t          cvt;
        size_t          len;

        /*** Allocate some memory ***/
        len = wcslen( lpFileName ) * MB_CUR_MAX + 1;
        mbFileName = lib_malloc( len );
        if( mbFileName == NULL ) {
            return( INVALID_HANDLE_VALUE );
        }

        /*** Prepare to call the OS ***/
        cvt = wcstombs( mbFileName, lpFileName, len );
        if( cvt == (size_t)-1 ) {
            lib_free( mbFileName );
            return( INVALID_HANDLE_VALUE );
        }

        /*** Call the OS ***/
        osrc = CreateFileA( mbFileName, dwDesiredAccess, dwShareMode,
                            lpSecurityAttributes, dwCreationDisposition,
                            dwFlagsAndAttributes, hTemplateFile );
        lib_free( mbFileName );
        return( osrc );
    }
}
