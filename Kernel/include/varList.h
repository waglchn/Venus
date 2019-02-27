#ifndef __VARLIST_H__
#define __VARLIST_H__
#include "venusTypes.h"
#include "TAllocator.h"
namespace venus
{
	namespace core
	{
		enum VARTYPE
		{
			VT_NONE = 0,
			VT_SBYTE,
			VT_BYTE,
			VT_SHORT,
			VT_USHORT,
			VT_INT,
			VT_UINT,
			VT_LONG,
			VT_ULONG,
			VT_FLOAT,
			VT_DOUBLE,
			VT_STRINGC,
			VT_STRINGW,
			VT_USERDATA,
		};

		template<u32 BUFFERSIZE>
		class VarList
		{
		public:
			VarList() 
			{
				maxVarIndex =0;
				bufferCursor = 0;
				memset(dataBuffer, 0, sizeof(u8)*BUFFERSIZE);
			}
			~VarList()
			{
			}
		public:
			bool SetSByte(u8 index, s8& value)
			{
				u32 address = GetVarAddress(index );
				if (index >= maxVarIndex)
				{
					if (address < bufferCursor)
					{
						return false;
					}

					maxVarIndex = index + 1;
				}
				
				dataBuffer[address] = VT_SBYTE;
				dataBuffer[address + 1] = (u8)value;
				return true;
			}
			bool SetByte(u8 index, u8& value)
			{
				u32 address = GetVarAddress(index );
				if (index >= maxVarIndex)
				{
					if (address < bufferCursor)
					{
						return false;
					}

					maxVarIndex = index + 1;
				}
				dataBuffer[address] = VT_BYTE;
				dataBuffer[address + 1] = (u8)value;
				return true;
			}
			bool SetShort(u8 index, s16& value)
			{
				u32 address = GetVarAddress(index );
				if (index >= maxVarIndex)
				{
					if (address < bufferCursor)
					{
						return false;
					}

					maxVarIndex = index + 1;
				}
				dataBuffer[address] = VT_SHORT;
				dataBuffer[address + 2] = (u8)((u16)value & 0xFF);
				dataBuffer[address + 1] = (u8)(((u16)value >> 8) & 0xFF);
				return true;
			}
			bool SetUShort(u8 index, u16& value)
			{
				u32 address = GetVarAddress(index);
				if (index >= maxVarIndex)
				{
					if (address < bufferCursor)
					{
						return false;
					}

					maxVarIndex = index + 1;
				}
				dataBuffer[address] = VT_USHORT;
				dataBuffer[address + 2] = (u8)(value & 0xFF);
				dataBuffer[address + 1] = (u8)((value >> 8) & 0xFF);
				return true;
			}
			bool SetInt(u8 index, s32& value)
			{
				u32 address = GetVarAddress(index );
				if (index >= maxVarIndex)
				{
					if (address < bufferCursor)
					{
						return false;
					}

					maxVarIndex = index + 1;
				}
				dataBuffer[address] = VT_INT;
				dataBuffer[address + 4] = (u8)((u32)value & 0xFF);
				dataBuffer[address + 3] = (u8)(((u32)value >> 8) & 0xFF);
				dataBuffer[address + 2] = (u8)(((u32)value >> 16) & 0xFF);
				dataBuffer[address + 1] = (u8)(((u32)value >> 24) & 0xFF);

				return true;
			}
			bool SetUInt(u8 index, u32& value)
			{
				u32 address = GetVarAddress(index );
				if (index >= maxVarIndex)
				{
					if (address < bufferCursor)
					{
						return false;
					}

					maxVarIndex = index + 1;
				}
				dataBuffer[address] = VT_UINT;
				dataBuffer[address + 4] = (u8)(value & 0xFF);
				dataBuffer[address + 3] = (u8)((value >> 8) & 0xFF);
				dataBuffer[address + 2] = (u8)((value >> 16) & 0xFF);
				dataBuffer[address + 1] = (u8)((value >> 24) & 0xFF);
				return true;
			}
			bool SetLong(u8 index, s64& value)
			{
				if (index < maxVarIndex)
				{
					u8 type;
					u32 address;
					GetAddress(index, type, address);
					if (!ShrinkBuffer(index, type, address,sizeof(s64)))
					{
						return false;
					}

					///地址是原地址，内容写入覆盖
					memcpy(dataBuffer + address, &value, sizeof(s64));
				}
				else
				{
					if ((bufferCursor + sizeof(s64)) > GetVarAddress(index))
					{
						return false;
					}

					///新设置
					maxVarIndex = index + 1;
					u32 address = bufferCursor;
					SetAddress(index, VT_LONG, address);
					memcpy(dataBuffer + address, &value, sizeof(s64));
					bufferCursor +=  sizeof(s64);
				}
				
				return true;
			}
			bool SetULong(u8 index, u64& value)
			{
				if (index < maxVarIndex)
				{
					u8 type;
					u32 address;
					GetAddress(index, type, address);
					if (!ShrinkBuffer(index, type, address,sizeof(u64)))
					{
						return false;
					}

					///地址是原地址，内容写入覆盖
					memcpy(dataBuffer + address, &value, sizeof(u64));
				}
				else
				{
					if ((bufferCursor + sizeof(u64)) > GetVarAddress(index))
					{
						return false;
					}

					///新设置
					maxVarIndex = index + 1;
					u32 address = bufferCursor;
					SetAddress(index, VT_ULONG, address);
					memcpy(dataBuffer + address, &value, sizeof(u64));
					bufferCursor += sizeof(u64);
				}

				return true;
			}
			bool SetFloat(u8 index, f32& value)
			{
				if (index < maxVarIndex)
				{
					u8 type;
					u32 address;
					GetAddress(index, type, address);
					if (!ShrinkBuffer(index, type, address, sizeof(f32)))
					{
						return false;
					}

					///地址是原地址，内容写入覆盖
					memcpy(dataBuffer + address, &value, sizeof(f32));
				}
				else
				{
					if ((bufferCursor + sizeof(f32)) > GetVarAddress(index))
					{
						return false;
					}

					///新设置
					maxVarIndex = index + 1;
					u32 address = bufferCursor;
					SetAddress(index, VT_FLOAT, address);
					memcpy(dataBuffer + address, &value, sizeof(f32));
					bufferCursor += sizeof(f32);
				}

				return true;
			}
			bool SetDouble(u8 index, f64& value)
			{
				if (index < maxVarIndex)
				{
					u8 type;
					u32 address;
					GetAddress(index, type, address);
					if (!ShrinkBuffer(index, type, address, sizeof(f64)))
					{
						return false;
					}

					///地址是原地址，内容写入覆盖
					memcpy(dataBuffer + address, &value, sizeof(f64));
				}
				else
				{
					if ((bufferCursor + sizeof(f64)) > GetVarAddress(index))
					{
						return false;
					}

					///新设置
					maxVarIndex = index + 1;
					
					u32 address = bufferCursor;
					SetAddress(index, VT_DOUBLE, address);
					memcpy(dataBuffer + address, &value, sizeof(f64));
					bufferCursor += sizeof(f64);
				}

				return true;
			}
			bool SetStringc(u8 index, stringc& value)
			{
				u32 nSize = value.size()+1;
				if (index < maxVarIndex)
				{
					u8 type;
					u32 address;
					GetAddress(index, type, address);
					if (!ShrinkBuffer(index, type, address, nSize))
					{
						return false;
					}

					///地址是原地址，内容写入覆盖
					SetBuffer(address, (void*)value.c_str(), nSize);
				}
				else
				{
					if ((bufferCursor + nSize) > GetVarAddress(index))
					{
						return false;
					}

					///新设置
					maxVarIndex = index + 1;
					u32 address = bufferCursor;
					SetAddress(index, VT_STRINGC, address);
					SetBuffer(address, (void*)value.c_str(), nSize);
					bufferCursor +=  sizeof(u64) + nSize;
				}

				return true;
			}
			bool SetStringw(u8 index, stringw& value)
			{
				u32 nSize = (value.size()+1) * sizeof(wchar_t);
				if (index < maxVarIndex)
				{
					u8 type;
					u32 address;
					GetAddress(index, type, address);
					if (!ShrinkBuffer(index, type, address, nSize))
					{
						return false;
					}

					///地址是原地址，内容写入覆盖
					SetBuffer(address, (void*)value.c_str(), nSize);
				}
				else
				{
					if ((bufferCursor + nSize) > GetVarAddress(index))
					{
						return false;
					}

					///新设置
					maxVarIndex = index + 1;
					u32 address = bufferCursor;
					SetAddress(index, VT_STRINGW, address);
					SetBuffer(address, (void*)value.c_str(), nSize);
					bufferCursor +=  sizeof(u64)+nSize;
				}

				return true;
			}
			bool SetUserData(u8 index, void* value, u32 nSize)
			{
				if (index < maxVarIndex)
				{
					u8 type;
					u32 address;
					GetAddress(index, type, address);
					if (!ShrinkBuffer(index, type, address, nSize))
					{
						return false;
					}

					///地址是原地址，内容写入覆盖
					SetBuffer(address, value, nSize);
				}
				else
				{
					if ((bufferCursor + nSize) > GetVarAddress(index))
					{
						return false;
					}

					///新设置
					maxVarIndex = index + 1;
					u32 address = bufferCursor;
					SetAddress(index, VT_USERDATA, address);
					SetBuffer(address, value, nSize);
					bufferCursor += sizeof(u32)+ nSize;
				}

				return true;
			}
		public:
			
