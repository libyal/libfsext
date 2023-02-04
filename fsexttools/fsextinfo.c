/*
 * Shows information obtained from an Extended File System (ext) volume
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

#include <common.h>
#include <file_stream.h>
#include <memory.h>
#include <system_string.h>
#include <types.h>

#include <stdio.h>

#if defined( HAVE_IO_H ) || defined( WINAPI )
#include <io.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#include "fsexttools_getopt.h"
#include "fsexttools_libcerror.h"
#include "fsexttools_libclocale.h"
#include "fsexttools_libcnotify.h"
#include "fsexttools_libfsext.h"
#include "fsexttools_output.h"
#include "fsexttools_signal.h"
#include "fsexttools_unused.h"
#include "info_handle.h"

enum FSEXTINFO_MODES
{
	FSEXTINFO_MODE_FILE_ENTRIES,
	FSEXTINFO_MODE_FILE_ENTRY_BY_IDENTIFIER,
	FSEXTINFO_MODE_FILE_ENTRY_BY_PATH,
	FSEXTINFO_MODE_FILE_SYSTEM_HIERARCHY,
	FSEXTINFO_MODE_VOLUME
};

info_handle_t *fsextinfo_info_handle = NULL;
int fsextinfo_abort                  = 0;

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Use fsextinfo to determine information about an Extended\n"
	                 " File System (ext) volume.\n\n" );

	fprintf( stream, "Usage: fsextinfo [ -B bodyfile ] [ -E inode_number ] [ -F file_entry ]\n"
	                 "                 [ -o offset ] [ -dhHvV ] source\n\n" );

	fprintf( stream, "\tsource: the source file or device\n\n" );

	fprintf( stream, "\t-B:     output file system information as a bodyfile\n" );
	fprintf( stream, "\t-d:     calculate a MD5 hash of a file entry to include in the bodyfile\n" );
	fprintf( stream, "\t-E:     show information about a specific inode or \"all\".\n" );
	fprintf( stream, "\t-F:     show information about a specific file entry path.\n" );
	fprintf( stream, "\t-h:     shows this help\n" );
	fprintf( stream, "\t-H:     shows the file system hierarchy\n" );
	fprintf( stream, "\t-o:     specify the volume offset\n" );
	fprintf( stream, "\t-v:     verbose output to stderr\n" );
	fprintf( stream, "\t-V:     print version\n" );
}

/* Signal handler for fsextinfo
 */
