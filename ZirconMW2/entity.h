#ifndef __ENTITY_H__
#define __ENTITY_H__

enum entityType_t
{
	ET_GENERAL = 0x0,
	ET_PLAYER = 0x1,
	ET_PLAYER_CORPSE = 0x2,
	ET_ITEM = 0x3,
	ET_MISSILE = 0x4,
	ET_INVISIBLE = 0x5,
	ET_SCRIPTMOVER = 0x6,
	ET_SOUND_BLEND = 0x7,
	ET_FX = 0x8,
	ET_LOOP_FX = 0x9,
	ET_PRIMARY_LIGHT = 0xA,
	ET_TURRET = 0xB,
	ET_HELICOPTER = 0xC,
	ET_PLANE = 0xD,
	ET_VEHICLE = 0xE,
	ET_VEHICLE_COLLMAP = 0xF,
	ET_VEHICLE_CORPSE = 0x10,
	ET_VEHICLE_SPAWNER = 0x11
};

#define FL_GODMODE 0x1
#define FL_DEMI_GODMODE 0x2
#define FL_NO_KNOCKBACK 0x8
#define FL_CAN_RADIUS_DAMAGE 0x10
#define FL_SUPPORTS_LINKTO 0x1000
#define FL_GRENADE_TOUCH_DAMAGE 0x4000
#define FL_STABLE_MISSILES 0x20000

struct EntHandle {
	unsigned short number;
	unsigned short infoIndex;
};

struct LerpEntityStatePlayer
{
	int leanf;
	int movementDir;
	int torsoPitch;
	int waistPitch;
	int offhandWeapon;
	int lastSpawnTime;
};

struct LerpEntityStateAnonymous
{
	int data[9];
};

struct LerpEntityStateMissile
{
	int launchTime;
	int flightMode;
};

struct LerpEntityStateScriptMover
{
	int entToTakeMarksFrom;
	int xModelIndex;
	int animIndex;
	int animTime;
};

struct LerpEntityStateSoundBlend
{
	int lerp;
};

struct LerpEntityStateLoopFx
{
	int cullDist;
	int period;
};

struct LerpEntityStateTurret
{
	float gunAngles[3];
	int lastBarrelRotChangeTime;
	int lastBarrelRotChangeRate;
	int lastHeatChangeTime;
	int lastHeatChangeLevel;
};

struct LerpEntityStateVehicle
{
	int indices;
	int flags;
	int bodyPitch;
	int bodyRoll;
	int steerYaw;
	int gunPitch;
	int gunYaw;
	int playerIndex;
	int pad;
};

struct LerpEntityStatePlane
{
	int ownerNum;
	int enemyIcon;
	int friendIcon;
};

union LerpEntityStateTypeUnion
{
	LerpEntityStateTurret turret;
	LerpEntityStateLoopFx loopFx;
	LerpEntityStatePlayer player;
	LerpEntityStateScriptMover scriptMover;
	LerpEntityStateVehicle vehicle;
	LerpEntityStatePlane plane;
	LerpEntityStateMissile missile;
	LerpEntityStateSoundBlend soundBlend;
	LerpEntityStateAnonymous anonymous;
};

enum trType_t
{
	TR_STATIONARY = 0x0,
	TR_INTERPOLATE = 0x1,
	TR_LINEAR = 0x2,
	TR_LINEAR_STOP = 0x3,
	TR_SINE = 0x4,
	TR_GRAVITY = 0x5,
	TR_LOW_GRAVITY = 0x6,
	TR_ACCELERATE = 0x7,
	TR_DECELERATE = 0x8,
	TR_PHYSICS = 0x9,
	TR_ANIMATED_MOVER = 0xA,
	TR_FIRST_RAGDOLL = 0xB,
	TR_RAGDOLL = 0xB,
	TR_RAGDOLL_GRAVITY = 0xC,
	TR_RAGDOLL_INTERPOLATE = 0xD,
	TR_LAST_RAGDOLL = 0xD,
	NUM_TRTYPES = 0xE,
};

