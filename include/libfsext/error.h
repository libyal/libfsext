/*
 * The error code definitions for libfsext
 *
 * Copyright (C) 2010-2023, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBFSEXT_ERROR_H )
#define _LIBFSEXT_ERROR_H

#include <libfsext/types.h>

/* External error type definition hides internal structure
 */
typedef intptr_t libfsext_error_t;

/* The error domains
 */
enum LIBFSEXT_ERROR_DOMAINS
{
	LIBFSEXT_ERROR_DOMAIN_ARGUMENTS			= (int) 'a',
	LIBFSEXT_ERROR_DOMAIN_CONVERSION		= (int) 'c',
	LIBFSEXT_ERROR_DOMAIN_COMPRESSION		= (int) 'C',
	LIBFSEXT_ERROR_DOMAIN_IO			= (int) 'I',
	LIBFSEXT_ERROR_DOMAIN_INPUT			= (int) 'i',
	LIBFSEXT_ERROR_DOMAIN_MEMORY			= (int) 'm',
	LIBFSEXT_ERROR_DOMAIN_OUTPUT			= (int) 'o',
	LIBFSEXT_ERROR_DOMAIN_RUNTIME			= (int) 'r'
};

/* The argument error codes
 * to signify errors regarding arguments passed to a function
 */
enum LIBFSEXT_ARGUMENT_ERROR
{
	LIBFSEXT_ARGUMENT_ERROR_GENERIC			= 0,

	/* The argument contains an invalid value
	 */
	LIBFSEXT_ARGUMENT_ERROR_INVALID_VALUE		= 1,

	/* The argument contains a value less than zero
	 */
	LIBFSEXT_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO	= 2,

	/* The argument contains a value zero or less
	 */
	LIBFSEXT_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS	= 3,

	/* The argument contains a value that exceeds the maximum
	 * for the specific type
	 */
	LIBFSEXT_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM	= 4,

	/* The argument contains a value that is too small
	 */
	LIBFSEXT_ARGUMENT_ERROR_VALUE_TOO_SMALL		= 5,

	/* The argument contains a value that is too large
	 */
	LIBFSEXT_ARGUMENT_ERROR_VALUE_TOO_LARGE		= 6,

	/* The argument contains a value that is out of bounds
	 */
	LIBFSEXT_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS	= 7,

	/* The argument contains a value that is not supported
	 */
	LIBFSEXT_ARGUMENT_ERROR_UNSUPPORTED_VALUE	= 8,

	/* The argument contains a value that conficts with another argument
	 */
	LIBFSEXT_ARGUMENT_ERROR_CONFLICTING_VALUE	= 9
};

/* The conversion error codes
 * to signify errors regarding conversions
 */
enum LIBFSEXT_CONVERSION_ERROR
{
	LIBFSEXT_CONVERSION_ERROR_GENERIC		= 0,

	/* The conversion failed on the input
	 */
	LIBFSEXT_CONVERSION_ERROR_INPUT_FAILED		= 1,

	/* The conversion failed on the output
	 */
	LIBFSEXT_CONVERSION_ERROR_OUTPUT_FAILED		= 2
};

/* The compression error codes
 * to signify errors regarding compression
 */
enum LIBFSEXT_COMPRESSION_ERROR
{
	LIBFSEXT_COMPRESSION_ERROR_GENERIC		= 0,

	/* The compression failed
	 */
	LIBFSEXT_COMPRESSION_ERROR_COMPRESS_FAILED	= 1,

	/* The decompression failed
	 */
	LIBFSEXT_COMPRESSION_ERROR_DECOMPRESS_FAILED	= 2
};

/* The input/output error codes
 * to signify errors regarding input/output
 */
enum LIBFSEXT_IO_ERROR
{
	LIBFSEXT_IO_ERROR_GENERIC			= 0,

	/* The open failed
	 */
	LIBFSEXT_IO_ERROR_OPEN_FAILED			= 1,

	/* The close failed
	 */
	LIBFSEXT_IO_ERROR_CLOSE_FAILED			= 2,

	/* The seek failed
	 */
	LIBFSEXT_IO_ERROR_SEEK_FAILED			= 3,

	/* The read failed
	 */
	LIBFSEXT_IO_ERROR_READ_FAILED			= 4,

	/* The write failed
	 */
	LIBFSEXT_IO_ERROR_WRITE_FAILED			= 5,

	/* Access denied
	 */
	LIBFSEXT_IO_ERROR_ACCESS_DENIED			= 6,

