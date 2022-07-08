#include "Includes.h"

#define SYS_FREE_MEMORY 0x1840000

void* malloc(uint32_t a_uiSize) {
	sys_addr_t l_uiAddr = (sys_addr_t)(SYS_FREE_MEMORY);
	a_uiSize = ((a_uiSize + 65536) / 65536) * 65536;
	sys_memory_allocate(a_uiSize, SYS_MEMORY_PAGE_SIZE_64K, &l_uiAddr);
	return (void*)l_uiAddr;
}

void free(void *ptr) {
	if (ptr)
		sys_memory_free((sys_addr_t)ptr);
}

void *realloc(void *ptr, uint32_t size) {
	void *dest = malloc(size);
	memcpy(dest, ptr, size);
	free(ptr);
	return dest;
}