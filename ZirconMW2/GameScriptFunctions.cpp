#include "Includes.h"

opd_s BG_GetWeaponDef_t = { 0x032898, TOC };
opd_s BG_GetWeaponClassName_t = { 0x032550, TOC };
opd_s BG_GetWeaponTypeName_t = { 0x032538, TOC };
opd_s BG_TakePlayerWeapon_t = { 0x035070, TOC };
opd_s BG_GetPerkCodeIndexForName_t = { 0x020D70, TOC };
opd_s Bullet_Fire_t = { 0x165478, TOC };
opd_s G_FireGrenade_t = { 0x18EE08, TOC };
opd_s Weapon_GrenandeLauncher_Fire_t = { 0x1C11E8, TOC };
opd_s Weapon_RocketLauncher_Fire_t = { 0x1C0D10, TOC };
opd_s G_TempEntity_t = { 0x1BCE30, TOC };
opd_s G_InitializeAmmo_t = { 0x174BF8, TOC };
opd_s Drop_Weapon_t = { 0x1861C8, TOC };
opd_s Item_SetStateFromTag_t = { 0x184378, TOC };
opd_s Item_SetDefaultVelocity_t = { 0x184410, TOC };

int(*BG_GetWeaponDef)(Weapon weapon) = (int(*)(Weapon))&BG_GetWeaponDef_t;
const char*(*BG_GetWeaponClassName)(int weaponClass) = (const char*(*)(int))&BG_GetWeaponClassName_t;
const char*(*BG_GetWeaponTypeName)(int weaponType) = (const char*(*)(int))&BG_GetWeaponTypeName_t;
int(*BG_TakePlayerWeapon)(playerState_s* ps, Weapon weapon) = (int(*)(playerState_s*, Weapon))&BG_TakePlayerWeapon_t;
int(*Bullet_Fire)(gentity_s* attacker, float spread, weaponParms* wp, gentity_s* weaponEnt, PlayerHandIndex hand, int gameTime) = (int(*)(gentity_s* attacker, float spread, weaponParms* wp, gentity_s* weaponEnt, PlayerHandIndex hand, int gameTime))&Bullet_Fire_t;
gentity_s*(*G_FireGrenade)(gentity_s* parent, vec3_t start, vec3_t dir, Weapon grenadeWPID, int rotate, int explosionTime) = (gentity_s*(*)(gentity_s* parent, vec3_t start, vec3_t dir, Weapon grenadeWPID, int rotate, int explosionTime))&G_FireGrenade_t;
gentity_s*(*Weapon_GrenadeLauncher_Fire)(gentity_s* ent, Weapon grenade, weaponParms* wp) = (gentity_s*(*)(gentity_s* ent, Weapon grenade, weaponParms* w))&Weapon_GrenandeLauncher_Fire_t;
gentity_s*(*Weapon_RocketLauncher_Fire)(gentity_s* ent, Weapon weapon, float spread, weaponParms* wp, float* gunVel, missileFireParms* fireParams, bool magicBullet) = (gentity_s*(*)(gentity_s*, Weapon, float, weaponParms*, float*, missileFireParms*, bool))&Weapon_RocketLauncher_Fire_t;
gentity_s*(*G_TempEntity)(const float* start, int _event) = (gentity_s*(*)(const float*, int))&G_TempEntity_t;
void(*G_InitializeAmmo)(gentity_s* pSelf, Weapon weapon, char weaponModel, int hadWeapon) = (void(*)(gentity_s*, Weapon, char, int))&G_InitializeAmmo_t;
int(*BG_GetPerkCodeIndexForName)(const char* perkName) = (int(*)(const char*))&BG_GetPerkCodeIndexForName_t;
gentity_s*(*Drop_Weapon)(gentity_s* ent, int weaponId, char weaponModel, unsigned int tag) = (gentity_s*(*)(gentity_s*, int, char, unsigned int))&Drop_Weapon_t;
void(*Item_SetStateFromTag)(gentity_s* droppingEnt, uint16_t tag, gentity_s* droppedEnt) = (void(*)(gentity_s*, uint16_t, gentity_s*))&Item_SetStateFromTag_t;
void(*Item_SetDefaultVelocity)(gentity_s* droppingEnt, gentity_s* droppedEnt) = (void(*)(gentity_s*, gentity_s*))&Item_SetDefaultVelocity_t;

