/*
 * Signal handling functions
 *
 * Copyright (C) 2010-2020, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _FSEXTTOOLS_SIGNAL_H )
#define _FSEXTTOOLS_SIGNAL_H

#include <common.h>
#include <types.h>

#include "fsexttools_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_SIGNAL_H ) && !defined( WINAPI )
#error missing signal functions
#endif

#if defined( WINAPI )
typedef unsigned long fsexttools_signal_t;

#else
typedef int fsexttools_signal_t;

#endif /* defined( WINAPI ) */

#if defined( WINAPI )

BOOL WINAPI fsexttools_signal_handler(
             fsexttools_signal_t signal );

#if defined( _MSC_VER )

void fsexttools_signal_initialize_memory_debug(
      void );

#endif /* defined( _MSC_VER ) */

#endif /* defined( WINAPI ) */

int fsexttools_signal_attach(
     void (*signal_handler)( fsexttools_signal_t ),
     libcerror_error_t **error );

int fsexttools_signal_detach(
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _FSEXTTOOLS_SIGNAL_H ) */

