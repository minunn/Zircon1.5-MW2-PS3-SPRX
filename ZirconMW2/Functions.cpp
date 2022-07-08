#include "Includes.h"

opd_s G_DObjGetWorldTagPos_t = { G_DObjGetWorldTagPos_a, TOC };
opd_s Session_IsHost_t = { Sessions_IsHost_a, TOC };
opd_s G_SoundAliasIndex_t = { G_SoundAliasIndex_a, TOC };
opd_s G_EntLinkTo_t = { G_EntLinkTo_a, TOC };
opd_s G_GetHitLocationString_t = { G_GetHitLocationString_a, TOC };
opd_s BG_GetWeaponNameComplete_t = { BG_GetWeaponNameComplete_a, TOC };
opd_s ClientUserInfoChanged_t = { ClientUserInfoChanged_a, TOC };
opd_s SV_DropClient_t = { SV_DropClient_a, TOC };
opd_s Scr_PlayerDamage_t = { 0x1AEB90, TOC };
opd_s G_Spawn_t = { G_Spawn_a, TOC };
opd_s G_SetModel_t = { G_SetModel_a, TOC };
opd_s G_DObjUpdate_t = { G_DObjUpdate_a, TOC };
opd_s SP_script_model_t = { SP_script_model_a, TOC };
opd_s SV_UnlinkEntity_t = { SV_UnlinkEntity_a, TOC };
opd_s SV_LinkEntity_t = { SV_LinkEntity_a, TOC };
opd_s SV_SetBrushModel_t = { SV_SetBrushModel_a, TOC };
opd_s G_FreeEntity_t = { G_FreeEntity_a, TOC };
opd_s G_SetAngle_t = { G_SetAngle_a, TOC };
opd_s G_SetOrigin_t = { G_SetOrigin_a, TOC };
opd_s G_EntUnlink_t = { G_EntUnlink_a, TOC };
opd_s G_InitPlayerLinkAngles_t = { G_InitPlayerLinkAngles_a, TOC };
opd_s SetClientViewAngle_t = { SetClientViewAngle_a, TOC };
opd_s SV_DObjGetBoneIndex_t = { SV_DObjGetBoneIndex_a, TOC };
opd_s G_AddEvent_t = { G_AddEvent_a, TOC };
opd_s G_EffectIndex_t = { G_EffectIndex_a, TOC };
opd_s G_FindConfigStringIndex_t = { G_FindConfigStringIndex_a, TOC };
opd_s BG_GetWeaponForName_t = { G_GetWeaponForName_a, TOC };
opd_s G_irand_t = { G_irand_a, TOC };
opd_s G_CallSpawnEntity_t = { 0x1B8310, TOC };
opd_s SV_SetGameEndTime_t = { 0x219F90, TOC };
opd_s BG_GetPlayerEyePosition_t = { 0x01ED00, TOC };
opd_s SV_MapRestart_t = { 0x2131A8, TOC };
opd_s Cbuf_AddText_t = { Cbuf_AddText_a, TOC };
opd_s G_GivePlayerWeapon_t = { 0x1C0890, TOC };
opd_s Scr_SetFxAngles_t = { 0x1A9D68, TOC };
opd_s Scr_PlayFxInternal_t = { 0x1A9FC8, TOC };
opd_s G_ModelIndex_t = { 0x1BE0B8, TOC };
opd_s G_SpawnTurret_t = { 0x1C8820, TOC };
opd_s Scr_PrecacheModel_t = { 0x1A21A8, TOC };

opd_s G_LocationalTrace_t = { G_LocationalTrace_a, TOC };
opd_s G_LocationalTracePassed_t = { 0x188418, TOC };
opd_s Trace_GetEntityHitId_t = { Trace_GetEntityHitId_a, TOC };

opd_s SV_Cmd_ArgvBuffer_t = { SV_Cmd_ArgvBuffer_a, TOC };
opd_s Cmd_CheckNotify_t = { Cmd_CheckNetNotify_f_a, TOC };
opd_s SendScoreboard_t = { SendScoreboard_a, TOC };
opd_s Cmd_Where_f_t = { Cmd_Where_f_a, TOC };
opd_s Cmd_CallVote_f_t = { Cmd_Callvote_f_a, TOC };
opd_s Cmd_Vote_f_t = { Cmd_Vote_f_a, TOC };
opd_s Cmd_FollowCycle_f_t = { Cmd_FollowCycle_f_a, TOC };
opd_s Cmd_MenuResponse_f_t = { Cmd_MenuResponse_f_a, TOC };

void(*SV_Cmd_ArgvBuffer)(int, char*, int) = (void(*)(int, char*, int))&SV_Cmd_ArgvBuffer_t;
void(*Cmd_CheckNetNotify_f)(int) = (void(*)(int))&Cmd_CheckNotify_t;
void(*SendScoreboard)(gentity_s*) = (void(*)(gentity_s*))&SendScoreboard_t;
void(*Cmd_Where_f)(gentity_s*) = (void(*)(gentity_s*))&Cmd_Where_f_t;
void(*Cmd_CallVote_f)(gentity_s*) = (void(*)(gentity_s*))&Cmd_CallVote_f_t;
void(*Cmd_Vote_f)(gentity_s*) = (void(*)(gentity_s*))&Cmd_Vote_f_t;
void(*Cmd_FollowCycle_f)(gentity_s*, int) = (void(*)(gentity_s*, int))&Cmd_FollowCycle_f_t;
void(*Cmd_MenuResponse_f)(gentity_s*) = (void(*)(gentity_s*))&Cmd_MenuResponse_f_t;