			bool GetSByte(u8 index, s8& value)
			{
				if (index >= maxVarIndex)
				{
					return false;
				}

				u32 address = GetVarAddress(index);
				if (dataBuffer[address] != VT_SBYTE)
				{
					return false;
				}

				value = (s8)dataBuffer[address + 1];

				return true;
			}
			bool GetByte(u8 index, u8& value)
			{
				if (index >= maxVarIndex)
				{
					return false;
				}

				u32 address = GetVarAddress(index);
				if (dataBuffer[address] != VT_BYTE)
				{
					return false;
				}

				value = (s8)dataBuffer[address + 1];

				return true;
			}
			bool GetShort(u8 index, s16& value)
			{
				if (index >= maxVarIndex)
				{
					return false;
				}

				u32 address = GetVarAddress(index);
				if (dataBuffer[address] != VT_SHORT)
				{
					return false;
				}
				
				u16 sValue = dataBuffer[address + 1];
				sValue = ((sValue << 8) | dataBuffer[address + 2]);

				value = (s16)sValue;
				return true;
			}

			bool GetUShort(u8 index, u16& value)
			{
				if (index >= maxVarIndex)
				{
					return false;
				}

				u32 address = GetVarAddress(index);
				if (dataBuffer[address] != VT_USHORT)
				{
					return false;
				}

				value = (u16)dataBuffer[address + 1];
				value = ((value<<8)|dataBuffer[address + 2]);
				return true;
			}
			bool GetInt(u8 index, s32& value)
			{
				if (index > maxVarIndex)
				{
					return false;
				}

				u32 address = GetVarAddress(index);
				if (dataBuffer[address] != VT_INT)
				{
					return false;
				}

				u32 uValue = (u32)dataBuffer[address + 1];
				uValue = uValue << 8 | dataBuffer[address + 2];
				uValue = uValue << 8 | dataBuffer[address + 3];
				uValue = uValue << 8 | dataBuffer[address + 4];

				value = uValue;

				return true;
			}
			bool GetUInt(u8 index, u32& value)
			{
				if (index >= maxVarIndex)
				{
					return false;
				}

				u32 address = GetVarAddress(index);
				if (dataBuffer[address] != VT_UINT)
				{
					return false;
				}

				value = (u32)dataBuffer[address + 1];
				value = value << 8 | dataBuffer[address + 2];
				value = value << 8 | dataBuffer[address + 3];
				value = value << 8 | dataBuffer[address + 4];

				return true;
			}
			bool GetLong(u8 index, s64& value)
			{
				u8 type;
				u32 address;
				if (GetInnerAddress(index, type, address))
				{
					if (type != VT_LONG)
					{
						return false;
					}
					memcpy(value, dataBuffer + address, sizeof(s64));
					return true;
				}
				
				return false;
			}
			bool GetULong(u8 index, u64& value)
			{
				u8 type;
				u32 address;
				if (GetInnerAddress(index, type, address))
				{
					if (type != VT_ULONG)
					{
						return false;
					}
					memcpy(value, dataBuffer + address, sizeof(u64)); 
					return true;
				}

				return false;
			}
			bool GetFloat(u8 index, f32& value)
			{
				u8 type;
				u32 address;
				if (GetInnerAddress(index, type, address))
				{
					if (type != VT_FLOAT)
					{
						return false;
					}
					memcpy(value, dataBuffer + address, sizeof(f32)); 
					return true;
				}

				return false;
			}
			bool GetDouble(u8 index, f64& value)
			{
				u8 type;
				u32 address;
				if (GetInnerAddress(index, type, address))
				{
					if (type != VT_DOUBLE)
					{
						return false;
					}
					memcpy(value, dataBuffer + address, sizeof(f64));
					return true;
				}

				return false;
			}
			bool GetStringc(u8 index, stringc& value)
			{
				u8 type;
				u32 address;
				if (GetInnerAddress(index, type, address))
				{
					if (type != VT_STRINGC)
					{
						return false;
					}

					u8* ptr = (u8*)GetBuffer(address);
					value.append(ptr);
					return true;
				}

				return false;
			}
			bool GetStringw(u8 index, stringw& value)
			{
				u8 type;
				u32 address;
				if (GetInnerAddress(index, type, address))
				{
					if (type != VT_STRINGW)
					{
						return false;
					}

					wchar_t* ptr =(wchar_t*) GetBuffer(address);
					value.append(ptr);
					return true;
				}

				return false;
			}
			void* GetUserData(u8 index, u32& size)
			{
				u8 type;
				u32 address;
				if (GetInnerAddress(index, type, address))
				{
					if (type != VT_USERDATA)
					{
						return 0;
					}
					size = GetBufferSize(type,address);
					return GetBuffer(address);
				}

				return 0;
			}
		public:
			s8 GetSByte(u8 index)
			{
				if (index >= maxVarIndex)
				{
					return false;
				}

				u32 address = GetVarAddress(index);
				if (dataBuffer[address] != VT_SBYTE)
				{
					return false;
				}

				return (s8)dataBuffer[address + 1];
			}
			u8 GetByte(u8 index)
			{
				if (index >= maxVarIndex)
				{
					return 0;
				}

				u32 address = GetVarAddress(index);
				if (dataBuffer[address] != VT_BYTE)
				{
					return 0;
				}

				return dataBuffer[address + 1];
			}
			s16 GetShort(u8 index)
			{
				if (index >= maxVarIndex)
				{
					return 0;
				}

				u32 address = GetVarAddress(index);
				if (dataBuffer[address] != VT_SHORT)
				{
					return 0;
				}

				u16 sValue = dataBuffer[address + 1];
				sValue = ((sValue << 8) | dataBuffer[address + 2]);

				return (s16)sValue;
			}

