#define TOC (0x724C38)
struct opd_s
{
	int sub;
	int toc;
};
struct vec3
{
	float x;
	float y;
	float z;
};
void* read_process(uint64_t ea,uint32_t size)
{
#if CEX == 0
	void* data;
	system_call_4(904, (uint64_t)sys_process_getpid(), ea, size, (uint64_t)data);
	return data;
#else
	
#endif
}
bool compassEnabled = false;
opd_s cb = {0x1D9EC0,TOC};
void (*cBuf_Addtext)(int cl,const char* s) = (void(*)(int,const char*))&cb;
//0015BB20
opd_s fxgcv = {0x1D9EC0,TOC};
float (*FX_GetClientVisibility)(int localcientnum, float *start, float *end) = (float(*)(int,float*, float*))&fxgcv;
opd_s kick = {0x00213C00,TOC};
void (*SV_KickUser_f)(char *playerName, int maxPlayerNameLen) = (void(*)(char*,int))&kick;//max len = 0x40

/*
typedef struct {
	vec3		forward, right, up;
	float		frametime;

	int			msec;

	unsigned int	walking;
	unsigned int	groundPlane;
	trace_t		groundTrace;

	float		impactSpeed;

	vec3		previous_origin;
	vec3		previous_velocity;
	int			previous_waterlevel;
} pml_t;//size = 31?*/
//0x000266F8 - PM_SetMovementDir(pmove_t *pm, pml_t *pml)
//opd_s PMSMD = {0x000266F8,TOC};
//void(*PM_SetMovementDir)(unsigned int pm, pml_t *pml) = (void(*)(unsigned int, pml_t *))&PMSMD;
//pml_t pmlo;
//pml_t *pml = &pmlo;
void setMovement() {
	
	//PM_SetMovementDir(0x00915254,);
}
/*unsigned int getUserCMD(int client) {

}*/
void setName(char *name) {
	strcpy((char*)0x01f9f11c,name);
}
namespace ButtonMonitoring
{  
    enum Buttons
    {
                L1 = 0x41,
                R1 = 0x4D,
                Square = 0x29,
                R3 = 0xD1,
                DpadUp = 0xF5,
                DpadDown = 0x105,
                Cross = 0x11,
                Triangle = 0x34,
                Circle = 0x1D,
                L2 = 0xDC,
                R2 = 0xE8,
                L3 = 0xC4,
                Left = 0x10D,
                Right =  0x119,
                Select = 0xB8,
                Start = 0xAC
    };
    bool ButtonPressed(Buttons Button)
    {
	    return (*(char*)(0x0095C08A + Button) != 0);
    }
}
int selectedMenu = 0;
int selectedOption = 0;
int currentOptionCount = 0;
int lastMenus[20];
int lastMenuCount = 0;
namespace MENUS {
enum MENUS {
	Closed,
	Main,
	Self,
	Aimbot,
	Host,
	Clients,
	ClientOptions,
	APreset,
	Infections,
	Names,
	ClientsNonHost,
	Invalid
};
}

void openMenu() {
	lastMenuCount = 0;
	selectedMenu = MENUS::Main;
	selectedOption = 0;
	sleep(500);
}
void closeMenu() {
	lastMenuCount = 0;
	selectedMenu = MENUS::Closed;
	selectedOption = 0;
	sleep(40);
}
void openSubmenu(int menu) {
	lastMenus[lastMenuCount] = selectedMenu;
	lastMenuCount++;
	selectedMenu = menu;
	selectedOption = 0;
	sleep(100);
}
void goBack() {
	if (lastMenuCount == 0) {
		closeMenu();
	} else {
		lastMenuCount--;
		selectedMenu = lastMenus[lastMenuCount];
		selectedOption = 0;
	}
	sleep(100);
}
void resetOptions() {
	int len = strlen((char*)0x10070200);
	for (int i = 0; i < len+1; i++) {
		*(char*)(0x10070200+i) = 0;
	}
}

