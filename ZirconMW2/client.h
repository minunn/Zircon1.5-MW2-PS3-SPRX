#ifndef __CLIENT_H__
#define __CLIENT_H__

struct SprintState
{
	int sprintButtonUpRequired;
	int sprintDelay;
	int lastSprintStart;
	int lastSprintEnd;
	int sprintStartMaxLength;
};

struct MantleState
{
	float yaw;
	int timer;
	int transIndex;
	int flags;
};

enum weaponstate_t
{
	WEAPON_READY = 0x0,
	WEAPON_RAISING = 0x1,
	WEAPON_RAISING_ALTSWITCH = 0x2,
	WEAPON_DROPPING = 0x3,
	WEAPON_DROPPING_QUICK = 0x4,
	WEAPON_DROPPING_ALTSWITCH = 0x5,
	WEAPON_FIRING = 0x6,
	WEAPON_RECHAMBERING = 0x7,
	WEAPON_RELOADING = 0x8,
	WEAPON_RELOADING_INTERUPT = 0x9,
	WEAPON_RELOAD_START = 0xA,
	WEAPON_RELOAD_START_INTERUPT = 0xB,
	WEAPON_RELOAD_END = 0xC,
	WEAPON_MELEE_INIT,
	WEAPON_MELEE_FIRE,
	WEAPON_MELEE_END,
	WEAPON_OFFHAND_INIT,
	WEAPON_OFFHAND_PREPARE,
	WEAPON_OFFHAND_HOLD,
	WEAPON_OFFHAND_START,
	WEAPON_OFFHAND,
	WEAPON_OFFHAND_END,
	WEAPON_DETONATING,
	WEAPON_SPRINT_RAISE,
	WEAPON_SPRINT_LOOP,
	WEAPON_SPRINT_DROP,
	WEAPON_NIGHTVISION_WEAR,
	WEAPON_NIGHTVISION_REMOVE
};

struct WeaponState
{
	int weapAnim;
	int weaponTime;
	int weaponDelay;
	int weaponRestrictKickTime;
	weaponstate_t weaponstate;
	int weapHandFlags;
	int weaponShotCount;
};

enum OffhandSecondaryClass
{
	PLAYER_OFFHAND_SECONDARY_SMOKE = 0x0,
	PLAYER_OFFHAND_SECONDARY_FLASH = 0x1,
	PLAYER_OFFHAND_SECONDARY_STUN = 0x2,
};

struct ActionSlotParam_SpecifyWeapon
{
	unsigned int index;
};

struct ActionSlotParam
{
	ActionSlotParam_SpecifyWeapon specifyWeapon;
};

enum ActionSlotType
{
	ACTIONSLOTTYPE_DONOTHING = 0x0,
	ACTIONSLOTTYPE_SPECIFYWEAPON = 0x1,
	ACTIONSLOTTYPE_ALTWEAPONTOGGLE = 0x2,
	ACTIONSLOTTYPE_NIGHTVISION = 0x3,
	ACTIONSLOTTYPECOUNT = 0x4,
};

enum pmtype_t
{
	PM_NORMAL = 0x0,
	PM_NORMAL_LINKED = 0x1,
	PM_NOCLIP = 0x2,
	PM_UFO = 0x3,
	PM_SPECTATOR = 0x4,
	PM_INTERMISSION = 0x5,
	PM_LASTSTAND = 0x6,
	PM_DEAD = 0x7,
	PM_DEAD_LINKED = 0x8,
};

enum objectiveState_t
{
	OBJST_EMPTY = 0x0,
	OBJST_ACTIVE = 0x1,
	OBJST_INVISIBLE = 0x2,
	OBJST_DONE = 0x3,
	OBJST_CURRENT = 0x4,
	OBJST_FAILED = 0x5,
	OBJST_NUMSTATES = 0x6,
};

struct objective_t
{
	objectiveState_t state;
	float origin[3];
	int entNum;
	int teamNum;
	int icon;
};

enum PlayerSpreadOverrideState
{
	PSOS_DISABLED = 0x0,
	PSOS_RESETTING = 0x1,
	PSOS_ENABLED = 0x2
};

struct PlayerEquippedWeaponState
{
	bool usedBefore;
	bool dualWielding;
	bool inAltMode;
	bool needsRechamber[2];
	int zoomLevelIndex;
	bool thermalEnabled;
	bool hybridScope;
};

struct WeaponData {
	unsigned int weaponIdx : 8;
	unsigned int weaponVariation : 6;
	unsigned int weaponScopes : 3;
	unsigned int weaponUnderBarrels : 2;
	unsigned int weaponOthers : 7;
	unsigned int scopeVariation : 6;
};

