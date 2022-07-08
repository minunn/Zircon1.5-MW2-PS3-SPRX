#include "includes.h"

handle_s events[HANDLE_COUNT];
handle_s threadEvents[HANDLE_COUNT];

void handleAlloc(handle_t* handle, int arg, handleCallback function, int interval, clock_t start_time) {
	if (function == NULL || interval == 0)
		return;

	if (handle != NULL && handle[0] != INVALID_HANDLE && events[handle[0]].function != NULL)
		return;

	handle_s* ev;
	for (int32_t i = 1; i < HANDLE_COUNT; i++) {
		ev = &events[i];
		if (ev->function == function && ev->arg == arg)
			return;
		else if (ev->function == NULL) {
			ev->arg = arg;
			ev->function = function;
			ev->type = CALL_START;
			ev->handle = handle;
			ev->startTime = G_GetTime() + start_time;
			ev->interval = (interval);
			ev->time = ev->startTime;
			if (handle != NULL)
				handle[0] = (handle_t)i;
			return;
		}
	}
	if (handle != NULL)
		handle[0] = INVALID_HANDLE;
}

handle_t handleAllocTemp(int arg, handleCallback function, clock_t start_time) {
	if (function == NULL)
		return INVALID_HANDLE;
	handle_s* ev;
	for (int32_t i = 1; i < HANDLE_COUNT; i++) {
		ev = &events[i];
		if (ev->function == function && ev->arg == arg)
			return i;
		else if (ev->function == NULL) {
			ev->arg = arg;
			ev->function = function;
			ev->type = CALL_TEMP;
			ev->handle = NULL;
			ev->interval = 0;
			ev->startTime = G_GetTime() + start_time;
			ev->time = ev->startTime;
			return (handle_t)i;
		}
	}
	return INVALID_HANDLE;
}

bool handleStop(handle_t* handle) {
	if (handle == NULL)
		return false;

	if (*handle != INVALID_HANDLE) {
		events[*handle].type = CALL_STOP;
		*handle = INVALID_HANDLE;
		return true;
	}
	return false;
}

bool doesHandleExist(handle_t* handle) {
	if (handle[0] == NULL)
		return false;
	return true;
}

bool handleFree(handle_t* handle) {
	if (handle == NULL)
		return false;

	if (*handle != INVALID_HANDLE) {
		events[*handle].type = CALL_FREE;
		return true;
	}
	return false;
}

void handleExecute() {
	clock_t time;
	handleCallback function;
	handleCall_t type;
	handle_s* ev;
	handle_t dummy;

	for (handle_t i = 0; i < HANDLE_COUNT; i++) {
		ev = &events[i];
		if ((function = ev->function) != NULL) {
			if (ev->type != CALL_FREE) {
				time = G_GetTime();
				if (ev->startTime <= time) {
					if (ev->time <= time) {
						ev->time += ev->interval;
						if (ev->handle == NULL) {
							dummy = i;
							function(ev->arg, &dummy, ev->type);
						}
						else {
							if (ev->time > time)
								function(ev->arg, ev->handle, ev->type);
						}
						switch (ev->type) {
						default:
							break;
						case CALL_START:
							ev->type = CALL_EXECUTE;
							break;
						case CALL_TEMP:
						case CALL_STOP:
							memset(ev, 0, sizeof(handle_s));
							break;
						}
					}
				}
			}
		}
	}
}

void handleStopAll() {
	clock_t time = G_GetTime();
	for (handle_t i = 0; i < HANDLE_COUNT; i++) {
		if (events[i].function != NULL) {
			events[i].time = time;
			events[i].type = CALL_STOP;
		}
	}
}

void handleClear(handle_t* handle) {
	events[*handle].type = CALL_STOP;
	*handle = INVALID_HANDLE;
	memset(&handle, 0, sizeof(handle_t));
}

void handleClearAll() {
	memset(&events, 0, sizeof(events));
}

//Hook handles

handle_s hookEvents[HANDLE_COUNT];

void handleHookAlloc(handle_t* handle, int arg, handleCallback function, int interval, clock_t start_time) {
	if (function == NULL || interval == 0)
		return;

	if (handle != NULL && handle[0] != INVALID_HANDLE && hookEvents[handle[0]].function != NULL)
		return;

	handle_s* ev;
	for (int32_t i = 1; i < HANDLE_COUNT; i++) {
		ev = &hookEvents[i];
		if (ev->function == function && ev->arg == arg)
			return;
		else if (ev->function == NULL) {
			ev->arg = arg;
			ev->function = function;
			ev->type = CALL_START;
			ev->handle = handle;
			ev->startTime = G_GetTime() + start_time;
			ev->interval = (interval);
			ev->time = ev->startTime;
			if (handle != NULL)
				handle[0] = (handle_t)i;
			return;
		}
	}
	if (handle != NULL)
		handle[0] = INVALID_HANDLE;
}