void(*SV_GameSendServerCommand)(int clientNum, svscmd_type type, const char* cmd) = (void(*)(int, svscmd_type, const char*))SV_GameSendServerCommand_a;
int(*G_DObjGetWorldTagPos)(gentity_s* ent, scr_string_t tagName, float* out) = (int(*)(gentity_s*, scr_string_t, float*))&G_DObjGetWorldTagPos_t;
bool(*Session_IsHost)(int sessionData, int clientNum) = (bool(*)(int, int))&Session_IsHost_t;
int(*G_SoundAliasIndex)(const char* soundName) = (int(*)(const char*))&G_SoundAliasIndex_t;
int(*G_EntLinkTo)(gentity_s* self, gentity_s* parent, short tagName) = (int(*)(gentity_s*, gentity_s*, short))&G_EntLinkTo_t;
int16_t(*G_GetHitLocationString)(hitLocation_t hitLoc) = (int16_t(*)(hitLocation_t))&G_GetHitLocationString_t;
char*(*BG_GetWeaponNameComplete)(Weapon weapon, char* output, size_t maxStringLen) = (char*(*)(Weapon, char*, size_t))&BG_GetWeaponNameComplete_t;
void(*ClientUserInfoChanged)(int clientNum) = (void(*)(int))&ClientUserInfoChanged_t;
void(*SV_DropClient)(int cl, const char* reason, bool tellThem) = (void(*)(int, const char*, bool))&SV_DropClient_t;
dvar_s*(*Dvar_FindMalleableVar)(const char* dvarName) = (dvar_s*(*)(const char*))Dvar_FindMalleableVar_a;
void(*Scr_PlayerDamage)(gentity_s *self, gentity_s *inflictor, gentity_s *attacker, int damage, int dflags, int meansOfDeath, int iweapon, const float *vPoint, const float *vDir, hitLocation_t hitLoc, int timeOffset) = (void(*)(gentity_s*, gentity_s*, gentity_s*, int, int, int, int, const float*, const float*, hitLocation_t, int))&Scr_PlayerDamage_t;
void(*player_die)(gentity_s* self, gentity_s* inflictor, gentity_s* attacker, int damage, int meansOfDeath, int WeaponIndex, const float *vDir, int hitLocation, int psTime) = (void(*)(gentity_s*, gentity_s*, gentity_s*, int, int, int, const float*, int, int))player_die_a;
void(*G_SetModel)(gentity_s* ent, const char* model) = (void(*)(gentity_s*, const char*))&G_SetModel_t;
void(*G_DObjUpdate)(gentity_s* ent, int link) = (void(*)(gentity_s*, int))&G_DObjUpdate_t;
void(*G_FreeEntity)(gentity_s* ent) = (void(*)(gentity_s*))&G_FreeEntity_t;
gentity_s*(*G_Spawn)() = (gentity_s*(*)())&G_Spawn_t;
void(*SV_SetBrushModel)(gentity_s* ent) = (void(*)(gentity_s*))&SV_SetBrushModel_t;
void(*SP_script_model)(gentity_s* ent) = (void(*)(gentity_s*))&SP_script_model_t;
void(*SV_UnlinkEntity)(gentity_s* ent) = (void(*)(gentity_s*))&SV_UnlinkEntity_t;
void(*SV_LinkEntity)(gentity_s* ent) = (void(*)(gentity_s*))&SV_LinkEntity_t;
void(*G_LocationalTrace)(trace_t *results, const float *start, const float *end, int passEntityNum, int contentmask, char *priorityMap) = (void(*)(trace_t*, const float*, const float*, int, int, char*))&G_LocationalTrace_t;
int(*G_LocationalTracePassed)(const float *start, const float *end, int passEntityNum, int passEntityNum1, int contentmask, char *priorityMap) = (int(*)(const float*, const float*, int, int, int, char*))&G_LocationalTracePassed_t;
uint16_t(*Trace_GetEntityHitId)(trace_t* result) = (uint16_t(*)(trace_t*))&Trace_GetEntityHitId_t;
void(*G_SetAngle)(gentity_s* ent, const float* angles) = (void(*)(gentity_s*, const float*))&G_SetAngle_t;
void(*G_SetOrigin)(gentity_s* ent, const float* origin) = (void(*)(gentity_s*, const float*))&G_SetOrigin_t;
void(*G_InitPlayerLinkAngles)(gentity_s* ent) = (void(*)(gentity_s*))&G_InitPlayerLinkAngles_t;
void(*G_EntUnlink)(gentity_s* ent, bool relinking) = (void(*)(gentity_s*, bool))&G_EntUnlink_t;
const char*(*Dvar_GetString)(const char* dvarName) = (const char*(*)(const char*))Dvar_GetString_a;
void(*SetClientViewAngle)(gentity_s* ent, const float* angle) = (void(*)(gentity_s*, const float*))&SetClientViewAngle_t;
int(*SV_DObjGetBoneIndex)(gentity_s* ent, uint16_t tag) = (int(*)(gentity_s*, uint16_t))&SV_DObjGetBoneIndex_t;
void(*G_AddEvent)(gentity_s* ent, unsigned int Event, unsigned int eventParm) = (void(*)(gentity_s*, unsigned int, unsigned int))&G_AddEvent_t;
int(*G_EffectIndex)(const char* name) = (int(*)(const char*))&G_EffectIndex_t;
int(*G_FindConfigStringIndex)(const char* name, int start, const unsigned int max, const int create, const char *errormsg) = (int(*)(const char*, int, const unsigned int, const int, const char*))&G_FindConfigStringIndex_t;
int(*BG_GetWeaponForName)(const char* name) = (int(*)(const char*))&BG_GetWeaponForName_t;
int(*G_CallSpawnEntity)(gentity_s* ent) = (int(*)(gentity_s*))&G_CallSpawnEntity_t;
void(*SV_SetGameEndTime)(int time) = (void(*)(int))&SV_SetGameEndTime_t;
int(*G_irand)(int min, int max) = (int(*)(int, int))&G_irand_t;
void(*BG_GetPlayerEyePosition)(playerState_s* ps, float* origin, int gameTime) = (void(*)(playerState_s*, float*, int))&BG_GetPlayerEyePosition_t;
void(*SV_MapRestart)(int saveGame) = (void(*)(int))&SV_MapRestart_t;
void(*Cbuf_AddText)(int localClientNum, const char* text) = (void(*)(int, const char*))Cbuf_AddText_a;
void(*G_GivePlayerWeapon)(playerState_s* ps, Weapon weapon, char altWeaponIndex, bool isAkimbo) = (void(*)(playerState_s*, Weapon, char, bool))&G_GivePlayerWeapon_t;
void(*Scr_SetFxAngles)(int givenAxisCount, float(*axis)[3], float *angles) = (void(*)(int, float(*)[3], float*))&Scr_SetFxAngles_t;
gentity_s*(*Scr_PlayFxInternal)(int fxId, float* pos, float(*forward)[3], float(*up)[3]) = (gentity_s*(*)(int, float*, float(*)[3], float(*)[3]))&Scr_PlayFxInternal_t;
int(*G_ModelIndex)(const char* modelName) = (int(*)(const char*))&G_ModelIndex_t;
void(*G_SpawnTurret)(gentity_s* ent, const char* weaponInfoName, int useDropPitch) = (void(*)(gentity_s*, const char*, int))&G_SpawnTurret_t;

int G_GetTime() {
	return level_locals->time;
}

int getClient_s(int clientNum) {
	int clientPtr = *(int*)client_t_a;
	return (clientPtr + (clientNum * client_t_size));
}

char* getClientName(int clientNum, bool withAccess) {
	gclient_s* client = &g_clients[clientNum];
	memset((void*)(0x10046200 + (clientNum * 0x100)), 0, 0x100);
	char* nameBuffer = (char*)(0x10046200 + (clientNum * 0x100)); 
	if (withAccess) {
		strcpy(nameBuffer, accessLetters[Client[clientNum].Access]);
		strcat(nameBuffer, client->sess.cs.name);
		return nameBuffer;
	}
	return client->sess.newnetname;
}

void SP_script_origin(gentity_s* mSelf) {
	gentity_s* e = mSelf;
	mSelf->handler = 5;
	mSelf->r.svFlags = 0;
	mSelf->s.eType = 6;
	mSelf->s.lerp.u.player.movementDir = 0x7FF;
	mSelf->s.un1.eventParm2 = 0;
	mSelf->s.lerp.u.missile.flightMode = 0;
	e->s.lerp.pos.trBase[0] = e->r.currentOrigin[0];
	e->s.lerp.pos.trBase[1] = e->r.currentOrigin[1];
	e->s.lerp.pos.trBase[2] = e->r.currentOrigin[2];
	mSelf->s.lerp.pos.trType = TR_STATIONARY;
	e->s.lerp.apos.trBase[0] = e->r.currentAngles[0];
	e->s.lerp.apos.trBase[1] = e->r.currentAngles[1];
	mSelf->s.lerp.apos.trBase[2] = mSelf->r.currentAngles[2];
	e->flags |= 0x20;
	mSelf->s.lerp.apos.trType = TR_STATIONARY;
	mSelf->r.contents = 0;
	SV_LinkEntity(mSelf);
	e->r.svFlags |= 1;
}

void PlayerLinkTo(gentity_s* self, gentity_s* parent) {
	if (G_EntLinkTo(self, parent, 0))
		G_InitPlayerLinkAngles(self);
}

