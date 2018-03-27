//-------------------------------------------------------
//@file:compiler.h
//@brief:dll导入导出开关
//@author:wanglc
//@date:三月 2018
//-------------------------------------------------------
#ifndef __COMPILER_H__
#define __COMPILER_H__

//@ WIN32 for Windows32
//@ WIN64 for Windows64
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define _VENUS_WINDOWS_
#define _VENUS_WINDOWS_API_
#endif

//@ 代码引用需要显示声明
#ifndef _STATIC_LIB_
//@ 导出时需要定义编译宏
#ifdef _EXPORTS_DLL_
//@ Dll导出声明
#define VENUS_API __declspec(dllexport)
#else
//@ Dll导入声明
#define VENUS_API __declspec(dllimport)
#endif 
#else
#define VENUS_API
#endif 

//@ 声明调用规范
#if defined(_STDCALL_SUPPORTED)
#define VENUSCALL __stdcall
#else
#define VENUSCALL __cdecl
#endif 


//@ 定义调试中断宏
#if defined(_DEBUG)
#if defined(_VENUS_WINDOWS_API_) && defined(_MSC_VER)
#if defined(WIN64) || defined(_WIN64) 
#include <crtdbg.h>
#define DEBUG_BREAK_IF( _CONDITION_ ) if (_CONDITION_) {_CrtDbgBreak();}
#else
#define DEBUG_BREAK_IF( _CONDITION_ ) if (_CONDITION_) {_asm int 3}
#endif
#else
#include "assert.h"
#define DEBUG_BREAK_IF( _CONDITION_ ) assert( !(_CONDITION_) );
#endif
#else
#define DEBUG_BREAK_IF( _CONDITION_ )
#endif

#ifdef _VENUS_WINDOWS_API_
//@ 平台统一化
#if defined(_MSC_VER)
#define swprintf swprintf_s
#define snprintf sprintf_s
#else
#define swprintf _snwprintf
#define snprintf _snprintf
#endif
#endif

#endif
