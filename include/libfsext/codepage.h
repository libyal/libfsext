/*
 * Codepage definitions for libfsext
 *
 * Copyright (C) 2010-2019, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBFSEXT_CODEPAGE_H )
#define _LIBFSEXT_CODEPAGE_H

#include <libfsext/types.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* The codepage definitions
 */
enum LIBFSEXT_CODEPAGES
{
	LIBFSEXT_CODEPAGE_ASCII				= 20127,

	LIBFSEXT_CODEPAGE_ISO_8859_1			= 28591,
	LIBFSEXT_CODEPAGE_ISO_8859_2			= 28592,
	LIBFSEXT_CODEPAGE_ISO_8859_3			= 28593,
	LIBFSEXT_CODEPAGE_ISO_8859_4			= 28594,
	LIBFSEXT_CODEPAGE_ISO_8859_5			= 28595,
	LIBFSEXT_CODEPAGE_ISO_8859_6			= 28596,
	LIBFSEXT_CODEPAGE_ISO_8859_7			= 28597,
	LIBFSEXT_CODEPAGE_ISO_8859_8			= 28598,
	LIBFSEXT_CODEPAGE_ISO_8859_9			= 28599,
	LIBFSEXT_CODEPAGE_ISO_8859_10			= 28600,
	LIBFSEXT_CODEPAGE_ISO_8859_11			= 28601,
	LIBFSEXT_CODEPAGE_ISO_8859_13			= 28603,
	LIBFSEXT_CODEPAGE_ISO_8859_14			= 28604,
	LIBFSEXT_CODEPAGE_ISO_8859_15			= 28605,
	LIBFSEXT_CODEPAGE_ISO_8859_16			= 28606,

	LIBFSEXT_CODEPAGE_KOI8_R			= 20866,
	LIBFSEXT_CODEPAGE_KOI8_U			= 21866,

	LIBFSEXT_CODEPAGE_WINDOWS_874			= 874,
	LIBFSEXT_CODEPAGE_WINDOWS_932			= 932,
	LIBFSEXT_CODEPAGE_WINDOWS_936			= 936,
	LIBFSEXT_CODEPAGE_WINDOWS_949			= 949,
	LIBFSEXT_CODEPAGE_WINDOWS_950			= 950,
	LIBFSEXT_CODEPAGE_WINDOWS_1250			= 1250,
	LIBFSEXT_CODEPAGE_WINDOWS_1251			= 1251,
	LIBFSEXT_CODEPAGE_WINDOWS_1252			= 1252,
	LIBFSEXT_CODEPAGE_WINDOWS_1253			= 1253,
	LIBFSEXT_CODEPAGE_WINDOWS_1254			= 1254,
	LIBFSEXT_CODEPAGE_WINDOWS_1255			= 1255,
	LIBFSEXT_CODEPAGE_WINDOWS_1256			= 1256,
	LIBFSEXT_CODEPAGE_WINDOWS_1257			= 1257,
	LIBFSEXT_CODEPAGE_WINDOWS_1258			= 1258
};

#define LIBFSEXT_CODEPAGE_US_ASCII			LIBFSEXT_CODEPAGE_ASCII

#define LIBFSEXT_CODEPAGE_ISO_WESTERN_EUROPEAN		LIBFSEXT_CODEPAGE_ISO_8859_1
#define LIBFSEXT_CODEPAGE_ISO_CENTRAL_EUROPEAN		LIBFSEXT_CODEPAGE_ISO_8859_2
#define LIBFSEXT_CODEPAGE_ISO_SOUTH_EUROPEAN		LIBFSEXT_CODEPAGE_ISO_8859_3
#define LIBFSEXT_CODEPAGE_ISO_NORTH_EUROPEAN		LIBFSEXT_CODEPAGE_ISO_8859_4
#define LIBFSEXT_CODEPAGE_ISO_CYRILLIC			LIBFSEXT_CODEPAGE_ISO_8859_5
#define LIBFSEXT_CODEPAGE_ISO_ARABIC			LIBFSEXT_CODEPAGE_ISO_8859_6
#define LIBFSEXT_CODEPAGE_ISO_GREEK			LIBFSEXT_CODEPAGE_ISO_8859_7
#define LIBFSEXT_CODEPAGE_ISO_HEBREW			LIBFSEXT_CODEPAGE_ISO_8859_8
#define LIBFSEXT_CODEPAGE_ISO_TURKISH			LIBFSEXT_CODEPAGE_ISO_8859_9
#define LIBFSEXT_CODEPAGE_ISO_NORDIC			LIBFSEXT_CODEPAGE_ISO_8859_10
#define LIBFSEXT_CODEPAGE_ISO_THAI			LIBFSEXT_CODEPAGE_ISO_8859_11
#define LIBFSEXT_CODEPAGE_ISO_BALTIC			LIBFSEXT_CODEPAGE_ISO_8859_13
#define LIBFSEXT_CODEPAGE_ISO_CELTIC			LIBFSEXT_CODEPAGE_ISO_8859_14