gentity_s* Scr_Spawn(const char* classname, float* origin, int flag) {
	gentity_s* ent = G_Spawn();
	Scr_SetString(&ent->classname, SL_GetString(classname));
	VectorCopy(origin, ent->r.currentOrigin);
	ent->spawnFlags = 0;

	if (G_CallSpawnEntity(ent)) {
		if (flag)
			ent->r.contents = 0;
	
	} 
	else {
		//Here you would call G_FreeEntity but thats a meme in this plugin
#ifdef __DEBUG__
		printf("Failed to spawn entity\n");
#endif
	}

	return ent;
}

float Vec3DistanceSq(float* veca, float* vecb) {
	float x = (vecb[0] - veca[0]);
	float y = (vecb[1] - veca[1]);
	float z = (vecb[2] - veca[2]);
	return f_sqrtf((x * x) + (y * y) + (z * z));
}

bool Scr_Closer(float* startingPoint, float* trueIfCloser, float* falseIfCloser) {
	float firstDistance = Vec3DistanceSq(startingPoint, trueIfCloser);
	float secondDistance = Vec3DistanceSq(startingPoint, falseIfCloser);
	return (firstDistance < secondDistance);
}

void UnlocksThread(uint64_t arg) {
	SV_GameSendServerCommand(arg, SV_CMD_CAN_IGNORE, "f \"^1U^2n^3l^4o^5c^6k^2i^1n^3g ^2a^4l^5l^6 c^2h^4a^7l^3l^2e^1n^6g^5e^2s\"");
	SV_GameSendServerCommand(arg, SV_CMD_CAN_IGNORE, "N 2056 206426");
	sleep(100);
	int index = 3500;
	char buffer[0x200];
	while (index < 5001) {
		sleep(5);
		sprintf(buffer, "N %d 99 %d 99 %d 99 %d 99 %d 99 %d 99 %d 99 %d 99 %d 99 %d 99", index, index + 1, index + 2, index + 3, index + 4, index + 5, index + 6, index + 7, index + 8, index + 9);
		SV_GameSendServerCommand(arg, SV_CMD_CAN_IGNORE, buffer);
		index += 10;
	}
	sleep(1000);
	SV_GameSendServerCommand(arg, SV_CMD_CAN_IGNORE, "f \"^1U^3n^4l^5o^6c^7k ^2a^4l^6l^5: ^2C^1o^3m^4p^5l^6e^1t^2e\"");
	SV_GameSendServerCommand(arg, SV_CMD_RELIABLE, "o \"mp_challenge_complete\"");
	sys_ppu_thread_exit(0);
}

gentity_s* getBrushModel() {
	gentity_s* script_brushmodel = 0;
	for (int i = 0x7FF; i > 18; i--) {
		script_brushmodel = &g_entities[i];
		char* ent_classname = SL_ConvertToString(script_brushmodel->classname);
		scr_const->script_brushmodel;
		if (strstr(ent_classname, "script_brushmodel"))
			return script_brushmodel;
	}
}


int GetBrushModel() {
	const char* MapName = ui_mapname->current.string;
	if (!strcmp(MapName, "mp_afghan")) 
		return 0x1394A00;
	if (!strcmp(MapName, "mp_derail"))  
		return 0x1375880;
	if (!strcmp(MapName, "mp_estate")) 
		return 0x1361100;
	if (!strcmp(MapName, "mp_favela")) 
		return 0x1386E00;
	if (!strcmp(MapName, "mp_highrise")) 
		return 0x138C580;
	if (!strcmp(MapName, "mp_invasion")) 
		return 0x1389380;
	if (!strcmp(MapName, "mp_checkpoint")) 
		return 0x1383480;
	if (!strcmp(MapName, "mp_quarry")) 
		return 0x13AF800;
	if (!strcmp(MapName, "mp_rundown")) 
		return 0x137BA00;
	if (!strcmp(MapName, "mp_rust")) 
		return 0x1352B00;
	if (!strcmp(MapName, "mp_boneyard")) 
		return 0x1321500;
	if (!strcmp(MapName, "mp_nightshift")) 
		return 0x1350A80;
	if (!strcmp(MapName, "mp_subbase")) 
		return 0x136F980;
	if (!strcmp(MapName, "mp_terminal")) 
		return 0x1323F80;
	if (!strcmp(MapName, "mp_underpass")) 
		return 0x137CE00;
	if (!strcmp(MapName, "mp_brecourt")) 
		return 0x132B780;
}


gentity_s* SpawnModel(const char* model, float* origin, bool makeSolid) {
	if (level_locals->num_entities < 0x7FE) {
		gentity_s* ent = G_Spawn();
		VectorCopy(origin, ent->r.currentOrigin);
		ent->spawnFlags = 0;
		G_SetModel(ent, model);
		SP_script_model(ent);
		if (makeSolid) {
			ent->r.bmodel = 4;
			gentity_s* brushmodel = (gentity_s*)GetBrushModel();
			ent->s.surfType = brushmodel->s.surfType;
			int ret = ent->r.contents;
			SV_SetBrushModel(ent);
			ent->r.contents = (ret | ent->r.contents);
		}
		return ent;
	}
	return 0;
}

void SpawnTurret(const char* turretWeapon, float* origin, float* angles) {
	gentity_s* turret = G_Spawn();
	Scr_SetString(&turret->code_classname, SL_GetString("misc_turret"));
	Scr_SetString(&turret->classname, SL_GetString("misc_turret"));
	VectorCopy(origin, turret->r.currentOrigin);
	VectorCopy(angles, turret->r.currentAngles);
	turret->model = G_ModelIndex("weapon_minigun");
	G_SpawnTurret(turret, turretWeapon, 1);
}

void DeletePlatform() {
	if (level->isPlatformSpawned) {
		if (level->Platform[0]) {
			for (int i = 0; i < level->crateCount; i++) {
				if (level->Platform[i])
					handleHookAllocTemp(level->Platform[i]->s.number, handleFreeEntity, 5 * i);
			}
		}
	}
	level->crateCount = 0;
	level->isPlatformSpawned = 0;
}

void SpawnObject(float origin[3]) {
	int object = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_uav_static_mp", newOrigin, true);
		}
	}
}

void SpawnObject2(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_av8b_harrier_jet_mp", newOrigin, true);
		}
	}
}

void SpawnObject3(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_little_bird_armed", newOrigin, true);
		}
	}
}

void SpawnObject4(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_ac130_coop", newOrigin, true);
		}
	}
}

void SpawnObject5(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("sentry_minigun", newOrigin, true);
		}
	}
}

void SpawnObject7(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_b2_bomber", newOrigin, true);
		}
	}
}


void SpawnPlatform(float origin[3]) {
	int crateCount = 0;
	DeletePlatform();
	vec3 newOrigin;
	VectorCopy(origin, level->platformOrigin);
	for (int i = -5; i < 6; i++) {
		for (int x = -3; x < 4; x++) {
			newOrigin(origin[0] + (55 * x), origin[1] + (30 * i), origin[2]);
			level->Platform[level->crateCount] = SpawnModel("com_plasticcase_friendly", newOrigin, true);
			level->crateCount++;
		}
	}
	level->isPlatformSpawned = 1;
}

void setGameDvars() {
	testClients_doMove->current.enabled = false;
	testClients_watchKillcams->current.enabled = false;
}

void switchToPrevious(int clientNum, handle_t* handle, handleCall_t type) {
	SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, va("a %i", Client[clientNum].previousWeapon));
}

bool isSniper(int clientNum) {
	char* weapon = (char*)getCurrentWeapon(clientNum);
	return (strstr(weapon, "cheytac") || strstr(weapon, "barrett") || strstr(weapon, "m21") || strstr(weapon, "wa2000") || strstr(weapon, "fal"));
}

