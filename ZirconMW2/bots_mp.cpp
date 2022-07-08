#include "Includes.h"

opd_s SV_AddTestClient_t = { SV_AddTestClient_a, TOC };
opd_s SV_GetGuid_t = { 0x218E28, TOC };
char*(*SV_GetGuid)(int clientNum) = (char*(*)(int))&SV_GetGuid_t;
gentity_s*(*SV_AddTestClient)() = (gentity_s*(*)())&SV_AddTestClient_t;

int getAmountOnTeam(team_t team) {
	int count = 0;
	for (int i = 0; i < level_locals->maxclients; i++) {
		gclient_s* client = &g_clients[i];
		if (client->sess.cs.team == team)
			++count;
	}
	return count;
}

void SetTeam(int botNum, handle_t* handle, handleCall_t type) {
	gclient_s* bot = &g_clients[botNum];
	if (strcmp(ui_gametype->current.string, "dm")) {
		if (!level->botTeamIndex) {
			if (level->spawnerClient->sess.cs.team == TEAM_AXIS) {
				Scr_AddString("allies");
				bot->sess.cs.team = TEAM_ALLIES;
				Client[botNum].azzaTeam = TEAM_ALLIES;
			}
			else if (level->spawnerClient->sess.cs.team == TEAM_ALLIES) {
				Scr_AddString("axis");
				bot->sess.cs.team = TEAM_AXIS;
				Client[botNum].azzaTeam = TEAM_AXIS;
			}
		}
		else if (level->botTeamIndex == 1) {
			if (level->spawnerClient->sess.cs.team == TEAM_AXIS) {
				Scr_AddString("axis");
				bot->sess.cs.team = TEAM_AXIS;
				Client[botNum].azzaTeam = TEAM_AXIS;
			}
			else if (level->spawnerClient->sess.cs.team == TEAM_ALLIES) {
				Scr_AddString("allies");
				bot->sess.cs.team = TEAM_ALLIES;
				Client[botNum].azzaTeam = TEAM_ALLIES;
			}
		}
	}
	else {
		Scr_AddString("autoassign");
		bot->sess.cs.team = TEAM_FREE;
		Client[botNum].azzaTeam = TEAM_FREE;
	}
	Scr_AddString("team_marinesopfor");
	Scr_NotifyNum(botNum, CT_ENTITY, scr_const->menuresponse, 2);
}

void SetClass(int botNum, handle_t* handle, handleCall_t type) {
	Scr_AddString("class0");
	Scr_AddString("changeclass");
	Scr_NotifyNum(botNum, CT_ENTITY, scr_const->menuresponse, 2);
}

void setupBot(int botNum, handle_t* handle, handleCall_t type) {
	gclient_s* client = &g_clients[botNum];
	client->sess.cs.rank = 0x45;
	client->sess.cs.prestige = G_irand(0, 11);
	client->sess.emblem = G_irand(0, 251);
	client->sess.title = G_irand(0, 251);
}

void SpawnBots(int botAmount) {
	if (strcmp(ui_gametype->current.string, "dm")) {
		if (!level->botTeamIndex && getAmountOnTeam(TEAM_AXIS) >= 9 || level->botTeamIndex == 1 && getAmountOnTeam(TEAM_ALLIES) >= 9)
			return;
	}
	if (botAmount > level_locals->maxclients)
		botAmount = level_locals->maxclients;
	for (int i = 0; i < botAmount; i++) {
		gentity_s* botent = SV_AddTestClient();
		if (botent) {
			handleHookAllocTemp(botent->s.number, SetTeam, 300);
			handleHookAllocTemp(botent->s.number, SetClass, 600);
			handleAllocTemp(botent->s.number, setupBot, 750);
		}
	}
}

void spawnBots(int arg, handle_t* handle, handleCall_t type) {
	SpawnBots(arg);
}

bool IsBot(int clientNum) {
	return strstr(SV_GetGuid(clientNum), "bot");
}