#define LIBFSEXT_CODEPAGE_ISO_LATIN_1			LIBFSEXT_CODEPAGE_ISO_8859_1
#define LIBFSEXT_CODEPAGE_ISO_LATIN_2			LIBFSEXT_CODEPAGE_ISO_8859_2
#define LIBFSEXT_CODEPAGE_ISO_LATIN_3			LIBFSEXT_CODEPAGE_ISO_8859_3
#define LIBFSEXT_CODEPAGE_ISO_LATIN_4			LIBFSEXT_CODEPAGE_ISO_8859_4
#define LIBFSEXT_CODEPAGE_ISO_LATIN_5			LIBFSEXT_CODEPAGE_ISO_8859_9
#define LIBFSEXT_CODEPAGE_ISO_LATIN_6			LIBFSEXT_CODEPAGE_ISO_8859_10
#define LIBFSEXT_CODEPAGE_ISO_LATIN_7			LIBFSEXT_CODEPAGE_ISO_8859_13
#define LIBFSEXT_CODEPAGE_ISO_LATIN_8			LIBFSEXT_CODEPAGE_ISO_8859_14
#define LIBFSEXT_CODEPAGE_ISO_LATIN_9			LIBFSEXT_CODEPAGE_ISO_8859_15
#define LIBFSEXT_CODEPAGE_ISO_LATIN_10			LIBFSEXT_CODEPAGE_ISO_8859_16

#define LIBFSEXT_CODEPAGE_KOI8_RUSSIAN			LIBFSEXT_CODEPAGE_KOI8_R
#define LIBFSEXT_CODEPAGE_KOI8_UKRAINIAN		LIBFSEXT_CODEPAGE_KOI8_U

#define LIBFSEXT_CODEPAGE_WINDOWS_THAI			LIBFSEXT_CODEPAGE_WINDOWS_874
#define LIBFSEXT_CODEPAGE_WINDOWS_JAPANESE		LIBFSEXT_CODEPAGE_WINDOWS_932
#define LIBFSEXT_CODEPAGE_WINDOWS_CHINESE_SIMPLIFIED	LIBFSEXT_CODEPAGE_WINDOWS_936
#define LIBFSEXT_CODEPAGE_WINDOWS_KOREAN		LIBFSEXT_CODEPAGE_WINDOWS_949
#define LIBFSEXT_CODEPAGE_WINDOWS_CHINESE_TRADITIONAL	LIBFSEXT_CODEPAGE_WINDOWS_950
#define LIBFSEXT_CODEPAGE_WINDOWS_CENTRAL_EUROPEAN	LIBFSEXT_CODEPAGE_WINDOWS_1250
#define LIBFSEXT_CODEPAGE_WINDOWS_CYRILLIC		LIBFSEXT_CODEPAGE_WINDOWS_1251
#define LIBFSEXT_CODEPAGE_WINDOWS_WESTERN_EUROPEAN	LIBFSEXT_CODEPAGE_WINDOWS_1252
#define LIBFSEXT_CODEPAGE_WINDOWS_GREEK			LIBFSEXT_CODEPAGE_WINDOWS_1253
#define LIBFSEXT_CODEPAGE_WINDOWS_TURKISH		LIBFSEXT_CODEPAGE_WINDOWS_1254
#define LIBFSEXT_CODEPAGE_WINDOWS_HEBREW		LIBFSEXT_CODEPAGE_WINDOWS_1255
#define LIBFSEXT_CODEPAGE_WINDOWS_ARABIC		LIBFSEXT_CODEPAGE_WINDOWS_1256
#define LIBFSEXT_CODEPAGE_WINDOWS_BALTIC		LIBFSEXT_CODEPAGE_WINDOWS_1257
#define LIBFSEXT_CODEPAGE_WINDOWS_VIETNAMESE		LIBFSEXT_CODEPAGE_WINDOWS_1258

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBFSEXT_CODEPAGE_H ) */