char* randHitLoc() {
	int rand = G_irand(0, 11);
	switch (rand)
	{
		case 0: return "j_neck";
		case 1: return "j_hip_le";
		case 2: return "j_wrist_le";
		case 3: return "j_shoulder_le";
		case 4: return "j_elbow_le";
		case 5: return "j_spinelower";
		case 6: return "j_shoulder_ri";
		case 7: return "j_spineupper";
		case 8: return "j_spine4";
		case 9: return "j_knee_le";
		case 10: return "j_ankle_ri";
	}
}

void SilentAimbot(int clientNum) {
	gentity_s* self = &g_entities[clientNum];
	gclient_s* client = self->client;

	gentity_s* target = 0, *possibleTarget = 0;
	gclient_s* possibleClientTarget = 0;

	for (int i = 0; i < level_locals->maxclients; i++) {
		possibleTarget = &g_entities[i];
		possibleClientTarget = possibleTarget->client;
		if (possibleTarget == self || !possibleTarget->health || client->sess.cs.team == possibleClientTarget->sess.cs.team && strcmp(ui_gametype->current.string, "dm"))
			continue;

		if (Client[clientNum].checkMidair && (client->ps.groundEntityNum != 0x7FF))
			continue;

		if (Client[clientNum].checkSniper && !isSniper(clientNum))
			continue;

		if (Client[clientNum].checkADS && !((client->buttons | client->buttonsSinceLastFrame) & 0x800))
			continue;

		if (Client[clientNum].disableWallbangs && !BulletTracePassed(0x7FF, client->ps.origin, possibleClientTarget->ps.origin, false))
			continue;

		if (!target || Scr_Closer(client->ps.origin, possibleTarget->r.currentOrigin, target->r.currentOrigin))
			target = possibleTarget;
	}

	if (target) {
		int rand = G_irand(0, 10);
		int timeOffset = Client[clientNum].killcamTimer;
		if (timeOffset == 1337) { //Random timers
			int _rand = G_irand(0, 10);
			if (rand >= 5) {
				timeOffset = 100;
				if (rand == 9)
					timeOffset = 43;
			}
			else
				timeOffset = 200;
		}
		vec3 bulletDestination;
		char* hitLoc = randHitLoc();
		if (rand >= 9)
			G_DObjGetWorldTagPos(target, scr_const->j_head, bulletDestination);
		else
			G_DObjGetWorldTagPos(target, SL_GetString(hitLoc), bulletDestination);
		Scr_PlayerDamage(target, self, self, 0x7FFFFFFF, 2, (rand >= 9 ? MOD_HEAD_SHOT : MOD_RIFLE_BULLET), self->client->ps.weapon.data, bulletDestination, bulletDestination, (rand >= 9 ? HITLOC_HEAD : HITLOC_HEAD), timeOffset);
	}
}

void SilentAimbotNoHead(int clientNum) {
	gentity_s* self = &g_entities[clientNum];
	gclient_s* client = self->client;

	gentity_s* target = 0, *possibleTarget = 0;
	gclient_s* possibleClientTarget = 0;

	for (int i = 0; i < level_locals->maxclients; i++) {
		possibleTarget = &g_entities[i];
		possibleClientTarget = possibleTarget->client;
		if (possibleTarget == self || !possibleTarget->health || client->sess.cs.team == possibleClientTarget->sess.cs.team && strcmp(ui_gametype->current.string, "dm"))
			continue;

		if (Client[clientNum].checkMidair && (client->ps.groundEntityNum != 0x7FF))
			continue;

		if (Client[clientNum].checkSniper && !isSniper(clientNum))
			continue;

		if (Client[clientNum].checkADS && !((client->buttons | client->buttonsSinceLastFrame) & 0x800))
			continue;

		if (Client[clientNum].disableWallbangs && !BulletTracePassed(0x7FF, client->ps.origin, possibleClientTarget->ps.origin, false))
			continue;

		if (!target || Scr_Closer(client->ps.origin, possibleTarget->r.currentOrigin, target->r.currentOrigin))
			target = possibleTarget;
	}

	if (target) {
		int rand = G_irand(0, 10);
		int timeOffset = Client[clientNum].killcamTimer;
		if (timeOffset == 1337) { //Random timers
			int _rand = G_irand(0, 10);
			if (rand >= 5) {
				timeOffset = 100;
				if (rand == 9)
					timeOffset = 43;
			}
			else
				timeOffset = 200;
		}
		vec3 bulletDestination;
		char* hitLoc = randHitLoc();
		if (rand >= 9)
			G_DObjGetWorldTagPos(target, scr_const->j_head, bulletDestination);
		else
			G_DObjGetWorldTagPos(target, SL_GetString(hitLoc), bulletDestination);
		Scr_PlayerDamage(target, self, self, 0x7FFFFFFF, 2, (rand >= 9 ? MOD_HEAD_SHOT : MOD_RIFLE_BULLET), self->client->ps.weapon.data, bulletDestination, bulletDestination, (rand >= 9 ? HITLOC_TORSO_UPR : HITLOC_TORSO_UPR), timeOffset);
	}
}

void AimbotWTF(int clientNum) {
	gentity_s* self = &g_entities[clientNum];
	gclient_s* client = self->client;

	gentity_s* target = 0, *possibleTarget = 0;
	gclient_s* possibleClientTarget = 0;

	for (int i = 0; i < level_locals->maxclients; i++) {
		possibleTarget = &g_entities[i];
		possibleClientTarget = possibleTarget->client;
		if (possibleTarget == self || !possibleTarget->health || client->sess.cs.team == possibleClientTarget->sess.cs.team && strcmp(ui_gametype->current.string, "dm"))
			continue;

		if (Client[clientNum].checkMidair && (client->ps.groundEntityNum != 0x7FF))
			continue;

		if (Client[clientNum].checkSniper && !isSniper(clientNum))
			continue;

		if (Client[clientNum].checkADS && !((client->buttons | client->buttonsSinceLastFrame) & 0x800))
			continue;

		if (Client[clientNum].disableWallbangs && !BulletTracePassed(0x7FF, client->ps.origin, possibleClientTarget->ps.origin, false))
			continue;

		if (!target || Scr_Closer(client->ps.origin, possibleTarget->r.currentOrigin, target->r.currentOrigin))
			target = possibleTarget;
	}

	if (target) {
		int rand = G_irand(0, 10);
		int timeOffset = Client[clientNum].killcamTimer;
		if (timeOffset == 1337) { //Random timers
			int _rand = G_irand(0, 10);
			if (rand >= 5) {
				timeOffset = 100;
				if (rand == 9)
					timeOffset = 43;
			}
			else
				timeOffset = 200;
		}
		vec3 bulletDestination;
		char* hitLoc = randHitLoc();
		if (rand >= 9)
			G_DObjGetWorldTagPos(target, scr_const->j_head, bulletDestination);
		else
			G_DObjGetWorldTagPos(target, SL_GetString(hitLoc), bulletDestination);
		Scr_PlayerDamage(target, self, self, 0x7FFFFFFF, 2, (rand >= 9 ? MOD_CRUSH : MOD_CRUSH), self->client->ps.weapon.data, bulletDestination, bulletDestination, (rand >= 9 ? HITLOC_TORSO_UPR : HITLOC_TORSO_UPR), timeOffset);
	}
}

