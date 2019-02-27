//-------------------------------------------------------
//@file: streamWriter.h
//@brief: streamWriter
//@author: venus
//@date: 2018/12/07-17:59
//-------------------------------------------------------
#ifndef __STREAM_WRITER_H_INCLUDED__
#define __STREAM_WRITER_H_INCLUDED__

#include "venusTypes.h"
#include "venusString.h"
#include "TAllocator.h"

namespace venus
{
	namespace core
	{
		///´æµµbuffer
		class StreamWriter
		{
			typedef TAllocator<u8> TAlloc;
			TAlloc tAlloc;
			bool allocated;
		public:
			StreamWriter(u32 size)
			{
				Cursor = 0;
				Buffer = tAlloc.allocate(size);
				allocated = true;
				Size = size;
			}

			StreamWriter(u8* buffer, u32 size)
			{
				allocated = false;
				Cursor = 0;
				Buffer = buffer;
				Size = size;
			}

			~StreamWriter()
			{
				Cursor = 0;
				Size = 0;
				if (allocated)
				{
					tAlloc.deallocate(Buffer);
					allocated = false;
				}
				Buffer = NULL;
			}
		public:
			void Load(u8* buffer, u32 size)
			{
				if (allocated)
				{
					tAlloc.deallocate(Buffer);
					allocated = false;
				}
				
				Cursor = 0;
				Buffer = buffer;
				Size = size;
			}
		public:
			bool WriteS8(s8 &value)
			{
				if (Cursor + sizeof(u8) > Size)
				{
					return false;
				}

				*(Buffer+Cursor) = value;
				Cursor += sizeof(u8);
				return true;
			}
			bool WriteU8(u8 &value)
			{
				if (Cursor + sizeof(u8) > Size)
				{
					return false;
				}

				*(Buffer+Cursor) = value;
				Cursor += sizeof(u8);
				return true;
			}
			bool WriteC8(c8 &value)
			{
				if (Cursor + sizeof(u8) > Size)
				{
					return false;
				}

				*(Buffer+Cursor) = value;
				Cursor += sizeof(u8);
				return true;
			}
			bool WriteS16(s16 &value)
			{
				if (Cursor + sizeof(u16) > Size)
				{
					return false;
				}
				u16 uValue = (u16)value;
				*(Buffer+Cursor)   = (uValue>>8)&0xFF;
				*(Buffer+Cursor+1) = (uValue) & 0xFF;
				
				Cursor += sizeof(u16);
				return true;
			}
			bool WriteU16(u16 &value)
			{
				if (Cursor + sizeof(u16) > Size)
				{
					return false;
				}

				*(Buffer+Cursor) = (value >> 8) & 0xFF;
				*(Buffer+Cursor + 1) = (value) & 0xFF;
				
				Cursor += sizeof(u16);
				return true;
			}
			bool WriteS32(s32 &value)
			{
				if (Cursor + sizeof(u32) > Size)
				{
					return false;
				}

				u32 uValue = (u32)value;
				*(Buffer + Cursor)   = (uValue >> 24) & 0xFF;
				*(Buffer + Cursor + 1) = (uValue >> 16) & 0xFF;
				*(Buffer + Cursor + 2) = (uValue >> 8) & 0xFF;
				*(Buffer + Cursor + 3) = (uValue) & 0xFF;

				Cursor += sizeof(u32);
				return true;
			}
			bool WriteU32(u32 &value)
			{
				if (Cursor + sizeof(u32) > Size)
				{
					return false;
				}

				*(Buffer + Cursor) = (value >> 24) & 0xFF;
				*(Buffer + Cursor + 1) = (value >> 16) & 0xFF;
				*(Buffer + Cursor + 2) = (value >> 8) & 0xFF;
				*(Buffer + Cursor + 3) = (value) & 0xFF;

				Cursor += sizeof(u32);
				return true;
			}
			bool WriteS64(s64 &value)
			{
				if (Cursor + sizeof(s64) > Size)
				{
					return false;
				}

				memcpy((void*)(Buffer + Cursor), &value, sizeof(s64));

				Cursor += sizeof(s64);
				return true;
			}
			bool WriteU64(u64 &value)
			{
				if (Cursor + sizeof(u64) > Size)
				{
					return false;
				}

				memcpy((void*)(Buffer + Cursor), &value,sizeof(u64));

				Cursor += sizeof(u64);
				return true;
			}
			bool WriteF32(f32 &value)
			{
				if (Cursor + sizeof(f32) > Size)
				{
					return false;
				}

				memcpy((void*)(Buffer+Cursor), (void*)&value, sizeof(f32));

				Cursor += sizeof(f32);
				return true;
			}
			bool WriteF64(f64 &value)
			{
				if (Cursor+ sizeof(f64) > Size)
				{
					return false;
				}

				memcpy((void*)(Buffer + Cursor), (void*)&value, sizeof(f64));

				Cursor += sizeof(f64);
				return true;
			}
			bool WriteStringc(stringc &value)
			{
				u32 size = (value.size() + 1)*sizeof(c8);
				if (Cursor + sizeof(u32)+ size > Size)
				{
					return false;
				}

				*(Buffer + Cursor) = (size >> 24) & 0xFF;
				*(Buffer + Cursor + 1) = (size >> 16) & 0xFF;
				*(Buffer + Cursor + 2) = (size >> 8) & 0xFF;
				*(Buffer + Cursor + 3) = (size) & 0xFF;
				
				Cursor += sizeof(u32);
				memcpy((void*)(Buffer + Cursor), (void*)value.c_str(), size);

				Cursor += size;
				return true;
			}
			bool WriteStringw(stringw &value)
			{
				u32 size = (value.size() + 1)*sizeof(wchar_t) ;
				if (Cursor + sizeof(u32) + size > Size)
				{
					return false;
				}

				*(Buffer + Cursor) = (size >> 24) & 0xFF;
				*(Buffer + Cursor + 1) = (size >> 16) & 0xFF;
				*(Buffer + Cursor + 2) = (size >> 8) & 0xFF;
				*(Buffer + Cursor + 3) = (size) & 0xFF;

				Cursor += sizeof(u32);
				memcpy((void*)(Buffer + Cursor), (void*)value.c_str(), size);

				Cursor += size;
				return true;
			}
			bool WriteUserData(void*value, u32 size)
			{
				if (Cursor + sizeof(u32) + size > Size)
				{
					return false;
				}

				*(Buffer + Cursor) = (size >> 24) & 0xFF;
				*(Buffer + Cursor + 1) = (size >> 16) & 0xFF;
				*(Buffer + Cursor + 2) = (size >> 8) & 0xFF;
				*(Buffer + Cursor + 3) = (size) & 0xFF;

				Cursor += sizeof(u32);
				memcpy((void*)(Buffer + Cursor), (void*)value, size);

				Cursor += size;
				return true;
			}
		private:
			u8* Buffer;
			u32 Size;
			u32 Cursor;
		};
	}
}
#endif