bool IsHost(int clientNum) {
	return Session_IsHost(0x1FF49B0, clientNum);
}

char* substring(char* string, int startIndex, int endIndex) {
	char value[0x418];
	int i = 0;
	char* str = &string[startIndex];
	char* ch = (char*)(&value[-startIndex] - str);
	int n = -(uint32_t)str;
	do
	{
		if (!*str)
			break;
		str[(uint32_t)ch] = *str;
		++str;
		++i;
	} while ((uint32_t)&str[n] < endIndex);
	value[i] = 0;
	return value;
}

bool BulletTrace(int clientNum, const float* start, const float* end, float* vecOut, int* hitId, bool hitCharacters) {
	trace_t results;
	G_LocationalTrace(&results, start, end, clientNum, hitCharacters ? 0x2806831 : 0x806831, NULL);
	if (vecOut) {
		vecOut[0] = (end[0] - start[0]) * results.fraction + start[0];
		vecOut[1] = (end[1] - start[1]) * results.fraction + start[1];
		vecOut[2] = (end[2] - start[2]) * results.fraction + start[2];
	}
	if (hitId)
		*hitId = Trace_GetEntityHitId(&results);
	return (results.fraction < 1.0);
}

bool BulletTracePassed(int clientNum, const float* start, const float* end, bool hitCharacters) {
	return G_LocationalTracePassed(start, end, clientNum, 0x7FF, hitCharacters ? 0x2806831 : 0x806831, NULL);
}

gentity_s* MagicBullet(gentity_s* self, const char* weapon, float* start, float* end) {
	float gunVel[3] = {};
	weaponParms parms = {};
	float fraction, length, x, y, z;
	float targetOffset[3], forward[3], direction[3];
	gentity_s* rocket = 0;

	Weapon wep; wep.data = BG_GetWeaponForName(weapon);

	parms.weapon = wep.data;
	VectorCopy(start, parms.muzzleTrace);
	x = end[0] - start[0];
	y = end[1] - start[1];
	z = end[2] - start[2];
	length = f_sqrtf(x * x + y * y + z * z);
	fraction = length >= 0 ? 1 / length : 1;
	VectorSet(parms.forward, x * fraction, y * fraction, z * fraction);
	VectorCopy(parms.forward, forward);

	int weaponClass = *(int*)(BG_GetWeaponDef(wep) + 0x30);
	int weaponType = *(int*)(BG_GetWeaponDef(wep) + 0x2C);
	const char* typeName = BG_GetWeaponTypeName(weaponType);
	switch (weaponType) {
	case WEAPTYPE_BULLET:
		Bullet_Fire(self, 0, &parms, 0, WEAPON_HAND_DEFAULT, level_locals->time);
		break;
	case WEAPTYPE_GRENADE:
		VectorScale(parms.forward, 10000, direction);
		rocket = G_FireGrenade(self, start, direction, wep, 0, (2 * 1000));
		break;
	case WEAPTYPE_PROJECTILE:
		if (weaponClass == WEAPCLASS_GRENADE)
			rocket = Weapon_GrenadeLauncher_Fire(self, wep, &parms);
		else if (weaponClass == WEAPCLASS_ROCKETLAUNCHER) {
			if (!strcmp(weapon, "remotemissile_projectile_mp"))
				gunVel[2] -= 10000;
			rocket = Weapon_RocketLauncher_Fire(self, wep, 0, &parms, gunVel, NULL, false);
		}
		break;

	default:
		return;
	}
	gentity_s* tempEntity = G_TempEntity(start, 0x1E);
	tempEntity->s.weapon = wep;
	tempEntity->s.eventParms[tempEntity->s.eventSequence] = 0;
	tempEntity->s.eventParm = self->s.number;
	return rocket;
}

void allPerks(int clientNum, bool state) {
	gclient_s* client = &g_clients[clientNum];
	if (state) {
		client->ps.perks[0] = client->ps.perks[1] = -1;
		const char* shitPerks[] = { "specialty_extendedmags", "specialty_jumpdive", "specialty_explosivebullets", "specialty_gpsjammer" }; //niggers perks we dont want
		int perkCount = 4, perkIndex = 0;
		do
		{
			perkIndex = BG_GetPerkCodeIndexForName(shitPerks[perkCount - 1]);
			client->ps.perks[perkIndex / 32] &= ~(1 << perkIndex);
			--perkCount;
		} while (perkCount);
	}
	else
		client->ps.perks[0] = client->ps.perks[1] = 0;
}

