namespace PS3
{
	int console_write(const char * s)
	{
		uint32_t len;
		system_call_4(403, 0, (uint64_t)s, std::strlen(s), (uint64_t)&len);
		return_to_user_prog(int);
	}
	void sleep(usecond_t time)
	{
		sys_timer_usleep(time * 1000);
	}
	int32_t write_process(uint64_t ea, const void * data, uint32_t size)
	{
		system_call_4(905, (uint64_t)sys_process_getpid(), ea, size, (uint64_t)data);
		return_to_user_prog(int32_t);
	}
	void* read_process(uint64_t ea,uint32_t size)
	{
		void* data;
		system_call_4(904, (uint64_t)sys_process_getpid(), ea, size, (uint64_t)data);
		return data;
	}
	int Memcpy(void* destination, const void* source, size_t size)
	{
		system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);
		__dcbst(destination);
		__sync();
		__isync();
		return_to_user_prog(int);
	}
	const char* ReadString(int addr, int len)
	{
		char* buff = "";
		for(int i =0;i<len;i++)
		{
			buff[i] = *(char*)(addr + i);
		}
		return buff;
	}
	//Require For Hooking
	//Credits To Thriefboy For Hooking/Write Process Func
	void PatchInJump(int Address, int Destination, bool Linked) 
	{
		// use this data to copy over the address
		int FuncBytes[4];

		// Get the actual destination address
		Destination = *(int *)Destination;

		FuncBytes[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF); // lis     %r11, dest>>16
		if (Destination & 0x8000) // If bit 16 is 1
			FuncBytes[0] += 1;

			FuncBytes[1] = 0x396B0000 + (Destination & 0xFFFF); // addi    %r11, %r11, dest&0xFFFF
			FuncBytes[2] = 0x7D6903A6; // mtctr    %r11

			FuncBytes[3] = 0x4E800420; // bctr

			if (Linked)
				FuncBytes[3] += 1; // bctrl

			Memcpy((void*)Address, FuncBytes, 4 * 4);
	}
	int cstrcmp(const char* s1, const char* s2)
	{
		while (*s1 && (*s1 == *s2))
			s1++, s2++;
		return *(const unsigned char*)s1 - *(const unsigned char*)s2;
	}	
	char byteArray[100];
	char* ReadBytesC(int address, int length)
	{
		for (int i = 0; i < length; i++)
		{
			byteArray[i] =  *(char*)(address + (i));
		}
		return byteArray;
	}
		char returnRead[100];
	char* ReadStringC(int address)
	{
		memset(&returnRead[0], 0, sizeof(returnRead));
		int strlength = 100;
		char* StrBytes = ReadBytesC(address, strlength);
		for (int i = 0; i < strlength; i++)
		{
			if (StrBytes[i] != 0x00)
				returnRead[i] = StrBytes[i];
			else
				break;
		}
		return returnRead;
	}
}