#include <limits.h>
#include <sys/prx.h>
#include <sys/syscall.h>
#include <sys/ppu_thread.h>
#include <sys/sys_time.h>
#include <sys/time_util.h>
#include <sys/process.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/types.h>
#include <math.h>
#include <fastmath.h>
#include <cellstatus.h>
#include <sys/timer.h>
#include <cell/sysmodule.h>
#include <sys/random_number.h>
#include <ppu_intrinsics.h>
#include <time.h>
#include <sysutil/sysutil_msgdialog.h>
#include <sysutil/sysutil_oskdialog.h>
#include <sysutil/sysutil_oskdialog_ext.h>
#include <setjmp.h>

#include "cstring.h"
#include "stdio.h"
#include "stdlib.h"
#include "Memory.h"

void sleep(usecond_t time) {
	sys_timer_usleep(time * 1000);
}

#include <ctime>

inline void mySleep(clock_t sec) // clock_t is a like typedef unsigned int clock_t. Use clock_t instead of integer in this context
{
clock_t start_time = clock();
clock_t end_time = sec * 1000 + start_time;
while(clock() != end_time);
}

int CountString(char* text, char Find) {
	int i = 0;
	while (*text) {
		if (*text == Find)
			i++;
		text++;
	}
	return i + 1;
}

unsigned char bittest(const int* a, int b) {
	return (unsigned char)(a[b >> 5] >> (b & 0x1F)) & 1;
}

int32_t sys_dbg_read_process_memory(uint64_t address, void *data, size_t size)
{
	system_call_4(904, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
	return_to_user_prog(int32_t);
}

int32_t sys_dbg_write_process_memory(uint64_t address, const void *data, size_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
	__dcbst((void*)address);
	__sync();
	__isync();
	return_to_user_prog(int32_t);
}

int32_t sys_dbg_write_process_memory_p(void* destination, const void *data, size_t size) {
	system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)data);
	__dcbst(destination);
	__sync();
	__isync();
	return_to_user_prog(int32_t);
}

void WriteProcess(void* destination, const void *data, uint32_t size) {
	sys_dbg_write_process_memory_p(destination, data, size);
}

void PatchInJump(int Address, int Destination, bool Linked) {
	int FuncBytes[4];
	Destination = *(int *)Destination;
	FuncBytes[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF);
	if (Destination & 0x8000)
		FuncBytes[0] += 1;
	FuncBytes[1] = 0x396B0000 + (Destination & 0xFFFF);
	FuncBytes[2] = 0x7D6903A6;
	FuncBytes[3] = 0x4E800420;
	if (Linked)
		FuncBytes[3] += 1;
	WriteProcess((void*)Address, FuncBytes, 4 * 4);
}

void HookFunctionStart(uint32_t functionStartAddress, uint32_t newFunction, uint32_t functionStub)
{
	functionStub = *(int *)functionStub;
	int BranchtoAddress = functionStartAddress + (4 * 4);
	int StubData[8];
	StubData[0] = 0x3D600000 + ((BranchtoAddress >> 16) & 0xFFFF);
	if (BranchtoAddress & 0x8000)
		StubData[0] += 1;
	StubData[1] = 0x396B0000 + (BranchtoAddress & 0xFFFF);
	StubData[2] = 0x7D6903A6;
	WriteProcess(&StubData[3], (void*)functionStartAddress, 4 * 4);
	StubData[7] = 0x4E800420;
	WriteProcess((void*)functionStub, StubData, 8 * 4);
	PatchInJump(functionStartAddress, newFunction, false);
}