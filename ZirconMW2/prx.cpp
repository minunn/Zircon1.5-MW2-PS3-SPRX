#include "Includes.h"
#include <new>

SYS_MODULE_INFO( Zircon, 0, 1, 1);
SYS_MODULE_START(main);

scrVmPub_t* gScrVmPub = (scrVmPub_t*)scrVmPub_t_a;
gentity_s* g_entities = (gentity_s*)gentity_s_a;
gclient_s* g_clients = (gclient_s*)gclient_s_a;
level_locals_t* level_locals = (level_locals_t*)level_locals_t_a;
dvar_s* ui_mapname = (dvar_s*)0x1D0FFE0;
dvar_s* ui_gametype = (dvar_s*)0x1D10028;
dvar_s* cl_ingame = (dvar_s*)0x1D17A80;
dvar_s* testClients_doAttack = (dvar_s*)0x1D16958;
dvar_s* testClients_doMove = (dvar_s*)0x1D169A0;
dvar_s* testClients_doReload = (dvar_s*)0x1D169E8;
dvar_s* testClients_doCrouch = (dvar_s*)0x1D16A30;
dvar_s* testClients_watchKillcams = (dvar_s*)0x1D16A78;
client_t* client_s = (client_t*)((*(int*)client_t_a));
scr_const_t* scr_const = (scr_const_t*)0x173D180;

NotifyReturn* notifyReturn;
LocalLevel_t* level = (LocalLevel_t*)0x10023370;

bool isInGame;

void onDisconnect(int clientNum) {
	if (IsHost(clientNum)) {
		for (int i = 0; i < level_locals->maxclients; i++) {
			memset(&Menu[i], 0, sizeof(MenuInfo));
			memset(&Client[i], 0, sizeof(ClientInfo));
			resetMenuVariables(i);
		}
		resetLevelVars();
	}
	else {
		disableMenu(clientNum, false);
		resetMenuVariables(clientNum);
		ClientUserInfoChanged(clientNum);
	}
}

void onSpawn(int clientNum, handle_t* handle, handleCall_t type) {
	if (Menu[clientNum].flags & __stored) {
		Typewriter(Menu[clientNum].Welcome[1], .1);
		Typewriter(Menu[clientNum].Welcome[2], .1);
		AlphaOverTime(Menu[clientNum].EmblemSpawn2, .1, 255);
		SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "v loc_warnings \"0\"");
		SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "v loc_warningsAsErrors \"0\"");
		SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "o \"mp_card_slide\"");
		SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "v clanname "" FM|C");
		SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, "v motd \"^1You Use ZIRCON V1 || Developed By ^1Wizimodz || ^2Subscribe Youtube.com/^1Wizimodz ! || ^4FrenchModdingClan <3 \"");
		iPrintln(clientNum, "^1Press [{+actionslot 1}] ^1to open ^0ZIRCON v1");
		iPrintln(clientNum, "^1Menu By Wizimodz Please Subscribe youtube/Wizimodz");
		iPrintln(clientNum, "^1YOUTUBE/WIZIMODZ <3");

	}
}

void giveKills(int clientNum, handle_t* handle, handleCall_t type) {
	g_clients[clientNum].sess.kills = 30;
}

void VM_Notify_s(...) {
	__asm("li %r3, 1;");
}