void fsextinfo_signal_handler(
      fsexttools_signal_t signal FSEXTTOOLS_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "fsextinfo_signal_handler";

	FSEXTTOOLS_UNREFERENCED_PARAMETER( signal )

	fsextinfo_abort = 1;

	if( fsextinfo_info_handle != NULL )
	{
		if( info_handle_signal_abort(
		     fsextinfo_info_handle,
		     &error ) != 1 )
		{
			libcnotify_printf(
			 "%s: unable to signal info handle to abort.\n",
			 function );

			libcnotify_print_error_backtrace(
			 error );
			libcerror_error_free(
			 &error );
		}
	}
	/* Force stdin to close otherwise any function reading it will remain blocked
	 */
#if defined( WINAPI ) && !defined( __CYGWIN__ )
	if( _close(
	     0 ) != 0 )
#else
	if( close(
	     0 ) != 0 )
#endif
	{
		libcnotify_printf(
		 "%s: unable to close stdin.\n",
		 function );
	}
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libfsext_error_t *error                          = NULL;
	system_character_t *option_bodyfile              = NULL;
	system_character_t *option_file_entry_identifier = NULL;
	system_character_t *option_file_entry_path       = NULL;
	system_character_t *option_volume_offset         = NULL;
	system_character_t *source                       = NULL;
	char *program                                    = "fsextinfo";
	system_integer_t option                          = 0;
	size_t string_length                             = 0;
	uint64_t file_entry_identifier                   = 0;
	uint8_t calculate_md5                            = 0;
	int option_mode                                  = FSEXTINFO_MODE_VOLUME;
	int verbose                                      = 0;

	libcnotify_stream_set(
	 stderr,
	 NULL );
	libcnotify_verbose_set(
	 1 );

	if( libclocale_initialize(
             "fsexttools",
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize locale values.\n" );

		goto on_error;
	}
        if( fsexttools_output_initialize(
             _IONBF,
             &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize output settings.\n" );

		goto on_error;
	}
	fsexttools_output_version_fprint(
	 stdout,
	 program );

	while( ( option = fsexttools_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "B:dE:F:hHo:vV" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM "\n",
				 argv[ optind - 1 ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (system_integer_t) 'B':
				option_bodyfile = optarg;

				break;

			case (system_integer_t) 'd':
				calculate_md5 = 1;

				break;

			case (system_integer_t) 'E':
				option_mode                  = FSEXTINFO_MODE_FILE_ENTRY_BY_IDENTIFIER;
				option_file_entry_identifier = optarg;

				break;

			case (system_integer_t) 'F':
				option_mode            = FSEXTINFO_MODE_FILE_ENTRY_BY_PATH;
				option_file_entry_path = optarg;

				break;

			case (system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'H':
				option_mode = FSEXTINFO_MODE_FILE_SYSTEM_HIERARCHY;

				break;

			case (system_integer_t) 'o':
				option_volume_offset = optarg;

				break;

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
				fsexttools_output_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file or device.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

	libcnotify_verbose_set(
	 verbose );
	libfsext_notify_set_stream(
	 stderr,
	 NULL );
	libfsext_notify_set_verbose(
	 verbose );

	if( info_handle_initialize(
	     &fsextinfo_info_handle,
	     calculate_md5,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize info handle.\n" );

		goto on_error;
	}
	if( option_bodyfile != NULL )
	{
		if( info_handle_set_bodyfile(
		     fsextinfo_info_handle,
		     option_bodyfile,
		     &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to set bodyfile.\n" );

			goto on_error;
		}
	}
	if( option_volume_offset != NULL )
	{
		if( info_handle_set_volume_offset(
		     fsextinfo_info_handle,
		     option_volume_offset,
		     &error ) != 1 )
		{
			libcnotify_print_error_backtrace(
			 error );
			libcerror_error_free(
			 &error );

			fprintf(
			 stderr,
			 "Unsupported volume offset defaulting to: %" PRIi64 ".\n",
			 fsextinfo_info_handle->volume_offset );
		}
	}
	if( info_handle_open_input(
	     fsextinfo_info_handle,
	     source,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to open: %" PRIs_SYSTEM ".\n",
		 source );

		goto on_error;
	}
	if( option_mode == FSEXTINFO_MODE_FILE_ENTRY_BY_IDENTIFIER )
	{
		if( option_file_entry_identifier == NULL )
		{
			fprintf(
			 stderr,
			 "Mising file entry identifier string.\n" );

			goto on_error;
		}
		string_length = system_string_length(
				 option_file_entry_identifier );

		if( ( string_length == 3 )
		 && ( system_string_compare(
		       option_file_entry_identifier,
		       _SYSTEM_STRING( "all" ),
		       3 ) == 0 ) )
		{
			option_mode = FSEXTINFO_MODE_FILE_ENTRIES;
		}
		else if( info_handle_system_string_copy_from_64_bit_in_decimal(
		          option_file_entry_identifier,
		          string_length + 1,
		          &file_entry_identifier,
		          &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to copy file entry identifier string to 64-bit decimal.\n" );

			goto on_error;
		}
		else if( file_entry_identifier > (uint64_t) UINT32_MAX )
		{
			fprintf(
			 stderr,
			 "Invalid file entry identifier value out of bounds." );

			goto on_error;
		}
	}
	switch( option_mode )
	{
		case FSEXTINFO_MODE_FILE_ENTRIES:
			if( info_handle_file_entries_fprint(
			     fsextinfo_info_handle,
			     &error ) != 1 )
			{
				fprintf(
				 stderr,
				 "Unable to print file entries.\n" );

				goto on_error;
			}
			break;

		case FSEXTINFO_MODE_FILE_ENTRY_BY_IDENTIFIER:
			if( info_handle_file_entry_fprint_by_identifier(
			     fsextinfo_info_handle,
			     (uint32_t) file_entry_identifier,
			     &error ) != 1 )
			{
				fprintf(
				 stderr,
				 "Unable to print file entry: %" PRIu64 ".\n",
				 file_entry_identifier );

				goto on_error;
			}
			break;

		case FSEXTINFO_MODE_FILE_ENTRY_BY_PATH:
			if( info_handle_file_entry_fprint_by_path(
			     fsextinfo_info_handle,
			     option_file_entry_path,
			     &error ) != 1 )
			{
				fprintf(
				 stderr,
				 "Unable to print file entry information.\n" );

				goto on_error;
			}
			break;

		case FSEXTINFO_MODE_FILE_SYSTEM_HIERARCHY:
			if( info_handle_file_system_hierarchy_fprint(
			     fsextinfo_info_handle,
			     &error ) != 1 )
			{
				fprintf(
				 stderr,
				 "Unable to print file system hierarchy.\n" );

				goto on_error;
			}
			break;

		case FSEXTINFO_MODE_VOLUME:
		default:
			if( info_handle_volume_fprint(
			     fsextinfo_info_handle,
			     &error ) != 1 )
			{
				fprintf(
				 stderr,
				 "Unable to print volume information.\n" );

				goto on_error;
			}
			break;
	}
	if( info_handle_close_input(
	     fsextinfo_info_handle,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close info handle.\n" );

		goto on_error;
	}
	if( info_handle_free(
	     &fsextinfo_info_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free info handle.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( fsextinfo_info_handle != NULL )
	{
		info_handle_free(
		 &fsextinfo_info_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

