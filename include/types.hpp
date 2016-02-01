/**
 * @file types.hpp
 *
 * @todo Add description
 *
 * @author Matthew Rodusek (matthew.rodusek@gmail.com)
 * @date   Jan 23, 2016
 *
 */

/*
 * Change Log:
 *
 * Jan 23, 2016: 
 * - types.hpp created
 */
#ifndef INCLUDE_TYPES_HPP_
#define INCLUDE_TYPES_HPP_

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <cstddef>
#include <climits>
#include <SDL2/SDL.h>

namespace vdk{

#if (UCHAR_MAX == 0xff)
	typedef signed char   s8;  /* signed byte   */
	typedef unsigned char u8; /* unsigned byte */
#else
	#error "No 8-bit sized type available."
#endif

#if (USHRT_MAX == 0xffff)
	typedef signed short   s16;  /* signed 16 bit integer   */
	typedef unsigned short u16;  /* unsigned 16 bit integer */
#elif (UINT_MAX == 0xffff)
	typedef signed int     s16;  /* signed 16 bit integer   */
	typedef unsigned int   u16;  /* unsigned 16 bit integer */
#endif

#if (UINT_MAX == 0xffffffffL)
	typedef signed int    s32;  /* signed 32 bit integer   */
	typedef unsigned int  u32;  /* unsigned 32 bit integer */
#elif (ULONG_MAX == 0xffffffffL)
	typedef signed long   s32;  /* signed 32 bit integer   */
	typedef unsigned long u32;  /* unsigned 32 bit integer */
#endif

	//--------------------------------------------------------------------------
	// System-Specific Lexical Types
	//--------------------------------------------------------------------------

	typedef signed char    byte;       ///< Signed 1-byte primitive
	typedef unsigned char  ubyte;      ///< Unsigned 1-byte primitive
	typedef int            word;       ///< Signed instruction-sized integer (Word)
	typedef unsigned int   uword;      ///< Unsigned instruction-sized integer (Word)

	//---------------------------------------------------------------------------

	typedef unsigned char  uchar;      ///< Unsigned char type
	typedef unsigned short ushort;     ///< Unsigned short type
	typedef unsigned int   uint;       ///< Unsigned int type
	typedef unsigned long  ulong;      ///< Unsigned long type

	typedef float  f32;
	typedef double f64;
	typedef long double highp;

	//--------------------------------------------------------------------------

	typedef SDL_Rect Rect;
	typedef SDL_Point Point;

} // namespace valknut

#endif /* INCLUDE_TYPES_HPP_ */
