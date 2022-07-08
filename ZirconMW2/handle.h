#ifndef __HANDLE_H__
#define __HANDLE_H__

#include <sys/prx.h>
#include <time.h>

typedef uint32_t handle_t;

enum handleCall_t {
	CALL_START = 0x1,
	CALL_EXECUTE = 0x2,
	CALL_TEMP = 0x3,
	CALL_STOP = 0x4,
	CALL_FREE = 0x5,
};

typedef void(*handleCallback)(int32_t arg, handle_t* handle, handleCall_t type);

#define HANDLE_COUNT		0x100
#define INVALID_HANDLE		((handle_t)-1)

#define TIME_NOW			clock()
#define TIME_NOW_OFF(x)		(clock() + (x * (CLOCKS_PER_SEC / 1000)))

struct handle_s {
	int arg;
	handleCallback function;
	handleCall_t type;
	handle_t* handle;
	clock_t interval;
	clock_t time;
	clock_t startTime;
};

void handleAlloc(handle_t* handle, int arg, handleCallback function, int interval, clock_t start_time);
handle_t handleAllocTemp(int arg, handleCallback function, clock_t start_time);
bool handleStop(handle_t* handle);
bool doesHandleExist(handle_t* handle);
bool handleFree(handle_t* handle);
void handleExecute();
void handleStopAll();
void handleClear(handle_t* handle);
void handleClearAll();

//Hook handles
void handleHookAlloc(handle_t* handle, int arg, handleCallback function, int interval, clock_t start_time);
handle_t handleHookAllocTemp(int arg, handleCallback function, clock_t start_time);
bool handleHookStop(handle_t* handle);
bool doesHandleHookExist(handle_t* handle);
bool handleHookFree(handle_t* handle);
void handleHookExecute();
void handleHookStopAll();
void handleHookClear(handle_t* handle);
void handleHookClearAll();

void handleConstantAlloc(handle_t* handle, int arg, handleCallback function, int interval, clock_t start_time);
void handleConstant();
bool doesConstantHandleExist(handle_t* handle);
bool handleConstantStop(handle_t* handle);

#endif /*__HANDLE_H__*/