			u16 GetUShort(u8 index)
			{
				if (index >= maxVarIndex)
				{
					return 0;
				}

				u32 address = GetVarAddress(index);
				if (dataBuffer[address] != VT_USHORT)
				{
					return 0;
				}

				u16 value = (u16)dataBuffer[address + 1];
				value = ((value << 8) | dataBuffer[base + 2]);
				return value;
			}
			s32 GetInt(u8 index)
			{
				if (index > maxVarIndex)
				{
					return 0;
				}

				u32 address = GetVarAddress(index);
				if (dataBuffer[address] != VT_INT)
				{
					return 0;
				}
			
				u32 uValue = (u32)dataBuffer[base + 1];
				uValue = uValue << 8 | dataBuffer[base + 2];
				uValue = uValue << 8 | dataBuffer[base + 3];
				uValue = uValue << 8 | dataBuffer[base + 4];

				return (s32)uValue;
			}
			u32 GetUInt(u8 index)
			{
				if (index >= maxVarIndex)
				{
					return 0;
				}

				u32 address = GetVarAddress(index);
				if (dataBuffer[address] != VT_UINT)
				{
					return 0;
				}

				u32 value = dataBuffer[base + 1];
				value = value << 8 | dataBuffer[base + 2];
				value = value << 8 | dataBuffer[base + 3];
				value = value << 8 | dataBuffer[base + 4];

				return value;
			}
			s64 GetLong(u8 index)
			{
				u8 type;
				u32 address;
				if (GetInnerAddress(index, type, address))
				{
					if (type != VT_LONG)
					{
						return 0;
					}

					s64 value=0;
					memcpy(&value, dataBuffer + address, sizeof(s64));
					return value;
				}

				return 0;
			}
			u64 GetULong(u8 index)
			{
				u8 type;
				u32 address;
				if (GetInnerAddress(index, type, address))
				{
					if (type != VT_ULONG)
					{
						return 0;
					}

					u64 value = 0;
					memcpy(&value, dataBuffer + address, sizeof(u64));
					return value;
				}

				return 0;
			}
			f32 GetFloat(u8 index)
			{
				u8 type;
				u32 address;
				if (GetInnerAddress(index, type, address))
				{
					if (type != VT_FLOAT)
					{
						return 0.0f;
					}
					f32 value=0.0f;
					memcpy(&value, dataBuffer + address, sizeof(f32));
					return value;
				}

				return 0.0f;
			}
			f64 GetDouble(u8 index)
			{
				u8 type;
				u32 address;
				if (GetInnerAddress(index, type, address))
				{
					if (type != VT_DOUBLE)
					{
						return 0.0f;
					}

					f64 value = 0.0f;
					memcpy(&value, dataBuffer + address, sizeof(f64));
					return value;
				}
				
				return 0.0f;
			}
			c8* GetStringc(u8 index)
			{
				u8 type;
				u32 address;
				if (GetInnerAddress(index, type, address))
				{
					if (type != VT_STRINGC)
					{
						return "";
					}
					u32 nSize = GetBufferSize(type,address);
					if (nSize == 0)
					{
						return "";
					}
				
					return (c8*)GetBuffer(address);
				}

				return "";
			}
			wchar_t* GetStringw(u8 index)
			{
				u8 type;
				u32 address;
				if (GetInnerAddress(index, type, address))
				{
					if (type != VT_STRINGW)
					{
						return L"";
					}

					u32 nSize = GetBufferSize(type, address);
					if (nSize == 0)
					{
						return L"";
					}

					return (wchar_t*)GetBuffer(address);
				}

				return L"";
			}
			