void AimbotWTF2(int clientNum) {
	gentity_s* self = &g_entities[clientNum];
	gclient_s* client = self->client;

	gentity_s* target = 0, *possibleTarget = 0;
	gclient_s* possibleClientTarget = 0;

	for (int i = 0; i < level_locals->maxclients; i++) {
		possibleTarget = &g_entities[i];
		possibleClientTarget = possibleTarget->client;
		if (possibleTarget == self || !possibleTarget->health || client->sess.cs.team == possibleClientTarget->sess.cs.team && strcmp(ui_gametype->current.string, "dm"))
			continue;

		if (Client[clientNum].checkMidair && (client->ps.groundEntityNum != 0x7FF))
			continue;

		if (Client[clientNum].checkSniper && !isSniper(clientNum))
			continue;

		if (Client[clientNum].checkADS && !((client->buttons | client->buttonsSinceLastFrame) & 0x800))
			continue;

		if (Client[clientNum].disableWallbangs && !BulletTracePassed(0x7FF, client->ps.origin, possibleClientTarget->ps.origin, false))
			continue;

		if (!target || Scr_Closer(client->ps.origin, possibleTarget->r.currentOrigin, target->r.currentOrigin))
			target = possibleTarget;
	}

	if (target) {
		int rand = G_irand(0, 10);
		int timeOffset = Client[clientNum].killcamTimer;
		if (timeOffset == 1337) { //Random timers
			int _rand = G_irand(0, 10);
			if (rand >= 5) {
				timeOffset = 100;
				if (rand == 9)
					timeOffset = 43;
			}
			else
				timeOffset = 200;
		}
		vec3 bulletDestination;
		char* hitLoc = randHitLoc();
		if (rand >= 9)
			G_DObjGetWorldTagPos(target, scr_const->j_head, bulletDestination);
		else
			G_DObjGetWorldTagPos(target, SL_GetString(hitLoc), bulletDestination);
		Scr_PlayerDamage(target, self, self, 0x7FFFFFFF, 2, (rand >= 9 ? MOD_CRUSH : MOD_CRUSH), self->client->ps.weapon.data, bulletDestination, bulletDestination, (rand >= 9 ? HITLOC_TORSO_UPR : HITLOC_TORSO_UPR), timeOffset);
	}
}

void AimbotWTF3(int clientNum) {
	gentity_s* self = &g_entities[clientNum];
	gclient_s* client = self->client;

	gentity_s* target = 0, *possibleTarget = 0;
	gclient_s* possibleClientTarget = 0;

	for (int i = 0; i < level_locals->maxclients; i++) {
		possibleTarget = &g_entities[i];
		possibleClientTarget = possibleTarget->client;
		if (possibleTarget == self || !possibleTarget->health || client->sess.cs.team == possibleClientTarget->sess.cs.team && strcmp(ui_gametype->current.string, "dm"))
			continue;

		if (Client[clientNum].checkMidair && (client->ps.groundEntityNum != 0x7FF))
			continue;

		if (Client[clientNum].checkSniper && !isSniper(clientNum))
			continue;

		if (Client[clientNum].checkADS && !((client->buttons | client->buttonsSinceLastFrame) & 0x800))
			continue;

		if (Client[clientNum].disableWallbangs && !BulletTracePassed(0x7FF, client->ps.origin, possibleClientTarget->ps.origin, false))
			continue;

		if (!target || Scr_Closer(client->ps.origin, possibleTarget->r.currentOrigin, target->r.currentOrigin))
			target = possibleTarget;
	}

	if (target) {
		int rand = G_irand(0, 10);
		int timeOffset = Client[clientNum].killcamTimer;
		if (timeOffset == 1337) { //Random timers
			int _rand = G_irand(0, 10);
			if (rand >= 5) {
				timeOffset = 100;
				if (rand == 9)
					timeOffset = 43;
			}
			else
				timeOffset = 200;
		}
		vec3 bulletDestination;
		char* hitLoc = randHitLoc();
		if (rand >= 9)
			G_DObjGetWorldTagPos(target, scr_const->j_head, bulletDestination);
		else
			G_DObjGetWorldTagPos(target, SL_GetString(hitLoc), bulletDestination);
		Scr_PlayerDamage(target, self, self, 0x7FFFFFFF, 2, (rand >= 9 ? MOD_CRUSH : MOD_CRUSH), self->client->ps.weapon.data, bulletDestination, bulletDestination, (rand >= 9 ? HITLOC_TORSO_UPR : HITLOC_TORSO_UPR), timeOffset);
	}
}

void ExplosiveBullets(int clientNum) {
	gentity_s* self = &g_entities[clientNum];
	gclient_s* client = self->client;

	gentity_s* target = 0, *possibleTarget = 0;
	gclient_s* possibleClientTarget = 0;

	for (int i = 0; i < level_locals->maxclients; i++) {
		possibleTarget = &g_entities[i];
		possibleClientTarget = possibleTarget->client;
		if (possibleTarget == self || !possibleTarget->health || client->sess.cs.team == possibleClientTarget->sess.cs.team && strcmp(ui_gametype->current.string, "dm"))
			continue;

		if (Client[clientNum].checkMidair && (client->ps.groundEntityNum != 0x7FF))
			continue;

		if (Client[clientNum].checkSniper && !isSniper(clientNum))
			continue;

		if (Client[clientNum].checkADS && !((client->buttons | client->buttonsSinceLastFrame) & 0x800))
			continue;

		if (Client[clientNum].disableWallbangs && !BulletTracePassed(0x7FF, client->ps.origin, possibleClientTarget->ps.origin, false))
			continue;

		if (!target || Scr_Closer(client->ps.origin, possibleTarget->r.currentOrigin, target->r.currentOrigin))
			target = possibleTarget;
	}
	if (target) {
		vec3 start, end, bulletOrigin;
		BG_GetPlayerEyePosition(&client->ps, start, G_GetTime());
		anglesToForward(end, client->ps.viewAngles, start, 1000000);
		BulletTrace(clientNum, start, end, bulletOrigin, 0, false);
		float distanceTo = Vec3DistanceSq(bulletOrigin, target->client->ps.origin);

		if (distanceTo < Client[clientNum].ebRange) {
			int rand = G_irand(0, 10);
			int timeOffset = Client[clientNum].killcamTimer;
			if (timeOffset == 1337) { //Random timers
				int _rand = G_irand(0, 10);
				if (rand >= 5) {
					timeOffset = 100;
					if (rand >= 9)
						timeOffset = 43;
				}
				else
					timeOffset = 200;
			}
			vec3 bulletDestination;
			char* hitLoc = randHitLoc();
			if (rand >= 9)
				G_DObjGetWorldTagPos(target, scr_const->j_head, bulletDestination);
			else
				G_DObjGetWorldTagPos(target, SL_GetString(hitLoc), bulletDestination);
			if (target->flags & 1)
				target->flags &= ~1;
			Scr_PlayerDamage(target, self, self, 0x7FFFFFFF, 2, (rand >= 9 ? MOD_HEAD_SHOT : MOD_RIFLE_BULLET), self->client->ps.weapon.data, bulletDestination, bulletDestination, (rand >= 9 ? HITLOC_HEAD : HITLOC_TORSO_UPR), timeOffset);
		}
	}
}

void resetXPFFA(int arg, handle_t* handle, handleCall_t type) {
	Cbuf_AddText(0, "set scr_dm_score_kill 50");
}
void resetXPTDM(int arg, handle_t* handle, handleCall_t type) {
	Cbuf_AddText(0, "set scr_war_score_kill 100");
}
void fastLastKill(int arg, handle_t* handle, handleCall_t type) {
	gentity_s* target = &g_entities[arg], *self = &g_entities[Client[arg].FastLast];
	vec3 null;
	player_die(target, self, self, 10000, 0xE, 0, null.convert(), 0, 0);
	if (!strcmp(ui_gametype->current.string, "dm")) {
		self->client->sess.kills = 29;
		Client[Client[arg].FastLast].FFA29 = true;
	}
}