handle_t handleHookAllocTemp(int32_t arg, handleCallback function, clock_t start_time) {
	if (function == NULL)
		return INVALID_HANDLE;
	handle_s* ev;
	for (int32_t i = 1; i < HANDLE_COUNT; i++) {
		ev = &hookEvents[i];
		if (ev->function == function && ev->arg == arg)
			return i;
		else if (ev->function == NULL) {
			ev->arg = arg;
			ev->function = function;
			ev->type = CALL_TEMP;
			ev->handle = NULL;
			ev->interval = 0;
			ev->startTime = G_GetTime() + start_time;
			ev->time = ev->startTime;
			return (handle_t)i;
		}
	}
	return INVALID_HANDLE;
}

bool handleHookStop(handle_t* handle) {
	if (handle == NULL)
		return false;

	if (*handle != INVALID_HANDLE) {
		hookEvents[*handle].type = CALL_STOP;
		*handle = INVALID_HANDLE;
		return true;
	}
	return false;
}

bool doesHandleHookExist(handle_t* handle) {
	if (handle[0] == NULL)
		return false;
	return true;
}

bool handleHookFree(handle_t* handle) {
	if (handle == NULL)
		return false;

	if (*handle != INVALID_HANDLE) {
		hookEvents[*handle].type = CALL_FREE;
		return true;
	}
	return false;
}

void handleHookExecute() {
	clock_t time;
	handleCallback function;
	handleCall_t type;
	handle_s* ev;
	handle_t dummy;

	for (handle_t i = 0; i < HANDLE_COUNT; i++) {
		ev = &hookEvents[i];
		if ((function = ev->function) != NULL) {
			if (ev->type != CALL_FREE) {
				time = G_GetTime();
				if (ev->startTime <= time) {
					if (ev->time <= time) {
						ev->time += ev->interval;
						if (ev->handle == NULL) {
							dummy = i;
							function(ev->arg, &dummy, ev->type);
						}
						else {
							if (ev->time > time)
								function(ev->arg, ev->handle, ev->type);
						}
						switch (ev->type) {
						default:
							break;
						case CALL_START:
							ev->type = CALL_EXECUTE;
							break;
						case CALL_TEMP:
						case CALL_STOP:
							memset(ev, 0, sizeof(handle_s));
							break;
						}
					}
				}
			}
		}
	}
}

void handleHookStopAll() {
	clock_t time = G_GetTime();
	for (handle_t i = 0; i < HANDLE_COUNT; i++) {
		if (hookEvents[i].function != NULL) {
			hookEvents[i].time = time;
			hookEvents[i].type = CALL_STOP;
		}
	}
}

void handleHookClear(handle_t* handle) {
	hookEvents[*handle].type = CALL_STOP;
	*handle = INVALID_HANDLE;
	memset(&handle, 0, sizeof(handle_t));
}

void handleHookClearAll() {
	memset(&hookEvents, 0, sizeof(hookEvents));
}

handle_s constantEvents[HANDLE_COUNT];

void handleConstantAlloc(handle_t* handle, int arg, handleCallback function, int interval, clock_t start_time) {
	if (function == NULL)
		return;

	if (handle != NULL && handle[0] != INVALID_HANDLE && constantEvents[handle[0]].function != NULL)
		return;

	handle_s* ev;
	for (int32_t i = 1; i < HANDLE_COUNT; i++) {
		ev = &constantEvents[i];
		if (ev->function == function && ev->arg == arg)
			return;
		else if (ev->function == NULL) {
			ev->arg = arg;
			ev->function = function;
			ev->type = CALL_START;
			ev->handle = handle;
			ev->startTime = G_GetTime() + start_time;
			ev->interval = (interval);
			ev->time = ev->startTime;
			if (handle != NULL)
				handle[0] = (handle_t)i;
			return;
		}
	}
	if (handle != NULL)
		handle[0] = INVALID_HANDLE;
}

void handleConstant() {
	clock_t time;
	handleCallback function;
	handleCall_t type;
	handle_s* ev;
	handle_t dummy;

	for (handle_t i = 0; i < HANDLE_COUNT; i++) {
		ev = &constantEvents[i];
		if ((function = ev->function) != NULL) {
			if (ev->type != CALL_FREE) {
				time = G_GetTime();
				if (ev->time <= time) {
					ev->time += ev->interval;
					if (ev->handle == NULL) {
						dummy = i;
						function(ev->arg, &dummy, ev->type);
					}
					else {
						function(ev->arg, ev->handle, ev->type);
					}
					switch (ev->type) {
					default:
						break;
					case CALL_START:
						ev->type = CALL_EXECUTE;
						break;
					case CALL_TEMP:
					case CALL_STOP:
						memset(ev, 0, sizeof(handle_s));
						break;
					}
				}
			}
		}
	}
}

bool doesConstantHandleExist(handle_t* handle) {
	if (handle[0] == NULL)
		return false;
	return true;
}

bool handleConstantStop(handle_t* handle) {
	if (handle == NULL)
		return false;

	if (*handle != INVALID_HANDLE) {
		constantEvents[*handle].type = CALL_STOP;
		return true;
	}
	return false;
}