#ifndef __LEVEL_H__
#define __LEVEL_H__

struct SpawnVar
{
	bool spawnVarsValid;
	int numSpawnVars;
	char *spawnVars[64][2];
	int numSpawnVarChars;
	char spawnVarChars[2048];
};

struct cached_tag_mat_t
{
	int time;
	int entnum;
	unsigned short name;
	float tagMat[4][3];
};

struct com_parse_mark_t
{
	int lines;
	const char *text;
	int ungetToken;
	int backup_lines;
	const char *backup_text;
};


struct trigger_info_t
{
	unsigned short entnum;
	unsigned short otherEntnum;
	int useCount;
	int otherUseCount;
};

struct level_locals_t
{
	gclient_s *clients; //0x00 - 0x04
	gentity_s *gentities; //0x04 - 0x08
	int num_entities; //0x08 - 0x0C
	gentity_s *firstFreeEnt; //0x0C - 0x10
	gentity_s *lastFreeEnt; //0x10 - 0x14
	int turrets; //0x14 - 0x18
	void *logFile; //0x18 - 0x1C
	int initializing; //0x1C - 0x20
	int clientSpawning;
	objective_t objectives[32];
	int maxclients;
	int framenum;
	int time;
	int previousTime;
	int frameTime;
	int startTime;
	int teamScores[4];
	int lastTeammateHealthTime;
	int bUpdateScoresForIntermission;
	bool teamHasRadar[4];
	bool teamRadarBlocked[4];
	int manualNameChange;
	int numConnectedClients;
	int sortedClients[18];
	char voteString[1024];
	char voteDisplayString[1024];
	int voteTime;
	int voteExecuteTime;
	int voteYes;
	int voteNo;
	int numVotingClients;
	SpawnVar spawnVar;
	int savepersist;
	EntHandle droppedWeaponCue[32];
	float fFogOpaqueDist;
	float fFogOpaqueDistSqrd;
	int currentPlayerClone;
	trigger_info_t pendingTriggerList[256];
	trigger_info_t currentTriggerList[256];
	int pendingTriggerListSize;
	int currentTriggerListSize;
	int finished;
	int bPlayerIgnoreRadiusDamage;
	int bPlayerIgnoreRadiusDamageLatched;
	int registerWeapons;
	int bRegisterItems;
	int currentEntityThink;
	void *openScriptIOFileHandles[1];
	void *openScriptIOFileBuffers[1];
	com_parse_mark_t currentScriptIOLineMark;
	cached_tag_mat_t cachedTagMat;
	int scriptPrintChannel;
	float compassMapUpperLeft[2];
	float compassMapWorldSize[2];
	float compassNorth[2];
	int vehicles;
	int hudElemLastAssignedSoundId;
};

#define __nomessages__			0x1
#define __unfrozenmenu__		0x2
#define __nosounds__			0x4
#define __novision__			0x10
#define __stealth__				0x200
#define __nopregametext__		0x400

struct LocalLevel_t {
	gentity_s* Slides[50], *Platform[100], *object[1];
	char crateCount, slideCount, spawnObject;
	char isPlatformSpawned;
	float platformOrigin[3];

	bool pulsingEnabled;
	game_hudelem_s* pulseElem;
	char* pulsingText;
	handle_t doHeart;

	int32_t menuFlags;
	gclient_s* spawnerClient;
	int8_t antiLeave, isAzza, disabledAnti, botTeamIndex;
	int32_t oldScoreLimit, oldTimeLimit;
};


extern level_locals_t* level_locals;
extern LocalLevel_t* level;

#endif /* __LEVEL_H__ */