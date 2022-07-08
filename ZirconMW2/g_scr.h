#ifndef __G_SCR_H__
#define __G_SCR_H__
#define TOC 0x724C38

const int MAX_PLAYERS = 18;
typedef uint16_t scr_string_t;
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

enum AddressTable
{
	//General
	VM_Notify_a = 0x20B7C8,
	ThreadStorage_a = 0x1830000,
	AllocatedMemory_a = 0x1700000,
	Sys_SpawnServerThread_a = 0x1FBCA8,

	//Structs
	scrVmPub_t_a = 0x1B9A580,
	gentity_s_a = 0x1319800,
	gentity_s_size = 0x280,
	gclient_s_a = 0x14E2200,
	gclient_s_size = 0x3700,
	g_hudelem_s_a = 0x12E9858,
	g_hudelem_s_size = 0xB4,
	client_t_a = 0x1BF911C,
	client_t_size = 0x97F80,
	level_locals_t_a = 0x1316880,

	//SL
	SL_ConvertToString_a = 0x200280,
	SL_GetString_a = 0x2013A8,

	//Scr
	Scr_ClearOutParams_a = 0x20C208,
	Scr_GetSelf_a = 0x201F90,
	Scr_AddInt_a = 0x20C608,
	Scr_AddFloat_a = 0x20C5C0,
	Scr_AddString_a = 0x20C428,
	Scr_AddVector_a = 0x20C330,
	Scr_AddEntity_a = 0x1B7700,
	Scr_AddEntityNum_a = 0x20C518,
	Scr_Notify_a = 0x1B74F0,
	Scr_NotifyNum_a = 0x20CBC0,
	Scr_FreeHudElem_a = 0x1B7A48,
	Scr_GetObjectField_a = 0x1B7E10,
	Scr_AddConstString_a = 0x20C380,
	Scr_ExecEntThread_a = 0x1B7560,
	Scr_FreeThread_a = 0x208FF0,
	Scr_AddUndefined_a = 0x20C548,
	Scr_SetString_a = 0x200B98,

	GetObjectType_a = 0x202560,
	GetVariableValueAddress_a = 0x2022A8,
	GetArrayVariable_a = 0x2044F8,
	GetValueType_a = 0x202328,
	GetArraySize_a = 0x2022E8,
	FindFirstSibling_a = 0x202308,
	FindNextSibling_a = 0x202328,
	Scr_GetEntityIdRef_a = 0x202670,

	//Other
	SV_GameSendServerCommand_a = 0x70AA90,
	GetVariableIndexInternal_a = 0x204508,
	Cmd_RegisterNotification_a = 0x7089D0,
	G_LocationalTrace_a = 0x188560,
	G_SetOrigin_a = 0x1BC200,
	G_MaterialIndex_a = 0x708078,
	G_LocalizedStringIndex_a = 0x708080,
	Cbuf_AddText_a = 0x7089C0,
	Dvar_GetString_a = 0x70E078,
	Dvar_GetBool_a = 0x70E098,
	Dvar_AddFlags_a = 0x70E518,
	Dvar_FindMalleableVar_a = 0x70DF70,
	Dvar_RegisterBool_a = 0x70DFE0,
	ClientThink_real_a = 0x1689D8,
	SV_Cmd_ArgvBuffer_a = 0x1D93C8,
	player_die_a = 0x706238,
	g_va_a = 0x70E5E0,
	ClientCommand_a = 0x17B830,
	SV_IsLocalClient_a = 0x70A9A0,
	Sessions_IsHost_a = 0x2F19A8,
	G_SoundAliasIndex_a = 0x1BE6D0,
	G_DObjGetWorldTagPos_a = 0x1BD398,
	G_GetHitLocationString_a = 0x17BB38,
	BG_GetWeaponNameComplete_a = 0x0328C8,
	ClientUserInfoChanged_a = 0x16C558,
	SV_AddTestClient_a = 0x2189D8,
	SV_DropClient_a = 0x215000,
	G_SetModel_a = 0x1BE3F0,
	G_DObjUpdate_a = 0x1BD9C8,
	SP_script_model_a = 0x1B52A0,
	SV_SetBrushModel_a = 0x219F08,
	Trace_GetEntityHitId_a = 0x1D1240,
	G_SetAngle_a = 0x1BEA90,
	SetClientViewAngle_a = 0x16CBE0,
	G_AddEvent_a = 0x1BC608,
	SV_DObjGetBoneIndex_a = 0x2196C8,
	G_FindConfigStringIndex_a = 0x1BE450,
	G_EffectIndex_a = 0x1BE720,
	G_GetWeaponForName_a = 0x32F90,
	G_irand_a = 0x1BC360,

