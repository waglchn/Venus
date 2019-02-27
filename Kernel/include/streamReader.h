//-------------------------------------------------------
//@file: streamReader.h
//@brief: streamReader
//@author: venus
//@date: 2018/12/07-17:59
//-------------------------------------------------------
#ifndef __STREAM_READER_H_INCLUDED__
#define __STREAM_READER_H_INCLUDED__

#include "venusTypes.h"
#include "venusString.h"

namespace venus
{
	namespace core
	{
		///´æµµbuffer
		class StreamReader
		{
		public:
			StreamReader(u8* buffer, u32 size)
			{
				Cursor = 0;
				Buffer = buffer;
				Size = size;
			}
			~StreamReader()
			{
				Cursor = 0;
				Size = 0;
				Buffer = NULL;
			}
		public:
			void Load(u8* buffer, u32 size)
			{
				Cursor = 0;
				Buffer = buffer;
				Size = size;
			}
		public:
			bool ReadS8(s8 &value)
			{
				if (Cursor + sizeof(s8) > Size)
				{
					value = 0;
					return false;
				}

				value = (s8)*(Buffer+Cursor);
				Cursor += sizeof(u8);
				return true;
			}
			bool ReadU8(u8 &value)
			{
				if (Cursor + sizeof(u8) > Size)
				{
					value = 0;
					return false;
				}

				value = *(Buffer+Cursor);
				Cursor += sizeof(u8);
				return true;
			}
			bool ReadC8(c8 &value)
			{
				if (Cursor + sizeof(c8) > Size)
				{
					value = 0;
					return false;
				}

				value = (c8)*(Buffer+Cursor);
				Cursor += sizeof(u8);
				return true;
			}
			bool ReadS16(s16 &value)
			{
				if (Cursor + sizeof(s16) > Size)
				{
					value = 0;
					return false;
				}

				u16 uValue = *(Buffer+Cursor);
				uValue = uValue << 8 | *(Buffer+Cursor + 1);
				value = (s16)uValue;

				Cursor += sizeof(u16);
				return true;
			}
			bool ReadU16(u16 &value)
			{
				if (Cursor + sizeof(u16) > Size)
				{
					value = 0;
					return false;
				}

				value = *(Buffer+Cursor);
				value = value << 8 | *(Buffer+Cursor + 1);
				
				Cursor += sizeof(u16);
				return true;
			}
			bool ReadS32(s32 &value)
			{
				if (Cursor + sizeof(s32) > Size)
				{
					value = 0;
					return false;
				}

				u32 uValue = *(Buffer+Cursor);
				uValue = uValue << 8 | *(Buffer + Cursor + 1);
				uValue = uValue << 8 | *(Buffer + Cursor + 2);
				uValue = uValue << 8 | *(Buffer + Cursor + 3);
				value = (u32)uValue;

				Cursor += sizeof(u32);
				return true;
			}
			bool ReadU32(u32 &value)
			{
				if (Cursor + sizeof(u32) > Size)
				{
					value = 0;
					return false;
				}

				value = *(Buffer+Cursor);
				value = value << 8 | *(Buffer + Cursor + 1);
				value = value << 8 | *(Buffer + Cursor + 2);
				value = value << 8 | *(Buffer + Cursor + 3);

				Cursor += sizeof(u32);
				return true;
			}
			bool ReadS64(s64 &value)
			{
				if (Cursor + sizeof(s64) > Size)
				{
					value = 0;
					return false;
				}

				memcpy(&value, (void*)(Buffer+Cursor), sizeof(s64));

				Cursor += sizeof(s64);
				return true;
			}
			bool ReadU64(u64 &value)
			{
				if (Cursor + sizeof(u64) > Size)
				{
					value = 0;
					return false;
				}

				memcpy(&value, (void*)(Buffer+Cursor), sizeof(u64));

				Cursor += sizeof(u64);
				return true;
			}
			bool ReadF32(f32 &value)
			{
				if (Cursor + sizeof(f32) > Size)
				{
					value = 0;
					return false;
				}

				memcpy(&value, (void*)(Buffer + Cursor), sizeof(f32));

				Cursor += sizeof(f32);
				return true;
			}
			bool ReadF64(f64 &value)
			{
				if (Cursor+ sizeof(f64) > Size)
				{
					value = 0;
					return false;
				}

				memcpy(&value, (void*)(Buffer + Cursor), sizeof(f64));

				Cursor += sizeof(f64);
				return true;
			}
			bool ReadStringc(stringc &value)
			{
				if (Cursor + sizeof(u32) > Size)
				{
					value = "";
					return false;
				}
				u32 size; 
				size = *(Buffer+Cursor);
				size = size << 8 | *(Buffer + Cursor + 1);
				size = size << 8 | *(Buffer + Cursor + 2);
				size = size << 8 | *(Buffer + Cursor + 3);
				Cursor += sizeof(u32);
				value = (c8*)(Buffer+Cursor);
				
				Cursor += size;
				return true;
			}
			bool ReadStringw(stringw &value)
			{
				if (Cursor + sizeof(u32) > Size)
				{
					value = L"";
					return false;
				}
				u32 size;
				size = *(Buffer+Cursor);
				size = size << 8 | *(Buffer + Cursor + 1);
				size = size << 8 | *(Buffer + Cursor + 2);
				size = size << 8 | *(Buffer + Cursor + 3);
				Cursor += sizeof(u32);
				value = (wchar_t*)(Buffer + Cursor);

				Cursor += size;
				return true;
			}
			void* ReadUserData(u32& size)
			{
				if (Cursor + sizeof(u32) > Size)
				{
					size = 0;
					return NULL;
				}
			
				size = Buffer[Cursor];
				size = size << 8 | *(Buffer+Cursor + 1);
				size = size << 8 | *(Buffer+Cursor + 2);
				size = size << 8 | *(Buffer+Cursor + 3);
				Cursor += sizeof(u32);
				u32 address = Cursor;
				Cursor +=size;
				return (void*)(Buffer + address);
			}
		private:
			u8* Buffer;
			u32 Size;
			u32 Cursor;
		};
	}
}
#endif

