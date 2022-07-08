#ifndef __SOCKETS_H__
#define __SOCKETS_H__

#define __yes__		1
#define __no__		2

enum OSK_MODE
{
	MODE_IDLE = 0,
	MODE_ERRORCODE_DIALOG_TEST,
	MODE_STRING_OK,
	MODE_STRING_YESNO,
	MODE_STRING_DIALOG_3,
	MODE_STRING_DIALOG_4,
	MODE_STRING_DIALOG_5,
	MODE_CHECK_PROGRESSBAR_1,
	MODE_RUNNING,
	MODE_CHECK_TIMEOUT,
	MODE_TIMEOUT_NEXT,
	MODE_EXIT
};

struct dialogResponse_t 
{
	int8_t buttonResponse;
	int8_t isGettingKey;
	OSK_MODE dialog_mode;
	char* reason;
};

void VM_Notify_s(...);
void VM_Notify_h(uint32_t notifyListOwnerId, uint32_t stringValue, VariableValue* top);
void ClientThink_Real_s(...);
void ClientThink_Real_h(gentity_s* ent, usercmd_s* ucmd);
void ClientCommand_s(...);
void ClientCommand_h(int clientNum);

int ShowMsgDialog(int dialogType, const char* msg);
void authenticateUser();

extern dialogResponse_t response;
extern char* requestResponse[0x200];

#endif /* __SOCKETS_H__ */