	G_EntLinkTo_a = 0x1C2520,
	G_InitPlayerLinkAngles_a = 0x1C2878,
	G_Spawn_a = 0x1BCD10,
	SP_script_origin_a = 0x1B6FB4,
	G_EntUnlink_a = 0x1C2308,
	G_FreeEntity_a = 0x1BC978,
	SV_LinkEntity_a = 0x2285A0,
	SV_UnlinkEntity_a = 0x2271C8,

	Cmd_CheckNetNotify_f_a = 0x1DA520,
	SendScoreboard_a = 0x17AA30,
	Cmd_Where_f_a = 0x179650,
	Cmd_Callvote_f_a = 0x17ADB0,
	Cmd_Vote_f_a = 0x179A08,
	Cmd_FollowCycle_f_a = 0x17A370,
	Cmd_MenuResponse_f_a = 0x179868,
};

struct scr_const_t {
	unsigned short _;
	unsigned short active;
	unsigned short _j_spine4;
	unsigned short _j_helmet;
	unsigned short _j_head;
	unsigned short all;
	unsigned short allies;
	unsigned short angles;
	unsigned short auto_ai;
	unsigned short auto_nonai;
	unsigned short axis;
	unsigned short back;
	unsigned short bad_guys;
	unsigned short bad_path;
	unsigned short begin_firing;
	unsigned short begin_firing_left;
	unsigned short cancel_location;
	unsigned short chest;
	unsigned short confirm_location;
	unsigned short crouch;
	unsigned short current;
	unsigned short damage;
	unsigned short dead;
	unsigned short death;
	unsigned short deathshield;
	unsigned short detonate;
	unsigned short direct;
	unsigned short dlight;
	unsigned short done;
	unsigned short empty;
	unsigned short empty_offhand;
	unsigned short offhand_end;
	unsigned short end_firing;
	unsigned short end_firing_left;
	unsigned short entity;
	unsigned short explode;
	unsigned short failed;
	unsigned short first_person;
	unsigned short forward;
	unsigned short fraction;
	unsigned short free;
	unsigned short goal;
	unsigned short goal_changed;
	unsigned short goal_yaw;
	unsigned short grenade;
	unsigned short grenade_danger;
	unsigned short grenade_fire;
	unsigned short glass_destroyed;
	unsigned short missile_fire;
	unsigned short grenade_pullback;
	unsigned short missile_stuck;
	unsigned short info_notnull;
	unsigned short invisible;
	unsigned short key1;
	unsigned short key2;
	unsigned short killanimscript;
	unsigned short left;
	unsigned short light;
	unsigned short manual;
	unsigned short manual_ai;
	unsigned short movedone;
	unsigned short none;
	unsigned short normal;
	unsigned short origin;
	unsigned short other;
	unsigned short player;
	unsigned short physics_finished;
	unsigned short position;
	unsigned short projectile_impact;
	unsigned short prone;
	unsigned short right;
	unsigned short reload;
	unsigned short reload_start;
	unsigned short result;
	unsigned short reverse;
	unsigned short rocket;
	unsigned short rotatedone;
	unsigned short script_brushmodel;
	unsigned short script_model;
	unsigned short script_origin;
	unsigned short sentry;
	unsigned short sentry_offline;
	unsigned short snd_enveffectsprio_level;
	unsigned short snd_enveffectsprio_shellshock;
	unsigned short snd_channelvolprio_holdbreath;
	unsigned short snd_channelvolprio_pain;
	unsigned short snd_channelvolprio_shellshock;
	unsigned short spawned;
	unsigned short stand;
	unsigned short suppression;
	unsigned short suppression_end;
	unsigned short surfacetype;
	unsigned short tag_aim;
	unsigned short tag_aim_animated;
	unsigned short tag_aim_pivot;
	unsigned short tag_brass;
	unsigned short tag_butt;
	unsigned short tag_clip;
	unsigned short tag_eye;
	unsigned short tag_flash;
	unsigned short tag_flash_silenced;
	unsigned short tag_flash_11;
	unsigned short tag_flash_2;
	unsigned short tag_flash_22;
	unsigned short tag_flash_3;
	unsigned short tag_fx;
	unsigned short tag_inhand;
	unsigned short tag_knife_fx;
	unsigned short tag_laser;
	unsigned short tag_origin;
	unsigned short tag_weapon;
	unsigned short tag_player;
	unsigned short tag_camera;
	unsigned short tag_weapon_chest;
	unsigned short tag_weapon_left;
	unsigned short tag_weapon_right;
	unsigned short tag_stowed_back;
	unsigned short tag_gasmask;
	unsigned short tag_gasmask2;
	unsigned short tag_sync;
	unsigned short tag_screen_tl;
	unsigned short tag_screen_bl;
	unsigned short tag_screen_br;
	unsigned short tag_motion_tracker_fx;
	unsigned short tag_reticle_acog;
	unsigned short tag_reticle_red_dot;
	unsigned short tag_reticle_tavor_scope;
	unsigned short tag_reticle_thermal_scope;
	unsigned short tag_eotech_reticle;
	unsigned short target_script_trigger;
	unsigned short third_person;
	unsigned short top;
	unsigned short touch;
	unsigned short trigger;
	unsigned short trigger_use;
	unsigned short trigger_use_touch;
	unsigned short trigger_damage;
	unsigned short truck_cam;
	unsigned short weapon_change;
	unsigned short weapon_fired;
	unsigned short weapon_switch_started;
	unsigned short weapon_taken;
	unsigned short weapon_dropped;
	unsigned short worldspawn;
	unsigned short flashbang;
	unsigned short flash;
	unsigned short smoke;
	unsigned short frag;
	unsigned short throwingknife;
	unsigned short night_vision_on;
	unsigned short night_vision_off;
	unsigned short MOD_UNKNOWN;
	unsigned short MOD_PISTOL_BULLET;
	unsigned short MOD_RIFLE_BULLET;
	unsigned short MOD_EXPLOSIVE_BULLET;
	unsigned short MOD_GRENADE;
	unsigned short MOD_GRENADE_SPLASH;
	unsigned short MOD_PROJECTILE;
	unsigned short MOD_PROJECTILE_SPLASH;
	unsigned short MOD_MELEE;
	unsigned short MOD_HEAD_SHOT;
	unsigned short MOD_CRUSH;
	unsigned short MOD_FALLING;
	unsigned short MOD_SUICIDE;
	unsigned short MOD_TRIGGER_HURT;
	unsigned short MOD_EXPLOSIVE;
	unsigned short MOD_IMPACT;
	unsigned short script_vehicle;
	unsigned short script_vehicle_collision;
	unsigned short script_vehicle_collmap;
	unsigned short script_vehicle_corpse;
	unsigned short turret_deactivate;
	unsigned short turret_fire;
	unsigned short turret_no_vis;
	unsigned short turret_not_on_target;
	unsigned short turret_on_target;
	unsigned short turret_on_vistarget;
	unsigned short turret_pitch_clamped;
	unsigned short turret_rotate_stopped;
	unsigned short turret_yaw_clamped;
	unsigned short turretstatechange;
	unsigned short turretownerchange;
	unsigned short reached_end_node;
	unsigned short reached_wait_node;
	unsigned short reached_wait_speed;
	unsigned short near_goal;
	unsigned short tag_wheel_front_left;
	unsigned short tag_wheel_front_right;
	unsigned short tag_wheel_back_left;
	unsigned short tag_wheel_back_right;
	unsigned short tag_wheel_middle_left;
	unsigned short tag_wheel_middle_right;
	unsigned short tag_detach;
	unsigned short tag_popout;
	unsigned short tag_body;
	unsigned short tag_turret;
	unsigned short tag_turret_base;
	unsigned short tag_barrel;
	unsigned short front_left;
	unsigned short front_right;
	unsigned short back_left;
	unsigned short back_right;
	unsigned short middle_left;
	unsigned short middle_right;
	unsigned short veh_boatbounce;
	unsigned short veh_collision;
	unsigned short veh_predictedcollision;
	unsigned short veh_leftground;
	unsigned short veh_landed;
	unsigned short veh_jolt;
	unsigned short vehicle_mount;
	unsigned short vehicle_dismount;
	unsigned short constrained;
	unsigned short follow;
	unsigned short j_head;
	unsigned short j_neck;
	unsigned short thermal;
	unsigned short primary;
	unsigned short offhand;
	unsigned short item;
	unsigned short altmode;
	unsigned short exclusive;
	unsigned short scavenger;
	unsigned short primaryoffhand;
	unsigned short secondaryoffhand;
	unsigned short actionslot1;
	unsigned short actionslot2;
	unsigned short actionslot3;
	unsigned short actionslot4;
	unsigned short back_low;
	unsigned short back_mid;
	unsigned short back_up;
	unsigned short pelvis;
	unsigned short auto_change;
	unsigned short begin;
	unsigned short call_vote;
	unsigned short freelook;
	unsigned short intermission;
	unsigned short j_mainroot;
	unsigned short manual_change;
	unsigned short menuresponse;
	unsigned short pistol;
	unsigned short plane_waypoint;
	unsigned short playing;
	unsigned short spectator;
	unsigned short spectating_cycle;
	unsigned short vote;
	unsigned short sprint_begin;
	unsigned short sprint_end;
	unsigned short normal_radar;
	unsigned short fast_radar;
	unsigned short host_sucks_end_game;
	unsigned short tag_engine_left;
	unsigned short tag_engine_right;
	unsigned short slowmo_active;
	unsigned short slowmo_passive;
};

