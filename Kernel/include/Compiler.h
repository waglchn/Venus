//-------------------------------------------------------
//@file: compiler.h
//@brief: compile and debug environment params
//@author: venus
//@date: 2018/12/07-11:42
//-------------------------------------------------------

#ifndef __COMPILER_H__
#define __COMPILER_H__

//@ WIN32 for Windows32
//@ WIN64 for Windows64
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define _VENUS_WINDOWS_
#define _VENUS_WINDOWS_API_
#endif

//@ no static include
#ifndef _STATIC_LIB_
//@ if publish dll macro
#ifdef _EXPORTS_DLL_
//@ Dll export
#define VENUS_API __declspec(dllexport)
#else
//@ Dll improt
#define VENUS_API __declspec(dllimport)
#endif 
#else
#define VENUS_API
#endif 

//@ call standard
#if defined(_STDCALL_SUPPORTED)
#define VENUSCALL __stdcall
#else
#define VENUSCALL __cdecl
#endif 


//@ breaking if condition
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

// memory debugging
#if defined(_DEBUG) && defined(_MSC_VER)
#define CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)
#include <stdlib.h>
#include <crtdbg.h>
#define new DEBUG_CLIENTBLOCK
#endif

///safe memory release
#define  DELETE_IF(_TARGET_) if (_TARGET_) { delete _TARGET_; _TARGET_ =NULL;}
#define  DELETE_IF_ARRAY(_TARGET_ARRAY_) if (_TARGET_ARRAY_) { delete[] _TARGET_ARRAY_; _TARGET_ARRAY_ =NULL; }

#ifdef _VENUS_WINDOWS_API_
//@ platform standard interface
#if defined(_MSC_VER)
#define swprintf swprintf_s
#define snprintf sprintf_s
#else
#define swprintf _snwprintf
#define snprintf _snprintf
//include memset memcpy
#include <string.h>
#define stricmp strcasecmp
#include <unistd.h>
#define Sleep usleep
#endif
#endif

#endif
