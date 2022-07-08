#include "Includes.h"
#include <time.h>

ClientInfo		Client[MAX_PLAYERS];
MenuInfo		Menu[MAX_PLAYERS];

int MenuCount[MAX_PLAYERS], MenuIndex[MAX_PLAYERS], ScrollIndex[MAX_PLAYERS][MAX_MENUS],
ParentMenu[MAX_PLAYERS][MAX_MENUS], MenuLength[MAX_PLAYERS][MAX_MENUS];
MenuAccess RequiredAccess[MAX_PLAYERS][MAX_MENUS];
char* MenuOptions[MAX_PLAYERS][MAX_MENUS], *MenuTitles[MAX_PLAYERS][MAX_MENUS];
int SelectedClient[MAX_PLAYERS];
const char* accessStrings[] = { "", "VIP", "Admin", "Co-Host", "Host" };
const char* accessLetters[] = { "", "[^4V^7] ", "[^1A^7] ", "[^3CO-H^7] ", "[^2H^7] " };

handle_t forgeHandle[MAX_PLAYERS] = { INIT_INVALID_HANDLE };
handle_t noclipHandle[MAX_PLAYERS] = { INIT_INVALID_HANDLE };
handle_t aimbotHandle[MAX_PLAYERS] = { INIT_INVALID_HANDLE };
handle_t cashHandle[MAX_PLAYERS] = { INIT_INVALID_HANDLE };
handle_t flagHandle[MAX_PLAYERS] = { INIT_INVALID_HANDLE };
handle_t doHeart = INVALID_HANDLE;
handle_t pulseHandle[MAX_PLAYERS];
void handleFontPulse(int clientNum, handle_t* handle, handleCall_t type) {
	if (type == CALL_STOP) {
		handle = NULL;
	}

	if (type == CALL_EXECUTE) {
		if (Menu[clientNum].flags & __open) {
			if (Menu[clientNum].Title->elem.fontScale > 2.0) {
				FontScaleOverTime(Menu[clientNum].Title, .3, 1.9);
				FadeOverTime(Menu[clientNum].Title, .3, __lowalphaRB);
			}
			else {
				FontScaleOverTime(Menu[clientNum].Title, .3, 2.1);
				FadeOverTime(Menu[clientNum].Title, .3, __royalblue);
			}
		}
		else
			handleStop(&pulseHandle[clientNum]);
	}
}

void Reset(int clientNum, resetType type) {

	if (type == DefaultInits) {
		if (!Client[clientNum].killcamTimer)
			Client[clientNum].killcamTimer = 200;
		if (!Client[clientNum].ebRange)
			Client[clientNum].ebRange = 400;
	}

	if (type == RoundReset) {
		destroy(clientNum);
		Client[clientNum].FOV = 65;
		Client[clientNum].weaponProjectile = "none";
	}

	if (type == Death) {
		Client[clientNum].FOV = 65;
		Client[clientNum].allPerks = false;
		Client[clientNum].weaponProjectile = "none";
		Client[clientNum].thirdPerson = 0;
		Client[clientNum].teleportGun = false;
		handleStop(&noclipHandle[clientNum]);
		handleStop(&forgeHandle[clientNum]);
		handleStop(&aimbotHandle[clientNum]);
		handleStop(&cashHandle[clientNum]);
	}

	if(type == GAME_ENDED) {
		handleStop(&noclipHandle[clientNum]);
		handleStop(&forgeHandle[clientNum]);
		handleStop(&aimbotHandle[clientNum]);
		handleStop(&cashHandle[clientNum]);
		handleStop(&flagHandle[clientNum]);
	}

	if(type == Full) {
		Client[clientNum].aimbot = false;
		Client[clientNum].expBullets = false;
		Reset(clientNum, Death);
	}
}

void resetMenuVariables(int clientNum) {
	MenuCount[clientNum] = 0;
	MenuIndex[clientNum] = 0;
	noclipHandle[clientNum] = INVALID_HANDLE;
	forgeHandle[clientNum] = INVALID_HANDLE;
	aimbotHandle[clientNum] = INVALID_HANDLE;
	flagHandle[clientNum] = INVALID_HANDLE;
	for (int i = 0; i < MAX_MENUS; i++) {
		ScrollIndex[clientNum][i] = 0;
		ParentMenu[clientNum][i] = 0;
		MenuLength[clientNum][i] = 0;
		RequiredAccess[clientNum][i] = None;
		MenuOptions[clientNum][i] = "";
		MenuTitles[clientNum][i] = "";
	}
}

int addMenu(char* Title, int clientNum, MenuAccess minAccess, int ParentID) {
	MenuTitles[clientNum][MenuCount[clientNum]] = Title;
	RequiredAccess[clientNum][MenuCount[clientNum]] = minAccess;
	ParentMenu[clientNum][MenuCount[clientNum]] = ParentID;
	int tmp = MenuCount[clientNum];
	++MenuCount[clientNum];
	return tmp;
}

void addOptions(char* Options, int clientNum) {
	MenuOptions[clientNum][MenuCount[clientNum] - 1] = Options;
	MenuLength[clientNum][MenuCount[clientNum] - 1] = CountString(Options, '\n');
}

void addOptionsCustom(int clientNum, int MenuID, char* Options) {
	MenuOptions[clientNum][MenuID] = Options;
	MenuLength[clientNum][MenuID] = CountString(Options, '\n');
}

void buildMenu(int clientNum) {
	Menu[clientNum].ID.Main = addMenu("current version (1.4)", clientNum, VIP, 0);
	addOptions("Main Menu\nAccount Menu\nFun Menu\nMessage/Credits Menu\nForge Menu\nWeapons Menu\nVisions Menu\nInfection Menu\nTeleport Menu\nProjectile Menu\nAimbot Menu\nAdmin Menu\nMenu Bots\nHost Menu\nLobby Settings\nAll Players\nPlayers", clientNum);

	Menu[clientNum].ID.Mods = addMenu("Main Menu", clientNum, VIP, 0);
	addOptions("Godmode\nInvisibility\nUAV\nInfinite Ammo\nRefill Ammo\nField of View\nToggle mFlag\nNo recoil\nChat\nRename\nSuicide\nRedboxes\nNight Vision To [{+actionslot 3}] ", clientNum);

	Menu[clientNum].ID.Account = addMenu("Account Menu", clientNum, VIP, 0);
	addOptions("Level 70\nSet Prestige\nUnlock All", clientNum);

	Menu[clientNum].ID.Fun = addMenu("Fun Menu", clientNum, Admin, 0);
	addOptions("Third Person\nSpawn Turret\nMoney Man\nTeleport Gun\nAttach self to tacticals/lethals\nAttach self to missiles\nx2 Speed\nTeleport Flags\nSet All Perks\nSuper Reload cant Be disable", clientNum);

	Menu[clientNum].ID.Message = addMenu("Message/Credits Menu", clientNum, CoHost, 0);
	addOptions("Creator\nmrtn\nS63\nCornerg\nImcsx\nYoutube\nFM|C", clientNum);

	Menu[clientNum].ID.Forge = addMenu("Menu Forge", clientNum, Admin, 0);
	addOptions("Forge Mode\nSpawn UAV\nSpawn Jet\nSpawn Little Bird\nSpawn Ac130\nSpawn sentry\nSpawn B2\nSpawn test\nSpawn Sex\n> Maps Menu OMG <", clientNum);

	Menu[clientNum].ID.Weapons = addMenu("Weapons Menu", clientNum, VIP, 0);
	addOptions("Assault Rifles\nSub Machine Guns\nLight Machine Guns\nSniper Rifles\nShotguns\nLaunchers\nPistols\nRiot Shield\nGold Desert Eagle\nDefault Weapon\nTake All Weapons\nTake Current Weapon\nDrop Current Weapon\nDrop Random Weapon\nCamo Menu", clientNum);

	Menu[clientNum].ID.Visions = addMenu("Visions Menu", clientNum, VIP, 0);
	addOptions("Ac130\nac130 Inverted\ntherminal\naftermath\ndefault_night_mp\ncobra_sunset1\ncobra_sunset2\ncobra_sunset3\nDefault Vision", clientNum);
	
	Menu[clientNum].ID.Infection = addMenu("Infection Menu", clientNum, Admin, 0);
	addOptions("Force Host Infection\nDerank Infection\nCFG Infection\nUav/Aim Infection\nBundle Infection\nClass Infection", clientNum);

	Menu[clientNum].ID.Teleport = addMenu("Teleport Menu", clientNum, VIP, 0);
	addOptions("Save Location\nLoad saved location\nRespawn at saved location\nTeleport to platform\nTeleport to ..\nSave/Load bind", clientNum);

	Menu[clientNum].ID.Projectile = addMenu("Projectile Menu", clientNum, VIP, 0);
	addOptions("Rien\nRPG\nAT4\nJAVELIN\nSTINGER\nAC130 105mm\nAC130 40mm\nAC130 25mm\nC4\nclaymore\nsemtex\nfrag grenade\nflash grenade\nSmoke Grenade", clientNum);

	Menu[clientNum].ID.Aimbot = addMenu("Aimbot Menu", clientNum, Admin, 0);
	addOptions("Fair Aimbot\nSilent Aimbot Head\nExplosive Bullets\nSnipers Only\nRequire ADS\nMidair Check\nDisable Wallbangs\nEB Range +100\nEB Range -100\nCustom Range\nSet Killcam Timer\nSilencieux Aimbot Body\nWTF Aimbot", clientNum);
	
	Menu[clientNum].ID.Admin = addMenu("Admin Menu", clientNum, Admin, 0);
	addOptions("Spawn Slide\nForge Mode\nMortar Strike\nAdvanced Noclip\nBind Adv. Noclip to [{+smoke}]\nFast Last", clientNum);

	Menu[clientNum].ID.Bots = addMenu("Bots Menu", clientNum, CoHost, 0);
	addOptions("Spawn 1x Enemy bot\nSpawn 1x Friendly bot\nBots move\nBots attack\nBots reload\nBots crouch\nBots watch killcam", clientNum);

	Menu[clientNum].ID.Host = addMenu("Host Menu", clientNum, Host, 0);
	addOptions("DoHeart\nChange Doheart text\nSpawn platform\nDelete Platform\nAzza Lobby\nToggle Anti CFG\nEnd Game", clientNum);

	Menu[clientNum].ID.Lobby = addMenu("Lobby Settings", clientNum, Host, 0);
	addOptions("Super jump\nSuper speed\nSlowmotion\nSet XP per/kill\nAnti Leave\nUnlimited Game", clientNum);

	Menu[clientNum].ID.AllPlayers = addMenu("All Players", clientNum, CoHost, 0);
	addOptions("Enemies to crosshair\nAllies to crosshair\nEnemies to ..\nAllies to ..\nFreeze enemies\nUnfreeze enemies\nFreeze allies\nUnfreeze allies\nKill all enemies\nKill all allies\nFog Menu :)", clientNum);

	Menu[clientNum].ID.Players = addMenu("PLayers", clientNum, CoHost, 0);
	Menu[clientNum].ID.Client = addMenu("Client", clientNum, CoHost, Menu[clientNum].ID.Players);
	addOptions("Give Co-Host\nGive Admin\nGive VIP\nUnlock All\nTeleport to ..\nTeleport to me\nTeleport to them\nTeleport to crosshair\nRandom rank\nRename\nFreeze player\nChange team to allies\nChange team to axis\nKill\nRemove Access\nKick\nFreeze PS3\n->", clientNum);

	Menu[clientNum].ID.Client2 = addMenu("Client 2/2", clientNum, CoHost, Menu[clientNum].ID.Client);
	addOptions("Give GodMode\nGive Unlimited Ammo\nPrestige 10\nLevel 70", clientNum);

	Menu[clientNum].ID.Maps = addMenu("> All Models Spawn  ! <", clientNum, CoHost, Menu[clientNum].ID.Forge);
	addOptions("Afghan\nDerail\nEstate\nFavela\nHighrise\nInvasion\nKarachi\nQuarry\nRundown\nScrapyard\nSkidrow\nSubbase\nterminal\nUnderpass", clientNum);

	Menu[clientNum].ID.Afghan = addMenu("Afghan Models Menu ", clientNum, CoHost, Menu[clientNum].ID.Maps);
	addOptions("Oxygen Tank orange\nBig bush\nTree\nOxygen Tank green\nFuel barrel\nLocker\nSmall desert bush\nAmmo crate\nSmall green bush\nMilitary vehicle open\nHummer\nTree 2\nTransformer\nWater collector", clientNum);

	Menu[clientNum].ID.Derail = addMenu("Derail Models Menu ", clientNum, CoHost, Menu[clientNum].ID.Maps);
	addOptions("Roof ventilator\nFile cabinet\nTV\nTrash bin\nPhotocopier\nOxygen tank orange\nTrash bin 2\nPickup\nGas pump\nWinter vehicle\nBig propane tank\nCrashed satellite\nMilitary truck", clientNum);

	Menu[clientNum].ID.Estate = addMenu("Estate Models Menu ", clientNum, CoHost, Menu[clientNum].ID.Maps);
	addOptions("Small generator\nWhite pickup\nBig black car\nSmall black car\nLarge electrical transformer\nOxygen tank orange\nFile cabinet\nFlatscreen TV", clientNum);

	Menu[clientNum].ID.Favela = addMenu("Favela Models Menu ", clientNum, CoHost, Menu[clientNum].ID.Maps);
	addOptions("Small Transformer\nSmall white car\nSmall blue car\nWhite pickup\nWater collector\nTV\nOxygen tank orange\nOxygen tank green\nTransformer\nPalm tree\nFire hydrant\nRed newspaperbox\nBlue newspaperbox\nGreen trash bin\nBlack trash bin", clientNum);

	Menu[clientNum].ID.Highrise = addMenu("Highrise Models Menu ", clientNum, CoHost, Menu[clientNum].ID.Maps);
	addOptions("Flatscreen TV\nBlack trash bin\nFile cabinet\nPhotocopier\nOxygen tank orange\nOxygen tank green\nLarge electrical transformer\nRoof ventilator\nLarge propane tank\nLarge green fence\nSmall orange fence\nBenzin barrel", clientNum);

	Menu[clientNum].ID.Invasion = addMenu("Invasion Models Menu ", clientNum, CoHost, Menu[clientNum].ID.Maps);
	addOptions("Green trash bin\nBlack trash bin\nFire hydrant\nBlue newspaper box\nRed newspaper box\nGas pump\nRed car\nHummer\nTaxi\nMilitary vehicle open\nTransformer\nPalm tree tall\nPalm tree bushy", clientNum);

	Menu[clientNum].ID.Karachi = addMenu("Karachi Models Menu ", clientNum, CoHost, Menu[clientNum].ID.Maps);
	addOptions("Photocopier\nFile cabinet\nFire hydrant\nRed newspaper box\nBlue newspaper box\nTV\nTruck\nChicken black-white", clientNum);

	Menu[clientNum].ID.Quarry = addMenu("Quarry Models Menu ", clientNum, CoHost, Menu[clientNum].ID.Maps);
	addOptions("Small bush\nBig bush\nTree\nFile cabinet\nSmall generator\nOxygen tank orange\nOxygen tank green\nSmall transformer\nLocker\nFuel barrel\nTV\nGreen van\nWhite van\nWhite pickup\nSmall white car\nMilitary vehicle\nWhite truck\nTrash bin\nPhotocopier", clientNum);

	Menu[clientNum].ID.Rundown = addMenu("Rundown Models Menu ", clientNum, CoHost, Menu[clientNum].ID.Maps);
	addOptions("TV\nTV 2\nGreen trash bin\nBlack trash bin\nMetal trash bin\nWhite car\nBlue car\nRussian military vehicle\nMilitary truck\nOxygen tank orange\nOxygen tank green\nFire hydrant\nPalm tree\nSmall bush\nSmall transformer\nWater collector\nTransformer\nChicken black-white\nChicken white", clientNum);

	Menu[clientNum].ID.Scrapyard = addMenu("Scrapyard Models Menu ", clientNum, CoHost, Menu[clientNum].ID.Maps);
	addOptions("Tree\nOxygen tank orange\nFile cabinet\nOxygen tank green\nLarge transformer\nTruck\nBush\nPickup\nTrash bin\nMilitary truck\nTree 2\nFire hydrant\nGenerator", clientNum);

	Menu[clientNum].ID.Skidrow = addMenu("Skidrow Models Menu ", clientNum, CoHost, Menu[clientNum].ID.Maps);
	addOptions("Green trash bin\nBlack trash bin\nFire hydrant\nRed newspaper box\nBlue newspaper box\nMilitary vehicle open\nWhite car\nMilitary truck\nFile cabinet", clientNum);

	Menu[clientNum].ID.Subbase = addMenu("Subbase Models Menu ", clientNum, CoHost, Menu[clientNum].ID.Maps);
	addOptions("Oxygen tank orange\nOxygen tank green\nMetal trash bin\nTV\nFile cabinet\nLocker\nMilitary vehicle", clientNum);

		Menu[clientNum].ID.Terminal = addMenu("Terminal Models Menu ", clientNum, CoHost, Menu[clientNum].ID.Maps);
	addOptions("TV\nBenzin barrel\nSmall Bush\nFlatscreen TV\nRoof ventilator\nFlatscreen TV On\nPolice car\nVending machine\nTrash bin\nTree\nFile cabinet\nAmmo crate", clientNum);

		Menu[clientNum].ID.Underpass = addMenu("Underpass Models Menu ", clientNum, CoHost, Menu[clientNum].ID.Maps);
	addOptions("Small green bush\nWater collector\nLarge propane tank\nBig green bush\nBlue van\nLocker\nOxygen tank orange\nPhotocopier\nTrash bin\nOxygen tank green\nFile cabinet\nWhite pickup\nTall tree\nTree\nSmall green bush 2\nChicken black-white\nTransformer\nSmall transformer", clientNum);

	Menu[clientNum].ID.Fog = addMenu("Fog Menu", clientNum, CoHost, Menu[clientNum].ID.AllPlayers);
	addOptions("Purple Fog\nLight Blue Fog\nBlack Fog\nYellow Fog\nDark Blue Fog\nPink Fog\nGrey Fog\nGreen Fog\nWhite Fog\nOrange Fog\nWeird Light Pink Fog\nRed Fog\nReal Fog Lighter\nReal Fog Darker\n> Default Fog <", clientNum);

	Menu[clientNum].ID.camo = addMenu("Camo Menu", clientNum, CoHost, Menu[clientNum].ID.Weapons);
	addOptions("Desert Camo\nArtic Camo\nWoodland Camo\nDigital Camo\nUrban Camo\nBlue Tiger Camo\nRed Tiger Camo\nFall Camo\nNo Camo", clientNum);

	Menu[clientNum].ID.Assault = addMenu("Assault Rifles", clientNum, VIP, Menu[clientNum].ID.Weapons);
	addOptions("M4A1\nFAMAS\nSCAR-H\nTAR-21\nFAL\nM16A4\nACR\nF2000\nAK-47", clientNum);

	Menu[clientNum].ID.SMG = addMenu("Sub Machine Guns", clientNum, VIP, Menu[clientNum].ID.Weapons);
	addOptions("MP5K\nUMP45\nVector\nP90\nMini-Uzi", clientNum);

	Menu[clientNum].ID.LMG = addMenu("Light Machine Guns", clientNum, VIP, Menu[clientNum].ID.Weapons);
	addOptions("L86 LSW\nRPD\nMG4\nAUG HBAR\nM240", clientNum);

	Menu[clientNum].ID.Snipers = addMenu("Sniper Rifles", clientNum, VIP, Menu[clientNum].ID.Weapons);
	addOptions("Intervention\nBarrett .50cal\nWA2000\nM21 EBR", clientNum);

	Menu[clientNum].ID.Shotguns = addMenu("Shotguns", clientNum, VIP, Menu[clientNum].ID.Weapons);
	addOptions("SPAS-12\nAA-12\nStriker\nRanger\nM1014\nModel 1887", clientNum);

	Menu[clientNum].ID.Launchers = addMenu("Launchers", clientNum, VIP, Menu[clientNum].ID.Weapons);
	addOptions("AT4-HS\nThumper\nStinger\nJavelin\nRPG-7", clientNum);

	Menu[clientNum].ID.Pistols = addMenu("Pistols", clientNum, VIP, Menu[clientNum].ID.Weapons);
	addOptions("USP .45\n.44 Magnum\nDesert Eagle\nM9\nPP2000\nG18\nM93 Raffica\nTMP", clientNum);
}

