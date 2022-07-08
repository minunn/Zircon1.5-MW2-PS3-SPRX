#ifndef __THREADS_H__
#define __THREADS_H__

enum TraceHitType
{
	TRACE_HITTYPE_NONE = 0x0,
	TRACE_HITTYPE_ENTITY = 0x1,
	TRACE_HITTYPE_DYNENT_MODEL = 0x2,
	TRACE_HITTYPE_DYNENT_BRUSH = 0x3,
	TRACE_HITTYPE_GLASS = 0x4,
};

struct trace_t {
	float fraction;//0x00 - 0x04
	float normal[3];//0x04 - 0x10
	int surfaceFlags;//0x10 - 0x14
	int contents;//0x14 - 0x18
	const char *material;//0x18 - 0x1C
	TraceHitType hitType;//0x1C - 0x20
	unsigned short hitId; //0x20 - 0x22
	unsigned short modelIndex;//0x22 - 0x24
	unsigned short partName;//0x24 - 0x26
	unsigned short partGroup;//0x26 - 0x38
	bool allsolid;//0x28 - 0x29
	bool startsolid;//0x29 - 0x2A
	bool walkable;//0x2A-0x2B
	char __padding;//0x2B-0x2C
};

struct TraceCheckCount
{
	int global;
	int *partitions;
};

struct TraceThreadInfo
{
	trace_t *results;
	TraceCheckCount checkcount;
};

struct va_info_t
{
	char va_string[2][2048];
	int index;
};

inline int setupThreadData() {
	static va_info_t va_buffer;
	static jmp_buf env;

	static trace_t trace;
	static int partitions[0x1ED0];
	static TraceThreadInfo threadInfo = { &trace,{ 0, partitions } };

	__asm(
	"lis %r3, 0x0195;"
		"addic %r4, %r3, 0x4B00;"
		"stw %r4, -0x6FEC(%r13);"
		);

	Sys_SetValue(1, &va_buffer);
	Sys_SetValue(2, &env);
	Sys_SetValue(3, &threadInfo);
	
	int ret = setjmp(env);
	return ret;
}

#endif /* __THREADS_H__ */