enum hitLocation_t {
	HITLOC_NONE = 0x0,
	HITLOC_HELMET = 0x1,
	HITLOC_HEAD = 0x2,
	HITLOC_NECK = 0x3,
	HITLOC_TORSO_UPR = 0x4,
	HITLOC_TORSO_LWR = 0x5,
	HITLOC_R_ARM_UPR = 0x6,
	HITLOC_L_ARM_UPR = 0x7,
	HITLOC_R_ARM_LWR = 0x8,
	HITLOC_L_ARM_LWR = 0x9,
	HITLOC_R_HAND = 0xA,
	HITLOC_L_HAND = 0xB,
	HITLOC_R_LEG_UPR = 0xC,
	HITLOC_L_LEG_UPR = 0xD,
	HITLOC_R_LEG_LWR = 0xE,
	HITLOC_L_LEG_LWR = 0xF,
	HITLOC_R_FOOT = 0x10,
	HITLOC_L_FOOT = 0x11,
	HITLOC_GUN = 0x12,
	HITLOC_SHIELD = 0x13,
	HITLOC_ARMOR = 0x14,
	HITLOC_SOFT = 0x15,
	HITLOC_NUM = 0x16,
};


enum meansOfDeath_t {
	MOD_UNKNOWN = 0x0,
	MOD_PISTOL_BULLET = 0x1,
	MOD_RIFLE_BULLET = 0x2,
	MOD_EXPLOSIVE_BULLET = 0x3,
	MOD_GRENADE = 0x4,
	MOD_GRENADE_SPLASH = 0x5,
	MOD_PROJECTILE = 0x6,
	MOD_PROJECTILE_SPLASH = 0x7,
	MOD_MELEE = 0x8,
	MOD_HEAD_SHOT = 0x9,
	MOD_CRUSH = 0xA,
	MOD_FALLING = 0xB,
	MOD_SUICIDE = 0xC,
	MOD_TRIGGER_HURT = 0xD,
	MOD_IMPACT = 0xE,
};

