//-------------------------------------------------------
//@file:Types.h
//@brief:基础数据类型定义，多平台统一声明，增加平台可移植性
//@author:wanglc
//@date:2018/12/07-11:38
//-------------------------------------------------------

#ifndef __TYPES_H__
#define __TYPES_H__

#include "compiler.h"
#include <wchar.h>

namespace venus
{
	//@ 8位无符号变量
#if defined(_MSC_VER)
	typedef unsigned __int8		u8;
#else
	typedef unsigned char		u8;
#endif

	//@ 8位有符号变量
#if defined(_MSC_VER)
	typedef __int8			s8;
#else
	typedef signed char		s8;
#endif

	//@ 8位字符变量
	typedef char			c8;

	//@ 16位无符号变量
#if defined(_MSC_VER) 
	typedef unsigned __int16	u16;
#else
	typedef unsigned short		u16;
#endif

	//@ 16位有符号变量
#if defined(_MSC_VER) 
	typedef __int16			s16;
#else
	typedef signed short		s16;
#endif

	//@ 32位无符号变量
#if defined(_MSC_VER) 
	typedef unsigned __int32	u32;
#else
	typedef unsigned int		u32;
#endif

	//@ 32位有符号变量
#if defined(_MSC_VER) 
	typedef __int32			s32;
#else
	typedef signed int		s32;
#endif

	//@ 64位无符号变量
#if defined(_MSC_VER)
	typedef unsigned __int64			u64;
#elif __GNUC__
#if __WORDSIZE == 64
	typedef unsigned long int 			u64;
#else
	__extension__ typedef unsigned long long	u64;
#endif
#else
	typedef unsigned long long			u64;
#endif

	//@ 64位有符号变量
#if defined(_MSC_VER)
	typedef __int64					s64;
#elif __GNUC__
#if __WORDSIZE == 64
	typedef long int 				s64;
#else
	__extension__ typedef long long			s64;
#endif
#else
	typedef long long				s64;
#endif

	//@ 32位单精度浮点变量
	typedef float				f32;

	//@ 64位双精度浮点变量
	typedef double				f64;

	//@ windows平台需要额外定义

#ifndef _WCHAR_T_DEFINED
	//@ 16位宽字符如果没有定义的话
	typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif 

#if defined(_WCHAR_FILESYSTEM)
	typedef wchar_t fschar_t;
#define VENUS_TEXT(X) L##X
#else
	typedef char fschar_t;
#define VENUS_TEXT(X) X
#endif

#define MAKE_ID(c0, c1, c2, c3) \
		((venus::u32)(venus::u8)(c0) | ((venus::u32)(venus::u8)(c1) << 8) | \
		((venus::u32)(venus::u8)(c2) << 16) | ((venus::u32)(venus::u8)(c3) << 24 ))
}

#endif