union Weapon {
	WeaponData __s0;
	unsigned int data;
};

struct usercmd_s { //size 0x28
	int serverTime; //0x00 - 0x04
	unsigned int buttons; //0x04 - 0x08
	int angles[3]; //0x08 - 0x14
	Weapon weapon; //0x14 - 0x18
	char offHand[2]; //0x18 - 0x1A
	char forwardmove; //0x1A - 0x1B
	char rightmove; //0x1B - 0x1C 
	unsigned short airburstMarkDistance; //0x1C - 0x1E
	unsigned short meleeChargeEnt; //0x1E - 0x20
	char meleeChargeDist; //0x20 - 0x21
	char selectedLoc[2]; //0x21 - 0x23
	char selectedLocAngle; //0x23 - 0x24
	char __0x1[0x1]; //0x24 - 0x25
};

struct GlobalAmmo
{
	unsigned short ammoType;
	int ammoCount;
};

struct ClipAmmo
{
	uint64_t clipIndex;
	int ammoCount[2];
};

enum OffhandClass
{
	OFFHAND_CLASS_NONE = 0x0,
	OFFHAND_CLASS_FRAG_GRENADE = 0x1,
	OFFHAND_CLASS_SMOKE_GRENADE = 0x2,
	OFFHAND_CLASS_FLASH_GRENADE = 0x3,
	OFFHAND_CLASS_THROWINGKNIFE = 0x4,
	OFFHAND_CLASS_OTHER = 0x5,
	OFFHAND_CLASS_COUNT = 0x6,
};

enum clientConnected_t
{
	CON_DISCONNECTED = 0x0,
	CON_CONNECTING = 0x1,
	CON_CONNECTED = 0x2,
};

enum sessionState_t
{
	SESS_STATE_PLAYING = 0x0,
	SESS_STATE_DEAD = 0x1,
	SESS_STATE_SPECTATOR = 0x2,
	SESS_STATE_INTERMISSION = 0x3,
};

struct playerTeamState_t {
	int location;
};

enum team_t
{
	TEAM_FREE = 0x0,
	TEAM_AXIS = 0x1,
	TEAM_ALLIES = 0x2,
	TEAM_SPECTATOR = 0x3,
};

typedef struct clientState_s
{
	int clientIndex;
	team_t team;
	int modelindex;
	int dualWielding;
	int riotShieldNext;
	int attachModelIndex[6];
	int attachTagIndex[6];
	char name[0x20];
	float maxSprintTimeMultiplier;
	int rank;
	int prestige;
	int perks[2];
	int diveState;
	int voiceConnectivityBits;
	char clanAbb[4];
} clientState_s;