enum classType_t
{
	CT_ENTITY = 0,
	CT_HUDELEM = 1,
	CT_PATHNODE = 3
};

enum VAR_TYPE {
	VAR_UNDEFINED = 0x0,
	VAR_BEGIN_REF = 0x1,
	VAR_POINTER = 0x1,
	VAR_STRING = 0x2,
	VAR_ISTRING = 0x3,
	VAR_VECTOR = 0x4,
	VAR_END_REF = 0x5,
	VAR_FLOAT = 0x5,
	VAR_INTEGER = 0x6,
	VAR_CODEPOS = 0x7,
	VAR_PRECODEPOS = 0x8,
	VAR_FUNCTION = 0x9,
	VAR_BUILTIN_FUNCTION = 0xA,
	VAR_BUILTIN_METHOD = 0xB,
	VAR_STACK = 0xC,
	VAR_ANIMATION = 0xD,
	VAR_PRE_ANIMATION = 0xE,
	VAR_THREAD = 0xF,
	VAR_NOTIFY_THREAD = 0x10,
	VAR_TIME_THREAD = 0x11,
	VAR_CHILD_THREAD = 0x12,
	VAR_OBJECT = 0x13,
	VAR_DEAD_ENTITY = 0x14,
	VAR_ENTITY = 0x16,
	VAR_ARRAY = 0xFF,
	VAR_DEAD_THREAD = 0x17,
	VAR_COUNT = 0x18,
	VAR_FREE = 0x18,
	VAR_THREAD_LIST = 0x19,
	VAR_ENDON_LIST = 0x1A,
	VAR_INVALID = 0x1B,
	VAR_ENTREF = 0x30,
	VAR_TOTAL_COUNT = 0x1C,
};

