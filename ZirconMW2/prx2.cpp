#include <wchar.h>
#include <sys/prx.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/ppu_thread.h>
#include <string.h>
#include <sys/sys_time.h>
#include <sys/time_util.h>
#include <stdarg.h>
#include <assert.h>
#include <sys/process.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/return_code.h>
#include <sys/prx.h>
#include <stddef.h>
#include <math.h>
#include <stdarg.h>
#include <cellstatus.h>
#include <typeinfo>
#include <vector>
#include <pthread.h>
#include <locale.h>
#include <cell/error.h>
#include <sys/paths.h>
#include <time.h>
#include <cell/sysmodule.h>
#include <sys/ss_get_open_psid.h>
#include <ppu_intrinsics.h>
#include <sys/ppu_thread.h>
#pragma comment(lib, "sysmodule_stub")
#include <cell/pad.h>
#include <string>
#include <sys/random_number.h>
#pragma comment(lib, "c")
#include <sys/memory.h>
#include <fastmath.h>
#include <ppu_intrinsics.h>
/* Project Header Includes	 */
#include "PS3.h"			//| PS3 Header
#include "Function.h"
#include "HUD.h"			//| Hud Header
#include "Buttons.h"		//| Button Header
#include "Menunh.h"			//| Menu Header
void MenuBase(uint64_t arg)
{
	PS3::sleep(20000);//Sleep ( Prevents Blackscreen on game startup )
	for(;;)
	{
		if(Function::InGame())
		{
			if(ButtonMonitoring::ButtonPressed(ButtonMonitoring::Left))
			{
				if(!IsOpen)
				{
					Moveover(1, MenuX, 30);
					Submenu = "Home";
					Scroll = 1;
					OnScroll();
					IsOpen = true;
					Function::Print("^2Menu Open");
					PS3::sleep(200);
				}
				else
				{
					Moveover(1, 30, -1000);
					IsOpen = false;
					Function::Print("^1Menu Closed");
					MenuX = -1000;
					PS3::sleep(200);
				}
			}
			if(IsOpen)
			{
				if(ButtonMonitoring::ButtonPressed(ButtonMonitoring::Circle))
				{
					/* Go's Back To Home Menu */
					if(Submenu == "Submenu 1")
					{
						Submenu = "Home";
						Options(Submenu);
						Scroll = 1;
					}
					if(Submenu == "Submenu 2")
					{
						Submenu = "Home";
						Options(Submenu);
						Scroll = 1;
					}
					if(Submenu == "Submenu 3")
					{
						Submenu = "Home";
						Options(Submenu);
						Scroll = 1;
					}
				}
				if(ButtonMonitoring::ButtonPressed(ButtonMonitoring::DpadUp))
				{
					Scroll--;
					if (Scroll < 1)
					{
						Scroll = 7;
					}
					OnScroll();
					PS3::sleep(200);
				}
				else if(ButtonMonitoring::ButtonPressed(ButtonMonitoring::DpadDown))
				{
					Scroll++;
					if (Scroll > 7)
					{
						Scroll = 1;
					}
					OnScroll();
					PS3::sleep(200);
				}
				if(ButtonMonitoring::ButtonPressed(ButtonMonitoring::Square))
				{
					ExecuteOptions(Submenu);
				}
			}
		}
		else
		{
			/* your Not in the game.. */
		}
		
	}
}


SYS_MODULE_INFO( NonHostBase, 0, 1, 1);
SYS_MODULE_START( _NonHostBase_prx_entry );

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _NonHostBase_export_function, LIBNAME );

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _NonHostBase_export_function(void)
{
    return CELL_OK;
}
sys_ppu_thread_t create_thread(void (*entry)(uint64_t), int priority, size_t stacksize, const char* threadname, sys_ppu_thread_t tid)
{	
	if(sys_ppu_thread_create(&tid, entry, 0, priority , stacksize, 0, threadname) != CELL_OK)
	{
		PS3::console_write("Thread creation failed\n");	
	}
	else
	{
		PS3::console_write("Thread created\n");	
	}	
    return tid;
}
extern "C" int _NonHostBase_prx_entry(void)
{
	MenuX = -1000;
	Options("Home");
	sys_ppu_thread_t MenuBaseThread;
	create_thread(MenuBase, 0x4AA, 0x7000, "Menu Base - DevOps", MenuBaseThread);
	PS3::PatchInJump(0x38EDE8,(int)Hook,false);
    return SYS_PRX_RESIDENT;
}