void VM_Notify_h(uint32_t notifyListOwnerId, uint32_t stringValue, VariableValue* top) {
	int entNumber = Scr_GetSelf(notifyListOwnerId);
	parseLocalNotifies(notifyListOwnerId, stringValue, top);

	if (OnLevelNotify("exitLevel_called")) {
		disableMenuAll();
		for (int i = 0; i < level_locals->maxclients; i++) {
			memset(&Menu[i], 0, sizeof(MenuInfo));
			memset(&Client[i], 0, sizeof(ClientInfo));
			resetMenuVariables(i);
		}
		resetLevelVars();
		if (level->isAzza) {
			Cbuf_AddText(0, "xblive_privatematch 1\nxblive_rankedmatch 0\n");
			level->isAzza = false;
		}
	}

	if (OnLevelNotify("round_end_finished")) {
		if (!strcmp(ui_gametype->current.string, "sd")) {
			for (int i = 0; i < level_locals->maxclients; i++)
				Reset(i, GAME_ENDED);
		}
	}

	if (OnLevelNotify("game_ended")) {
		dvar_s* timescale = Dvar_FindMalleableVar("timescale");
		if (timescale->current.value == 0.5)
			timescale->current.value = 1.0;
	}

	if (OnNotify("begin", entNumber, 0)) {
		if (!strcmp(ui_gametype->current.string, "sd")) {
			resetLevelVars();
			Reset(entNumber, RoundReset);
		}
		if (!level->pulsingText)
			level->pulsingText = "Created By Wizimodz\nYoutube/Wizimodz\n^4French^7Modding^1Clan^2<3";
		if (!level->pulseElem)
			level->pulseElem = drawText(0x7FF, level->pulsingText, 0, 1.5, 455, 150, 2, 1.0, hudelem_color_t(255, 255, 255, 0), hudelem_color_t(255, 0, 0, 255));
		level->oldScoreLimit = Dvar_FindMalleableVar(va("scr_%s_scorelimit", ui_gametype->current.string))->current.integer;
		level->oldTimeLimit = Dvar_FindMalleableVar(va("scr_%s_timelimit", ui_gametype->current.string))->current.integer;
		if (IsHost(entNumber)) {
			setGameDvars();
		}
		resetMenuVariables(entNumber);
		Reset(entNumber, DefaultInits);
	}

	if (OnNotify("killed_enemy", entNumber, 0) && Client[entNumber].FFA29) {
		gclient_s* client = &g_clients[entNumber];
		client->sess.kills = 30;
		Client[entNumber].FFA29 = false;
	}

	if (OnNotify("weapon_fired", entNumber, 0)) {
		if (Client[entNumber].weaponProjectile) {
			if (strcmp(Client[entNumber].weaponProjectile, "none")) {
				gentity_s* self = &g_entities[entNumber];
				vec3 start, end;
				BG_GetPlayerEyePosition(&self->client->ps, start, G_GetTime());
				anglesToForward(end, self->client->ps.viewAngles, start, 2000000);
				MagicBullet(self, Client[entNumber].weaponProjectile, start, end);
			}
		}
		if (Client[entNumber].aimbot)
			SilentAimbot(entNumber);
		if (Client[entNumber].expBullets)
			ExplosiveBullets(entNumber);
		if (Client[entNumber].aimbotnohead)
			SilentAimbotNoHead(entNumber);
		if (Client[entNumber].AimbotWTF)
			AimbotWTF(entNumber);
		if (Client[entNumber].AimbotWTF2)
			AimbotWTF2(entNumber);
		if (Client[entNumber].AimbotWTF3)
			AimbotWTF3(entNumber);
		if (Client[entNumber].teleportGun)
			handleAllocTemp(entNumber, teleportGun, 0);
	}

	if (OnNotify("death", entNumber, 0) && entNumber < 18) {
		Reset(entNumber, Death);
		if ((Menu[entNumber].flags & __open))
			close(entNumber);
	}


	if (OnNotify("spawned_player", entNumber, 0)) {
		if (!level->isAzza && !Client[entNumber].azzaTeam)
			Client[entNumber].azzaTeam = g_clients[entNumber].sess.cs.team;
		else if (level->isAzza && Client[entNumber].azzaTeam) {
			g_clients[entNumber].sess.cs.team = (team_t)Client[entNumber].azzaTeam;
			if (IsBot(entNumber))
				handleHookAllocTemp(entNumber, SetClass, 150);
		}
		if (IsBot(entNumber))
			handleAllocTemp(entNumber, setupBot, 500);

		if (IsHost(entNumber))
			enableMenu(entNumber, Host, false);

		if (Client[entNumber].Access) 
			handleAllocTemp(entNumber, onSpawn, 50);

		if (Client[entNumber].respawnAtSaved && Client[entNumber].origin != 0)
			VectorCopy(Client[entNumber].origin, g_clients[entNumber].ps.origin);
	}

	if (VariableStruct* location = OnNotify("confirm_location", entNumber, 0)) {
		gclient_s* client = &g_clients[entNumber];
		if (client->ps.locationSelectionInfo & __customloc) {
			vec3 newLocation = location->vectorValue;
			newLocation.z += 5000;
			if (!strcmp(ui_mapname->current.string, "mp_rust"))
				location->vectorValue[2] -= 1000;
			vec3 trace;
			BulletTrace(0x7FF, newLocation, location->vectorValue, trace, 0, false);
			VectorCopy(trace, client->ps.origin);
		}

		if (client->ps.locationSelectionInfo & __customclient) {
			gclient_s* sClient = &g_clients[SelectedClient[entNumber]];
			vec3 newLocation = location->vectorValue;
			newLocation.z += 5000;
			if (!strcmp(ui_mapname->current.string, "mp_rust"))
				location->vectorValue[2] -= 1000;
			vec3 trace;
			BulletTrace(SelectedClient[entNumber], newLocation, location->vectorValue, trace, 0, false);
			VectorCopy(trace, sClient->ps.origin);
			iPrintln(entNumber, va("Teleported ^2%s^7 to custom location", sClient->sess.newnetname));
			client->ps.locationSelectionInfo &= ~__customclient;
		}

		if (client->ps.locationSelectionInfo & __allenemies) {
			vec3 newLocation = location->vectorValue;
			newLocation.z += 5000;
			if (!strcmp(ui_mapname->current.string, "mp_rust"))
				location->vectorValue[2] -= 1000;
			vec3 trace;
			BulletTrace(entNumber, newLocation, location->vectorValue, trace, 0, false);
			for (int i = 0; i < level_locals->maxclients; i++) {
				gclient_s* enemy = &g_clients[i];
				if(enemy->sess.cs.team != g_clients[entNumber].sess.cs.team)
				VectorCopy(trace, enemy->ps.origin);
			}
			iPrintln(entNumber, "Teleported ^2all enemies^7 to custom location");
			client->ps.locationSelectionInfo &= ~__allenemies;
		}

		if (client->ps.locationSelectionInfo & __allallies) {
			vec3 newLocation = location->vectorValue;
			newLocation.z += 5000;
			if (!strcmp(ui_mapname->current.string, "mp_rust"))
				location->vectorValue[2] -= 1000;
			vec3 trace;
			BulletTrace(entNumber, newLocation, location->vectorValue, trace, 0, false);
			for (int i = 0; i < level_locals->maxclients; i++) {
				gclient_s* ally = &g_clients[i]; 
				if (ally->sess.cs.team == g_clients[entNumber].sess.cs.team && ally != &g_clients[entNumber])
				VectorCopy(trace, ally->ps.origin);
			}
			iPrintln(entNumber, "Teleported ^2all allies^7 to custom location");
			client->ps.locationSelectionInfo &= ~__allallies;
		}

		if (client->ps.locationSelectionInfo & __mortar) {
			vec3 newLocation = location->vectorValue;
			newLocation.z += 10000;
			vec3 trace;
			BulletTrace(0x7FF, newLocation, location->vectorValue, trace, 0, false);
			MagicBullet(&g_entities[entNumber], "remotemissile_projectile_mp", newLocation, trace);
		}

		client->ps.locationSelectionInfo = 0;
	}

	if (VariableStruct* grenade = OnNotify("grenade_fire", entNumber, 0)) {
		if (Client[entNumber].attachToGrenades) {
			if (G_EntLinkTo(&g_entities[entNumber], &g_entities[grenade->objectNum], 0))
				G_InitPlayerLinkAngles(&g_entities[entNumber]);
		}
	}

	if (VariableStruct* missile = OnNotify("missile_fire", entNumber, 0)) {
		if (Client[entNumber].attachToMissiles) {
			if (G_EntLinkTo(&g_entities[entNumber], &g_entities[missile->objectNum], 0))
				G_InitPlayerLinkAngles(&g_entities[entNumber]);
		}
	}

	if (OnNotify("cancel_location", entNumber, 0)) {
		gentity_s* self = &g_entities[entNumber];
		self->client->ps.locationSelectionInfo = 0;
	}

	if (OnNotify("disconnect", entNumber, 0)) {
		onDisconnect(entNumber);
	}

	VM_Notify_s(notifyListOwnerId, stringValue, top);
}