void FastLast(int clientNum) {
	if (!strcmp(ui_gametype->current.string, "dm") || !strcmp(ui_gametype->current.string, "war") || !strcmp(ui_gametype->current.string, "sd")) {
		gclient_s* client = &g_clients[clientNum];
		if (!strcmp(ui_gametype->current.string, "dm")) {
			for (int i = 0; i < level_locals->maxclients; i++) {
				gentity_s* ent = &g_entities[i];
				if (i != clientNum && ent->health) {
					int score = client->sess.score;
					int num = 1450 - score;
					Cbuf_AddText(0, va("set scr_dm_score_kill %i", num));
					Client[i].FastLast = clientNum;
					handleHookAllocTemp(i, fastLastKill, 10);
					handleAllocTemp(i, resetXPFFA, 150);
					return;
				}
			}
		}
		else if (!strcmp(ui_gametype->current.string, "war")) {
			int score = level_locals->teamScores[client->sess.cs.team];
			for (int i = 0; i < level_locals->maxclients; i++) {
				gentity_s* ent = &g_entities[i];
				if (i != clientNum && ent->health && ent->client->sess.cs.team != client->sess.cs.team) {
					int num = 7400 - score;
					Cbuf_AddText(0, va("set scr_war_score_kill %i", num));
					Client[i].FastLast = clientNum;
					handleHookAllocTemp(i, fastLastKill, 10);
					handleAllocTemp(i, resetXPTDM, 150);
					return;
				}
			}
		}
		else {
			int playerCount = 0;
			for (int i = 0; i < level_locals->maxclients; i++) {
				gentity_s* ent = &g_entities[i];
				if (i != clientNum && ent->health &&
						ent->client->sess.cs.team != client->sess.cs.team) {
					++playerCount;
				}
			}
			for (int i = 0; i < level_locals->maxclients; i++) {
				gentity_s* ent = &g_entities[i];
				if (i != clientNum && ent->health &&
					ent->client->sess.cs.team != client->sess.cs.team) {
					handleHookAllocTemp(i, fastLastKill, 10);
					--playerCount;
				}
				if (playerCount < 2) 
					break;
			}
		}
	}
	else
		iPrintln(clientNum, "^1Fast Last is only supported in SnD, FFA, & TDM");
}

void resetLevelVars() {
	level->pulsingText = "Created By Wizimodz\nYoutube/Wizimodz\n^4French^7Modding^1Clan^2<3";
	level->doHeart = INVALID_HANDLE;
	level->slideCount = 0;
	level->pulseElem = NULL;
	level->antiLeave = false;
	level->isPlatformSpawned = 0;
}

void monitorSlides(int clientNum) {
	gclient_s* client = &g_clients[clientNum];
	for (int i = 0; i < level->slideCount; i++) {
		if (Vec3DistanceSq(client->ps.origin, level->Slides[i]->r.currentOrigin) < 75) {
			vec3 velocity = client->ps.velocity;
			vec3 angles;
			AngleVectors(client->ps.viewAngles, angles, 0, 0);
			vec3 newVelocity(velocity.x + (angles.x * 1000), velocity.y + (angles.y * 1000), velocity.z + 1500);
			VectorCopy((float*)&newVelocity, client->ps.velocity);
		}
	}
}

void SetTeamForClient(int arg, handle_t* handle, handleCall_t type) {
	if(ScrollIndex[arg][Menu[arg].ID.Client] == 11)
		Scr_AddString("allies");
	else if(ScrollIndex[arg][Menu[arg].ID.Client] == 12)
		Scr_AddString("axis");
	Scr_AddString("team_marinesopfor");
	Scr_NotifyNum(SelectedClient[arg], CT_ENTITY, scr_const->menuresponse, 2);
}

	void SetPrestige(int clientNum,int prestige) {
	SV_GameSendServerCommand(SelectedClient[clientNum],SV_CMD_RELIABLE, "N 2064 0A000");
}

	bool RB[18];
	void RedBoxes(int clientNum)
	{
		if(RB[clientNum] == false)
		{
			*(char*)(0x014E2213 + 0x3700 * clientNum) = 0x55;
			iPrintln(clientNum, "RedBoxes ^2ON");
			RB[clientNum] = true;
		}
		else
		{
			*(char*)(0x014E2213 + 0x3700 * clientNum) = 0x00;
			iPrintln(clientNum, "RedBoxes ^1OFF");
			RB[clientNum] = false;
		}
	}

		bool BIND[18];
	void NightVision(int clientNum)
	{
		if(BIND[clientNum] == false)
		{
			*(char*)(0x14E265B + 0x3700 * clientNum) = 0xFF;
		iPrintln(clientNum, "NightVision ^2ON");
			BIND[clientNum] = true;
		}
		else
		{
			*(char*)(0x14E265B + 0x3700 * clientNum) = 0x02;
			iPrintln(clientNum, "NightVision ^1OFF");
			BIND[clientNum] = false;
		}
	}

	void SpawnObject8(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("test_sphere_silver", newOrigin, true);
		}
	}
}

	void SpawnObject9(float origin[3]) {
	int crateCount = 1;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("furniture_blowupdoll01", newOrigin, true);
		}
	}
}

	void SpawnObject10(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank01", newOrigin, true);
		}
	}
}

void SpawnObject11(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_pacific_bushtree02_animated", newOrigin, true);
		}
	}
}

void SpawnObject12(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_cod5_tree_jungle_02_animated", newOrigin, true);
		}
	}
}

void SpawnObject13(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank02", newOrigin, true);
		}
	}
}

void SpawnObject14(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_barrel_russian_fuel_dirt", newOrigin, true);
		}
	}
}

void SpawnObject15(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_locker_double", newOrigin, true);
		}
	}
}

void SpawnObject16(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_pacific_bushtree02_halfsize_animated", newOrigin, true);
		}
	}
}

void SpawnObject17(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_plasticcase_black_big_us_dirt", newOrigin, true);
		}
	}
}

void SpawnObject18(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_pacific_bushtree01_halfsize_animated", newOrigin, true);
		}
	}
}

void SpawnObject19(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_uaz_open_destructible", newOrigin, true);
		}
	}
}

void SpawnObject20(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_hummer_destructible", newOrigin, true);
		}
	}
}

void SpawnObject21(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_cod5_tree_pine05_large_animated", newOrigin, true);
		}
	}
}

void SpawnObject22(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("utility_transformer_ratnest01", newOrigin, true);
		}
	}
}

void SpawnObject23(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("utility_water_collector", newOrigin, true);
		}
	}
}

void SpawnObject24(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_roofvent2_animated", newOrigin, true);
		}
	}
}

void SpawnObject25(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_filecabinetblackclosed", newOrigin, true);
		}
	}
}

void SpawnObject26(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_tv1_testpattern", newOrigin, true);
		}
	}
}

void SpawnObject27(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("usa_gas_station_trash_bin_02", newOrigin, true);
		}
	}
}

void SpawnObject28(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("prop_photocopier_destructible_02", newOrigin, true);
		}
	}
}

void SpawnObject29(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank01", newOrigin, true);
		}
	}
}

void SpawnObject30(float origin[3]) {
	int crateCount = 0;
		vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_trashbin01", newOrigin, true);
		}
	}
}

void SpawnObject31(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_pickup_destructible_mp", newOrigin, true);
		}
	}
}

void SpawnObject32(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("furniture_gaspump01_damaged", newOrigin, true);
		}
	}
}

void SpawnObject33(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_uaz_winter_destructible", newOrigin, true);
		}
	}
}