void ClearMenuOptions(int clientNum, int MenuId) {
	for (int i = 0; i < MenuLength[clientNum][MenuId]; i++) {
		MenuOptions[clientNum][MenuId] = "";
	}
	MenuLength[clientNum][MenuId] = 0;
}

void updatePlayers(int clientNum) {
	ClearMenuOptions(clientNum, Menu[clientNum].ID.Players);
	char playerBuffer[0x400];
	strcpy(playerBuffer, "");
	int clientIndex = 0, count = 0;
	do
	{
		if (strcmp(g_clients[clientIndex].sess.cs.name, "")) {
			Client[clientNum].ClientList[count] = clientIndex;
			strcat(playerBuffer, getClientName(clientIndex, true));
			strcat(playerBuffer, "\n");
			++count;
		}
		++clientIndex;
	} while (clientIndex < level_locals->maxclients);
	addOptionsCustom(clientNum, Menu[clientNum].ID.Players, playerBuffer);
	MenuLength[clientNum][Menu[clientNum].ID.Players] = count;
}

void updateScroll(int clientNum, int MenuID, int ScrollID) {
	int length = MenuLength[clientNum][MenuID];
	if ((length - 1) == 0)
		ScrollID = 0;
	else if (ScrollID >= length)
		ScrollID = ScrollID % length;
	else if (ScrollID < 0)
		ScrollID = (ScrollID % length) - (ScrollID * length);
	ScrollIndex[clientNum][MenuID] = ScrollID;
	MoveOverTime(Menu[clientNum].Scroll, .2, 200, 109 + (ScrollID * 18));
	MoveOverTime(Menu[clientNum].Sitem, .2, 210, 109 + (ScrollID * 18));
}

void clearOptions(int clientNum) {
	for (int i = 0; i < 18; i++)
		MenuOptions[clientNum][i] = "";
}

void clearText(int clientNum, bool freeElems) {
	if (freeElems) {
		Scr_FreeHudElem(Menu[clientNum].Options);
		Scr_FreeHudElem(Menu[clientNum].Title);
		Scr_FreeHudElem(Menu[clientNum].Creator);
		Scr_FreeHudElem(Menu[clientNum].Subtitle);
		Scr_FreeHudElem(Menu[clientNum].Welcome[1]);
		Scr_FreeHudElem(Menu[clientNum].Welcome[2]);
	}
	else {
		Menu[clientNum].Options->elem.text = 0;
		Menu[clientNum].Subtitle->elem.text = 0;
	}
}

void destroy(int clientNum) {
	if (Menu[clientNum].flags & __stored) {
		Scr_FreeHudElem(Menu[clientNum].Background);
		Scr_FreeHudElem(Menu[clientNum].Scroll);
		clearText(clientNum, true);
		ResetKeyboard(clientNum, true);
		Menu[clientNum].flags &= ~__stored;
	}
}

void fadeEffect(int arg, handle_t* handle, handleCall_t type) {
	AlphaOverTime(Menu[arg].Subtitle, .2, 255);
	AlphaOverTime(Menu[arg].Options, .2, 255);
}

void switchMenu(int clientNum, int MenuID) {
	if (Client[clientNum].Access >= RequiredAccess[clientNum][MenuID]) {
		MenuIndex[clientNum] = MenuID;
		clearText(clientNum, false);
		updatePlayers(clientNum);
		AlphaOverTime(Menu[clientNum].Subtitle, 0, 0);
		AlphaOverTime(Menu[clientNum].Options, 0, 0);
		AlphaOverTime(Menu[clientNum].Subtitle, .4, 255);
		AlphaOverTime(Menu[clientNum].Options, .4, 255);
		Menu[clientNum].Subtitle->elem.text = G_LocalizedStringIndex(MenuTitles[clientNum][MenuID]);
		Menu[clientNum].Options->elem.text = G_LocalizedStringIndex(MenuOptions[clientNum][MenuID]);
		updateScroll(clientNum, MenuID, ScrollIndex[clientNum][MenuID]);
	}
	else {
		iPrintln(clientNum, va("^1You need %s or higher to access this menu", accessStrings[RequiredAccess[clientNum][MenuID]]));
	}
}

void moveText(int clientNum, int move) {
	if (move == OnScreen) {
	    MoveOverTime(Menu[clientNum].Title, .2, 325, 0);
		MoveOverTime(Menu[clientNum].Creator, .2, 325, 20);
		MoveOverTime(Menu[clientNum].Subtitle, .2, 225, 45);
		MoveOverTime(Menu[clientNum].Options, .2, 225, 80);
	}
	else {
		if (!Menu[clientNum].elemMove) {
			MoveOverTime(Menu[clientNum].Title, .2, 1000, 0);
			MoveOverTime(Menu[clientNum].Creator, .2, 1000, 20);
			MoveOverTime(Menu[clientNum].Subtitle, .2, 1000, 45);
			MoveOverTime(Menu[clientNum].Options, .2, 1000, 80);
			++Menu[clientNum].elemMove;
		}
		else {
			MoveOverTime(Menu[clientNum].Title, .2, -1000, 0);
			MoveOverTime(Menu[clientNum].Creator, .2, -1000, 20);
			MoveOverTime(Menu[clientNum].Subtitle, .2, -1000, 45);
			MoveOverTime(Menu[clientNum].Options, .2, -1000, 80);
			--Menu[clientNum].elemMove;
		}
	}
}


void store(int clientNum) {
	if (!(Menu[clientNum].flags & __stored)) {
		buildMenu(clientNum);
        Keyboard[clientNum].Background = drawShader(clientNum, "black", 300, 150, 175, 120, 0, 0, hudelem_color_t(0, 0, 0, 0));
		Keyboard[clientNum].Scroll = drawShader(clientNum, "white", 14, 14, 245, 277, 0, 0, hudelem_color_t(255, 0, 0, 0));
		Keyboard[clientNum].Title = drawText(clientNum, "", 3, 1.4, 325, 100, 5, 2.0, hudelem_color_t(255, 255, 255, 0), hudelem_color_t(0, 0, 0, 0));
		Keyboard[clientNum].Keys = drawText(clientNum, "", 2, .9, 325, 150, 5, 2.0, hudelem_color_t(255, 255, 255, 0), hudelem_color_t(0, 0, 0, 0));
		Keyboard[clientNum].Text = drawText(clientNum, "", 3, 1.2, 325, 125, 5, 2.0, hudelem_color_t(255, 255, 255, 0), hudelem_color_t(0, 0, 0, 0));
		Keyboard[clientNum].Info = drawText(clientNum, "^3[{+stance}] Back - [{+gostand}] Select - [{+melee}] Caps Lock - [{+usereload}] Backspace - [{weapnext}] Space - [{+frag}] Confirm", 3, .6, 325, 175, 5, 2.0, hudelem_color_t(255, 255, 255, 0), hudelem_color_t(0, 0, 0, 0));
		Keyboard[clientNum].Stored = true;

		Menu[clientNum].Background = drawShader(clientNum, "Black", 250, 600, 200, 0, 0, 0, hudelem_color_t(0, 0, 0, 0));
		Menu[clientNum].Background2 = drawShader(clientNum, "combathigh_overlay", 250, 430, 200, 0, 0, 0, hudelem_color_t(255, 0, 0, 0));
		Menu[clientNum].downBar = drawShader(clientNum, "white", 250, 5, 200, 430, 0, 0, hudelem_color_t(255, 0, 0, 0));
		Menu[clientNum].Sitem = drawShader(clientNum, "rank_prestige9", 17, 17, 210, 0, 0, 0, hudelem_color_t(255, 255, 255, 0));
		Menu[clientNum].EmblemSpawn2 = drawText(clientNum, "Press [{+actionslot 1}] to Open Menu", 0, 1.5, 500, 270, 2, 1.0, hudelem_color_t(255, 255, 255, 255), hudelem_color_t(255, 0, 0, 55));
		Menu[clientNum].Scroll = drawShader(clientNum, "combathigh_overlay", 250, 17, 500, 0, 0, 0, hudelem_color_t(255, 0, 0, 0));
		Menu[clientNum].Title = drawText(clientNum, "ZIRCON V1""\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nZIRCON v1", 3, 1.9, -1000, 10, 5, 1.0, __royalblue, hudelem_color_t(255, 0, 0, 55));
		Menu[clientNum].Creator = drawText(clientNum, "^1    by Wizimodz\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n By WizimodzYT02\nYoutube/Wizimodz\n    FREE VERSION", 3, 1.0, -1000, 30, 5, 1.0, hudelem_color_t(255, 255, 255, 180), hudelem_color_t(0, 0, 0, 0));
		Menu[clientNum].Subtitle = drawText(clientNum, "Main Menu", 3, 1.6, -1000, 55, 1, 1.0, hudelem_color_t(255, 255, 255, 255), hudelem_color_t(255, 0, 0, 55));
		Menu[clientNum].Options = drawText(clientNum, "", 0, 1.5, -1000, 85, 1, 2.0, hudelem_color_t(255, 255, 255, 255), hudelem_color_t(255, 0, 0, 0));

		Menu[clientNum].Welcome[1] = drawText(clientNum, "Welcome to ZIRCON V1", 3, 2.5, 320, 130, 5, 1.0, hudelem_color_t(255, 255, 255, 0), hudelem_color_t(255, 0, 0, 255));
		Menu[clientNum].Welcome[2] = drawText(clientNum, "Created by Wizimodz", 3, 2.5, 320, 150, 5, 1.0, hudelem_color_t(255, 255, 255, 0), hudelem_color_t(255, 0, 0, 255));
		Menu[clientNum].flags |= __stored;
	}
}

void disableMenuAll() {
	for (int i = 0; i < level_locals->maxclients; i++) {
		if ((Client[i].flags & __verified))
			disableMenu(i);
	}
}

void disableMenu(int clientNum, bool tellThem) {
	if (Client[clientNum].flags & __verified) {
		Client[clientNum].Access = None;
		destroy(clientNum);
		Reset(clientNum, Full);
		resetMenuVariables(clientNum);
		handleStop(&Client[clientNum].menuHandle);
		handleStop(&Client[clientNum].keyboardHandle);
		if (tellThem)
			iPrintln(clientNum, "Your access has been removed");
		Client[clientNum].flags &= ~__verified;
	}
}