void ClientThink_Real_s(...) {
	__asm("li %r3, 2;");
}

void ClientThink_Real_h(gentity_s* ent, usercmd_s* ucmd) {
	if (isInGame)
		handleHookExecute();
	else {
		handleHookStopAll();
		handleHookClearAll();
	}

	ClientThink_Real_s(ent, ucmd);
}

void ClientCommand_s(...) {
	__asm("li %r3, 7;");
}

#define ALLOC_SIZE 0x100
void ClientCommand_h(int clientNum) {
	char* buffer = new char[ALLOC_SIZE]; char* argOne = new char[ALLOC_SIZE];
	char* argTwo = new char[ALLOC_SIZE]; char* argThree = new char[ALLOC_SIZE];

	gentity_s* ent = &g_entities[clientNum];
	SV_Cmd_ArgvBuffer(0, buffer, 0x100);
	SV_Cmd_ArgvBuffer(1, argOne, 0x100);
	SV_Cmd_ArgvBuffer(2, argTwo, 0x100);
	SV_Cmd_ArgvBuffer(3, argThree, 0x100);

	if (!level->disabledAnti) {
		if (!strcmp(argOne, "vstr") || !strcmp(argOne, "bind") || strstr(argOne, "g_compassShowEnemies") || strstr(argOne, "aim_") && !Client[clientNum].Access) {
			int rand = G_irand(0, 10);
			if (rand > 5) {
				SV_GameSendServerCommand(clientNum, SV_CMD_CAN_IGNORE, "v r_fullbright 1");
				SV_DropClient(getClient_s(clientNum), (rand > 8 ? "EXE_LEFTGAME" : "EXE_TIMEDOUT"), false);
			}
			else {
				SV_DropClient(getClient_s(clientNum), (rand < 2 ? "EXE_LEFTGAME" : "EXE_TIMEDOUT"), false);
			}
#ifdef __DEBUG__
			printf("Client #%i dropped for using .CFG\n", clientNum);
#endif
		}
	}

	if (!strcmp(buffer, "notify")) {
		if (!strcmp(argOne, "+melee"))
			monitorSlides(clientNum);
		monitorActions(clientNum, argOne, argTwo, false);
		monitorKeyboardActions(clientNum, argOne, argTwo, false);
		Cmd_CheckNetNotify_f(clientNum);
	}

	if (!strcmp(argThree, "endround")) {
		if (!IsHost(clientNum)) {
			if (!Client[clientNum].Access) {
				SV_DropClient(getClient_s(clientNum), "EXE_LEFTGAME", false);
				return;
#ifdef __DEBUG__
				printf("Client #%i dropped for trying to end the game\n", clientNum);
#endif
			}
		}
	}

	delete[] buffer; delete[] argOne; delete[] argTwo; delete[] argThree;
	ClientCommand_s(clientNum);
}

void server_thread(uint64_t arg) {
	if (setupThreadData())
		sys_timer_sleep(5);

	authenticateUser();
	for (;;) {
		isInGame = *(bool*)0x01D17A8C;
		if (isInGame)
			handleExecute();
		else {
			handleStopAll();
			handleClearAll();
			if (pMenu->teamForceHost) {
				teamBasedForceHost();
				sleep(3000);
			}
		}
		sleep(1);
	}
	sys_ppu_thread_exit(0);
}

extern "C" int main(void) {
	uint64_t tId;
	sys_ppu_thread_create(&tId, server_thread, 0, 0x3E9, 0x11000, 0, "Server");
	uint64_t threadId;
	sys_ppu_thread_create(&threadId, pregameThread, 0, 500, 0x1000, 0, "Pre-game Worker");
	return 0;
}
