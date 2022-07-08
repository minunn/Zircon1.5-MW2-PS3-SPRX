#ifndef __MENU_H__
#define __MENU_H__

#define __stored			1
#define __open				2
#define __locked			4
#define __unfrozencontrols	0x10

#define __royalblue			(hudelem_color_t(255, 0, 0, 255))
#define __lowalphaRB		(hudelem_color_t(255, 0, 0, 55))
#define __white				(hudelem_color_t(255, 255, 255, 255))

#define MAX_MENUS			25
#define MAX_OPTIONS			25

extern const char* accessStrings[];
extern const char* accessLetters[];

#define INIT_INVALID_HANDLE  INVALID_HANDLE, INVALID_HANDLE, INVALID_HANDLE, INVALID_HANDLE,  INVALID_HANDLE, INVALID_HANDLE, INVALID_HANDLE, INVALID_HANDLE, INVALID_HANDLE, INVALID_HANDLE, INVALID_HANDLE, INVALID_HANDLE, INVALID_HANDLE, INVALID_HANDLE, INVALID_HANDLE, INVALID_HANDLE, INVALID_HANDLE, INVALID_HANDLE 

//Assault Rifles\nSub Machine Guns\nLight Machine Guns\nSniper Rifles\nShotguns\nLaunchers\nPistols
struct MenuInfo {
	game_hudelem_s*  Background, *Background2, *Scroll, *Sitem, *downBar, *EmblemSpawn, *EmblemSpawn2, *OpenMenu, *Title, *Title2, *Creator, *Subtitle, *Options, *Welcome[3], *By[3];
	int8_t flags;
	int elemMove;

	struct {
		int Main, Mods, Account, Fun, Message, Forge,
			Weapons, Visions, Infection, Teleport, Projectile, Aimbot, camo, Maps, Afghan, Derail, Estate, Favela, Highrise, Invasion, Karachi, Quarry, Rundown, Scrapyard, Skidrow, Subbase, Terminal, Underpass,
			Admin, Bots, Host, Lobby,
			AllPlayers, Players, Client, Client2, Fog;
		int Assault, SMG, LMG, Snipers, Shotguns, Launchers, Pistols;
	} ID;
};

#define __customloc			0x1000
#define __mortar			0x2000
#define __customclient		0x4000
#define __allenemies		0x8000
#define __allallies			0x10000

#define __up				1
#define __down				2
#define __left				4
#define __right				0x10
#define __cross				0x20
#define __square			0x40
#define __melee				0x80
#define __smoke				0x100
#define __frag				0x400
#define __weapnext			0x1000
#define __stance			0x2000

#define __verified			1

enum MenuAccess {
	None, VIP, Admin, CoHost, Host
};

enum resetType {
	RoundReset,
	Death,
	Full,
	DefaultInits,
	GAME_ENDED,
};

enum {
	OffScreen,
	OnScreen,
};

struct ClientInfo {
	int16_t buttons;
	int8_t flags;
	MenuAccess Access;
	int ClientList[MAX_PLAYERS];

	int8_t FOV;
	vec3 origin;
	int8_t respawnAtSaved;
	int16_t forgeButtons;
	int8_t noclipBind;

	handle_t menuHandle, keyboardHandle;
	char* weaponProjectile;
	hudelem_color_t textColor, textGlow, titleGlow;

	int8_t aimbot, expBullets, aimbotnohead, AimbotWTF, AimbotWTF2, AimbotWTF3, checkMidair, checkSniper,
		checkADS, disableWallbangs, thirdPerson, knockBack, attachToGrenades, attachToMissiles,
		saveLoadBind, UAV, teleportGun, previousWeapon, allPerks;
	int16_t killcamTimer, ebRange, azzaTeam;

	int8_t FastLast, FFA29;
};

void Reset(int clientNum, resetType type);
void resetMenuVariables(int clientNum);
void buildMenu(int clientNum);
void destroy(int clientNum);
void disableMenuAll();
void disableMenu(int clientNum, bool tellThem = false);

void close(int clientNum);
void open(int clientNum);
void enableMenu(int clientNum, MenuAccess Access, bool tellThem = false);
void monitor(int clientNum, handle_t* handle, handleCall_t type);
void monitorActions(int clientNum, char* button, char* dpadNum, bool reset);

extern ClientInfo		Client[MAX_PLAYERS];
extern MenuInfo			Menu[MAX_PLAYERS];
extern int SelectedClient[MAX_PLAYERS];
extern int ScrollIndex[MAX_PLAYERS][MAX_MENUS];
extern dvar_s* ui_mapname;
extern dvar_s* ui_gametype;
extern dvar_s* cl_ingame;
extern dvar_s* testClients_doAttack;
extern dvar_s* testClients_doMove;
extern dvar_s* testClients_doReload;
extern dvar_s* testClients_doCrouch;
extern dvar_s* testClients_watchKillcams;

#endif /* __MENU_H__*/