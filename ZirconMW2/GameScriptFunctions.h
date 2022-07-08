#ifndef __GAMESCRIPTFUNCTIONS_H__
#define __GAMESCRIPTFUNCTIONS_H__

struct weaponParms {
	float forward[3];
	float right[3];
	float up[3];
	float muzzleTrace[3];
	float gunForward[3];
	int weapon;
	bool isAlternate;
	int weapDef; 
	int weapCompleteDef; 
};

struct missileFireParms {
	gentity_s* target;
	float targetPosOrOffset[3];
	float autoDetonateTime;
	bool lockon;
	bool topFire;
};

enum PlayerHandIndex
{
	WEAPON_HAND_RIGHT = 0x0,
	WEAPON_HAND_LEFT = 0x1,
	NUM_WEAPON_HANDS = 0x2,
	WEAPON_HAND_DEFAULT = 0x0,
};

enum weapType_t {
	WEAPTYPE_BULLET = 0x0,
	WEAPTYPE_GRENADE = 0x1,
	WEAPTYPE_PROJECTILE = 0x2,
	WEAPTYPE_RIOTSHIELD = 0x3,
	WEAPTYPE_NUM = 0x4,
};

enum weapClass_t {
	WEAPCLASS_RIFLE = 0x0,
	WEAPCLASS_SNIPER = 0x1,
	WEAPCLASS_MG = 0x2,
	WEAPCLASS_SMG = 0x3,
	WEAPCLASS_SPREAD = 0x4,
	WEAPCLASS_PISTOL = 0x5,
	WEAPCLASS_GRENADE = 0x6,
	WEAPCLASS_ROCKETLAUNCHER = 0x7,
	WEAPCLASS_TURRET = 0x8,
	WEAPCLASS_THROWINGKNIFE = 0x9,
	WEAPCLASS_NON_PLAYER = 0xA,
	WEAPCLASS_ITEM = 0xB,
	WEAPCLASS_NUM = 0xC,
};

enum weaponIconRatioType_t
{
	WEAPON_ICON_RATIO_1TO1 = 0x0,
	WEAPON_ICON_RATIO_2TO1 = 0x1,
	WEAPON_ICON_RATIO_4TO1 = 0x2,
	WEAPON_ICON_RATIO_COUNT = 0x3,
};

extern int(*BG_TakePlayerWeapon)(playerState_s* ps, Weapon weapon);
extern void(*G_InitializeAmmo)(gentity_s* pSelf, Weapon weapon, char weaponModel, int hadWeapon);

bool IsHost(int clientNum);
char* substring(char* string, int startIndex, int endIndex);
void giveWeapon(int clientNum, const char* weaponName, int camoIndex, bool isAkimbo);
bool BulletTrace(int clientNum, const float* start, const float* end, float* vecOut, int* hitId, bool hitCharacters);
bool BulletTracePassed(int clientNum, const float* start, const float* end, bool hitCharacters);
gentity_s* MagicBullet(gentity_s* self, const char* weapon, float* start, float* end);
const char* getStance(int clientNum);
void dropItem(int clientNum, const char* itemName);
void allPerks(int clientNum, bool state);
void setPerk(int clientNum, const char* perkName);
void unsetPerk(int clientNum, const char* perkName);
void giveStartAmmo(int clientNum, bool refillAll, Weapon* weapon);
const char* getCurrentWeapon(int clientNum);
bool hasWeapon(int clientNum, const char* weaponName);
void takeAllWeapons(int clientNum);
void takeWeapon(int clientNum, const char* weaponName);
int playLoopedFX(int clientNum, const char* effectName, float delay, float* origin, float(*pos)[3] = 0);
gentity_s* PlayFxOnTag(int clientNum, const char* fx, uint16_t tag);
void setOrigin(gentity_s* ent, const float* origin);
void PlayLocalSound(int clientNum, const char* sound);
void VisionSetNakedForPlayer(int clientNum, const char* visionName, float time);
void SetBlurForPlayer(int clientNum, float blur_target, float blur_duration);
void SetWaterSheeting(int clientNum, bool state, float time);
void iPrintlnBool(int clientNum, const char* text, bool state);
void iPrintln(int clientNum, const char* text);
bool AdsButtonPressed(int clientNum);
bool toggleVisibility(int clientNum);
bool toggleGodmode(int clientNum);

#endif /* __GAMESCRIPTFUNCTIONS_H__ */