void dropItem(int clientNum, const char* itemName) {
	gentity_s* self = &g_entities[clientNum];
	uint16_t tag = scr_const->tag_weapon_left;
	int weaponId = BG_GetWeaponForName(itemName);
	gentity_s* dropWeapon = Drop_Weapon(self, weaponId, 0, tag);
	if (dropWeapon) {
		Item_SetStateFromTag(self, tag, dropWeapon);
		Item_SetDefaultVelocity(self, dropWeapon);
	}
}

const char* getStance(int clientNum) {
	gclient_s* client = &g_clients[clientNum];
	if ((client->ps.pm_flags & 1))
		return "prone";
	if ((client->ps.pm_flags & 2))
		return "crouch";
	return "stand";
}

void setPerk(int clientNum, const char* perkName) {
	gentity_s* self = &g_entities[clientNum];
	int perkIndex = BG_GetPerkCodeIndexForName(perkName);
	int id = perkIndex / 32;
	self->client->ps.perks[id] |= (1 << perkIndex);
	self->client->sess.cs.perks[id] |= (1 << perkIndex);
}

void unsetPerk(int clientNum, const char* perkName) {
	gentity_s* self = &g_entities[clientNum];
	int perkIndex = BG_GetPerkCodeIndexForName(perkName);
	int id = perkIndex / 32;
	self->client->ps.perks[id] &= ~(1 << perkIndex);
	self->client->sess.cs.perks[id] &= ~(1 << perkIndex);
}

void giveStartAmmo(int clientNum, bool refillAll, Weapon* weapon) {
	gentity_s* self = &g_entities[clientNum];
	
	if (!refillAll) {
		if (weapon->data)
			G_InitializeAmmo(self, *weapon, 0, false);
	}
	else {
		Weapon* weapons = (Weapon*)&self->client->ps.weaponsEquipped;
		int weaponsEquipped = 15;
		do
		{
			if (weapons->data)
				G_InitializeAmmo(self, *weapons, 0, false);
			++weapons;
			--weaponsEquipped;
		} while (weaponsEquipped);
	}
}

const char* getCurrentWeapon(int clientNum) {
	gclient_s* client = &g_clients[clientNum];
	char output[0x400];
	return BG_GetWeaponNameComplete(client->ps.weapon, output, 0x400);
}

const char* getCurrentOffhand(int clientNum) {
	gclient_s* client = &g_clients[clientNum];
	char output[0x400];
	return BG_GetWeaponNameComplete(client->ps.offHand, output, 0x400);
}

int weaponIndex = 0;
void handleWeaponSwitch(int clientNum, handle_t* handle, handleCall_t type) {
	SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, va("a %i", weaponIndex));
}

void giveWeapon(int clientNum, const char* weaponName, int camoIndex, bool isAkimbo) {
	gentity_s* self = &g_entities[clientNum];
	Weapon weapon; weapon.data = BG_GetWeaponForName(weaponName);
	G_GivePlayerWeapon(&self->client->ps, weapon, camoIndex, isAkimbo);
	G_InitializeAmmo(self, weapon, 0, false);
	weaponIndex = weapon.data;
	handleAllocTemp(clientNum, handleWeaponSwitch, 500);
}

void takeWeapon(int clientNum, const char* weaponName) {
	gentity_s* self = &g_entities[clientNum];
	Weapon weapon; weapon.data = BG_GetWeaponForName(weaponName);
	if (weapon.data)
		BG_TakePlayerWeapon(&self->client->ps, weapon);
}

bool hasWeapon(int clientNum, const char* weaponName) {
	gentity_s* self = &g_entities[clientNum];
	Weapon* weapons = (Weapon*)&self->client->ps.weaponsEquipped;
	int weaponsEquipped = 15;
	do
	{
		if (weapons->data) {
			if (!strcmp(BG_GetWeaponNameComplete(*weapons, 0, 0x400), weaponName))
				return true;
		}
		++weapons;
		--weaponsEquipped;
	} while (weaponsEquipped);
}