		private:
			///检测该位置放置一个大小Size的buffer是否可以放下
			void GetAddress(u8 index, u8 &type, u32& address)
			{
				u32 baseAddress = GetVarAddress(index);
				type = dataBuffer[baseAddress];

				address = dataBuffer[baseAddress + 1];
				address = (address << 8)|dataBuffer[baseAddress + 2];
				address = (address << 8)|dataBuffer[baseAddress + 3];
				address = (address << 8)|dataBuffer[baseAddress + 4];
			}
			bool GetInnerAddress(u8 index, u8 &type, u32& address)
			{
				if (index >= maxVarIndex)
				{
					return false;
				}
				u32 baseAddress = GetVarAddress(index);
				type = dataBuffer[baseAddress];

				address = dataBuffer[baseAddress + 1];
				address = (address << 8) | dataBuffer[baseAddress + 2];
				address = (address << 8) | dataBuffer[baseAddress + 3];
				address = (address << 8) | dataBuffer[baseAddress + 4];

				return true;
			}
			void SetAddress(u8 index, u8 type, u32 address)
			{
				u32 baseAddress = GetVarAddress(index);
				dataBuffer[baseAddress] = type;
				dataBuffer[baseAddress + 1] = (address >> 24) & 0xFF;
				dataBuffer[baseAddress + 2] = (address >> 16) & 0xFF;
				dataBuffer[baseAddress + 3] = (address >> 8) & 0xFF;
				dataBuffer[baseAddress + 4] = (address) & 0xFF;
			}