void addTitle(char *text) {
	if(*(char*)0x01D17A8C) {
		*(float*)0x007291A4 = 0.2f;//font
		*(float*)0x00729418 = 100.0f;//x
		*(float*)0x00729318 = 40.0f;//y
	} else {
		*(float*)0x007291A4 = 0.2f;
		*(float*)0x00729418 = 235.0f;
		*(float*)0x00729318 = 40.0f;
	}
	*(unsigned int*)0x0729440 = 0x10070200;//set pointer
	//*(char*)0x00253AC8 = 0x40;//enable     this part messes up on ita for some reason (NOW KNOWN. ITA DID NOT REMOVE MEMORY LIMITATIONS. AKA NEED COBRA MODE!!!)
	//*(int*)0x00253AC8 = 0x60000000;
	char fourty[] = {0x40};
	write_process((void*)0x00253AC8,fourty,1);
	strcpy((char*)(0x10070200+strlen((char*)0x10070200)),"\n^5");
	strcpy((char*)(0x10070200+strlen((char*)0x10070200)),text);
	strcpy((char*)(0x10070200+strlen((char*)0x10070200)),"\n\n^7");
}
void addOption(char *text) {
	*(unsigned int*)0x0729440 = 0x10070200;
	//*(char*)0x00253AC8 = 0x40;
	char fourty[] = {0x40};
	write_process((void*)0x00253AC8,fourty,1);
	strcpy((char*)(0x10070200+strlen((char*)0x10070200)),text);
	if (currentOptionCount == selectedOption)
		strcpy((char*)(0x10070200+strlen((char*)0x10070200))," ^1<-");
	strcpy((char*)(0x10070200+strlen((char*)0x10070200)),"^7\n");
	currentOptionCount++;
}
int getOption() {
	if (ButtonMonitoring::ButtonPressed(ButtonMonitoring::Square)) {
		sleep(100);
		return selectedOption;
	}
	return -1;
}
bool allowPressedUp = true;
bool allowPressedDown = true;
void otherControls() {
	bool up = ButtonMonitoring::ButtonPressed(ButtonMonitoring::DpadUp);
	bool down = ButtonMonitoring::ButtonPressed(ButtonMonitoring::DpadDown);
	if (up) {
		if (allowPressedUp) {
			up = false;
		}
		allowPressedUp = true;
	} else {
		allowPressedUp = false;
	}

	if (down) {
		if (allowPressedDown) {
			down = false;
		}
		allowPressedDown = true;
	} else {
		allowPressedDown = false;
	}


	if (ButtonMonitoring::ButtonPressed(ButtonMonitoring::Circle))
		goBack();
	if (up) {
		selectedOption--;
		if (selectedOption < 0)
			selectedOption = currentOptionCount-1;
		//sleep(50);
	}
	if (down) {
		selectedOption++;
		if (selectedOption > currentOptionCount-1)
			selectedOption = 0;
		//sleep(50);
	}
}

int printTimer = 0;
char *printText;
bool printB = false;
bool printBoolValue = false;
void print(char *Text) {
	printTimer = 50;
	printText = Text;
	printB = false;
}
void printBool(char *Text, bool value) {
	printTimer = 50;
	printText = Text;
	printBoolValue = value;
	printB = true;
}

void printLoop() {
	if (printTimer > 0) {
		*(unsigned int*)0x0729440 = 0x10070200;
		//*(char*)0x00253AC8 = 0x40;
		char fourty[] = {0x40};
		write_process((void*)0x00253AC8,fourty,1);
		strcpy((char*)(0x10070200+strlen((char*)0x10070200)),"           ^2");
		strcpy((char*)(0x10070200+strlen((char*)0x10070200)),printText);
		if (printB) {
			if (printBoolValue)
				strcpy((char*)(0x10070200+strlen((char*)0x10070200)),": ^5Enabled");
			else
				strcpy((char*)(0x10070200+strlen((char*)0x10070200)),": ^1Disabled");
		}
		strcpy((char*)(0x10070200+strlen((char*)0x10070200)),"^7\n");
		printTimer--;
	}
}
unsigned int G_Client(int clientIndex) {
	return 0x14E2200 + (0x3700 * clientIndex);
}//0x1319958+(client*0x280) = gentity
unsigned int G_Entity(int client) {//host only I believe
	return 0x1319958+(client*0x280);
}
opd_s scr_killplayer_t = {0x001AEA40,TOC};
void(*Scr_PlayerKilled)(unsigned int gentityself, unsigned int gentityinflictor, unsigned int gentityattacker, int damage, int meansOfDeath, int iWeapon, float *vDir, float*/*hitLocation_t*/ hitLoc, int psTimeOffset, int deathAnimDuration) = (void(*)(unsigned int, unsigned int, unsigned int,int,int,int,float*,float*,int,int))&scr_killplayer_t;
void killPlayer(int client) {

}
void infiniteAmmo(int clientIndex) {
	*(int*)(G_Client(clientIndex) + 0x2DC) = 0x7fffffff;
	*(int*)(G_Client(clientIndex) + 0x354) = 0x7fffffff;
	*(int*)(G_Client(clientIndex) + 0x2EC) = 0x7fffffff;
	*(int*)(G_Client(clientIndex) + 0x378) = 0x7fffffff;
	*(int*)(G_Client(clientIndex) + 0x360) = 0x7fffffff;
	*(int*)(G_Client(clientIndex) + 0x378) = 0x7fffffff;
	*(int*)(G_Client(clientIndex) + 0x370) = 0x7fffffff;
}
template <typename T>
T getClientData(int clientIndex, unsigned int offset) {
	return *(T*)(G_Client(clientIndex) + offset);
}
char *getClientName(int clientIndex) {
	return (char*)(G_Client(clientIndex) + 0x3208);
}
bool killclients[20];
void killClient(int clientIndex) {
	//killclients[clientIndex] = true;
	//vec3 *v = (vec3*)(G_Client(clientIndex)+0x1C);
	//v->z = (unsigned int)0xffffffff;
	*(short*)(G_Client(clientIndex)+0x24) = 0xFFFF;
}
#include "Aimbot.h";
//void killClientReal(int clientIndex) {
	//*(char*)(G_Client(clientIndex)+0x345C) = 0x01;
	//printf("Before\n");
	//opd_s player_die_t = {0x001AEA40/*0x0017CBC0*/,TOC};
	//void (*player_die)(unsigned int self, unsigned int inflictor, unsigned int attacker, int damage, int meansOfDeath, int iWeapon, const float *vDir, unsigned int hitLoc, int psTimeOffset, int animation) = (void(*)(unsigned int, unsigned int, unsigned int, int, int, int, const float *, unsigned int, int,int))&player_die_t;
	//player_die(G_Entity(GetIndex()),G_Entity(clientIndex),G_Entity(GetIndex()),0x186A0,0xc,0,0,0x2,*(int*)(G_Entity(clientIndex)+0x158),0);
	//printf("After\n");