void SpawnObject34(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_propane_tank02", newOrigin, true);
		}
	}
}

void SpawnObject35(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("crashed_satellite", newOrigin, true);
		}
	}
}

void SpawnObject36(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_bm21_cover_destructible", newOrigin, true);
		}
	}
}

void SpawnObject37(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_generator", newOrigin, true);
		}
	}
}

void SpawnObject38(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_pickup_destructible_mp", newOrigin, true);
		}
	}
}

void SpawnObject39(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_coupe_white_destructible", newOrigin, true);
		}
	}
}

void SpawnObject40(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_suburban_destructible_dull", newOrigin, true);
		}
	}
}

void SpawnObject41(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_luxurysedan_2008_destructible", newOrigin, true);
		}
	}
}

void SpawnObject42(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_electrical_transformer_large_dam", newOrigin, true);
		}
	}
}

void SpawnObject43(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank01", newOrigin, true);
		}
	}
}

void SpawnObject44(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_filecabinetblackclosed", newOrigin, true);
		}
	}
}

void SpawnObject45(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("ma_flatscreen_tv_on_wallmount_02", newOrigin, true);
		}
	}
}

void SpawnObject46(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("utility_transformer_small01", newOrigin, true);
		}
	}
}

void SpawnObject47(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_small_hatch_white_destructible_mp", newOrigin, true);
		}
	}
}

void SpawnObject48(float origin[3]) {
	int crateCount = 0;
		vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_small_hatch_blue_destructible_mp", newOrigin, true);
		}
	}
}

void SpawnObject49(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_pickup_destructible_mp", newOrigin, true);
		}
	}
}

void SpawnObject50(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("utility_water_collector", newOrigin, true);
		}
	}
}

void SpawnObject51(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_tv2", newOrigin, true);
		}
	}
}

void SpawnObject52(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank01", newOrigin, true);
		}
	}
}

void SpawnObject53(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank02", newOrigin, true);
		}
	}
}

void SpawnObject54(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("utility_transformer_ratnest01", newOrigin, true);
		}
	}
}

void SpawnObject55(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_tree_palm_bushy_3", newOrigin, true);
		}
	}
}

void SpawnObject56(float origin[3]) {
	int crateCount = 0;
		vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_firehydrant", newOrigin, true);
		}
	}
}

void SpawnObject57(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_newspaperbox_red", newOrigin, true);
		}
	}
}

void SpawnObject58(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_newspaperbox_blue", newOrigin, true);
		}
	}
}

void SpawnObject59(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_trashbin01", newOrigin, true);
		}
	}
}

void SpawnObject60(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_trashbin02", newOrigin, true);
		}
	}
}

void SpawnObject61(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("ma_flatscreen_tv_wallmount_01", newOrigin, true);
		}
	}
}

void SpawnObject62(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_trashbin02", newOrigin, true);
		}
	}
}

void SpawnObject63(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_filecabinetblackclosed", newOrigin, true);
		}
	}
}

void SpawnObject64(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("prop_photocopier_destructible_02", newOrigin, true);
		}
	}
}

void SpawnObject65(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank01", newOrigin, true);
		}
	}
}

void SpawnObject66(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank02", newOrigin, true);
		}
	}
}

void SpawnObject67(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_electrical_transformer_large_dam", newOrigin, true);
		}
	}
}

void SpawnObject68(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_roofvent2_animated", newOrigin, true);
		}
	}
}

void SpawnObject69(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_propane_tank02", newOrigin, true);
		}
	}
}

void SpawnObject70(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("highrise_fencetarp_04", newOrigin, true);
		}
	}
}

void SpawnObject71(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("highrise_fencetarp_05", newOrigin, true);
		}
	}
}

void SpawnObject72(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_barrel_benzin", newOrigin, true);
		}
	}
}

void SpawnObject73(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_trashbin01", newOrigin, true);
		}
	}
}

void SpawnObject74(float origin[3]) {
	int crateCount = 0;
		vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_trashbin02", newOrigin, true);
		}
	}
}

void SpawnObject75(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_firehydrant", newOrigin, true);
		}
	}
}

void SpawnObject76(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_newspaperbox_blue", newOrigin, true);
		}
	}
}

void SpawnObject77(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_newspaperbox_red", newOrigin, true);
		}
	}
}

void SpawnObject78(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("furniture_gaspump01_damaged", newOrigin, true);
		}
	}
}

void SpawnObject79(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_80s_wagon1_red_destructible_mp", newOrigin, true);
		}
	}
}

void SpawnObject80(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_hummer_destructible", newOrigin, true);
		}
	}
}

void SpawnObject81(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_taxi_yellow_destructible", newOrigin, true);
		}
	}
}

void SpawnObject82(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_uaz_open_destructible", newOrigin, true);
		}
	}
}

void SpawnObject83(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("utility_transformer_small01", newOrigin, true);
		}
	}
}

void SpawnObject84(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_tree_palm_tall_1", newOrigin, true);
		}
	}
}

void SpawnObject85(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_tree_palm_bushy_1", newOrigin, true);
		}
	}
}

void SpawnObject86(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("prop_photocopier_destructible_02", newOrigin, true);
		}
	}
}

void SpawnObject87(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_filecabinetblackclosed", newOrigin, true);
		}
	}
}

void SpawnObject88(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_firehydrant", newOrigin, true);
		}
	}
}

void SpawnObject89(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_newspaperbox_red", newOrigin, true);
		}
	}
}
void SpawnObject90(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_newspaperbox_blue", newOrigin, true);
		}
	}
}

void SpawnObject91(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_tv1", newOrigin, true);
		}
	}
}

void SpawnObject92(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_moving_truck_destructible", newOrigin, true);
		}
	}
}

void SpawnObject93(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("chicken_black_white", newOrigin, true);
		}
	}
}

void SpawnObject94(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_pacific_bushtree02_animated", newOrigin, true);
		}
	}
}

void SpawnObject95(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_tree_oak_1_animated2", newOrigin, true);
		}
	}
}

void SpawnObject96(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_cod5_tree_jungle_02_animated", newOrigin, true);
		}
	}
}

void SpawnObject97(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_filecabinetblackclosed", newOrigin, true);
		}
	}
}

void SpawnObject98(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_generator", newOrigin, true);
		}
	}
}

void SpawnObject99(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank01", newOrigin, true);
		}
	}
}

void SpawnObject100(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank02", newOrigin, true);
		}
	}
}

void SpawnObject101(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("utility_transformer_small01", newOrigin, true);
		}
	}
}

void SpawnObject102(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_locker_double", newOrigin, true);
		}
	}
}

void SpawnObject103(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_barrel_russian_fuel_dirt", newOrigin, true);
		}
	}
}

void SpawnObject104(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_tv1", newOrigin, true);
		}
	}
}

void SpawnObject105(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_van_green_destructible", newOrigin, true);
		}
	}
}

void SpawnObject106(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_van_white_destructible", newOrigin, true);
		}
	}
}

void SpawnObject107(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_pickup_destructible_mp", newOrigin, true);
		}
	}
}

void SpawnObject108(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_small_hatch_turq_destructible_mp", newOrigin, true);
		}
	}
}

void SpawnObject109(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_uaz_open_destructible", newOrigin, true);
		}
	}
}

void SpawnObject110(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_moving_truck_destructible", newOrigin, true);
		}
	}
}

void SpawnObject111(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("usa_gas_station_trash_bin_02", newOrigin, true);
		}
	}
}

void SpawnObject112(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("prop_photocopier_destructible_02", newOrigin, true);
		}
	}
}

void SpawnObject113(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_tv1", newOrigin, true);
		}
	}
}

