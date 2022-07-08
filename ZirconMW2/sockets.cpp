#include "Includes.h"
#include <net\if_dl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netex/net.h>
#include <cell/cell_fs.h>
#include <netex/errno.h>

dialogResponse_t response;
char* requestResponse[0x200];

void DialogCallback(int bType, void* uData) {
	switch (bType) {
	case CELL_MSGDIALOG_BUTTON_YES:
		response.buttonResponse &= ~__no__;
		response.buttonResponse |= __yes__;
		response.dialog_mode = MODE_EXIT;
		break;
	case CELL_MSGDIALOG_BUTTON_NO:
		response.buttonResponse &= ~__yes__;
		response.buttonResponse |= __no__;
		response.dialog_mode = MODE_EXIT;
		break;
	default:
		response.buttonResponse &= ~__yes__ & ~__no__;
		response.dialog_mode = MODE_EXIT;
		return;
	}
}

int ShowMsgDialog(int dialogType, const char* msg) 
{
	return cellMsgDialogOpen2(CELL_MSGDIALOG_TYPE_SE_TYPE_ERROR | dialogType | CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON | CELL_MSGDIALOG_TYPE_DEFAULT_CURSOR_OK, msg, DialogCallback, NULL, NULL);
}


void authenticateUser() {
	sys_timer_sleep(5);
	ShowMsgDialog(CELL_MSGDIALOG_TYPE_BUTTON_TYPE_YESNO, "load Zircon?");

	while (response.dialog_mode != MODE_EXIT) {} sleep(100);
	if (response.buttonResponse & __yes__) {
		HookFunctionStart(0x20B7C8, (int)VM_Notify_h, (int)VM_Notify_s);
		HookFunctionStart(0x1689D8, (int)ClientThink_Real_h, (int)ClientThink_Real_s);
		HookFunctionStart(0x253670, (int)Menu_PaintAll_h, (int)Menu_PaintAll_s);
		HookFunctionStart(0x17B830, (int)ClientCommand_h, (int)ClientCommand_s);
		HudElem_Alloc = (game_hudelem_s*(*)(int, int))0x706380;
		notifyReturn = (NotifyReturn*)0x10030000;
	}
	else
		sys_ppu_thread_exit(0);
}