struct playerState_s {
	int commandTime; //0x00 - 0x04
	pmtype_t pm_type; //0x04 - 0x08
	int bobCycle; //0x08 - 0x0C
	int pm_flags; //0x0C - 0x10
	int otherFlags; //0x10 - 0x14
	int linkFlags; //0x14 - 0x18
	int pm_time; //0x18 - 0x1C
	float origin[3]; //0x1C - 0x28
	float velocity[3]; //0x28 - 0x34
	int weaponTime; //0x34 - 0x38
	int weaponDelay; //0x38 - 0x3C
	int grenadeTimeLeft; //0x3C - 0x40
	int throwBackGrenadeOwner; //0x40 - 0x44
	int remoteEyesEnt; //0x44 - 0x48
	int remoteEyesTagname; //0x44 - 0x4C
	int remoteControlEnt; //0x4C - 0x50
	int foliageSoundTime; //0x50 - 0x54
	int gravity; //0x54 - 0x58
	float leanf; //0x58 - 0x5C
	int speed; //0x5C - 0x60
	float delta_angles[3]; //0x60 - 0x6C
	int groundEntityNum; //0x6C - 0x70
	float vLadderVec[3]; //0x70 - 0x7C
	int jumpTime; //0x7C - 0x80
	float jumpOriginZ; //0x80 - 0x84
	int legsTimer; //0x84 - 0x8C
	int legsAnim; //0x8C - 0x90
	int torsoTimer; //0x90 - 0x94
	int torsoAnim; //0x94 - 0x98
	int legsAnimDuration; //0x98 - 0x9C
	int torsoAnimDuration; //0x9C - 0x100
	int damageTimer; //0x100 - 0x104
	int damageDuration; //0x104 - 0x108
	int flinchYawAnim; //0x108 - 0x10C
	int corpseIndex; //0x10C - 0x110
	int movementDir; //0x110 - 0x114
	int eFlags; //0x114 - 0x118
	int eventSequence;
	int events[4];
	unsigned int eventParms[4];
	int oldEventSequence;
	int unpredictableEventSequence;
	int unpredictableEventSequenceOld;
	int unpredictableEvents[4];
	unsigned int unpredictableEventParms[4];
	int clientNum;
	int viewmodelIndex;
	float viewAngles[3];
	int viewHeightTarget;
	float viewHeightCurrent;
	char unknown_data8[0x94];
	int locationSelectionInfo;
	SprintState sprintState;
	float holdBreathScale;
	int holdBreathTimer;
	float moveSpeedScaleMultiplier;
	MantleState mantleState;
	WeaponState weaponStates[2];
	Weapon weaponsEquipped[15]; //0x220 - 0x25C
	char unknown_data[0x4C]; //0x25C - 0x2A8
	Weapon offHand; //0x2A8 - 0x2AC
	OffhandSecondaryClass offhandPrimary; //0x2AC - 0x2B0
	OffhandSecondaryClass offhandSecondary; //0x2B0 - 0x2B4
	Weapon weapon; //0x2B4 - 0x2B8
	unsigned int primaryWeaponForAltMode; //0x2B8 - 0x2BC
	int weapFlags; //0x2BC - 0x2C0
	float fWeaponPosFrac; //0x2C0 - 0x2C4
	float aimSpreadScale; //0x2C4 - 0x2C8
	int adsDelayTime; //0x2C8 - 0x2CC
	int spreadOverride; //0x2CC - 0x2D0
	PlayerSpreadOverrideState spreadOverrideState; //0x2D0 - 0x2D4
	int isDualWeilding; //0x2D4 - 0x2D8
	int __pad; //0x2D8 - 0x2DC
	int unk1_ammo; //0x2DC - 0x2E0
	char __pad2[0xC]; //0x2E0 - 0x2EC
	int unk2_ammo; //0x2EC - 0x2F0
	char __pad3[0x64]; //0x2F0 - 0x354
	int unk3_ammo; //0x354 - 0x358
	char __pad4[0x8]; //0x358 - 0x360
	int unk4_ammo; //0x360 - 0x364
	char __pad5[0x8]; //0x364 - 0x36C
	int unk5_ammo; //0x36C - 0x370
	char __pad6[0x8]; //0x370 - 0x378
	int unk6_ammo; //0x378 - 0x37C
	char unknown_data1[0x88];
	int weapLockedFlags;
	int weapLockedEntnum;
	float weapLockedPos[3];
	int weaponIdleTime;
	float meleeChargeYaw;
	int meleeChargeDist;
	int meleeChargeTime;
	int perks[2];
	int perkSlots[8];
	ActionSlotType actionSlotType[4];
	ActionSlotParam actionSlotParam[4];
	int weaponHudIconOverrides[6];
	int animScriptedType;
	int shellshockIndex;
	int shellshockTime;
	int shellshockDuration;
	float dofNearStart;
	float dofNearEnd;
	float dofFarStart;
	float dofFarEnd;
	float dofNearBlur;
	float dofFarBlur;
	float dofViewmodelStart;
	float dofViewmodelEnd;
	objective_t objective[0x20];
	char unknown_data3[0x2958];
};

struct clientSession_t {
	sessionState_t sessionState;
	int uknown6;
	int score;
	int deaths;
	int kills;
	int assists;
	short scriptpersid;
	char undefined;
	clientConnected_t connected;
	usercmd_s cmd;
	usercmd_s oldcmd;
	int localClient;
	int predictItemPickup;
	char newnetname[0x20];
	int maxHealth;							//0x3228
	int enterTime;							//0x322C
	playerTeamState_t teamState;			//0x3230
	int voteCount;							//0x3234
	int teamVoteCount;						//0x3238
	float moveSpeedScaleMultiplier;			//0x323C
	int viewmodelIndex;						//0x3240
	int noSpectate;							//0x3244
	int teamInfo;							//0x3248
	clientState_s cs;						//0x324C - 0x32D0
	int __padding;							//0x32D0 - 0x32D4
	int title;								//0x32D4 - 0x32D8
	int emblem;								//0x32D8 - 0x32DC
	int __padding2;							//0x32DC - 0x32E0
	int psOffsetTime;						//0x32E0 - 0x32E4
	int hasRadar;							//0x32E4 - 0x32E8
	int isRadarBlocked;						//0x32E8 - 0x32EC
	char unknown_data5[0x130];				//0x32EC - 0x341C
};

struct gclient_s {
	playerState_s ps;
	clientSession_t sess;
	int spectatorclient;
	int flags;
	char __0x8[0x8];
	int buttons;
	int oldbuttons;
	int latched_buttons;
	int buttonsSinceLastFrame;
	char __0x2C4[0x2C4];
};

extern gclient_s* g_clients;

#endif /* __CLIENT_H__ */