			void SetBuffer(u32 address, void* buffer, u32 size)
			{
				///write size
				dataBuffer[address + 0] = (size >> 24) & 0xFF;
				dataBuffer[address + 1] = (size >> 16) & 0xFF;
				dataBuffer[address + 2] = (size >> 8) & 0xFF;
				dataBuffer[address + 3] = (size) & 0xFF;
				if(size > 0)
				{
					//write buffer
					memcpy(dataBuffer + address + 4, (u8*)buffer, size);
				}
			}
			bool ShrinkBuffer(u8 index,u8 type,u32 address,u32 nSize)
			{
				///以前值，进行修改长度
				u32 nbufferSize = GetBufferSize(type, address);
				if (nbufferSize == nSize)
				{
					return true;
				}

				if (nbufferSize > nSize)
				{
					u32 shrinkSize = nbufferSize-nSize;
					///变小，内存反向移动
					for (u8 i = index + 1; i <maxVarIndex; i++)
					{
						u8 type;
						u32 address;
						GetAddress(i, type, address);
						u32 nbufferSize2 = GetBufferSize(type, address);
						if (nbufferSize2 == 0)
						{
							///不需要拷贝的类型不存在Size
							continue;
						}

						SetAddress(i, type, address - shrinkSize);
						memmove(dataBuffer + address - shrinkSize,dataBuffer + address, nbufferSize2+sizeof(u32));
					}

					///肯定减小缩小空间
					bufferCursor -= shrinkSize;
				}
				else
				{
					///变大
					u32 shrinkSize = nSize - nbufferSize;
					if (bufferCursor + shrinkSize >= GetCeilAddress())
					{
						///即使移动内存也无法满足需求了
						return false;
					}

					///依次推后移动
					for (u8 i = maxVarIndex - 1; i > index; i--)
					{
						u8 type;
						u32 address;
						GetAddress(i, type, address);
						u32 nbufferSize2 = GetBufferSize(type, address);
						if (nbufferSize2 == 0)
						{
							///不需要拷贝的类型不存在Size
							continue;
						}

						SetAddress(i, type, address + shrinkSize);
						memmove(dataBuffer + address + shrinkSize, dataBuffer + address , nbufferSize2 + sizeof(u32));
					}

					///肯定减小缩小空间
					bufferCursor += shrinkSize;
				}
				
				return true;
			}
			u32 GetBufferSize(u8 type,u32 address)
			{
				switch (type)
				{
				case VT_LONG:
					return sizeof(s64);
				case VT_ULONG:
					return sizeof(u64);
				case VT_FLOAT:
					return sizeof(f32);
				case VT_DOUBLE:
					return sizeof(f64);
				case VT_STRINGC:
				case VT_STRINGW:
				case VT_USERDATA:
				{
					///write size
					u32 size = dataBuffer[address + 0];
					size = size << 8 | dataBuffer[address + 1];
					size = size << 8 | dataBuffer[address + 2];
					size = size << 8 | dataBuffer[address + 3];

					return size;
				}
				default:
					break;
				}
				return 0;

			}
			