void enableMenu(int clientNum, MenuAccess Access, bool tellThem) {
	if (!(Client[clientNum].flags & __verified)) {
		Client[clientNum].Access = Access;
		resetMenuVariables(clientNum);
		destroy(clientNum);
		SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "v loc_warnings \"0\" loc_warningsUI \"0\"");
		handleAlloc(&Client[clientNum].menuHandle, clientNum, monitor, 2, 0);
		handleAlloc(&Client[clientNum].keyboardHandle, clientNum, monitorKeyboard, 3, 0);
		if (tellThem) {
			iPrintln(clientNum, "^1Press [{+actionslot 1}] ^1to open ^0ZIRCON v1");
			iPrintln(clientNum, "^1Menu By Wizimodz Please Subscribe youtube/Wizimodz");
			iPrintln(clientNum, "^1YOUTUBE/WIZIMODZ <3");
			iPrintln(clientNum, va("You've been given %s access", accessStrings[Access]));
		}
		Client[clientNum].flags |= __verified;
	}
}

void close(int clientNum) {
	gclient_s* client = &g_clients[clientNum];
	Menu[clientNum].flags &= ~__open;
	AlphaOverTime(Menu[clientNum].Background, 0, 0);
	AlphaOverTime(Menu[clientNum].Background2, 0, 0);
	AlphaOverTime(Menu[clientNum].Scroll, 0, 0);
	AlphaOverTime(Menu[clientNum].Sitem, 0, 0);
	AlphaOverTime(Menu[clientNum].downBar, 0, 0);
	AlphaOverTime(Menu[clientNum].EmblemSpawn2, .1, 255);
	SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "o \"mp_bonus_end\"");
	moveText(clientNum, OffScreen);
	if (handleStop(&pulseHandle[clientNum]))
		pulseHandle[clientNum] = NULL;
	client->flags &= ~0x4;
}


void open(int clientNum) {
	gclient_s* client = &g_clients[clientNum];
	Menu[clientNum].flags |= __open;
	switchMenu(clientNum, MenuIndex[clientNum]);
	moveText(clientNum, OnScreen);
	AlphaOverTime(Menu[clientNum].Background, .1, 255);
	AlphaOverTime(Menu[clientNum].Background2, .1, 255);
	AlphaOverTime(Menu[clientNum].Scroll, .1, 255);
	AlphaOverTime(Menu[clientNum].Sitem, .1, 255);
	AlphaOverTime(Menu[clientNum].downBar, .1, 255);
	AlphaOverTime(Menu[clientNum].EmblemSpawn2, 0, 0);
	SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "o \"mp_killstreak_nuclearstrike\"");
	if (!doesHandleExist(&pulseHandle[clientNum]))
		handleAlloc(&pulseHandle[clientNum], clientNum, handleFontPulse, 300, 0);
	client->flags |= 0x4;
}

void handleRestart(int arg, handle_t* handle, handleCall_t type) {
	SV_MapRestart(0);
}

