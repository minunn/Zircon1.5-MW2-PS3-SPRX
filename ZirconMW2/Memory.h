#ifndef __MEMORY_H__
#define __MEMORY_H__

void sleep(usecond_t time);
int CountString(char* text, char Find);
unsigned char bittest(const int* a, int b);
int32_t sys_dbg_write_process_memory(uint64_t address, const void *data, size_t size);
int32_t sys_dbg_read_process_memory(uint64_t address, void *data, size_t size);

template<typename T>
uint32_t ReadProcessMemory(uint32_t address, const T data, size_t size) {
	return sys_dbg_read_process_memory(address, &data, size);
}
template<typename T>
uint32_t WriteProcessMemory(uint32_t address, const T data, size_t size) {
	return sys_dbg_write_process_memory(address, &data, size);
}

void PatchInJump(int Address, int Destination, bool Linked);
void HookFunctionStart(uint32_t functionStartAddress, uint32_t newFunction, uint32_t functionStub);


#endif /* __MEMORY_H__ */