struct trajectory_t
{
	trType_t trType;
	int trTime;
	int trDuration;
	float trBase[3];
	float trDelta[3];
};

struct LerpEntityState
{
	int eFlags;
	trajectory_t pos;
	trajectory_t apos;
	LerpEntityStateTypeUnion u;
};

struct entityState_s
{
	int number;	// 0x0
	int eType;	// 0x4
	LerpEntityState lerp;	// 0x8
	int time2;	// 0x78
	int otherEntityNum;	// 0x7C
	int attackerEntityNum;	// 0x80
	int groundEntityNum;	// 0x84
	int surfType;	// 0x88
	int loopSound;	// 0x8C
	union
	{
		int brushmodel;
		int item;
		int xmodel;
		int primaryLight;
	} index;	// 0x90
	int clientNum;	// 0x94
	int iHeadIcon;	// 0x98
	int iHeadIconTeam;	// 0x9C
	int solid;	// 0xA0
	int eventParm;	// 0xA4
	int eventSequence;	// 0xA8
	int events[4];	// 0xAC
	int eventParms[4];	// 0xBC
	Weapon weapon;	// 0xCC
	int legsAnim;	// 0xD0
	int torsoAnim;	// 0xD4
	union
	{
		int scale;
		int eventParm2;
		int helicopterStage;
	} un1;	// 0xD8
	union
	{
		int hintString;
		int grenadeInPickupRange;
		int vehicleXModel;
	} un2;	// 0xDC
	int clientLinkInfo;
	int partBits[6];	// 0xE4
	int clientMask[1];	// 0x0
};

struct enitityShared_t
{
	char linked;	// 0x4
	char bmodel;	// 0x5
	char svFlags;	// 0x6
	char inuse;	// 0x7
	float mins[3];	// 0x8
	float maxs[3];	// 0x14
	int contents;	// 0x20
	float absmin[3];	// 0x24
	float absmax[3];	// 0x30
	float currentOrigin[3];	// 0x3C
	float currentAngles[3];	// 0x48
	EntHandle ownerNum;	// 0x54
	int eventTime;	// 0x58
};

struct gentity_s
{
	entityState_s s; // 0x0
	enitityShared_t r; // 0xFC
	gclient_s *client; // 0x158
	int pTurretInfo; // 0x15C
	int scr_vehicle; // 0x160
	int physicsBody; // 0x164
	short model; // 0x168
	char physicsObject; // 0x16A
	char takedamage;  // 0x16B
	char active; // 0x16C
	char handler; // 0x16D
	char team; // 0x16E
	char freeAfterEvent;
	short code_classname; // 0x172
	short classname; // 0x174
	short script_linkname; // 0x176
	unsigned short target; // 0x178
	unsigned short targetname; // 0x17A
	int attachIgnoreCollision; // 0x17C
	int spawnFlags; // 0x180
	int flags; // 0x184
	int unlinkAfterEvent; // 0x188
	int clipMask;  // 0x18C
	int processedFrame; // 0x190
	EntHandle parent; // 0x194
	int nextthink; // 0x198
	int health; // 0x19C
	int maxhealth; // 0x1A0
	int damage; // 0x1A4
	int count; // 0x1A8
	char __0x1AC[0x60]; //0x1AC
	EntHandle projEntity;	// 0x20C
	EntHandle linkedEntity;// 0x210
	int tagInfo;	// 0x214
	gentity_s *tagChildren;// 0x218
	unsigned short attachModelNames[19];// 0x21C
	unsigned short attachTagNames[19];// 0x242
	int useCount;	// 0x268
	int nextFree;	// 0x26C
	int birthtime; // 0x270
	char unknown[0xC]; // 0x274
};

extern gentity_s* g_entities;

#endif /* __ENTITY_H__ */