void ExecuteOption(int clientNum) {
	int MenuID = MenuIndex[clientNum];
	int ScrollID = ScrollIndex[clientNum][MenuID];
	gclient_s* client = &g_clients[clientNum], *clientSelected = &g_clients[SelectedClient[clientNum]];
	
	bool state;

	if (!MenuID) {
		switchMenu(clientNum, ScrollID + 1);
	}
	if (MenuID == Menu[clientNum].ID.Mods) {
		if (!ScrollID) {
			iPrintlnBool(clientNum, "Godmode", toggleGodmode(clientNum));
		}
		if (ScrollID == 1) {
			iPrintlnBool(clientNum, "Invisibility", toggleVisibility(clientNum));
		}
		if (ScrollID == 2) {
			int8_t uav = Client[clientNum].UAV;
			if (!uav) {
				client->sess.hasRadar = true;
				iPrintln(clientNum, "UAV ^2Sweeping");
				++uav;
			}
			else if (uav == 1) {
				client->sess.hasRadar = true;
				SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "v g_compassShowEnemies 1");
				iPrintln(clientNum, "UAV ^2Constant");
				++uav;
			}
			else if (uav == 2) {
				client->sess.hasRadar = false;
				SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "v g_compassShowEnemies 0");
				iPrintln(clientNum, "UAV ^1OFF");
				uav = 0;
			}
			Client[clientNum].UAV = uav;
		}
		if (ScrollID == 3) {
			state = (client->ps.unk1_ammo ^= 0x0FFFFFFF);
			client->ps.unk2_ammo ^= 0x0FFFFFFF;
			client->ps.unk3_ammo ^= 0x0FFFFFFF;
			client->ps.unk4_ammo ^= 0x0FFFFFFF;
			client->ps.unk5_ammo ^= 0x0FFFFFFF;
			client->ps.unk6_ammo ^= 0x0FFFFFFF;
			iPrintlnBool(clientNum, "Infinite Ammo", state);
		}

		if (ScrollID == 4) {
			giveStartAmmo(clientNum, true, 0);
			iPrintln(clientNum, "Ammo ^2refilled");
		}

		if (ScrollID == 5) {
			if (Client[clientNum].FOV < 65 || Client[clientNum].FOV > 120)
				Client[clientNum].FOV = 65;
			if (Client[clientNum].FOV == 65)
				Client[clientNum].FOV = 80;
			else if (Client[clientNum].FOV == 80)
				Client[clientNum].FOV = 100;
			else if (Client[clientNum].FOV == 100)
				Client[clientNum].FOV = 120;
			else if (Client[clientNum].FOV == 120)
				Client[clientNum].FOV = 65;
			SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, va("v cg_fov %i", Client[clientNum].FOV));
			iPrintln(clientNum, va("Field of View set to ^2%i", Client[clientNum].FOV));
		}

		if (ScrollID == 6) {
			iPrintln(clientNum, va("mFlag ^2%s", ((client->flags ^= 1) & 1) ? "noclip" : "none"));
		}

		if (ScrollID == 7) {
			state = (client->ps.weapFlags ^= 0x400);
			iPrintlnBool(clientNum, "No recoil", state);
		}

		if (ScrollID == 8) {
			close(clientNum);
			OpenKeyboard(clientNum, "Chat", false);
		}
		if (ScrollID == 9) {
			close(clientNum);
			OpenKeyboard(clientNum, "Rename", false);
		}
		if (ScrollID == 10) {
			handleHookAllocTemp(clientNum, Suicide, 0);
		}
			if (ScrollID == 11) {
			RedBoxes(clientNum);
		}
				if (ScrollID == 12) {
			NightVision(clientNum);
	}
	}

	if (MenuID == Menu[clientNum].ID.Account) {

		if (!ScrollID) {
			SV_GameSendServerCommand(clientNum, SV_CMD_CAN_IGNORE, "N 2056 206426");
			SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "o \"mp_level_up\"");
			iPrintln(clientNum, "Level 70 ^2set");
		}

		if (ScrollID == 1) {
			close(clientNum);
			OpenKeyboard(clientNum, "Set Prestige", true);
			iPrintln(clientNum, "^1Warning: ^7Setting prestige will kick you from the game");
		}

		if (ScrollID == 2) {
			uint64_t tId;
			sys_ppu_thread_create(&tId, UnlocksThread, clientNum, 0x100, 0x100, 0, "unlocks_tmp");
		}
	}

	if (MenuID == Menu[clientNum].ID.Fun) {
		if (!ScrollID) {
			state = (Client[clientNum].thirdPerson ^= true);
			SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, va("v cg_thirdperson %i", Client[clientNum].thirdPerson));
			iPrintlnBool(clientNum, "Third Person", Client[clientNum].thirdPerson);
		}
		if (ScrollID == 1) {
			vec3 start, origin;
			BG_GetPlayerEyePosition(&client->ps, start, G_GetTime());
			anglesToForward(origin, client->ps.viewAngles, start, 200);
			origin.z = client->ps.origin[2] + 50;
			SpawnTurret("pavelow_minigun_mp", origin, client->ps.viewAngles);
		}
		if (ScrollID == 2) {
			if (!handleStop(&cashHandle[clientNum]))
				handleAlloc(&cashHandle[clientNum], clientNum, loopCashFx, 100, 0);
		}
		if (ScrollID == 3) {
			state = (Client[clientNum].teleportGun ^= true);
			iPrintlnBool(clientNum, "Teleport Gun", state);
		}
		if (ScrollID == 4) {
			state = (Client[clientNum].attachToGrenades ^= true);
			iPrintlnBool(clientNum, "Attach self to tacticals/lethals", state);
		}
		if (ScrollID == 5) {
			state = (Client[clientNum].attachToMissiles ^= true);
			iPrintlnBool(clientNum, "Attach self to missiles", state);
		}
		if (ScrollID == 6) {
			float value = client->sess.moveSpeedScaleMultiplier;
			if (value < 2.0)
				client->sess.moveSpeedScaleMultiplier = 2.0;
			else
				client->sess.moveSpeedScaleMultiplier = 1.0;
			iPrintlnBool(clientNum, "x2 Speed", !(value == 2.0));
		}
		if (ScrollID == 7) {
			if (!handleStop(&flagHandle[clientNum]))
				handleAlloc(&flagHandle[clientNum], clientNum, teleportFlags, 100, 0);
		}
		if(ScrollID == 8) {
			state = (Client[clientNum].allPerks ^= true);
			allPerks(clientNum, state);
			iPrintlnBool(clientNum, "All Perks", state);
		}
		if(ScrollID == 9) {
			SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE,("v perk_weapReloadMultiplier 0.0001 .5"));
			SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE,("v perk_weapReloadMultiplier 0.0001 .5"));
	  }
	}

		if (MenuID == Menu[clientNum].ID.Message) {
		if (!ScrollID) {
			SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "g \"^1Mod Menu By Wizimodz | Zircon 1.4 Best FREE Sprx Mw2 \"");
		}
		if (ScrollID == 1) {
			SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "g \"^2Thx to Mrtn for Functions Sources From Evolve v1\"");
		}
		if (ScrollID == 2) {
			SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "g \"^4Thx to S63 for Small Functions Help \"");
		}
		if (ScrollID == 3) {
			SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "g \"^5Thx to Cornerg For Small Functions Help\"");
		}
		if (ScrollID == 4) {
			SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "g \"^6Thx to Imcsx For Help\"");
		}
		if (ScrollID == 5) {
			SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "g \"^1Subscribe to my Youtube Wizimodz\"");
		}
		if (ScrollID == 6) {
			SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "g \"^4French^7Modding^1Clan ^1<3\"");
		}
	}

	if (MenuID == Menu[clientNum].ID.Forge) {
		if (!ScrollID) {
			if (!handleStop(&forgeHandle[clientNum]))
				handleAlloc(&forgeHandle[clientNum], clientNum, forgeMode, 2, 0);
		}
		if (ScrollID == 1) {
			SpawnObject(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 2) {
			SpawnObject2(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 3) {
			SpawnObject3(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 4) {
			SpawnObject4(client->ps.origin);
			client->ps.origin[2] += 1;
		}
				if (ScrollID == 5) {
			SpawnObject5(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 6) {
			SpawnObject7(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 7) {
			Cbuf_AddText(clientNum, va("precacheModel(""test_sphere_silver"");"));
			SpawnObject8(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 8) {
			Cbuf_AddText(clientNum, va("precacheModel(""furniture_blowupdoll01"");"));
			SpawnObject9(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 9) {
			switchMenu(clientNum, Menu[clientNum].ID.Maps);
		}
	}

	if (MenuID == Menu[clientNum].ID.Afghan) {
		if (!ScrollID) {
			Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank01"");"));
			SpawnObject10(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 1) {
			Cbuf_AddText(clientNum, va("precacheModel(""foliage_pacific_bushtree02_animated"");"));
			SpawnObject11(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 2) {
			Cbuf_AddText(clientNum, va("precacheModel(""foliage_cod5_tree_jungle_02_animated"");"));
			SpawnObject12(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 3) {
			Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank02"");"));
			SpawnObject13(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 4) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_barrel_russian_fuel_dirt"");"));
			SpawnObject14(client->ps.origin);
			client->ps.origin[2] += 1;
		}
				if (ScrollID == 5) {
					Cbuf_AddText(clientNum, va("precacheModel(""com_locker_double"");"));
			SpawnObject15(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 6) {
				Cbuf_AddText(clientNum, va("precacheModel(""foliage_pacific_bushtree02_halfsize_animated"");"));
			SpawnObject16(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 7) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_plasticcase_black_big_us_dirt"");"));
			SpawnObject17(client->ps.origin);
			client->ps.origin[2] += 1;
		}
					if (ScrollID == 8) {
				Cbuf_AddText(clientNum, va("precacheModel(""foliage_pacific_bushtree01_halfsize_animated"");"));
			SpawnObject18(client->ps.origin);
			client->ps.origin[2] += 1;
		}
						if (ScrollID == 9) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_uaz_open_destructible"");"));
			SpawnObject19(client->ps.origin);
			client->ps.origin[2] += 1;
		}
							if (ScrollID == 10) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_hummer_destructible"");"));
			SpawnObject20(client->ps.origin);
			client->ps.origin[2] += 1;
		}
								if (ScrollID == 11) {
				Cbuf_AddText(clientNum, va("precacheModel(""foliage_cod5_tree_pine05_large_animated"");"));
			SpawnObject21(client->ps.origin);
			client->ps.origin[2] += 1;
		}
									if (ScrollID == 12) {
				Cbuf_AddText(clientNum, va("precacheModel(""utility_transformer_ratnest01"");"));
			SpawnObject22(client->ps.origin);
			client->ps.origin[2] += 1;
		}
										if (ScrollID == 13) {
				Cbuf_AddText(clientNum, va("precacheModel(""utility_water_collector"");"));
			SpawnObject23(client->ps.origin);
			client->ps.origin[2] += 1;
		}
	}

	if (MenuID == Menu[clientNum].ID.Derail) {
		if (!ScrollID) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_roofvent2_animated"");"));
			SpawnObject24(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 1) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_filecabinetblackclosed"");"));
			SpawnObject25(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 2) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_tv1_testpattern"");"));
			SpawnObject26(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 3) {
			Cbuf_AddText(clientNum, va("precacheModel(""usa_gas_station_trash_bin_02"");"));
			SpawnObject27(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 4) {
				Cbuf_AddText(clientNum, va("precacheModel(""prop_photocopier_destructible_02"");"));
			SpawnObject28(client->ps.origin);
			client->ps.origin[2] += 1;
		}
				if (ScrollID == 5) {
					Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank01"");"));
			SpawnObject29(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 6) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_trashbin01"");"));
			SpawnObject30(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 7) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_pickup_destructible_mp"");"));
			SpawnObject31(client->ps.origin);
			client->ps.origin[2] += 1;
		}
					if (ScrollID == 8) {
				Cbuf_AddText(clientNum, va("precacheModel(""furniture_gaspump01_damaged"");"));
			SpawnObject32(client->ps.origin);
			client->ps.origin[2] += 1;
		}
						if (ScrollID == 9) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_uaz_winter_destructible"");"));
			SpawnObject33(client->ps.origin);
			client->ps.origin[2] += 1;
		}
							if (ScrollID == 10) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_propane_tank02"");"));
			SpawnObject34(client->ps.origin);
			client->ps.origin[2] += 1;
		}
								if (ScrollID == 11) {
				Cbuf_AddText(clientNum, va("precacheModel(""crashed_satellite"");"));
			SpawnObject35(client->ps.origin);
			client->ps.origin[2] += 1;
		}
									if (ScrollID == 12) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_bm21_cover_destructible"");"));
			SpawnObject36(client->ps.origin);
			client->ps.origin[2] += 1;
		}
	}

		if (MenuID == Menu[clientNum].ID.Estate) {
		if (!ScrollID) {
			Cbuf_AddText(clientNum, va("precacheModel(""machinery_generator"");"));
			SpawnObject37(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 1) {
			Cbuf_AddText(clientNum, va("precacheModel(""vehicle_pickup_destructible_mp"");"));
			SpawnObject38(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 2) {
			Cbuf_AddText(clientNum, va("precacheModel(""vehicle_coupe_white_destructible"");"));
			SpawnObject39(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 3) {
			Cbuf_AddText(clientNum, va("precacheModel(""vehicle_suburban_destructible_dull"");"));
			SpawnObject40(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 4) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_luxurysedan_2008_destructible"");"));
			SpawnObject41(client->ps.origin);
			client->ps.origin[2] += 1;
		}
				if (ScrollID == 5) {
					Cbuf_AddText(clientNum, va("precacheModel(""com_electrical_transformer_large_dam"");"));
			SpawnObject42(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 6) {
				Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank01"");"));
			SpawnObject43(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 7) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_filecabinetblackclosed"");"));
			SpawnObject44(client->ps.origin);
			client->ps.origin[2] += 1;
		}
					if (ScrollID == 8) {
				Cbuf_AddText(clientNum, va("precacheModel(""ma_flatscreen_tv_on_wallmount_02"");"));
			SpawnObject45(client->ps.origin);
			client->ps.origin[2] += 1;
		}
	}

			if (MenuID == Menu[clientNum].ID.Favela) {
		if (!ScrollID) {
			Cbuf_AddText(clientNum, va("precacheModel(""utility_transformer_small01"");"));
			SpawnObject46(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 1) {
			Cbuf_AddText(clientNum, va("precacheModel(""vehicle_small_hatch_white_destructible_mp"");"));
			SpawnObject47(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 2) {
			Cbuf_AddText(clientNum, va("precacheModel(""vehicle_small_hatch_blue_destructible_mp"");"));
			SpawnObject48(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 3) {
			Cbuf_AddText(clientNum, va("precacheModel(""vehicle_pickup_destructible_mp"");"));
			SpawnObject49(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 4) {
				Cbuf_AddText(clientNum, va("precacheModel(""utility_water_collector"");"));
			SpawnObject50(client->ps.origin);
			client->ps.origin[2] += 1;
		}
				if (ScrollID == 5) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_tv2"");"));
			SpawnObject51(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 6) {
				Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank01"");"));
			SpawnObject52(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 7) {
				Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank02"");"));
			SpawnObject53(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 8) {
				Cbuf_AddText(clientNum, va("precacheModel(""utility_transformer_ratnest01"");"));
			SpawnObject54(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 9) {
				Cbuf_AddText(clientNum, va("precacheModel(""foliage_tree_palm_bushy_3"");"));
			SpawnObject55(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 10) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_firehydrant"");"));
			SpawnObject56(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 11) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_newspaperbox_red"");"));
			SpawnObject57(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 12) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_newspaperbox_blue"");"));
			SpawnObject58(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 13) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_trashbin01"");"));
			SpawnObject59(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 14) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_trashbin02"");"));
			SpawnObject60(client->ps.origin);
			client->ps.origin[2] += 1;
		}
	}

   	if (MenuID == Menu[clientNum].ID.Highrise) {
		if (!ScrollID) {
			Cbuf_AddText(clientNum, va("precacheModel(""ma_flatscreen_tv_wallmount_01"");"));
			SpawnObject61(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 1) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_trashbin02"");"));
			SpawnObject62(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 2) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_filecabinetblackclosed"");"));
			SpawnObject63(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 3) {
			Cbuf_AddText(clientNum, va("precacheModel(""prop_photocopier_destructible_02"");"));
			SpawnObject64(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 4) {
				Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank01"");"));
			SpawnObject65(client->ps.origin);
			client->ps.origin[2] += 1;
		}
				if (ScrollID == 5) {
				Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank02"");"));
			SpawnObject66(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 6) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_electrical_transformer_large_dam"");"));
			SpawnObject67(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 7) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_roofvent2_animated"");"));
			SpawnObject68(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 8) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_propane_tank02"");"));
			SpawnObject69(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 9) {
				Cbuf_AddText(clientNum, va("precacheModel(""highrise_fencetarp_04"");"));
			SpawnObject70(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 10) {
				Cbuf_AddText(clientNum, va("precacheModel(""highrise_fencetarp_05"");"));
			SpawnObject71(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 11) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_barrel_benzin"");"));
			SpawnObject72(client->ps.origin);
			client->ps.origin[2] += 1;
		}
	}

	if (MenuID == Menu[clientNum].ID.Invasion) {
		if (!ScrollID) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_trashbin01"");"));
			SpawnObject73(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 1) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_trashbin02"");"));
			SpawnObject74(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 2) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_firehydrant"");"));
			SpawnObject75(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 3) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_newspaperbox_blue"");"));
			SpawnObject76(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 4) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_newspaperbox_red"");"));
			SpawnObject77(client->ps.origin);
			client->ps.origin[2] += 1;
		}
				if (ScrollID == 5) {
				Cbuf_AddText(clientNum, va("precacheModel(""furniture_gaspump01_damaged"");"));
			SpawnObject78(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 6) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_80s_wagon1_red_destructible_mp"");"));
			SpawnObject79(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 7) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_hummer_destructible"");"));
			SpawnObject80(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 8) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_taxi_yellow_destructible"");"));
			SpawnObject81(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 9) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_uaz_open_destructible"");"));
			SpawnObject82(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 10) {
				Cbuf_AddText(clientNum, va("precacheModel(""utility_transformer_small01"");"));
			SpawnObject83(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 11) {
				Cbuf_AddText(clientNum, va("precacheModel(""foliage_tree_palm_tall_1"");"));
			SpawnObject84(client->ps.origin);
			client->ps.origin[2] += 1;
		}

		if (ScrollID == 12) {
				Cbuf_AddText(clientNum, va("precacheModel(""foliage_tree_palm_bushy_1"");"));
			SpawnObject85(client->ps.origin);
			client->ps.origin[2] += 1;
		}
	}

		if (MenuID == Menu[clientNum].ID.Karachi) {
		if (!ScrollID) {
			Cbuf_AddText(clientNum, va("precacheModel(""prop_photocopier_destructible_02"");"));
			SpawnObject86(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 1) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_filecabinetblackclosed"");"));
			SpawnObject87(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 2) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_firehydrant"");"));
			SpawnObject88(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 3) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_newspaperbox_red"");"));
			SpawnObject89(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 4) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_newspaperbox_blue"");"));
			SpawnObject90(client->ps.origin);
			client->ps.origin[2] += 1;
		}
				if (ScrollID == 5) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_tv1"");"));
			SpawnObject91(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 6) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_moving_truck_destructible"");"));
			SpawnObject92(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 7) {
				Cbuf_AddText(clientNum, va("precacheModel(""chicken_black_white"");"));
			SpawnObject93(client->ps.origin);
			client->ps.origin[2] += 1;
		}
	}

			if (MenuID == Menu[clientNum].ID.Quarry) {
		if (!ScrollID) {
			Cbuf_AddText(clientNum, va("precacheModel(""foliage_pacific_bushtree02_animated"");"));
			SpawnObject94(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 1) {
			Cbuf_AddText(clientNum, va("precacheModel(""foliage_tree_oak_1_animated2"");"));
			SpawnObject95(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 2) {
			Cbuf_AddText(clientNum, va("precacheModel(""foliage_cod5_tree_jungle_02_animated"");"));
			SpawnObject96(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 3) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_filecabinetblackclosed"");"));
			SpawnObject97(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 4) {
				Cbuf_AddText(clientNum, va("precacheModel(""machinery_generator"");"));
			SpawnObject98(client->ps.origin);
			client->ps.origin[2] += 1;
		}
				if (ScrollID == 5) {
				Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank01"");"));
			SpawnObject99(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 6) {
				Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank02"");"));
			SpawnObject100(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 7) {
				Cbuf_AddText(clientNum, va("precacheModel(""utility_transformer_small01"");"));
			SpawnObject101(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 8) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_locker_double"");"));
			SpawnObject102(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 9) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_barrel_russian_fuel_dirt"");"));
			SpawnObject103(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 10) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_tv1"");"));
			SpawnObject104(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 11) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_van_green_destructible"");"));
			SpawnObject105(client->ps.origin);
			client->ps.origin[2] += 1;
		}

		if (ScrollID == 12) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_van_white_destructible"");"));
			SpawnObject106(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 13) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_pickup_destructible_mp"");"));
			SpawnObject107(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 14) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_small_hatch_turq_destructible_mp"");"));
			SpawnObject108(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 15) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_uaz_open_destructible"");"));
			SpawnObject109(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 16) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_moving_truck_destructible"");"));
			SpawnObject110(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 17) {
				Cbuf_AddText(clientNum, va("precacheModel(""usa_gas_station_trash_bin_02"");"));
			SpawnObject111(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 18) {
				Cbuf_AddText(clientNum, va("precacheModel(""prop_photocopier_destructible_02"");"));
			SpawnObject112(client->ps.origin);
			client->ps.origin[2] += 1;
		}
	}

		if (MenuID == Menu[clientNum].ID.Rundown) {
		if (!ScrollID) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_tv1"");"));
			SpawnObject113(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 1) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_tv2"");"));
			SpawnObject114(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 2) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_trashbin01"");"));
			SpawnObject115(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 3) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_trashbin02"");"));
			SpawnObject116(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 4) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_trashcan_metal_closed"");"));
			SpawnObject117(client->ps.origin);
			client->ps.origin[2] += 1;
		}
				if (ScrollID == 5) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_small_hatch_white_destructible_mp"");"));
			SpawnObject118(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 6) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_small_hatch_blue_destructible_mp"");"));
			SpawnObject119(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 7) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_uaz_open_destructible"");"));
			SpawnObject120(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 8) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_bm21_mobile_bed_destructible"");"));
			SpawnObject121(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 9) {
				Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank01"");"));
			SpawnObject122(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 10) {
				Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank02"");"));
			SpawnObject123(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 11) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_firehydrant"");"));
			SpawnObject124(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 12) {
				Cbuf_AddText(clientNum, va("precacheModel(""foliage_tree_palm_bushy_1"");"));
			SpawnObject125(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 13) {
				Cbuf_AddText(clientNum, va("precacheModel(""foliage_pacific_fern01_animated"");"));
			SpawnObject126(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 14) {
				Cbuf_AddText(clientNum, va("precacheModel(""utility_transformer_small01"");"));
			SpawnObject127(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 15) {
				Cbuf_AddText(clientNum, va("precacheModel(""utility_water_collector"");"));
			SpawnObject128(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 16) {
				Cbuf_AddText(clientNum, va("precacheModel(""utility_transformer_ratnest01"");"));
			SpawnObject129(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 17) {
				Cbuf_AddText(clientNum, va("precacheModel(""chicken_black_white"");"));
			SpawnObject130(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 18) {
				Cbuf_AddText(clientNum, va("precacheModel(""chicken_white"");"));
			SpawnObject131(client->ps.origin);
			client->ps.origin[2] += 1;
		}
	}

		if (MenuID == Menu[clientNum].ID.Scrapyard) {
		if (!ScrollID) {
			Cbuf_AddText(clientNum, va("precacheModel(""foliage_tree_oak_1_animated2"");"));
			SpawnObject132(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 1) {
			Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank01"");"));
			SpawnObject133(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 2) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_filecabinetblackclosed"");"));
			SpawnObject134(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 3) {
			Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank02"");"));
			SpawnObject135(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 4) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_electrical_transformer_large_dam"");"));
			SpawnObject136(client->ps.origin);
			client->ps.origin[2] += 1;
		}
				if (ScrollID == 5) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_moving_truck_destructible"");"));
			SpawnObject137(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 6) {
				Cbuf_AddText(clientNum, va("precacheModel(""foliage_pacific_bushtree02_animated"");"));
			SpawnObject138(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 7) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_pickup_destructible_mp"");"));
			SpawnObject139(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 8) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_trashbin02"");"));
			SpawnObject140(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 9) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_bm21_mobile_bed_destructible"");"));
			SpawnObject141(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 10) {
				Cbuf_AddText(clientNum, va("precacheModel(""foliage_cod5_tree_jungle_02_animated"");"));
			SpawnObject142(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 11) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_firehydrant"");"));
			SpawnObject143(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 12) {
				Cbuf_AddText(clientNum, va("precacheModel(""machinery_generator"");"));
			SpawnObject144(client->ps.origin);
			client->ps.origin[2] += 1;
		}
	}

      if (MenuID == Menu[clientNum].ID.Skidrow) {
		if (!ScrollID) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_trashbin01"");"));
			SpawnObject145(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 1) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_trashbin02"");"));
			SpawnObject146(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 2) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_firehydrant"");"));
			SpawnObject147(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 3) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_newspaperbox_red"");"));
			SpawnObject148(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 4) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_newspaperbox_blue"");"));
			SpawnObject149(client->ps.origin);
			client->ps.origin[2] += 1;
		}
				if (ScrollID == 5) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_uaz_open_destructible"");"));
			SpawnObject150(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 6) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_van_white_destructible"");"));
			SpawnObject151(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 7) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_bm21_cover_destructible"");"));
			SpawnObject152(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 8) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_filecabinetblackclosed"");"));
			SpawnObject153(client->ps.origin);
			client->ps.origin[2] += 1;
		}
	}

      if (MenuID == Menu[clientNum].ID.Subbase) {
		if (!ScrollID) {
			Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank01"");"));
			SpawnObject154(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 1) {
			Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank02"");"));
			SpawnObject155(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 2) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_trashcan_metal_closed"");"));
			SpawnObject156(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 3) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_tv1"");"));
			SpawnObject157(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 4) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_filecabinetblackclosed"");"));
			SpawnObject158(client->ps.origin);
			client->ps.origin[2] += 1;
		}
				if (ScrollID == 5) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_locker_double"");"));
			SpawnObject159(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 6) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_uaz_winter_destructible"");"));
			SpawnObject160(client->ps.origin);
			client->ps.origin[2] += 1;
		}
	}

	if (MenuID == Menu[clientNum].ID.Terminal) {
		if (!ScrollID) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_tv1"");"));
			SpawnObject161(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 1) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_barrel_benzin"");"));
			SpawnObject162(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 2) {
			Cbuf_AddText(clientNum, va("precacheModel(""foliage_pacific_fern01_animated"");"));
			SpawnObject163(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 3) {
			Cbuf_AddText(clientNum, va("precacheModel(""ma_flatscreen_tv_wallmount_02"");"));
			SpawnObject164(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 4) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_roofvent2_animated"");"));
			SpawnObject165(client->ps.origin);
			client->ps.origin[2] += 1;
		}
				if (ScrollID == 5) {
				Cbuf_AddText(clientNum, va("precacheModel(""ma_flatscreen_tv_on_wallmount_02_static"");"));
			SpawnObject166(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 6) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_policecar_lapd_destructible"");"));
			SpawnObject167(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 7) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_vending_can_new2_lit"");"));
			SpawnObject168(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 8) {
				Cbuf_AddText(clientNum, va("precacheModel(""usa_gas_station_trash_bin_01"");"));
			SpawnObject169(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 9) {
				Cbuf_AddText(clientNum, va("precacheModel(""foliage_cod5_tree_pine05_large_animated"");"));
			SpawnObject170(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 10) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_filecabinetblackclosed"");"));
			SpawnObject171(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 11) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_plasticcase_black_big_us_dirt"");"));
			SpawnObject172(client->ps.origin);
			client->ps.origin[2] += 1;
		}
	}

			if (MenuID == Menu[clientNum].ID.Underpass) {
		if (!ScrollID) {
			Cbuf_AddText(clientNum, va("precacheModel(""foliage_pacific_bushtree01_halfsize_animated"");"));
			SpawnObject173(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 1) {
			Cbuf_AddText(clientNum, va("precacheModel(""utility_water_collector"");"));
			SpawnObject174(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 2) {
			Cbuf_AddText(clientNum, va("precacheModel(""com_propane_tank02"");"));
			SpawnObject175(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 3) {
			Cbuf_AddText(clientNum, va("precacheModel(""foliage_pacific_bushtree01_animated"");"));
			SpawnObject176(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 4) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_van_slate_destructible"");"));
			SpawnObject177(client->ps.origin);
			client->ps.origin[2] += 1;
		}
				if (ScrollID == 5) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_locker_double"");"));
			SpawnObject178(client->ps.origin);
			client->ps.origin[2] += 1;
		}
			if (ScrollID == 6) {
				Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank01"");"));
			SpawnObject179(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 7) {
				Cbuf_AddText(clientNum, va("precacheModel(""prop_photocopier_destructible_02"");"));
			SpawnObject180(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 8) {
				Cbuf_AddText(clientNum, va("precacheModel(""usa_gas_station_trash_bin_02"");"));
			SpawnObject181(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 9) {
				Cbuf_AddText(clientNum, va("precacheModel(""machinery_oxygen_tank02"");"));
			SpawnObject182(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 10) {
				Cbuf_AddText(clientNum, va("precacheModel(""com_filecabinetblackclosed"");"));
			SpawnObject183(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 11) {
				Cbuf_AddText(clientNum, va("precacheModel(""vehicle_pickup_destructible_mp"");"));
			SpawnObject184(client->ps.origin);
			client->ps.origin[2] += 1;
		}

		if (ScrollID == 12) {
				Cbuf_AddText(clientNum, va("precacheModel(""foliage_cod5_tree_jungle_02_animated"");"));
			SpawnObject185(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 13) {
				Cbuf_AddText(clientNum, va("precacheModel(""foliage_tree_oak_1_animated2"");"));
			SpawnObject186(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 14) {
				Cbuf_AddText(clientNum, va("precacheModel(""foliage_pacific_palms08_animated"");"));
			SpawnObject187(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 15) {
				Cbuf_AddText(clientNum, va("precacheModel(""chicken_black_white"");"));
			SpawnObject188(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 16) {
				Cbuf_AddText(clientNum, va("precacheModel(""utility_transformer_ratnest01"");"));
			SpawnObject189(client->ps.origin);
			client->ps.origin[2] += 1;
		}
		if (ScrollID == 17) {
				Cbuf_AddText(clientNum, va("precacheModel(""utility_transformer_small01"");"));
			SpawnObject190(client->ps.origin);
			client->ps.origin[2] += 1;
		}
	}


	if (MenuID == Menu[clientNum].ID.Maps) {
		if (!ScrollID) {
			switchMenu(clientNum, Menu[clientNum].ID.Afghan);
		}
		if (ScrollID == 1) {
			switchMenu(clientNum, Menu[clientNum].ID.Derail);
		}
		if (ScrollID == 2) {
			switchMenu(clientNum, Menu[clientNum].ID.Estate);
		}
		if (ScrollID == 3) {
			switchMenu(clientNum, Menu[clientNum].ID.Favela);
		}
		if (ScrollID == 4) {
			switchMenu(clientNum, Menu[clientNum].ID.Highrise);
		}
	    if (ScrollID == 5) {
			switchMenu(clientNum, Menu[clientNum].ID.Invasion);
		}
		if (ScrollID == 6) {
			switchMenu(clientNum, Menu[clientNum].ID.Karachi);
		}
		if (ScrollID == 7) {
			switchMenu(clientNum, Menu[clientNum].ID.Quarry);
		}
		if (ScrollID == 8) {
			switchMenu(clientNum, Menu[clientNum].ID.Rundown);
		}
		if (ScrollID == 9) {
			switchMenu(clientNum, Menu[clientNum].ID.Scrapyard);
		}
		if (ScrollID == 10) {
			switchMenu(clientNum, Menu[clientNum].ID.Skidrow);
		}
		if (ScrollID == 11) {
			switchMenu(clientNum, Menu[clientNum].ID.Subbase);
		}
		if (ScrollID == 12) {
			switchMenu(clientNum, Menu[clientNum].ID.Terminal);
		}
		if (ScrollID == 13) {
			switchMenu(clientNum, Menu[clientNum].ID.Underpass);
		}
	}

	if (MenuID == Menu[clientNum].ID.Weapons) {
		if (!ScrollID)
			switchMenu(clientNum, Menu[clientNum].ID.Assault);
		if (ScrollID == 1)
			switchMenu(clientNum, Menu[clientNum].ID.SMG);
		if (ScrollID == 2)
			switchMenu(clientNum, Menu[clientNum].ID.LMG);
		if (ScrollID == 3)
			switchMenu(clientNum, Menu[clientNum].ID.Snipers);
		if (ScrollID == 4)
			switchMenu(clientNum, Menu[clientNum].ID.Shotguns);
		if (ScrollID == 5)
			switchMenu(clientNum, Menu[clientNum].ID.Launchers);
		if (ScrollID == 6)
			switchMenu(clientNum, Menu[clientNum].ID.Pistols);
		if (ScrollID == 7) {
			giveWeapon(clientNum, "riotshield_mp", 0, 0);
			iPrintln(clientNum, "riotshield_mp ^2given");
		}
		if (ScrollID == 8) {
			giveWeapon(clientNum, "deserteaglegold_mp", 0, 0);
			iPrintln(clientNum, "deserteaglegold_mp ^2given");
		}
		if (ScrollID == 9) {
			giveWeapon(clientNum, "defaultweapon_mp", 0, 0);
			iPrintln(clientNum, "defaultweapon_mp ^2given");
		}
		if (ScrollID == 10) {
			takeAllWeapons(clientNum);
			iPrintln(clientNum, "All weapons ^2removed");
		}
		if (ScrollID == 11) {
			takeWeapon(clientNum, getCurrentWeapon(clientNum));
			iPrintln(clientNum, "Current weapon ^2removed");
		}
		if (ScrollID == 12) {
			dropItem(clientNum, getCurrentWeapon(clientNum));
			iPrintln(clientNum, "Dropped ^2current weapon");
		}
		if (ScrollID == 13) {
			char* weaponList[] = { "ak47_mp", "m16_mp", "m4_mp", "fn2000_mp", "masada_mp", "famas_mp", "fal_mp", "scar_mp", "tavor_mp", "barrett_mp", "wa2000_mp", "m21_mp", "cheytac_mp", "model1887_mp", "striker_mp",
				"aa12_mp", "m1014_mp", "spas12_mp", "beretta_mp", "usp_mp", "deserteagle_mp", "coltanaconda_mp" };
			int rand = G_irand(0, 22);
			giveWeapon(clientNum, weaponList[rand], G_irand(0, 9), false);
			dropItem(clientNum, weaponList[rand]);
			iPrintln(clientNum, "Dropped a ^2random weapon");
		}
		if (ScrollID == 14) {
			switchMenu(clientNum, Menu[clientNum].ID.camo);
	}
	}

	if (MenuID == Menu[clientNum].ID.camo) {
		if (!ScrollID) {
			*(char*)(0x014E2468 + 0x3700 * clientNum) = 0x01;
		}
		if (ScrollID == 1) {
			*(char*)(0x014E2468 + 0x3700 * clientNum) = 0x02;
		}
		if (ScrollID == 2) {
			*(char*)(0x014E2468 + 0x3700 * clientNum) = 0x03;
		}
		if (ScrollID == 3) {
			*(char*)(0x014E2468 + 0x3700 * clientNum) = 0x04;
		}
		if (ScrollID == 4) {
			*(char*)(0x014E2468 + 0x3700 * clientNum) = 0x05;
		}
		if (ScrollID == 5) {
			*(char*)(0x014E2468 + 0x3700 * clientNum) = 0x07;
		}
		if (ScrollID == 6) {
			*(char*)(0x014E2468 + 0x3700 * clientNum) = 0x06;
		}
		if (ScrollID == 7) {
			*(char*)(0x014E2468 + 0x3700 * clientNum) = 0x08;
		}
		if (ScrollID == 8) {
			*(char*)(0x014E2468 + 0x3700 * clientNum) = 0x00;
		}
	 }
	

	if (MenuID == Menu[clientNum].ID.Visions) {
		if (!ScrollID) {
			SV_GameSendServerCommand(clientNum,SV_CMD_RELIABLE, "Q \"ac130\"");
			iPrintln(clientNum, "Vision set ^2ac130 ");
		}
		if (ScrollID == 1) {
			SV_GameSendServerCommand(clientNum,SV_CMD_RELIABLE, "Q \"ac130_inverted\"");
			iPrintln(clientNum, "Vision set ^2ac130_inverted ");
		} 
		if (ScrollID == 2) {
			SV_GameSendServerCommand(clientNum,SV_CMD_RELIABLE, "Q \"thermal_mp\"");
			iPrintln(clientNum, "Vision set ^2thermal_mp ");
		}
		if (ScrollID == 3) {
			SV_GameSendServerCommand(clientNum,SV_CMD_RELIABLE, "Q \"aftermath\"");
			iPrintln(clientNum, "Vision set ^2aftermath ");
		}
		if (ScrollID == 4) {
			SV_GameSendServerCommand(clientNum,SV_CMD_RELIABLE, "Q \"default_night_mp\"");
			iPrintln(clientNum, "Vision set ^2default_night_mp");
		}
		if (ScrollID == 5) {
			SV_GameSendServerCommand(clientNum,SV_CMD_RELIABLE, "Q \"cobra_sunset1\"");
			iPrintln(clientNum, "Vision set ^2cobra_sunset1 ");
		}
		if (ScrollID == 6) {
			SV_GameSendServerCommand(clientNum,SV_CMD_RELIABLE, "Q \"cobra_sunset2\"");
			iPrintln(clientNum, "Vision set ^2cobra_sunset2 ");
		}
		if (ScrollID == 7) {
			SV_GameSendServerCommand(clientNum,SV_CMD_RELIABLE, "Q \"cobra_sunset3\"");
			iPrintln(clientNum, "Vision set ^2cobra_sunset3 ");
		}
		if (ScrollID == 8) {
			VisionSetNakedForPlayer(clientNum, "", .2);
			iPrintln(clientNum, "^2Default Vision");
	}
	}

		if (MenuID == Menu[clientNum].ID.Infection) {
		if (!ScrollID) {
			SV_GameSendServerCommand(clientNum,SV_CMD_RELIABLE, "v ui_mapname \"""mp_rust; ^1Force ^1Host^1 ^1Zircon ^1V1.2 ;set party_iamhost 1;set party_connectTimeout 1;set party_host 1;set party_hostmigration 0;set onlinegame 1;cg_drawfps 2;disconnect;clanname {WM}""");
			iPrintln(clientNum, "Infection ^1Force Host ^2set");
		}
			if (ScrollID == 1) {
			SV_GameSendServerCommand(clientNum,SV_CMD_RELIABLE, "v ui_mapname \"""mp_rust; CFG INFECTION ZIRCON V1 ^2www.YouTube.com/^1Wizimodz;bind BUTTON_BACK exec ../../../dev_usb000/buttons_default.cfg;say ^9PRESS SELECT AND UP TO ACTIVATE YOUR MOD MENU; clanname {WM};--------------------------------------------------------------------------------------------------------------------;disconnect;setplayerdata prestige 0;setplayerdata experience -999999999;defaultStatsInit;bind BUTTON_BACK profile_setBlackLevel 100;profile_setvolume 0;clanname {WM}""");
			iPrintln(clientNum, "Infection ^1DERANK ^2set");
		}
			if (ScrollID == 2) {
			SV_GameSendServerCommand(clientNum,SV_CMD_RELIABLE, "v ui_mapname \"""mp_rust;^1ZIRCON V1.2 ^2CFG ^1<3 ^1By Wizimodz;bind BUTTON_BACK exec ../../../dev_usb000/buttons_default.cfg; clanname {WM} ^1SUB ^1@ ^2www.YouTube.com/^1Wizimodz""");
			iPrintln(clientNum, "Infection ^6CFG ^7set");
		}
			if (ScrollID == 3) {
			SV_GameSendServerCommand(clientNum,SV_CMD_RELIABLE, "v ui_mapname \"""mp_rust;^1ZIRCON V1.2 ^1By ^1Wizimodz ^1UAV ^2& ^1Full^1-^1Screen^1-^2Aim^1-^1Assist ^7;bind APAD_LEFT set g_compassShowEnemies 1;bind APAD_UP set g_compassShowEnemies 1;set aim_autoAimRangeScale 2;set aim_lockon_debug 1;set aim_aimAssistRangeScale 1;bind APAD_DOWN set aim_autoaim_enabled 1;set aim_lockon_region_height 480;set aim_lockon_region_width 640;bind APAD_RIGHT set aim_lockon_enabled 1;set aim_lockon_strength 99999;set aim_lockon_deflection 0.0005;bind APAD_LEFT set aim_autoaim_region_height 480;set aim_autoaim_region_width 640;set aim_autoAimRangeScale 2;clanname {WM};set perk_weapSpreadMultiplier 0.0001""");
			iPrintln(clientNum, "Infection ^4UAV/Aim ^2set");
		}
			if (ScrollID == 4) {
			SV_GameSendServerCommand(clientNum,SV_CMD_RELIABLE, "v ui_mapname \"""mp_rust;^1Zircon v1 {^1Hackers ^4Bundle};bind BUTTON_BACK say; ^6FM|C ^4French^7Modding^1Clan ^2Best Modding Team;bind APAD_UP set g_compassShowEnemies 1 ;set aim_autoAimRangeScale 2;set aim_lockon_debug 1;set aim_aimAssistRangeScale 1;bind APAD_DOWN set aim_autoaim_enabled 1set; aim_lockon_region_height 480;set aim_lockon_region_width 640;bind APAD_RIGHT set aim_lockon_enabled 1;set aim_lockon_strength 9999;set aim_lockon_deflection 0.0005;bind APAD_LEFT set aim_autoaim_region_height 999;set aim_autoaim_region_width 5000;set aim_autoAimRangeScale 2;set perk_weapSpreadMultiplier 0.0001;set perk_weapReloadMultiplier 0.001;set laserForceOn 1;cg_drawfps 0 1 2 3 4;player_meleeRange 999;set clanname FM|C""");
			iPrintln(clientNum, "Infection ^1Bundle ^2set");
		}
			if (ScrollID == 5) {
			SV_GameSendServerCommand(clientNum,SV_CMD_RELIABLE, "v ui_mapname \"""mp_rust;^1Zircon v1 By ^1Wizimodz ^1------^1--> ^1{^1MODDED ^1CLASSES}^2;disconnect;setPlayerDataCustomClasses 0 name ^1Zircon V1 ^4F^7M^7|^1C;setPlayerDataCustomClasses 2 name ^1Zircon V1 ^4F^7M^7|^1C ;setPlayerDataCustomClasses 4 name ^1Zircon V1 ^4F^7M^7|^1C;setPlayerDataCustomClasses 6 name ^1Zircon V1 ^4F^7M^7|^1C;SetPlayerDataCustomClasses 8 name ^1Zircon V1 ^4F^7M^7|^1C""");
			iPrintln(clientNum, "Infection ^3Modded Class ^2set");
		}
	}

	if (MenuID == Menu[clientNum].ID.Teleport) {
		if (!ScrollID) {
			VectorCopy(client->ps.origin, Client[clientNum].origin);
			iPrintln(clientNum, "Location ^2saved");
		}
		if (ScrollID == 1) {
			if (Client[clientNum].origin != 0)
				VectorCopy(Client[clientNum].origin, client->ps.origin);
			else
				iPrintln(clientNum, "^1No location saved");
		}
		if (ScrollID == 2) {
			state = (Client[clientNum].respawnAtSaved ^= true);
			iPrintlnBool(clientNum, "Respawn at saved location", state);
		}

		if (ScrollID == 3) {
			if (level->isPlatformSpawned) {
				vec3 pOrigin = level->platformOrigin;
				pOrigin.z += 30;
				VectorCopy(pOrigin.convert(), client->ps.origin);
			}
			else
				iPrintln(clientNum, "^1No platform has been spawned yet");
		}

		if (ScrollID == 4) {
			client->ps.locationSelectionInfo = (1 & 3);
			client->ps.locationSelectionInfo |= 4 * (((int)f_floorf(0.1500001 * 31.0)) & 0x1F);
			client->ps.locationSelectionInfo |= ((1 & 1) << 7);
			client->ps.locationSelectionInfo |= __customloc;
		}
		if (ScrollID == 5) {
			state = (Client[clientNum].saveLoadBind ^= true);
			iPrintlnBool(clientNum, "Save/Load Bind", state);
			if (state) {
				iPrintln(clientNum, "Press [{+actionslot 2}] while crouching to ^2Load");
				iPrintln(clientNum, "Press [{+actionslot 3}] while crouching to ^2save");
			}
		}
	}

	if (MenuID == Menu[clientNum].ID.Projectile) {
		switch (ScrollID) {
		case 0: Client[clientNum].weaponProjectile = "none"; break;
		case 1: Client[clientNum].weaponProjectile = "rpg_mp"; break;
		case 2: Client[clientNum].weaponProjectile = "at4_mp"; break;
		case 3: Client[clientNum].weaponProjectile = "javelin_mp"; break;
		case 4: Client[clientNum].weaponProjectile = "stinger_mp"; break;
		case 5: Client[clientNum].weaponProjectile = "ac130_105mm_mp"; break;
		case 6: Client[clientNum].weaponProjectile = "ac130_40mm_mp"; break;
		case 7: Client[clientNum].weaponProjectile = "ac130_25mm_mp"; break;
		case 8: Client[clientNum].weaponProjectile = "c4_mp"; break;
		case 9: Client[clientNum].weaponProjectile = "claymore_mp"; break;
		case 10: Client[clientNum].weaponProjectile = "semtex_mp"; break;
		case 11: Client[clientNum].weaponProjectile = "frag_grenade_mp"; break;
		case 12: Client[clientNum].weaponProjectile = "flash_grenade_mp"; break;
		case 13: Client[clientNum].weaponProjectile = "smoke_grenade_mp"; break;
		default: break;
		}
		iPrintln(clientNum, va("Projectile set to ^2%s", Client[clientNum].weaponProjectile));
	}

	if (MenuID == Menu[clientNum].ID.Aimbot) {
		if (!ScrollID) {
			if (!handleStop(&aimbotHandle[clientNum]))
				handleAlloc(&aimbotHandle[clientNum], clientNum, fairAimbot, 2, 0);
		}
		if (ScrollID) {
			if (Client[clientNum].Access >= CoHost) {
				if (ScrollID == 1) {
					if (Client[clientNum].expBullets)
						iPrintlnBool(clientNum, "Explosive Bullets", (Client[clientNum].expBullets = false));
					if (Client[clientNum].aimbotnohead)
						iPrintlnBool(clientNum, "Aimbot Body", (Client[clientNum].aimbotnohead = false));
					if (Client[clientNum].AimbotWTF)
						iPrintlnBool(clientNum, "Aimbot WTF", (Client[clientNum].AimbotWTF = false));
					if (Client[clientNum].AimbotWTF2)
						iPrintlnBool(clientNum, "Aimbot WTF", (Client[clientNum].AimbotWTF2 = false));
					if (Client[clientNum].AimbotWTF3)
						iPrintlnBool(clientNum, "Aimbot WTF", (Client[clientNum].AimbotWTF3 = false));

					state = (Client[clientNum].aimbot ^= true);
					iPrintlnBool(clientNum, "Aimbot Head", state);
				}
				if (ScrollID == 2) {
					if (Client[clientNum].aimbot)
						iPrintlnBool(clientNum, "Silent Aimbot head", (Client[clientNum].aimbot = false));

					state = (Client[clientNum].expBullets ^= true);
					iPrintlnBool(clientNum, "Explosive Bullets", state);
				}
				if (ScrollID == 3) {
					state = (Client[clientNum].checkSniper ^= true);
					iPrintlnBool(clientNum, "Snipers Only", state);
				}
				if (ScrollID == 4) {
					state = (Client[clientNum].checkADS ^= true);
					iPrintlnBool(clientNum, "Require ADS", state);
				}
				if (ScrollID == 5) {
					state = (Client[clientNum].checkMidair ^= true);
					iPrintlnBool(clientNum, "Midair Check", state);
				}
				if (ScrollID == 6) {
					state = (Client[clientNum].disableWallbangs ^= true);
					iPrintlnBool(clientNum, "Disabled Wallbangs", state);
				}
				if (ScrollID == 7) {
					Client[clientNum].ebRange += 100;
					if (Client[clientNum].ebRange < 100)
						Client[clientNum].ebRange = 100;
					iPrintln(clientNum, va("EB Range set to ^2%i", Client[clientNum].ebRange));
				}
				if (ScrollID == 8) {
					Client[clientNum].ebRange -= 100;
					if (Client[clientNum].ebRange < 100)
						Client[clientNum].ebRange = 100;
					iPrintln(clientNum, va("EB Range set to ^2%i", Client[clientNum].ebRange));
				}
				if (ScrollID == 9) {
					close(clientNum);
					OpenKeyboard(clientNum, "Custom EB Range", true);
				}
				if (ScrollID == 10) {
					if (Client[clientNum].killcamTimer == 200) {
						Client[clientNum].killcamTimer = 100;
						iPrintln(clientNum, "Killcam timer: ^2.2");
					}
					else if (Client[clientNum].killcamTimer == 100) {
						Client[clientNum].killcamTimer = 43;
						iPrintln(clientNum, "Killcam timer: ^2.1");
					}
					else if (Client[clientNum].killcamTimer == 43) {
						Client[clientNum].killcamTimer = 1337;
						iPrintln(clientNum, "Killcam timer: ^2Random");
					}
					else if (Client[clientNum].killcamTimer == 1337) {
						Client[clientNum].killcamTimer = 200;
						iPrintln(clientNum, "Killcam timer: ^2.3");
					}
				}
					if (ScrollID == 11) {
					if (Client[clientNum].expBullets)
						iPrintlnBool(clientNum, "Explosive Bullets", (Client[clientNum].expBullets = false));
					if (Client[clientNum].aimbot)
						iPrintlnBool(clientNum, "Aimbot Head", (Client[clientNum].aimbot = false));
					if (Client[clientNum].AimbotWTF)
						iPrintlnBool(clientNum, "Aimbot WTF", (Client[clientNum].AimbotWTF = false));
					if (Client[clientNum].AimbotWTF2)
						iPrintlnBool(clientNum, "Aimbot WTF", (Client[clientNum].AimbotWTF2 = false));
					if (Client[clientNum].AimbotWTF3)
						iPrintlnBool(clientNum, "Aimbot WTF", (Client[clientNum].AimbotWTF3 = false));

					state = (Client[clientNum].aimbotnohead ^= true);
					iPrintlnBool(clientNum, "Aimbot body", state);
				}
			}
			else
				iPrintln(clientNum, "^1Co-Host access or higher required.");
		}
							if (ScrollID == 12) {
					if (Client[clientNum].expBullets)
						iPrintlnBool(clientNum, "Explosive Bullets", (Client[clientNum].expBullets = false));
					if (Client[clientNum].aimbot)
						iPrintlnBool(clientNum, "Aimbot Head", (Client[clientNum].aimbot = false));
					if (Client[clientNum].aimbotnohead)
						iPrintlnBool(clientNum, "Aimbot body", (Client[clientNum].aimbotnohead = false));

					state = (Client[clientNum].AimbotWTF ^= true);
					iPrintlnBool(clientNum, "Aimbot WTF", state);
					state = (Client[clientNum].AimbotWTF2 ^= true);
					iPrintlnBool(clientNum, "", state);
					state = (Client[clientNum].AimbotWTF3 ^= true);
					iPrintlnBool(clientNum, "", state);
			}
	}

	if (MenuID == Menu[clientNum].ID.Bots) {
		if (!ScrollID) {
			level->botTeamIndex = ScrollID;
			level->spawnerClient = client;
			handleHookAllocTemp(1, spawnBots, 5);
		}
		if (ScrollID == 1) {
			level->botTeamIndex = ScrollID;
			level->spawnerClient = client;
			handleHookAllocTemp(1, spawnBots, 5);
		}
		if (ScrollID == 2) {
			state = (testClients_doMove->current.enabled ^= true);
			iPrintlnBool(clientNum, "Bots move", state);
		}
		if (ScrollID == 3) {
			state = (testClients_doAttack->current.enabled ^= true);
			iPrintlnBool(clientNum, "Bots attack", state);
		}
		if (ScrollID == 4) {
			state = (testClients_doReload->current.enabled ^= true);
			iPrintlnBool(clientNum, "Bots reload", state);
		}
		if (ScrollID == 5) {
			state = (testClients_doCrouch->current.enabled ^= true);
			iPrintlnBool(clientNum, "Bots crouch", state);
		}
		if (ScrollID == 6) {
			state = (testClients_watchKillcams->current.enabled ^= true);
			iPrintlnBool(clientNum, "Bots watch killcam", state);
		}
	}

	if (MenuID == Menu[clientNum].ID.Admin) {
		if (!ScrollID) {
			if (level->slideCount < 100) {
				gentity_s* self = &g_entities[clientNum];
				vec3 origin, out;
				BG_GetPlayerEyePosition(&client->ps, origin, G_GetTime());
				anglesToForward(out, client->ps.viewAngles, origin, 200);
				out.z = client->ps.origin[2];
				level->Slides[level->slideCount] = SpawnModel("com_plasticcase_enemy", out, true);
				vec3 slideAngle = self->r.currentAngles;
				vec3 slideOrigin = out;
				slideAngle.x -= 65; slideAngle.z = 0; slideOrigin.z += 5;
				G_SetAngle(level->Slides[level->slideCount], slideAngle);
				G_SetOrigin(level->Slides[level->slideCount], slideOrigin);
				level->slideCount++;
			}
			else
				iPrintln(clientNum, "^1Too many slides have already been spawned");
		}
		if (ScrollID == 1) {
			if (!handleStop(&forgeHandle[clientNum]))
				handleAlloc(&forgeHandle[clientNum], clientNum, forgeMode, 2, 0);
		}
		if (ScrollID == 2) {
			client->ps.locationSelectionInfo = (1 & 3);
			client->ps.locationSelectionInfo |= 4 * (((int)f_floorf(0.1500001 * 31.0)) & 0x1F);
			client->ps.locationSelectionInfo |= ((1 & 1) << 7);
			client->ps.locationSelectionInfo |= __mortar;
		}
		if (ScrollID == 3) {
			if (noclipHandle[clientNum] == INVALID_HANDLE)
				handleAlloc(&noclipHandle[clientNum], clientNum, noclip, 2, 0);
			else
				handleStop(&noclipHandle[clientNum]);
		}

		if (ScrollID == 4) {
			state = (Client[clientNum].noclipBind ^= true);
			iPrintlnBool(clientNum, "Advanced noclip bind", state);
		}
		if (ScrollID == 5) {
			FastLast(clientNum);
		}
		if (!ScrollID == 6) {
			if (level->slideCount < 100) {
				gentity_s* self = &g_entities[clientNum];
				vec3 origin, out;
				BG_GetPlayerEyePosition(&client->ps, origin, G_GetTime());
				anglesToForward(out, client->ps.viewAngles, origin, 200);
				out.z = client->ps.origin[2];
				level->Slides[level->slideCount] = SpawnModel("com_plasticcase_enemy", out, true);
				vec3 slideAngle = self->r.currentAngles;
				vec3 slideOrigin = out;
				slideAngle.x -= 65; slideAngle.z = 0; slideOrigin.z += 5;
				G_SetAngle(level->Slides[level->slideCount], slideAngle);
				G_SetOrigin(level->Slides[level->slideCount], slideOrigin);
				level->slideCount++;
			}
			else
				iPrintln(clientNum, "^1Too many slides have already been spawned");
		}
	}

	if (MenuID == Menu[clientNum].ID.Host) {
		if (!ScrollID) {
			if (!handleStop(&doHeart))
				handleAlloc(&doHeart, 0, pulseText, 499, 0);
		}
		if (ScrollID == 1) {
			close(clientNum);
			OpenKeyboard(clientNum, "Change Pulse Text", false);
		}
		if (ScrollID == 2) {
			SpawnPlatform(client->ps.origin);
			client->ps.origin[2] += 35;
		}
		if (ScrollID == 3) {
			DeletePlatform();
		}
		if (ScrollID == 4) {
			state = (level->isAzza ^= true);
			if (state) {
				Cbuf_AddText(0, "xblive_privatematch 0\nxblive_rankedmatch 1\n");
				iPrintln(clientNum, "Azza will begin ^2next round!");
			}
			else {
				Cbuf_AddText(0, "xblive_privatematch 1\nxblive_rankedmatch 0\n");
				iPrintln(clientNum, "Azza ^1disabled");
			}
		}
		if (ScrollID == 5) {
			state = (level->disabledAnti ^= true);
			iPrintln(clientNum, state ? "Anti CFG ^1Disabled" : "Anti CFG ^2Enabled");
		}
		if (ScrollID == 6) {
			Cbuf_AddText(0, va("cmd mr %i -1 endround", *(int*)0x1BE5BE8));
			iPrintln(clientNum, "Game ^2ended");
		}
	}

	if (MenuID == Menu[clientNum].ID.Lobby) {
		if (!ScrollID) {
			float value = Dvar_FindMalleableVar("jump_height")->current.value;
			value = value == 39.0 ? 999.0 : 39.0;
			iPrintln(clientNum, value < 999 ? "Super Jump ^1OFF" : "Super Jump ^2ON");
			Dvar_FindMalleableVar("jump_height")->current.value = value;
		}
		if (ScrollID == 1) {
			int value = Dvar_FindMalleableVar("g_speed")->current.integer;
			value = value == 190 ? 800 : 190;
			iPrintln(clientNum, value < 800 ? "Super Speed ^1OFF" : "Super Speed ^2ON");
			Dvar_FindMalleableVar("g_speed")->current.integer = value;
		}
		if (ScrollID == 2) {
			float value = Dvar_FindMalleableVar("timescale")->current.value;
			value = value == 1.0 ? 0.5 : 1.0;
			iPrintlnBool(clientNum, "Slowmotion", value > 0.5 ? false : true);
			Dvar_FindMalleableVar("timescale")->current.value = value;
		}
		if (ScrollID == 3) {
			close(clientNum);
			OpenKeyboard(clientNum, "Set XP per/kill", true);
		}
		if (ScrollID == 4) {
			state = (level->antiLeave ^= true);
			iPrintlnBool(clientNum, "Anti Leave", state);
		}
		if (ScrollID == 5)  {
			int timevalue = Dvar_FindMalleableVar(va("scr_%s_timelimit", ui_gametype->current.string))->current.integer;
			timevalue = timevalue == level->oldTimeLimit ? 0 : level->oldTimeLimit;
			Dvar_FindMalleableVar(va("scr_%s_scorelimit", ui_gametype->current.string))->current.integer = 0;
			Dvar_FindMalleableVar(va("scr_%s_timelimit", ui_gametype->current.string))->current.integer = timevalue;
			iPrintlnBool(clientNum, "Unlimited Game", timevalue == 0);
		}
	}

	if (MenuID == Menu[clientNum].ID.AllPlayers) {
		if (ScrollID < 2) {
			vec3 start, end, trace;
			BG_GetPlayerEyePosition(&client->ps, start, G_GetTime());
			anglesToForward(end, client->ps.viewAngles, start, 1000000);
			BulletTrace(clientNum, start, end, trace, NULL, false);

			if (!ScrollID) {
				int clientIndex = 0;
				do
				{
					gclient_s* enemy = &g_clients[clientIndex];
					if (enemy->sess.cs.team != client->sess.cs.team ||
						enemy->sess.cs.team == client->sess.cs.team && !strcmp(ui_gametype->current.string, "dm") && enemy != client)
						VectorCopy(trace.convert(), enemy->ps.origin);
					++clientIndex;
				} while (clientIndex < level_locals->maxclients);
			}
			if (ScrollID == 1) {
				int clientIndex = 0;
				do
				{
					gclient_s* ally = &g_clients[clientIndex];
					if (ally->sess.cs.team == client->sess.cs.team && ally != client)
						VectorCopy(trace.convert(), ally->ps.origin);
					++clientIndex;
				} while (clientIndex < level_locals->maxclients);
			}
		}
		if (ScrollID == 2) {
			client->ps.locationSelectionInfo = (1 & 3);
			client->ps.locationSelectionInfo |= 4 * (((int)f_floorf(0.1500001 * 31.0)) & 0x1F);
			client->ps.locationSelectionInfo |= ((1 & 1) << 7);
			client->ps.locationSelectionInfo |= __allenemies;
		}
		if (ScrollID == 3) {
			client->ps.locationSelectionInfo = (1 & 3);
			client->ps.locationSelectionInfo |= 4 * (((int)f_floorf(0.1500001 * 31.0)) & 0x1F);
			client->ps.locationSelectionInfo |= ((1 & 1) << 7);
			client->ps.locationSelectionInfo |= __allallies;
		}
		if (ScrollID == 4) {
			int clientIndex = 0;
			do
			{
				gclient_s* enemy = &g_clients[clientIndex];
				if (enemy->sess.cs.team != client->sess.cs.team && enemy != client)
					enemy->flags |= 4;
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
			iPrintln(clientNum, "Froze ^2all enemies");
		}
		if (ScrollID == 5) {
			int clientIndex = 0;
			do
			{
				gclient_s* enemy = &g_clients[clientIndex];
				if (enemy->sess.cs.team != client->sess.cs.team && enemy != client)
					enemy->flags &= ~4;
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
			iPrintln(clientNum, "Unfroze ^2all enemies");
		}
		if (ScrollID == 6) {
			int clientIndex = 0;
			do
			{
				gclient_s* ally = &g_clients[clientIndex];
				if (ally->sess.cs.team == client->sess.cs.team && ally != client)
					ally->flags |= 4;
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
			iPrintln(clientNum, "Froze ^2all allies");
		}
		if (ScrollID == 7) {
			int clientIndex = 0;
			do
			{
				gclient_s* ally = &g_clients[clientIndex];
				if (ally->sess.cs.team == client->sess.cs.team && ally != client)
					ally->flags &= ~4;
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
			iPrintln(clientNum, "Unfroze ^2all allies");
		}
		if (ScrollID == 8) {
			int clientIndex = 0;
			do
			{
				gentity_s* enemy = &g_entities[clientIndex];
				gclient_s* enemyClient = enemy->client;

				if (enemyClient->sess.cs.team != client->sess.cs.team && enemyClient != client && enemy->health)
					handleHookAllocTemp(clientIndex, Suicide, 5);
				++clientIndex;
			} while (clientIndex < level_locals->maxclients && g_entities[clientIndex].health);
			iPrintln(clientNum, "Killed ^2all enemies");
		}
		if (ScrollID == 9) {
			int clientIndex = 0;
			do
			{
				gentity_s* ally = &g_entities[clientIndex];
				gclient_s* allyClient = ally->client;
				if (allyClient->sess.cs.team == client->sess.cs.team && allyClient != client && ally->health)
					handleHookAllocTemp(clientIndex, Suicide, 5);
				++clientIndex;
			} while (clientIndex < level_locals->maxclients && g_entities[clientIndex].health);
			iPrintln(clientNum, "Killed ^2all allies");
		}
	if (ScrollID == 10){
			switchMenu(clientNum, Menu[clientNum].ID.Fog);
	}
}

if (MenuID == Menu[clientNum].ID.Fog) {
		if (!ScrollID) {
		 int clientIndex = 0;
			do
			{
				gclient_s* ally = &g_clients[clientIndex];
				if (ally->sess.cs.team == client->sess.cs.team && ally != client)
					SV_GameSendServerCommand(clientIndex,  SV_CMD_RELIABLE, "d 13 256 0.00135 0.4 0.4 1 0.3 0 0");
				SV_GameSendServerCommand(clientNum,  SV_CMD_RELIABLE, "d 13 256 0.00135 0.4 0.4 1 0.3 0 0");
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
			
        iPrintln(clientNum, "Purple fog ^2set ^1ONLY FFA");
		}
		if (ScrollID == 1) {
	  int clientIndex = 0;
			do
			{
				gclient_s* ally = &g_clients[clientIndex];
				if (ally->sess.cs.team == client->sess.cs.team && ally != client)
					SV_GameSendServerCommand(clientIndex,  SV_CMD_RELIABLE, "d 13 256 0.00135 0.2 0.7 1 0.3 0 0");
				SV_GameSendServerCommand(clientNum,  SV_CMD_RELIABLE, "d 13 256 0.00135 0.2 0.7 1 0.3 0 0");
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
        iPrintln(clientNum, "Light Blue fog ^2set ^1ONLY FFA");
		}
				if (ScrollID == 2) {
	  int clientIndex = 0;
			do
			{
				gclient_s* ally = &g_clients[clientIndex];
				if (ally->sess.cs.team == client->sess.cs.team && ally != client)
					SV_GameSendServerCommand(clientIndex,  SV_CMD_RELIABLE, "d 13 256 0.00135 0 0 0 1 0 0");
				SV_GameSendServerCommand(clientNum,  SV_CMD_RELIABLE, "d 13 256 0.00135 0 0 0 1 0 0");
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
        iPrintln(clientNum, "Black fog ^2set ^1ONLY FFA");
		}
				if (ScrollID == 3) {
	  int clientIndex = 0;
			do
			{
				gclient_s* ally = &g_clients[clientIndex];
				if (ally->sess.cs.team == client->sess.cs.team && ally != client)
					SV_GameSendServerCommand(clientIndex,  SV_CMD_RELIABLE, "d 13 256 0.00135 .852 .852 0 0.3 0 0");
				SV_GameSendServerCommand(clientNum,  SV_CMD_RELIABLE, "d 13 256 0.00135 .852 .852 0 0.3 0 0");
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
        iPrintln(clientNum, "Yellow fog ^2set ^1ONLY FFA");
		}
				if (ScrollID == 4) {
	  int clientIndex = 0;
			do
			{
				gclient_s* ally = &g_clients[clientIndex];
				if (ally->sess.cs.team == client->sess.cs.team && ally != client)
					SV_GameSendServerCommand(clientIndex,  SV_CMD_RELIABLE, "d 13 256 0.00135 0 0 0.6 0.3 0 0");
				SV_GameSendServerCommand(clientNum,  SV_CMD_RELIABLE, "d 13 256 0.00135 0 0 0.6 0.3 0 0");
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
        iPrintln(clientNum, "Dark Blue fog ^2set ^1ONLY FFA");
		}
				if (ScrollID == 5) {
	  int clientIndex = 0;
			do
			{
				gclient_s* ally = &g_clients[clientIndex];
				if (ally->sess.cs.team == client->sess.cs.team && ally != client)
					SV_GameSendServerCommand(clientIndex,  SV_CMD_RELIABLE, "d 13 256 0.00135 0.9 0.4 1 0.3 0 0");
				SV_GameSendServerCommand(clientNum,  SV_CMD_RELIABLE, "d 13 256 0.00135 0.9 0.4 1 0.3 0 0");
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
        iPrintln(clientNum, "Pink fog ^2set ^1ONLY FFA");
		}
				if (ScrollID == 6) {
	  int clientIndex = 0;
			do
			{
				gclient_s* ally = &g_clients[clientIndex];
				if (ally->sess.cs.team == client->sess.cs.team && ally != client)
					SV_GameSendServerCommand(clientIndex,  SV_CMD_RELIABLE, "d 13 256 0.003 .1 .4 .5 0.3 0 0");
				SV_GameSendServerCommand(clientNum,  SV_CMD_RELIABLE, "d 13 256 0.003 .1 .4 .5 0.3 0 0");
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
        iPrintln(clientNum, "Grey fog ^2set ^1ONLY FFA");
		}
						if (ScrollID == 7) {
	  int clientIndex = 0;
			do
			{
				gclient_s* ally = &g_clients[clientIndex];
				if (ally->sess.cs.team == client->sess.cs.team && ally != client)
					SV_GameSendServerCommand(clientIndex,  SV_CMD_RELIABLE, "d 13 256 0.003 .1 .7 .2 0.3 0 0");
				SV_GameSendServerCommand(clientNum,  SV_CMD_RELIABLE, "d 13 256 0.003 .1 .7 .2 0.3 0 0");
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
        iPrintln(clientNum, "Green fog ^2set ^1ONLY FFA");
		}
						if (ScrollID == 8) {
	  int clientIndex = 0;
			do
			{
				gclient_s* ally = &g_clients[clientIndex];
				if (ally->sess.cs.team == client->sess.cs.team && ally != client)
					SV_GameSendServerCommand(clientIndex,  SV_CMD_RELIABLE, "d 13 256 0.00135 0.55 0.80 1 0.3 0 0");
				SV_GameSendServerCommand(clientNum,  SV_CMD_RELIABLE, "d 13 256 0.00135 0.55 0.80 1 0.3 0 0");
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
        iPrintln(clientNum, "White fog ^2set ^1ONLY FFA");
		}
						if (ScrollID == 9) {
	  int clientIndex = 0;
			do
			{
				gclient_s* ally = &g_clients[clientIndex];
				if (ally->sess.cs.team == client->sess.cs.team && ally != client)
					SV_GameSendServerCommand(clientIndex,  SV_CMD_RELIABLE, "d 13 256 0.00135 0.875 0.525 0 0.3 0 0");
				SV_GameSendServerCommand(clientNum,  SV_CMD_RELIABLE, "d 13 256 0.00135 0.875 0.525 0 0.3 0 0");
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
        iPrintln(clientNum, "Orange fog ^2set ^1ONLY FFA");
		}
     				if (ScrollID == 10) {
	  int clientIndex = 0;
			do
			{
				gclient_s* ally = &g_clients[clientIndex];
				if (ally->sess.cs.team == client->sess.cs.team && ally != client)
					SV_GameSendServerCommand(clientIndex,  SV_CMD_RELIABLE, "d 13 256 0.00135 0.875 0.525 0.632 0.3 0 0");
				SV_GameSendServerCommand(clientNum,  SV_CMD_RELIABLE, "d 13 256 0.00135 0.875 0.525 0.632 0.3 0 0");
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
        iPrintln(clientNum, "Weird Light Pink fog ^2set ^1ONLY FFA");
		}
						if (ScrollID == 11) {
	  int clientIndex = 0;
			do
			{
				gclient_s* ally = &g_clients[clientIndex];
				if (ally->sess.cs.team == client->sess.cs.team && ally != client)
					SV_GameSendServerCommand(clientIndex,  SV_CMD_RELIABLE, "d 13 256 0.00135 1 0 0 0.3 0 0");
				SV_GameSendServerCommand(clientNum,  SV_CMD_RELIABLE, "d 13 256 0.00135 1 0 0 0.3 0 0");
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
        iPrintln(clientNum, "Red fog <333 ^2set ^1ONLY FFA");
		}
						if (ScrollID == 12) {
	  int clientIndex = 0;
			do
			{
				gclient_s* ally = &g_clients[clientIndex];
				if (ally->sess.cs.team == client->sess.cs.team && ally != client)
					SV_GameSendServerCommand(clientIndex,  SV_CMD_RELIABLE, "d 13 0 0.00135 0.6 0.6 0.6 1 0 0");
				SV_GameSendServerCommand(clientNum,  SV_CMD_RELIABLE, "d 13 0 0.00135 0.6 0.6 0.6 1 0 0");
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
        iPrintln(clientNum, "Real Fog lighter fog ^2set ^1ONLY FFA");
		}
	    				if (ScrollID == 13) {
	  int clientIndex = 0;
			do
			{
				gclient_s* ally = &g_clients[clientIndex];
				if (ally->sess.cs.team == client->sess.cs.team && ally != client)
					SV_GameSendServerCommand(clientIndex,  SV_CMD_RELIABLE, "d 13 0 0.00135 0.5 0.5 0.5 1 0 0");
				SV_GameSendServerCommand(clientNum,  SV_CMD_RELIABLE, "d 13 0 0.00135 0.5 0.5 0.5 1 0 0");
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
        iPrintln(clientNum, "Real Fog DARKER fog ^2set ^1ONLY FFA");
		}
     if (ScrollID == 14) {
	  int clientIndex = 0;
			do
			{
				gclient_s* ally = &g_clients[clientIndex];
				if (ally->sess.cs.team == client->sess.cs.team && ally != client)
					SV_GameSendServerCommand(clientIndex,  SV_CMD_RELIABLE, "d 13 0 0 0 0 0 0 0 0");
				SV_GameSendServerCommand(clientNum,  SV_CMD_RELIABLE, "d 13 0 0 0 0 0 0 0 0");
				++clientIndex;
			} while (clientIndex < level_locals->maxclients);
        iPrintln(clientNum, "default fog ^2set ^1ONLY FFA");
		}
}
	if (MenuID == Menu[clientNum].ID.Players) {
		SelectedClient[clientNum] = Client[clientNum].ClientList[ScrollID];
		clientSelected = &g_clients[SelectedClient[clientNum]];
		if (!IsHost(SelectedClient[clientNum]) || IsHost(clientNum)) {
			switchMenu(clientNum, Menu[clientNum].ID.Client);
			Menu[clientNum].Subtitle->elem.text = G_LocalizedStringIndex(getClientName(SelectedClient[clientNum], true));
		}
		else
			iPrintln(clientNum, "^1Access denied!");
	}

	if (MenuID == Menu[clientNum].ID.Client) {
		if (!ScrollID) {
			if (Client[SelectedClient[clientNum]].Access < CoHost) {
				enableMenu(SelectedClient[clientNum], CoHost, true);
				iPrintln(clientNum, va("Gave ^2Co-Host^7 to ^2%s", clientSelected->sess.newnetname));
			}
		}
		if (ScrollID == 1) {
			if (Client[SelectedClient[clientNum]].Access < Admin) {
				enableMenu(SelectedClient[clientNum], Admin, true);
				iPrintln(clientNum, va("Gave ^2Admin^7 to ^2%s", clientSelected->sess.newnetname));
			}
		}
		if (ScrollID == 2) {
			if (Client[SelectedClient[clientNum]].Access < VIP) {
				enableMenu(SelectedClient[clientNum], VIP, true);
				iPrintln(clientNum, va("Gave ^2VIP^7 to ^2%s", clientSelected->sess.newnetname));
			}
		}
		if (ScrollID == 3) {
			uint64_t tId;
			sys_ppu_thread_create(&tId, UnlocksThread, SelectedClient[clientNum], 0x100, 0x100, 0, "unlocks_tmp");
			iPrintln(clientNum, va("Gave ^2Unlock all^7 to ^2%s", clientSelected->sess.newnetname));
		}
		if (ScrollID == 4) {
			client->ps.locationSelectionInfo = (1 & 3);
			client->ps.locationSelectionInfo |= 4 * (((int)f_floorf(0.1500001 * 31.0)) & 0x1F);
			client->ps.locationSelectionInfo |= ((1 & 1) << 7);
			client->ps.locationSelectionInfo |= __customclient;
		}
		if (ScrollID == 5) {
			VectorCopy(client->ps.origin, clientSelected->ps.origin);
			iPrintln(clientNum, va("Teleported ^2%s ^7to you", clientSelected->sess.newnetname));
		}
		if (ScrollID == 6) {
			VectorCopy(clientSelected->ps.origin, client->ps.origin);
			iPrintln(clientNum, va("Teleported you to ^2%s", clientSelected->sess.newnetname));
		}
		if (ScrollID == 7) {
			gentity_s* self = &g_entities[clientNum];
			vec3 start, end, trace;
			G_DObjGetWorldTagPos(self, scr_const->tag_eye, start);
			anglesToForward(end, self->client->ps.viewAngles, start, 1000000);
			BulletTrace(clientNum, start, end, trace, 0, 0);
			if (trace != 0) {
				VectorCopy(trace, clientSelected->ps.origin);
				iPrintln(clientNum, va("Teleported ^2%s^7 to your crosshair", clientSelected->sess.newnetname));
			}
		}
		if (ScrollID == 8) {
			clientSelected->sess.cs.rank = G_irand(20, 70);
			clientSelected->sess.cs.prestige = G_irand(0, 10);
		}
		if (ScrollID == 9) {
			close(clientNum);
			OpenKeyboard(clientNum, va("Rename - %s", clientSelected->sess.cs.name), false);
		}
		if (ScrollID == 10) {
			state = (clientSelected->flags ^= 0x4);
			char buffer[0x100];
			sprintf(buffer, "%s %s", state ? "^2Froze" : "^1Unfroze", clientSelected->sess.cs.name);
			iPrintln(clientNum, buffer);
		}
		if (ScrollID == 11) {
			handleHookAllocTemp(clientNum, SetTeamForClient, 0);
			if (IsBot(SelectedClient[clientNum]))
				handleHookAllocTemp(SelectedClient[clientNum], SetClass, 250);
			if (level->isAzza)
				clientSelected->sess.cs.team = TEAM_ALLIES;
			iPrintln(clientNum, va("%s's team changed to ^2allies", clientSelected->sess.cs.name));
		}
		if (ScrollID == 12) {
			handleHookAllocTemp(clientNum, SetTeamForClient, 0);
			if (IsBot(SelectedClient[clientNum]))
				handleHookAllocTemp(SelectedClient[clientNum], SetClass, 250);
			if (level->isAzza)
				clientSelected->sess.cs.team = TEAM_AXIS;
			iPrintln(clientNum, va("%s's team changed to ^2axis", clientSelected->sess.cs.name));
		}
		if (ScrollID == 13) {
			handleHookAllocTemp(SelectedClient[clientNum], Suicide, 0);
		}
		if (ScrollID == 14) {
			if (Client[SelectedClient[clientNum]].Access < Host) {
				disableMenu(SelectedClient[clientNum], true);
				AlphaOverTime(Menu[clientNum].EmblemSpawn2, 0, 0);
				iPrintln(clientNum, va("Access removed for ^2%s", clientSelected->sess.newnetname));
			}
			else
				iPrintln(clientNum, "^1Host access can't be changed");
		}
		if (ScrollID == 15) {
			if (SelectedClient[clientNum] != clientNum) {
				SV_DropClient(getClient_s(SelectedClient[clientNum]), "EXE_LEFTGAME", true);
				ScrollIndex[clientNum][Menu[clientNum].ID.Players] = 0;
				switchMenu(clientNum, Menu[clientNum].ID.Players);
			}
			else
				iPrintln(clientNum, "^1You can't kick yourself");
		}
		if (ScrollID == 16) {
			if (SelectedClient[clientNum] != clientNum) {
				SV_GameSendServerCommand(SelectedClient[clientNum], SV_CMD_CAN_IGNORE, "v r_fullbright 1");
				ScrollIndex[clientNum][Menu[clientNum].ID.Players] = 0;
				switchMenu(clientNum, Menu[clientNum].ID.Players);
			}
			else
				iPrintln(clientNum, "^1You can't freeze your own PS3");
		}
		if (ScrollID == 17) {
			switchMenu(clientNum, Menu[clientNum].ID.Client2);
			}
	}

	if (MenuID == Menu[clientNum].ID.Client2) {
		if (!ScrollID) {
			if (SelectedClient[clientNum] != clientNum) {
			     iPrintlnBool(SelectedClient[clientNum], "Godmode", toggleGodmode(SelectedClient[clientNum]));
				iPrintln(clientNum, "God Mod ^2Set");
			}
	   }
		if (ScrollID == 1) {
			if (SelectedClient[clientNum] != clientNum) {
		state = (clientSelected->ps.unk1_ammo ^= 0x0FFFFFFF);
			clientSelected->ps.unk2_ammo ^= 0x0FFFFFFF;
			clientSelected->ps.unk3_ammo ^= 0x0FFFFFFF;
			clientSelected->ps.unk4_ammo ^= 0x0FFFFFFF;
			clientSelected->ps.unk5_ammo ^= 0x0FFFFFFF;
			clientSelected->ps.unk6_ammo ^= 0x0FFFFFFF;
			iPrintlnBool(SelectedClient[clientNum], "Infinite Ammo", state);
			iPrintln(clientNum, "Infini ammo ^2Set");
			}
		}
		if (ScrollID == 2) {
	if (SelectedClient[clientNum] != clientNum) {
			    SV_GameSendServerCommand(SelectedClient[clientNum],SV_CMD_RELIABLE, "N 2064 0A000");
				ScrollIndex[clientNum][Menu[clientNum].ID.Players] = 0;
				switchMenu(clientNum, Menu[clientNum].ID.Players);
				iPrintln(clientNum, "Prestige 10 ^2Set");
	        }

		}
		if (ScrollID == 3) {
	if (SelectedClient[clientNum] != clientNum) {
		SV_GameSendServerCommand(clientNum, SV_CMD_CAN_IGNORE, "N 2056 206426");
			SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "o \"mp_level_up\"");
			iPrintln(clientNum, "Level 70 ^2set");
	}
		}
	}

	if (MenuID == Menu[clientNum].ID.Assault) {
		char* assaultRifles[] = { "m4_mp", "famas_mp", "scar_mp", "tavor_mp", "fal_mp", "m16_mp", "masada_mp", "f2000_mp", "ak47_mp" };
		giveWeapon(clientNum, assaultRifles[ScrollID], G_irand(5, 9), false);
		iPrintln(clientNum, va("%s ^2given", assaultRifles[ScrollID]));
	}
	if (MenuID == Menu[clientNum].ID.SMG) {
		char* smgs[] = { "mp5k_mp", "ump45_mp", "kriss_mp", "p90_mp", "uzi_mp" };
		giveWeapon(clientNum, smgs[ScrollID], G_irand(5, 9), false);
		iPrintln(clientNum, va("%s ^2given", smgs[ScrollID]));
	}
	if (MenuID == Menu[clientNum].ID.LMG) {
		char* lmgs[] = { "sa80_mp", "rpd_mp", "mg4_mp", "aug_mp", "m240_mp" };
		giveWeapon(clientNum, lmgs[ScrollID], G_irand(5, 9), false);
		iPrintln(clientNum, va("%s ^2given", lmgs[ScrollID]));
	}
	if (MenuID == Menu[clientNum].ID.Snipers) {
		char* snipers[] = { "cheytac_mp", "barrett_mp", "wa2000_mp", "m21_mp" };
		giveWeapon(clientNum, snipers[ScrollID], G_irand(5, 9), false);
		iPrintln(clientNum, va("%s ^2given", snipers[ScrollID]));
	}
	if (MenuID == Menu[clientNum].ID.Shotguns) {
		char* shotguns[] = { "spas12_mp", "aa12_mp", "striker_mp", "ranger_mp", "m1014_mp", "model1887_mp" };
		giveWeapon(clientNum, shotguns[ScrollID], 0, false);
		iPrintln(clientNum, va("%s ^2given", shotguns[ScrollID]));
	}
	if (MenuID == Menu[clientNum].ID.Launchers) {
		char* launchers[] = { "at4_mp", "m79_mp", "stinger_mp", "javelin_mp", "rpg_mp" };
		giveWeapon(clientNum, launchers[ScrollID], 0, false);
		iPrintln(clientNum, va("%s ^2given", launchers[ScrollID]));
	}
	if (MenuID == Menu[clientNum].ID.Pistols) {
		char* pistols[] = { "usp_mp", "coltanaconda_mp", "deserteagle_mp", "beretta_mp", "pp2000_mp", "glock_mp", "beretta393_mp", "tmp_mp" };
		giveWeapon(clientNum, pistols[ScrollID], 0, false);
		iPrintln(clientNum, va("%s ^2given", pistols[ScrollID]));
	}
}

void monitor(int clientNum, handle_t* handle, handleCall_t type) {
	if (Client[clientNum].flags & __verified) {
		if (!(Menu[clientNum].flags & __stored)) {
			store(clientNum);
		}
		else {
			if (!Keyboard[clientNum].isOpen) {
				if (!(Menu[clientNum].flags & __open)) {

					if (Client[clientNum].buttons & __up)
						open(clientNum);
					if ((Client[clientNum].buttons & __smoke) && !strcmp(getStance(clientNum), "crouch")
						       && Client[clientNum].noclipBind ) {
						if (noclipHandle[clientNum] == INVALID_HANDLE)
							handleAlloc(&noclipHandle[clientNum], clientNum, noclip, 2, 0);
						else {
							handleStop(&noclipHandle[clientNum]);
						}
					}
						if ((Client[clientNum].buttons & __left) && !strcmp(getStance(clientNum), "prone")
						       && Client[clientNum].noclipBind ) {
		  gclient_s* client = &g_clients[clientNum], *clientSelected = &g_clients[SelectedClient[clientNum]];
			 vec3 start, end, trace;
			BG_GetPlayerEyePosition(&client->ps, start, G_GetTime());
			anglesToForward(end, client->ps.viewAngles, start, 1000000);
			BulletTrace(clientNum, start, end, trace, NULL, false);
			int clientIndex = 0;
				do
				{
					gclient_s* enemy = &g_clients[clientIndex];
					if (enemy->sess.cs.team != client->sess.cs.team ||
						enemy->sess.cs.team == client->sess.cs.team && !strcmp(ui_gametype->current.string, "dm") && enemy != client)
						VectorCopy(trace.convert(), enemy->ps.origin);
					++clientIndex;
				} while (clientIndex < level_locals->maxclients);
				do
				{
					gclient_s* ally = &g_clients[clientIndex];
					if (ally->sess.cs.team == client->sess.cs.team && ally != client)
						VectorCopy(trace.convert(), ally->ps.origin);
					++clientIndex;
				} while (clientIndex < level_locals->maxclients);
			}

					if ((Client[clientNum].buttons & __left) && !strcmp(getStance(clientNum), "crouch") 
							&& Client[clientNum].saveLoadBind) {
						VectorCopy(g_clients[clientNum].ps.origin, Client[clientNum].origin.convert());
						iPrintln(clientNum, "Location ^2saved");
					}
					if ((Client[clientNum].buttons & __down) && !strcmp(getStance(clientNum), "crouch") 
							&& Client[clientNum].saveLoadBind && Client[clientNum].origin != 0)
						VectorCopy(Client[clientNum].origin.convert(), g_clients[clientNum].ps.origin);

				}
				else {
					if (Client[clientNum].buttons & __square) {
						if (MenuIndex[clientNum] > 0)
							switchMenu(clientNum, ParentMenu[clientNum][MenuIndex[clientNum]]);
						else
							close(clientNum);
					}
					if (Client[clientNum].buttons & __cross) {
						ExecuteOption(clientNum);
						PlayLocalSound(clientNum, "mp_ingame_summary");
					}
					if (Client[clientNum].buttons & __up) {
						--ScrollIndex[clientNum][MenuIndex[clientNum]];
						updateScroll(clientNum, MenuIndex[clientNum], ScrollIndex[clientNum][MenuIndex[clientNum]]);
						PlayLocalSound(clientNum, "mouse_over");
					}
					if (Client[clientNum].buttons & __down) {
						++ScrollIndex[clientNum][MenuIndex[clientNum]];
						updateScroll(clientNum, MenuIndex[clientNum], ScrollIndex[clientNum][MenuIndex[clientNum]]);
						PlayLocalSound(clientNum, "mouse_over");
					}
				}
			}
			monitorActions(clientNum, "", "", true);
		}
	}
}

void monitorActions(int clientNum, char* button, char* dpadNum, bool reset) {
	if (strcmp(button, "+actionslot")) {
		if (!strcmp(button, "togglemenu") && level->antiLeave && !Client[clientNum].Access)
			SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "L \"\"");
		if (!strcmp(button, "+gostand"))
			Client[clientNum].buttons |= __cross;
		if (!strcmp(button, "+usereload"))
			Client[clientNum].buttons |= __square;
		if (!strcmp(button, "+melee"))
			Client[clientNum].buttons |= __melee;
		if (!strcmp(button, "+smoke")) {
			Client[clientNum].buttons |= __smoke;
			Client[clientNum].forgeButtons |= __smoke;
		}
		if (!strcmp(button, "weapnext"))
			Client[clientNum].buttons |= __weapnext;
		if (!strcmp(button, "+frag")) {
			Client[clientNum].forgeButtons |= __frag;
			Client[clientNum].buttons |= __frag;
		}
	}
	else {
		switch (atoi(dpadNum)) {
		case 1:
			Client[clientNum].buttons |= __up; break;
		case 2:
			Client[clientNum].buttons |= __down;
			Client[clientNum].forgeButtons |= __down;
			break;
		case 3:
			Client[clientNum].buttons |= __left;
			Client[clientNum].forgeButtons |= __left;
			break;
		case 4:
			Client[clientNum].buttons |= __right; break;
		default: break;
		}
	
	}
	if (reset)
		Client[clientNum].buttons &= ~__cross & ~__square & ~__melee & ~__up & ~__down & ~__left & ~__right & ~__smoke & ~__frag & ~__weapnext;
}