void SpawnObject114(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_tv2", newOrigin, true);
		}
	}
}

void SpawnObject115(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_trashbin01", newOrigin, true);
		}
	}
}

void SpawnObject116(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_trashbin02", newOrigin, true);
		}
	}
}

void SpawnObject117(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_trashcan_metal_closed", newOrigin, true);
		}
	}
}

void SpawnObject118(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_small_hatch_white_destructible_mp", newOrigin, true);
		}
	}
}

void SpawnObject119(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_small_hatch_blue_destructible_mp", newOrigin, true);
		}
	}
}

void SpawnObject120(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_uaz_open_destructible", newOrigin, true);
		}
	}
}

void SpawnObject121(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_bm21_mobile_bed_destructible", newOrigin, true);
		}
	}
}

void SpawnObject122(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank01", newOrigin, true);
		}
	}
}

void SpawnObject123(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank02", newOrigin, true);
		}
	}
}

void SpawnObject124(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_firehydrant", newOrigin, true);
		}
	}
}

void SpawnObject125(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_tree_palm_bushy_1", newOrigin, true);
		}
	}
}

void SpawnObject126(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_pacific_fern01_animated", newOrigin, true);
		}
	}
}

void SpawnObject127(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("utility_transformer_small01", newOrigin, true);
		}
	}
}

void SpawnObject128(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("utility_water_collector", newOrigin, true);
		}
	}
}

void SpawnObject129(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("utility_transformer_ratnest01", newOrigin, true);
		}
	}
}

void SpawnObject130(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("chicken_black_white", newOrigin, true);
		}
	}
}

void SpawnObject131(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("chicken_white", newOrigin, true);
		}
	}
}

void SpawnObject132(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_tree_oak_1_animated2", newOrigin, true);
		}
	}
}

void SpawnObject133(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank01", newOrigin, true);
		}
	}
}

void SpawnObject134(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_filecabinetblackclosed", newOrigin, true);
		}
	}
}

void SpawnObject135(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank02", newOrigin, true);
		}
	}
}

void SpawnObject136(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_electrical_transformer_large_dam", newOrigin, true);
		}
	}
}

void SpawnObject137(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_moving_truck_destructible", newOrigin, true);
		}
	}
}

void SpawnObject138(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_pacific_bushtree02_animated", newOrigin, true);
		}
	}
}

void SpawnObject139(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_pickup_destructible_mp", newOrigin, true);
		}
	}
}

void SpawnObject140(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_trashbin02", newOrigin, true);
		}
	}
}

void SpawnObject141(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_bm21_mobile_bed_destructible", newOrigin, true);
		}
	}
}

void SpawnObject142(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_cod5_tree_jungle_02_animated", newOrigin, true);
		}
	}
}

void SpawnObject143(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_firehydrant", newOrigin, true);
		}
	}
}

void SpawnObject144(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_generator", newOrigin, true);
		}
	}
}
void SpawnObject145(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_trashbin01", newOrigin, true);
		}
	}
}
void SpawnObject146(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_trashbin02", newOrigin, true);
		}
	}
}
void SpawnObject147(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_firehydrant", newOrigin, true);
		}
	}
}
void SpawnObject148(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_newspaperbox_red", newOrigin, true);
		}
	}
}
void SpawnObject149(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_newspaperbox_blue", newOrigin, true);
		}
	}
}
void SpawnObject150(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_uaz_open_destructible", newOrigin, true);
		}
	}
}
void SpawnObject151(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_van_white_destructible", newOrigin, true);
		}
	}
}
void SpawnObject152(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_bm21_cover_destructible", newOrigin, true);
		}
	}
}
void SpawnObject153(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_filecabinetblackclosed", newOrigin, true);
		}
	}
}

void SpawnObject154(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank01", newOrigin, true);
		}
	}
}

void SpawnObject155(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank02", newOrigin, true);
		}
	}
}

void SpawnObject156(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_trashcan_metal_closed", newOrigin, true);
		}
	}
}

void SpawnObject157(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_tv1", newOrigin, true);
		}
	}
}

void SpawnObject158(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_filecabinetblackclosed", newOrigin, true);
		}
	}
}

void SpawnObject159(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_locker_double", newOrigin, true);
		}
	}
}

void SpawnObject160(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_uaz_winter_destructible", newOrigin, true);
		}
	}
}

void SpawnObject161(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_tv1", newOrigin, true);
		}
	}
}
void SpawnObject162(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_barrel_benzin", newOrigin, true);
		}
	}
}
void SpawnObject163(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_pacific_fern01_animated", newOrigin, true);
		}
	}
}
void SpawnObject164(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("ma_flatscreen_tv_wallmount_02", newOrigin, true);
		}
	}
}
void SpawnObject165(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_roofvent2_animated", newOrigin, true);
		}
	}
}
void SpawnObject166(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("ma_flatscreen_tv_on_wallmount_02_static", newOrigin, true);
		}
	}
}
void SpawnObject167(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_policecar_lapd_destructible", newOrigin, true);
		}
	}
}
void SpawnObject168(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_vending_can_new2_lit", newOrigin, true);
		}
	}
}
void SpawnObject169(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("usa_gas_station_trash_bin_01", newOrigin, true);
		}
	}
}
void SpawnObject170(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_cod5_tree_pine05_large_animated", newOrigin, true);
		}
	}
}
void SpawnObject171(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_filecabinetblackclosed", newOrigin, true);
		}
	}
}
void SpawnObject172(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_plasticcase_black_big_us_dirt", newOrigin, true);
		}
	}
}
void SpawnObject173(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_pacific_bushtree01_halfsize_animated", newOrigin, true);
		}
	}
}
void SpawnObject174(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("utility_water_collector", newOrigin, true);
		}
	}
}
void SpawnObject175(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_propane_tank02", newOrigin, true);
		}
	}
}
void SpawnObject176(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_pacific_bushtree01_animated", newOrigin, true);
		}
	}
}
void SpawnObject177(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_van_slate_destructible", newOrigin, true);
		}
	}
}
void SpawnObject178(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_locker_double", newOrigin, true);
		}
	}
}
void SpawnObject179(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank01", newOrigin, true);
		}
	}
}
void SpawnObject180(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("prop_photocopier_destructible_02", newOrigin, true);
		}
	}
}
void SpawnObject181(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("usa_gas_station_trash_bin_02", newOrigin, true);
		}
	}
}
void SpawnObject182(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("machinery_oxygen_tank02", newOrigin, true);
		}
	}
}
void SpawnObject183(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("com_filecabinetblackclosed", newOrigin, true);
		}
	}
}
void SpawnObject184(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("vehicle_pickup_destructible_mp", newOrigin, true);
		}
	}
}
void SpawnObject185(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_cod5_tree_jungle_02_animated", newOrigin, true);
		}
	}
}
void SpawnObject186(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_tree_oak_1_animated2", newOrigin, true);
		}
	}
}
void SpawnObject187(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("foliage_pacific_palms08_animated", newOrigin, true);
		}
	}
}
void SpawnObject188(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("chicken_black_white", newOrigin, true);
		}
	}
}
void SpawnObject189(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("utility_transformer_ratnest01", newOrigin, true);
		}
	}
}
void SpawnObject190(float origin[3]) {
	int crateCount = 0;
	vec3 newOrigin;
	for (int i = -1; i < 0; i++) {
		for (int x = -1; x < 0; x++) {
			newOrigin(origin[0] + (1 * x), origin[1] + (1 * i), origin[2]);
			level->object[level->crateCount] = SpawnModel("utility_transformer_small01", newOrigin, true);
		}
	}
}