void takeAllWeapons(int clientNum) {
	gentity_s* self = &g_entities[clientNum];
	Weapon* weapons = (Weapon*)&self->client->ps.weaponsEquipped;
	self->client->ps.weapon.data = 0;
	int weaponsEquipped = 15;
	do
	{
		if (weapons->data)
			BG_TakePlayerWeapon(&self->client->ps, *weapons);
		++weapons;
		--weaponsEquipped;
	} while (weaponsEquipped);
}

int playLoopedFX(int clientNum, const char* effectName, float delay, float* origin, float(*pos)[3]) {
	int delayTime = (int)f_floorf((float)(delay * 1000.0) + 0.5);
	int fxId = G_EffectIndex(effectName);
	if (!delayTime) {
		printf("playLoopedFX delay has to be greater than 0\n");
		return 0;
	}
	if (!fxId) {
		printf("Invalid effectName, G_EffectIndex returned %i\n", fxId);
		return 0;
	}
	gentity_s* ent = G_Spawn();
	ent->s.un1.eventParm2 = fxId;
	ent->s.eType = 0x9;
	G_SetOrigin(ent, origin);
	Scr_SetFxAngles(0, (float(*)[3])&pos, (float*)&ent->s.lerp.apos.trBase);
	ent->s.lerp.u.loopFx.period = 0;
	ent->s.lerp.u.turret.gunAngles[0] = delayTime;
}

gentity_s* PlayFxOnTag(int clientNum, const char* fx, uint16_t tag) {
	gentity_s* self = &g_entities[clientNum];
	int fxIndex = G_EffectIndex(fx);
	if (!self->model)
		return;
	vec3 fOut;
	G_DObjGetWorldTagPos(self, tag, fOut);
	return Scr_PlayFxInternal(fxIndex, fOut, 0, 0);
}

void setOrigin(gentity_s* ent, const float* origin) {
	G_SetOrigin(ent, origin);
	if (ent->r.linked)
		SV_LinkEntity(ent);
}

void PlayLocalSound(int clientNum, const char* sound) {
	int soundIndex = G_SoundAliasIndex(sound);
	if (soundIndex)
		SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, va("s %i", soundIndex));
}

void VisionSetNakedForPlayer(int clientNum, const char* visionName, float time) {
	char visionCmd[0x40];
	sprintf(visionCmd, "%c \"%s\" %i", 'Q', visionName, (int)f_floorf(time * 1000.0 + 0.5));
	SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, visionCmd);
}

void SetBlurForPlayer(int clientNum, float blur_target, float blur_duration) {
	SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, va("d %g %g 0 5", (int)f_floorf(blur_duration * 1000 + 0.5), blur_target));
}

void SetWaterSheeting(int clientNum, bool state, float time) {
	int flrTime = (int)f_floorf((time * 1000) + 0.5);
	SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, va("W %i %i", state, time));
}

void iPrintlnBool(int clientNum, const char* text, bool state) {
	iPrintln(clientNum, va("%s %s", text, (state ? "^2ON" : "^1OFF")));
}

void iPrintln(int clientNum, const char* text) {
	char buffer[0x200];
	sprintf(buffer, "%c \"%s\"", 'f', text);
	SV_GameSendServerCommand(clientNum, SV_CMD_CAN_IGNORE, buffer);
}

bool AdsButtonPressed(int clientNum) {
	gclient_s* client = &g_clients[clientNum];
	return ((client->buttons | client->buttonsSinceLastFrame) & 0x800);
}

bool toggleVisibility(int clientNum) {
	gentity_s* self = &g_entities[clientNum];
	if (self->s.lerp.eFlags & 0x20) {
		self->s.lerp.eFlags &= 0xFFFFFFDF;
		self->s.clientMask[0] = 0;
	}
	else {
		self->s.lerp.eFlags |= 0x20;
		self->s.clientMask[0] = -1;
	}
	return ((self->s.lerp.eFlags & 0x20) && self->s.clientMask[0] == -1);
}

bool toggleGodmode(int clientNum) {
	gentity_s* self = &g_entities[clientNum];
	if (self->flags & 2)
		self->flags &= ~2;
	if (self->flags & 1)
		self->flags &= ~1;
	else
		self->flags |= 1;
	return (self->flags & 1);
}