	/* The resource is invalid i.e. a missing file
	 */
	LIBFSEXT_IO_ERROR_INVALID_RESOURCE		= 7,

	/* The ioctl failed
	 */
	LIBFSEXT_IO_ERROR_IOCTL_FAILED			= 8,

	/* The unlink failed
	 */
	LIBFSEXT_IO_ERROR_UNLINK_FAILED			= 9
};

/* The input error codes
 * to signify errors regarding handing input data
 */
enum LIBFSEXT_INPUT_ERROR
{
	LIBFSEXT_INPUT_ERROR_GENERIC			= 0,

	/* The input contains invalid data
	 */
	LIBFSEXT_INPUT_ERROR_INVALID_DATA		= 1,

	/* The input contains an unsupported signature
	 */
	LIBFSEXT_INPUT_ERROR_SIGNATURE_MISMATCH		= 2,

	/* A checksum in the input did not match
	 */
	LIBFSEXT_INPUT_ERROR_CHECKSUM_MISMATCH		= 3,

	/* A value in the input did not match a previously
	 * read value or calculated value
	 */
	LIBFSEXT_INPUT_ERROR_VALUE_MISMATCH		= 4
};

/* The memory error codes
 * to signify errors regarding memory
 */
enum LIBFSEXT_MEMORY_ERROR
{
	LIBFSEXT_MEMORY_ERROR_GENERIC			= 0,

	/* There is insufficient memory available
	 */
	LIBFSEXT_MEMORY_ERROR_INSUFFICIENT		= 1,

	/* The memory failed to be copied
	 */
	LIBFSEXT_MEMORY_ERROR_COPY_FAILED		= 2,

	/* The memory failed to be set
	 */
	LIBFSEXT_MEMORY_ERROR_SET_FAILED		= 3
};

/* The output error codes
 */
enum LIBFSEXT_OUTPUT_ERROR
{
	LIBFSEXT_OUTPUT_ERROR_GENERIC			= 0,

	/* There is insuficient space to write the output
	 */
	LIBFSEXT_OUTPUT_ERROR_INSUFFICIENT_SPACE	= 1
};

/* The runtime error codes
 * to signify errors regarding runtime processing
 */
enum LIBFSEXT_RUNTIME_ERROR
{
	LIBFSEXT_RUNTIME_ERROR_GENERIC			= 0,

	/* The value is missing
	 */
	LIBFSEXT_RUNTIME_ERROR_VALUE_MISSING		= 1,

	/* The value was already set
	 */
	LIBFSEXT_RUNTIME_ERROR_VALUE_ALREADY_SET	= 2,

	/* The creation and/or initialization of an internal structure failed
	 */
	LIBFSEXT_RUNTIME_ERROR_INITIALIZE_FAILED	= 3,

	/* The resize of an internal structure failed
	 */
	LIBFSEXT_RUNTIME_ERROR_RESIZE_FAILED		= 4,

	/* The free and/or finalization of an internal structure failed
	 */
	LIBFSEXT_RUNTIME_ERROR_FINALIZE_FAILED		= 5,

	/* The value could not be determined
	 */
	LIBFSEXT_RUNTIME_ERROR_GET_FAILED		= 6,

	/* The value could not be set
	 */
	LIBFSEXT_RUNTIME_ERROR_SET_FAILED		= 7,

	/* The value could not be appended/prepended
	 */
	LIBFSEXT_RUNTIME_ERROR_APPEND_FAILED		= 8,

	/* The value could not be copied
	 */
	LIBFSEXT_RUNTIME_ERROR_COPY_FAILED		= 9,

	/* The value could not be removed
	 */
	LIBFSEXT_RUNTIME_ERROR_REMOVE_FAILED		= 10,

	/* The value could not be printed
	 */
	LIBFSEXT_RUNTIME_ERROR_PRINT_FAILED		= 11,

	/* The value was out of bounds
	 */
	LIBFSEXT_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS	= 12,

	/* The value exceeds the maximum for its specific type
	 */
	LIBFSEXT_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM	= 13,

	/* The value is unsupported
	 */
	LIBFSEXT_RUNTIME_ERROR_UNSUPPORTED_VALUE	= 14,

	/* An abort was requested
	 */
	LIBFSEXT_RUNTIME_ERROR_ABORT_REQUESTED		= 15
};

#endif /* !defined( _LIBFSEXT_ERROR_H ) */