			void* GetBuffer(u32 address)
			{
				return (void*)(dataBuffer + address + sizeof(u32));
			}
			u32 GetCeilAddress()
			{
				return BUFFERSIZE - ((sizeof(u8) + sizeof(u32))*(maxVarIndex));
			}
			
			u32 GetVarAddress(u8 index)
			{
				u32 nSize = (sizeof(u8) + sizeof(u32))*(index + 1);
				if (nSize > BUFFERSIZE)
				{
					return 0;
				}

				return BUFFERSIZE - nSize;
			}

			bool CheckVarRiseSafe(u8 index)
			{
				if (index < maxVarIndex)
				{
					return true;
				}

				///写入变量型只需检测地址表是否满足空间需求
				return bufferCursor <= GetCeilAddress();
			}

			bool CheckBufferRiseSafe(u8 index, u32 nSize)
			{
				u8 utype;
				u32 address;
				if (index < maxVarIndex)
				{
					GetAddress(index, utype, address);

					///以前值，进行修改长度
					u32 nbufferSize = GetBufferSize(utype, address);
					if (nbufferSize < nSize)
					{
						///增加了，右移
						return (bufferCursor + nbufferSize - nSize) < GetUpperAddress();
					}

					return true;
				}

				///写入一个新的buffer空间与变量空间都增长的情况下内存空间是否满足
				return (bufferCursor + nSize) < (GetUpperAddress() - (sizeof(u8) + sizeof(u32)));
			}

		private:
			///最大的变量设置编号
			u8 maxVarIndex;
			u8 dataBuffer[BUFFERSIZE];
			//buffer的末端指针
			u32 bufferCursor;
		};
		typedef VarList<512> CVarList;

	}
}
#endif 