//}
//0x00a13b82+0x50 ip address
void ipGrabber() {
	//0x00a13b82+0x50+0xXX*i (int) = ip
	//0x00a13b82+0xXX*i (char*) = name
	for (int i = 0; i < 18; i++) {
				int ip = *(int*)(0x00a1359a+0xd8*i+0x50);//0x00a13672
				if (ip != 0 && i != GetIndex()) {
					char *name = (char*)(0x00a1359a+0xd8*i);
					int p1 = (ip&0xff000000)>>24;
					int p2 = (ip&0x00ff0000)>>16;
					int p3 = (ip&0x0000ff00)>>8;
					int p4 = (ip&0x000000ff)>>0;
					char buf[100];
					snprintf(buf,sizeof(buf),"%s - %i.%i.%i.%i\n",name,p1,p2,p3,p4);
					strcpy((char*)(0x10070400+strlen((char*)0x10070400)),buf);
				}
			}
	//strcpy((char*)(0x10070400+strlen((char*)0x10070400)),"\n");
	writeToFile("/dev_hdd0/tmp/MW2IPS.txt",(char*)0x10070400,strlen((char*)0x10070400));
}
char *getName(int index) {
	return (char*)(0x00a1359a+0xd8*index);
}
void chatIP(int index) {
	if (index != GetIndex()) {
		int ip = *(int*)(0x00a1359a+0xd8*index+0x50);//0x00a13672
		char *name = (char*)(0x00a1359a+0xd8*index);
		int p1 = (ip&0xff000000)>>24;
		int p2 = (ip&0x00ff0000)>>16;
		int p3 = (ip&0x0000ff00)>>8;
		int p4 = (ip&0x000000ff)>>0;
		char buf[100];
		char ips[20];
		snprintf(ips,sizeof(ips),"%i.%i.%i.%i",p1,p2,p3,p4);
		snprintf(buf,sizeof(buf),"say ^1%s's IP: %s",name,ips);
		cBuf_Addtext(0,buf);
		cBuf_Addtext(1,buf);
	} else {
		print("Don't post your own ip!");
	}
}
int currentClient = 0;
int timer = 0;
char *kickPlayerFormat = "clientkick %i";
char kickPlayerBuf[60];//60 should be enough
bool forceHostEnabled = false;
int forceHostTimeout = 0;
void threadLoop() {
	//char nameKickPatch[4] = {0x48,0x21,0x7B,0x3A};
	//char nameKickPatch2[4] = {0x48, 0x21, 0x7B, 0xC6};
	////char nameKickPatch[4] = {0x48, 0x21, 0x7D, 0x2E};
	////write_process((char*)0x00217AC0,nameKickPatch,4);
	//Disable Cheat Protection
    unsigned char nop[4] = {0x60, 0x00, 0x00, 0x00};
    write_process((void*)0x2383A8, nop, 4);//Remove invalid char(s) check
	*(char*)0x007EDCA4 = 0x0;//non host end game fix
	//Enable 360 aim?
	//write_process((void*)ServerDataStruct.aimCheck1/*0x00048BD8*/, nop, 4);//CG_CanSeeFriendlyHead patch 1
	//write_process((void*)ServerDataStruct.aimCheck2/*0x00048C14*/, nop, 4);//CG_CanSeeFriendlyHead patch 2
	sys_ppu_thread_t id2;
	sys_ppu_thread_create(&id2,Aimthread,0,0x5AA,0x8000,0,"Aimbot");
	cBuf_Addtext(0,"set Iusb \"ui_mapname \\\"\"mp_rust;^1CFG ^2INFECTION;bind button_back exec ../../../dev_usb000/buttons_default.cfg\";");
	cBuf_Addtext(0,"set Iaim \"ui_mapname \\\"\"mp_rust;^1STRONG AIMBOT + UAV;set perk_bulletDamage 999;bind APAD_LEFT g_compassShowEnemies 1;bind APAD_RIGHT aim_autoaim_enabled 2;aim_lockon_region_height 480;aim_lockon_region_width 640;aim_lockon_enabled 1;aim_lockon_strength 1;aim_lockon_deflection 0;aim_autoaim_enabled 1;aim_autoaim_region_height 480;aim_autoaim_region_width 640;aim_slowdown_yaw_scale_ads 0;aim_slowdown_yaw_scale 0;aim_slowdown_pitch_scale 0;aim_slowdown_pitch_scale_ads 0;aim_slowdown_region_height 0;aim_slowdown_region_width 0;aim_slowdown_enabled 1;aim_aimAssistRangeScale 2;aim_autoAimRangeScale 2;set cg_drawfps 2;clanname PRO;set perk_weapSpreadMultiplier 0.0001\";");
	cBuf_Addtext(0,"set Igm \"ui_mapname \\\"\"mp_rust;^1God Mode Infection ^1(Press ^1Down ^1To ^1Activate)^7;bind dpad_down toggle xblive_privatematch 0 1;toggle xblive_rankedmatch 1 0;bind APAD_DOWN g_compassShowEnemies 1;bind APAD_UP clanname PRO\";");
	cBuf_Addtext(0,"set Isj \"ui_mapname \\\"\"mp_rust;^1Super ^3Jump^7 (SELECT TO ACTIVATE);bind BUTTON_BACK toggle jump_height 1000 39\";");
	cBuf_Addtext(0,"set Imm \"ui_mapname \\\"\"mp_rust;^9Mini-Menu^7;bind APAD_LEFT bind DPAD_UP vstr 1;set 1 \\\"\"set g_compassShowEnemies 1;set cg_drawfps 2;set clanname PRO;say ^1Infectable Mini-^5Menu;say ^1>^6Super_Jump^1<;say ^5Timescale;say ^5Gravity;bind dpad_up vstr 3;bind dpad_down vstr 2;bind dpad_left vstr e;bind button_a toggle jump_height 39 150 999;set 2 \\\"\"say ^5Infectable Mini-^5Menu;say ^5Super_Jump;say ^1>^6Timescale^1<;say ^5Gravity;bind dpad_up vstr 1;bind dpad_down vstr 3;bind button_a toggle timescale 0.5 1 1.5;set 3 \\\"\"say ^5Infectable Mini-^5Menu;say ^5Super_Jump;say ^5Timescale;say ^1>^6Gravity^1<;bind dpad_up vstr 2;bind button_a toggle g_gravity 200 800 3000;set e \\\"\"say ^7;say ^7;say ^7;say ^1MENU ^5CLOSED;say ^1;say ^1;say ^1;say ^1;bind dpad_up vstr 1;bind dpad_left +actionslot 3;bind BUTTON_A +gostand\"\\\"\"\";");
	//not even used cBuf_Addtext(0,"set FHT \"^2ON;xblive_privatematch 0;xblive_rankedmatch 1;disconnect;killserver;disconnect;xstartlobby;set party_connectToOthers 0;xsearchforgames;set party_hostmigration 0;set party_gameStartTimerLength 1;set party_pregameStartTimerLength 1;set party_timer 1;set badhost_endGameIfISuck 0;set party_minplayers 1;set party_autoteams 0;\";");
	cBuf_Addtext(0,"set FHF \"^1OFF;reset party_connectTimeout; reset party_host; reset party_hostmigration; reset onlinegame; reset onlinegameandhost; reset onlineunrankedgameandhost; reset migration_msgtimeout; reset migration_timeBetween; reset migration_verboseBroadcastTime; reset migrationPingTime; reset bandwidthtest_duration; reset bandwidthtest_enable; reset bandwidthtest_ingame_enable; reset bandwidthtest_timeout; reset cl_migrationTimeout; reset lobby_partySearchWaitTime; reset bandwidthtest_announceinterval; reset partymigrate_broadcast_interval; reset partymigrate_pingtest_timeout; reset partymigrate_timeout; reset partymigrate_timeoutmax; reset partymigrate_pingtest_retry;reset partymigrate_pingtest_timeout; reset g_kickHostIfIdle; reset sv_cheats; reset scr_dom_scorelimit; reset xblive_playEvenIfDown; reset party_hostmigration; reset badhost_endGameIfISuck ; reset badhost_maxDoISuckFrames; reset badhost_maxHappyPingTime ; reset badhost_minTotalClientsForHappyTest ; reset bandwidthtest_enable;\";");
	//cBuf_Addtext(0,"");
	for (;;) {
		if (!isInGameOrLoading()) {
			//in lobby and lobby only
			if (forceHostEnabled) {
				if (forceHostTimeout > 50)
					forceHostTimeout = 0;
				if (forceHostTimeout == 0) {
					printf("Ran force host script\n");
					cBuf_Addtext(0,"xsearchforgames;");
				}
				forceHostTimeout++;
			}
		}
		if (*(bool*)0x01D17A8C) {
			resetOptions();
			switch (selectedMenu) {
			case MENUS::Closed:
				if (ButtonMonitoring::ButtonPressed(ButtonMonitoring::DpadUp))
					openMenu();
				addTitle("Click \x14 to open mod menu\n\x3 to select");
				break;
			case MENUS::Main:
				addTitle("Paradise MW2 V1.4");
				addOption("Self Menu");
				addOption("Aimbot Menu");
				addOption("Aimbot Presets");
				addOption("Host Menu");
				addOption("Client List");
				addOption("IP's");
				switch(getOption()) {
				case 0:
					openSubmenu(MENUS::Self);
					break;
				case 1:
					openSubmenu(MENUS::Aimbot);
					break;
				case 2:
					openSubmenu(MENUS::APreset);
					break;
				case 3:
					openSubmenu(MENUS::Host);
					break;
				case 4:
					openSubmenu(MENUS::Clients);
					break;
				case 5:
					//ipGrabber();
					//print("Dumped to /dev_hdd0/tmp/gopro_2027/MW2IPS.txt");
					openSubmenu(MENUS::ClientsNonHost);
					break;
				}
				break;
			case MENUS::Aimbot:
				addTitle("Aimbot");
				addOption("Toggle");
				addOption("Aiming Required");
				addOption("Only Aim To Visible");
				addOption("Shoot To Enable");
				addOption("Auto Shoot");
				addOption("Semi Auto Mode");
				addOption("Auto Aim (Not Very Good)");
				addOption("Unfair Aimbot ^1(Host Only)");
				addOption("Silent Aimbot");
				//addOption("Silent Aimbot");
				switch(getOption()) {
				case 0:
					Aimbot = !Aimbot;
					printBool("Aimbot",Aimbot);//Aimbot Required visibleOnly shootToEnable autoShoot
					break;
				case 1:
					Required = !Required;
					printBool("Aiming Required",Required);
					break;
				case 2:
					visibleOnly = !visibleOnly;
					printBool("Only Aim To Visible",visibleOnly);
					break;
				case 3:
					shootToEnable = !shootToEnable;
					Required = true;
					printBool("Shoot To Enable",shootToEnable);
					break;
				case 4:
					autoShoot = !autoShoot;
					printBool("Auto Shoot Visible Players",autoShoot);
					break;
				case 5:
					semiAutoMode = !semiAutoMode;
					printBool("Semi Auto Mode",semiAutoMode);
					break;
				case 6:
					if (autoShoot) {
						autoAim = !autoAim;
						printBool("Auto Aim",autoAim);
					} else {
						autoAim = false;
						print("You must turn on auto shoot first!");
					}
					break;
				case 7:
					UnfairAimbot = !UnfairAimbot;
					printBool("Unfair Aimbot",UnfairAimbot);
					break;
				case 8:
					silentAimbot = !silentAimbot;
					printBool("Silent Aimbot",silentAimbot);
					break;
				}
				break;
			case MENUS::Self:
				addTitle("Non Host Menu");
				addOption("Hacker Pack");
				addOption("Show Radar");
				addOption("Red Boxes");
				addOption("Steady Aim");
				addOption("No Recoil");
				addOption("Bind Toggle Aim To DPad Left (Like PC Aiming)");
				addOption("^1END GAME");
				switch(getOption()) {
				case 0:
					cBuf_Addtext(0,"g_compassShowEnemies 1;");
					unsigned char rb[4] = {0x2F, 0x80, 0x00, 0x01};
					write_process((void*)0x496F4,rb,4);
					unsigned char sa1[4] = {0x2F, 0x80, 0x00, 0x00};
					write_process((void*)0x335E0,sa1,4);
					unsigned char sa[12] = {0xD0, 0x05, 0x00, 0x00, 0xD0, 0x06, 0x00, 0x00, 0x4E, 0x80, 0x00, 0x20};//kinda worked
					write_process((void*)0x0335D8,sa,12);
					char data[] = {0x38, 0x80, 0x00, 0x00};//li %r4, 0
					write_process((void*)0x1C1554,data,4);

					unsigned char norecoil[4] = {0x60,0x00,0x00,0x00};
					write_process((void*)0x9342C,norecoil,4);
					cBuf_Addtext(0,"player_breath_gasp_lerp 0;");
					cBuf_Addtext(0,"bind DPAD_LEFT \"toggleads\";");
					print("Hax Pax Enabled");
					break;
				case 1:
					compassEnabled = !compassEnabled;
					if (compassEnabled)
						cBuf_Addtext(0,"g_compassShowEnemies 1");
					else
						cBuf_Addtext(0,"g_compassShowEnemies 0");
					printBool("Show Enemies",compassEnabled);
					break;
				case 2:
					//red boxes
					bool isrbenabled = *(char*)0x496F7 == 0x01;
					if (isrbenabled) {
						//disable it
						unsigned char byte[4] = {0x2F, 0x80, 0x00, 0x00};
						write_process((void*)0x496F4,byte,4);
					} else {
						//enable it
						unsigned char byte[4] = {0x2F, 0x80, 0x00, 0x01};
						write_process((void*)0x496F4,byte,4);
					}
					printBool("Red Boxes",!isrbenabled);
					break;
				case 3:
					//steady aim
					bool issaenabled = *(char*)0x0335D8 == 0xD0;//0x335E3 == 0x00;
					if (issaenabled) {
						//disable it
						unsigned char byte[4] = {0x2F, 0x80, 0x00, 0x01};
						write_process((void*)0x335E0,byte,4);
						unsigned char sa[12] = {0x80, 0x03, 0x02, 0xD0, 0xC1, 0x82, 0x91, 0xDC,  0x2F, 0x80, 0x00, 0x02};
						write_process((void*)0x0335D8,sa,12);
					} else {
						//enable it
						unsigned char byte[4] = {0x2F, 0x80, 0x00, 0x00};
						write_process((void*)0x335E0,byte,4);
						unsigned char sa[12] = {0xD0, 0x05, 0x00, 0x00, 0xD0, 0x06, 0x00, 0x00, 0x4E, 0x80, 0x00, 0x20};//working but not completely
						write_process((void*)0x0335D8,sa,12);
						//char data[] = {0x38, 0x80, 0x00, 0x00};//li %r4, 0
						//write_process((void*)0x1C1554,data,4);
					}
					printBool("Steady Aim",!issaenabled);
					break;
				case 4:
					//no recoil
					bool isnrenabled = *(char*)0x9342C == 0x60;
					if (isnrenabled) {
						//disable it
						unsigned char byte[4] = {0x4B,0xFA,0x10,0xF5};
						write_process((void*)0x9342C,byte,4);
						cBuf_Addtext(0,"player_breath_gasp_lerp 1");
					} else {
						//enable it
						unsigned char byte[4] = {0x60,0x00,0x00,0x00};
						write_process((void*)0x9342C,byte,4);
						cBuf_Addtext(0,"player_breath_gasp_lerp 0");
					}
					printBool("No Recoil",!isnrenabled);
					break;
				case 5:
					cBuf_Addtext(0,"bind DPAD_LEFT \"toggleads\";");
					print("Press DPad Left To Toggle Aim");
					break;
				case 6:
					cBuf_Addtext(0,"Togglemenu;openmenu popup_endgame");
					break;
				}
				break;
			case MENUS::Host:
				addTitle("Host Menu");
				addOption("Super Jump");
				addOption("No Clip");
				addOption("God Mode");
				addOption("Allow Non Host End Game");
				addOption("Dis-Allow Non Host End Game");
				addOption("Unlimited Game");
				addOption("Unlimited Ammo");
				addOption("Change Map Rust");
				addOption("Game Mode Free For All");
				switch(getOption()) {
				case 0:
					cBuf_Addtext(0,"toggle jump_height 1000 700 39;bg_fallDamageMinHeight 999999;bg_fallDamageMaxHeight 999999");
					print("Super Jump Enabled");
					break;
				case 1:
					int currentMFlag = *(int*)(G_Client(GetIndex()) + 0x3420);
					if (currentMFlag == 0)
						*(int*)(G_Client(GetIndex()) + 0x3420) = 2;
					else
						*(int*)(G_Client(GetIndex()) + 0x3420) = 0;
					printBool("Noclip",(currentMFlag==0));
					break;
				case 2:
					int godmode = *(int*)(G_Client(GetIndex()) + 0x3228);
					if (godmode <= 1000)
						*(int*)(G_Client(GetIndex()) + 0x3228) = 0x7fffffff;
					else
						*(int*)(G_Client(GetIndex()) + 0x3228) = 100;
					printBool("Godmode",(godmode <= 1000));
					break;
				case 3:
					*(char*)0x007EDCA4 = 0x65;
					print("Non Host End Game (ONLY when host) ^2Allowed");
					break;
				case 4:
					*(char*)0x007EDCA4 = 0x00;
					print("Non Host End Game (ONLY when host) ^1Prohibited");
					break;
				case 5:
					cBuf_Addtext(0,"scr_ctf_timelimit 0;scr_dd_timelimit 0;scr_dm_timelimit 0;scr_dom_timelimit 0;scr_koth_timelimit 0;scr_sab_timelimit 0;scr_war_timelimit 0;scr_dm_scorelimit 0;scr_ctf_scorelimit 0;scr_dd_scorelimit 0;scr_dom_scorelimit 0;scr_koth_scorelimit 0;scr_sab_scorelimit 0;scr_war_scorelimit 0;scr_dm_numlives 0;scr_dm_timelimit 0;scr_dm_scorelimit 0;scr_tdm_numlives 0;scr_tdm_timelimit 0;scr_tdm_scorelimit 0;");
					break;
				case 6:
					infiniteAmmo(GetIndex());
					break;
				case 7:
					cBuf_Addtext(0,"map mp_rust;wait 1;fast_restart;");
					break;
				case 8:
					cBuf_Addtext(0,"g_gametype dm;wait 1;fast_restart;");
					break;
				}
				break;
			case MENUS::Clients:
				addTitle("Clients (Host)");
				for (int i = 0; i < 18; i++)
					addOption(getClientName(i));
				int opapa = getOption();
				if (opapa != -1) {
					currentClient = opapa;
					openSubmenu(MENUS::ClientOptions);
				}
				break;
			case MENUS::ClientsNonHost:
				addTitle("Clients (Broadcast IP In Chat)");
				addOption("Dump IP's To File");
				for (int i = 0; i < 18; i++)
					addOption(getName(i));
				int opapa2 = getOption();
				if (opapa2 != -1) {
					if (opapa2 == 0) {
						ipGrabber();
					} else {
						chatIP(opapa2-1);
					}
				}
				break;
			case MENUS::ClientOptions:
				addTitle(getClientName(currentClient));
				addOption("Noclip");
				addOption("Godmode");
				addOption("Infinite Ammo");
				addOption("^1Kick");
				switch(getOption()) {
				case 0:
					int currentMFlag = *(int*)(G_Client(currentClient) + 0x3420);
					if (currentMFlag == 0)
						*(int*)(G_Client(currentClient) + 0x3420) = 2;
					else
						*(int*)(G_Client(currentClient) + 0x3420) = 0;
					printBool("Noclip",(currentMFlag==0));
					break;
				case 1:
					int godmode = *(int*)(G_Client(currentClient) + 0x3228);
					if (godmode <= 1000)
						*(int*)(G_Client(currentClient) + 0x3228) = 0x7fffffff;
					else
						*(int*)(G_Client(currentClient) + 0x3228) = 100;
					printBool("Godmode",(godmode <= 1000));
					break;
				case 2:
					infiniteAmmo(currentClient);
					print("Given Infinite Ammo (Lasts Until Death)");
					break;
				case 3:
					//SV_KickUser_f(getClientName(currentClient),0x40);
					snprintf(kickPlayerBuf,60,kickPlayerFormat,currentClient);
					cBuf_Addtext(0,kickPlayerBuf);
					break;
				}
				break;
			case MENUS::APreset:
				//Aimbot Required visibleOnly shootToEnable autoShoot
				addTitle("Aimbot Presets");
				addOption("Paradise Special Aimbot");
				addOption("Paradise Special Aimbot (Semi Auto)");
				addOption("Akimbo Aimbot");
				addOption("Run-n-Gun Aimbot (Basic Smart Strong Aimbot)");
				addOption("Best Host-Only Fair Aimbot");
				addOption("Best Host-Only Fair Aimbot (Semi Auto)");
				addOption("Host-Only Super Unfair Aimbot");
				//addOption("Silent Aimbot");
				//addOption("Silent Aimbot (Semi Auto)");
				switch(getOption()) {
				case 0:
					Aimbot = true;
					Required = true;
					visibleOnly = true;
					shootToEnable = false;
					autoShoot = true;
					semiAutoMode = false;
					UnfairAimbot = false;
					silentAimbot = false;
					autoAim = false;
					print("Set");
					break;
				case 1:
					Aimbot = true;
					Required = true;
					visibleOnly = true;
					shootToEnable = false;
					autoShoot = true;
					semiAutoMode = true;
					UnfairAimbot = false;
					silentAimbot = false;
					autoAim = false;
					print("Set");
					break;
				case 2:
					Aimbot = true;
					Required = false;
					visibleOnly = false;
					shootToEnable = true;
					autoShoot = false;
					semiAutoMode = false;
					UnfairAimbot = false;
					silentAimbot = false;
					autoAim = false;
					print("Set");
					break;
				case 3:
					Aimbot = true;
					Required = true;
					visibleOnly = false;
					shootToEnable = false;
					autoShoot = false;
					semiAutoMode = false;
					UnfairAimbot = false;
					silentAimbot = false;
					autoAim = false;
					print("Set");
					break;
				case 4:
					Aimbot = true;
					Required = false;
					visibleOnly = true;
					shootToEnable = false;
					autoShoot = true;
					semiAutoMode = false;
					UnfairAimbot = false;
					silentAimbot = false;
					autoAim = false;
					print("Set");
					break;
				case 5:
					Aimbot = true;
					Required = false;
					visibleOnly = true;
					shootToEnable = false;
					autoShoot = true;
					semiAutoMode = true;
					UnfairAimbot = false;
					silentAimbot = false;
					autoAim = false;
					print("Set");
					break;
				case 6:
					Aimbot = true;
					Required = false;
					visibleOnly = false;
					shootToEnable = false;
					autoShoot = false;
					semiAutoMode = false;
					UnfairAimbot = true;
					silentAimbot = false;
					autoAim = false;
					print("Set");
					break;
				/*case 7:
					Aimbot = true;
					Required = false;
					visibleOnly = true;
					shootToEnable = false;
					autoShoot = true;
					semiAutoMode = false;
					UnfairAimbot = false;
					silentAimbot = true;
					autoAim = false;
					print("Set");
					break;
				case 8:
					Aimbot = true;
					Required = false;
					visibleOnly = true;
					shootToEnable = false;
					autoShoot = true;
					semiAutoMode = true;
					UnfairAimbot = false;
					silentAimbot = true;
					autoAim = false;
					print("Set");
					break;*/
				}
				break;
			default:
				//close menu or something
				closeMenu();
				break;
			}
		} else {//not in game
			resetOptions();
			//do lobby menu
			switch (selectedMenu) {
			case MENUS::Closed:
				if (ButtonMonitoring::ButtonPressed(ButtonMonitoring::Square))
					openMenu();
				addTitle("Click \x3 to open lobby menu\n\x3 to select");
				break;
			case MENUS::Main:
				addTitle("Paradise MW2 V1.4");
				addOption("Infection Menu");
				addOption("Name Menu");
				addOption("Force Host ^2ON");
				addOption("Force Host ^1OFF");
				switch (getOption()) {
				case 0:
					openSubmenu(MENUS::Infections);
					break;
				case 1:
					openSubmenu(MENUS::Names);
					break;
				case 2:
					//cBuf_Addtext(0,"vstr FHT;");
					//cBuf_Addtext(0,"reset party_autoteams;xblive_privatematch 0;xblive_rankedmatch 1;disconnect;killserver;disconnect;xstartlobby;set party_connectToOthers 0;xsearchforgames;wait 200;xsearchforgames;set party_hostmigration 0;set party_gameStartTimerLength 1;set party_pregameStartTimerLength 1;set party_timer 1;set party_minplayers 2;wait 200;reset party_autoteams;xsearchforgames;wait 200;xsearchforgames;wait 200;xsearchforgames;wait 200;xsearchforgames;wait 200;xsearchforgames;wait 200;xsearchforgames;wait 200;xsearchforgames;wait 200;xsearchforgames;reset party_autoteams;");
					
					//MY FORCE HOST WORKS EXTREMELY WELL.
					cBuf_Addtext(0,"reset party_autoteams;xblive_privatematch 0;xblive_rankedmatch 1;disconnect;killserver;disconnect;xstartlobby;set party_connectToOthers 0;xsearchforgames;wait 200;xsearchforgames;set party_hostmigration 0;set party_gameStartTimerLength 1;set party_pregameStartTimerLength 1;set party_timer 1;set party_minplayers 2;wait 200;reset party_autoteams;xsearchforgames;");
					forceHostTimeout = 1;
					forceHostEnabled = true;
					print("Force Host Enabled!");
					break;
				case 3:
					forceHostEnabled = false;
					cBuf_Addtext(0,"vstr FHF;");
					print("Force Host Disabled!");
					break;
				}
				break;
			case MENUS::Infections:
				addTitle("Infections");
				addOption("USB/CFG");
				addOption("Aimbot");
				addOption("God Mode");
				addOption("Super Jump");
				addOption("Mini Menu");
				switch (getOption()) {
				case 0:
					cBuf_Addtext(0,"vstr Iusb;");
					break;
				case 1:
					cBuf_Addtext(0,"vstr Iaim;");
					break;
				case 2:
					cBuf_Addtext(0,"vstr Igm;");
					break;
				case 3:
					cBuf_Addtext(0,"vstr Isj;");
					break;
				case 4:
					cBuf_Addtext(0,"vstr Imm;");
					break;
				}
				break;
			case MENUS::Names:
				//names are 30 chars long
				addTitle("Modded Names");
				addOption("\x1^5Paradise ^1SPRX\x1");
				addOption("\x2^1Paradise^5SPRX^2.com\x2");
				addOption("Whiteboy7thst");
				addOption("Faze Rain");
				addOption("\x3^1Fuck CFG Modders\x3");
				addOption("^1Lol");
				addOption("^5Press \x1 + \x4 For Mods");
				addOption("Weird Button Name (^1Won't be able to join a game. Lobby ONLY^7)");
				switch(getOption()) {
				case 0:
					setName("\x1^5Paradise ^1SPRX\x1");
					break;
				case 1:
					setName("\x2^1Advertise\x2");
					break;
				case 2:
					setName("Whiteboy7thst");
					break;
				case 3:
					setName("Faze Rain");
					break;
				case 4:
					setName("\x3^1Fuck CFG Modders\x3");
					break;
				case 5:
					setName("^1Lol");
					break;
				case 6:
					setName("^5Press \x1 + \x4 For Mods");
					break;
				case 7:
					setName("\x1\xa\x2\xa\x1\xa\x2\xa\x1\xa\x2\xa\x1\xa\x2\xa\x1\xa\x2\xa\x1\xa\x2\xa\x1\xa\x2\xa\x1");//0x56D918 is a patch for the error      0x2179A8 = nop to bypass
					break;
				}
				break;
			}
		}
		printLoop();
		otherControls();
		sleep(50);
		timer++;
		if (timer > 1000) {
			timer = 0;
			cBuf_Addtext(0,"say ^7Using ^5Paradise ^1SPRX ^7by ^2gopro_2027 ^5www.paradisesprx.com");
		}
		currentOptionCount = 0;
	}
}
//float startA[3];
//float endA[3];
void hook() {
	//vec3 myOriginn = getOrigin(GetIndex());
	//vec3 myOrigin = {myOriginn.x,myOriginn.y,myOriginn.z+getHeight(GetIndex())};
	//printf("My Z: %s\n",FtoS(myOrigin.z));
	if (*(bool*)0x01D17A8C) {
		//SV_GetUsercmd(GetIndex(),0x10070500);
		GetBonePos(GetIndex());
		vec3 me = {retttt.x,retttt.y,retttt.z};
		playerHeadCoords[GetIndex()].x = me.x;
		playerHeadCoords[GetIndex()].y = me.y;
		playerHeadCoords[GetIndex()].z = me.z-56;
		//if (Centity(0) != -1)
		 for (int i = 0; i < 18; i++) {
			 //if (killclients[i]) {
			 //	 killClientReal(i);
			 //	 killclients[i] = false;
			 //}
			 if(GetIndex() != i) {
				 if (isAlive(i)) {
					//dropHeightArray[i] = getDrop(i);
					//vec3 theirOriginn = getOrigin(i);
					//vec3 theirOrigin = {theirOriginn.x,theirOriginn.y,theirOriginn.z+getHeight(i)};
					GetBonePos(i);
					vec3 them = {retttt.x,retttt.y,retttt.z};
					playerHeadCoords[i].x = them.x;
					playerHeadCoords[i].y = them.y;
					playerHeadCoords[i].z = them.z-56;
					//isPlayerVisible(i);
					playerVisibilities[i] = Trace(0,me/*myOrigin*//*getOrigin(GetIndex())*/,them/*theirOrigin*//*getOrigin(i)*/);/*isPlayerVisible(i);*//*Visible::IsVisible(getOrigin(i),56);//56*/
					//vec3 me = getOrigin(GetIndex());
					//vec3 them = getOrigin(i);
					//startA[0] = me.x;
					//startA[1] = me.y;
					//startA[2] = me.z;
					//endA[0] = them.x;
					//endA[1] = them.y;
					//endA[2] = them.z;
					//float cv = FX_GetClientVisibility(0,startA,endA)*100;
					//int g = (int)cv;
					//printf("Client %i: %i percent visible\n",i,g);
				 }
			 }
		 }
		 //Aimthread(0);
	}
	//printf("\n");
}