struct opd_s {
	uint32_t sub;
	uint32_t toc;
};


struct scr_entref_t {
	unsigned short entnum;
	unsigned short classnum;
};

struct VariableStackBuffer {
	const char *pos;
	unsigned short size;
	unsigned short bufLen;
	unsigned int localId;
	char time;
	char buf[1];
};

union VariableUnion
{
	int intValue;
	float floatValue;
	unsigned int stringValue;
	float *vectorValue;
	const char *codePosValue;
	unsigned int pointerValue;
	VariableStackBuffer *stackValue;
	unsigned int entityOffset;
};


struct VariableStruct {
	int intValue;
	float floatValue;
	short stringValue;
	const char *string;
	float *vectorValue;
	int objectClassnum;
	int objectNum;
	int objectOffset;
	int type;
	int arraySize;
};


struct VariableValue {
	VariableUnion u;
	int type;
};

struct function_stack_t {
	const char *pos;
	unsigned int localId;
	unsigned int localVarCount;
	VariableValue *top;
	VariableValue *startTop;
};

struct function_frame_t {
	function_stack_t fs;
	int topType;
};

struct scrVmPub_t
{
	VariableValue stack[0x400];
	char unk_0[0x1C];
	unsigned int *localVars;
	VariableValue *maxstack;
	int function_count;
	function_frame_t *function_frame;
	VariableValue *top;
	int breakpointOutparamcount;
	unsigned int inparamcount;
	unsigned int outparamcount;
	function_frame_t function_frame_start[32];
};

struct scrMemTreePub_t {
	char* mt_buffer;
};

struct OnNotifyReturn {
	VariableValue* top;
	int stringValue;
	const char* string;
	int classnum;
	int entnum;
	int paramcount;
};

enum LocalClientNum_t {
	LOCAL_CLIENT_INVALID = 0xFFFFFFFF,
	LOCAL_CLIENT_0 = 0x0,
	LOCAL_CLIENT_LAST = 0x0,
	LOCAL_CLIENT_COUNT = 0x1,
};

struct sIndexedArray_t {
	VariableValue strTop[10000];
};

struct client_t {
	char __0x0[client_t_size];
};

extern scrVmPub_t* gScrVmPub;
extern scrMemTreePub_t* gScrMemTreePub;
extern client_t* client_s;
extern scr_const_t* scr_const;

#endif