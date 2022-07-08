//0x000135C0 AimTarget_IsTargetVisible
//0x00048600 CG_CanSeeFriendlyHead
//Original Aimbot By NickBeHaxing & Milky4444
int GetIndex()
{
	int cg_s = *(int*)(0x915254);
	if (cg_s == 0)
		return -1;
	return *(int*)(cg_s + 0x3250);
}
bool isInGameOrLoading() {
	int cg_s = *(int*)(0x915254);
	return cg_s;//cg_s != 0 when loading or in game
}
float angleseeeee[3];
vec3 vectoangles(vec3 Angles)
{
	float forward;
	float yaw, pitch;
	float PI = 3.1415926535897931;
	if (Angles.x == 0 && Angles.y == 0)
	{
		yaw = 0;
		if (Angles.z > 0) pitch = 90.00;
		else pitch = 270.00;
	}
	else
	{
		if (Angles.x != -1) yaw = (float)(atan2((double)Angles.y, (double)Angles.x) * 180.00 / PI);
		else if (Angles.y > 0) yaw = 90.00;
		else yaw = 270;
		if (yaw < 0) yaw += 360.00;

		forward = (float)sqrt((double)(Angles.x * Angles.x + Angles.y * Angles.y));
		pitch = (float)(atan2((double)Angles.z, (double)forward) * 180.00 / PI);
		if (pitch < 0) pitch += 360.00;
	}
	angleseeeee[0] = -pitch;
	angleseeeee[1] = yaw;
	angleseeeee[2] = 0;

	vec3 Angless = { angleseeeee[0], angleseeeee[1], angleseeeee[2] };
	return Angless;
}

/*
struct usercmd_s
{
    int commandTime; //0x0000 
    int buttons; //0x0004 
    vec3 viewangles; //0x0008 
	char _0x0014[20];
};//Size=0x0028
*/
/*
opd_s ucmd = {0x00218D68,TOC};
void(*SV_GetUsercmd)(int clientNum, unsigned int) = (void(*)(int,unsigned int))&ucmd;
usercmd_s *getMyCmd() {
	//SV_GetUsercmd(client,0x10070500);//should store the pointer at 0x10070500
	return (usercmd_s*)0x10070500;
}*/
/*void setViewAngles(vec3 angles) {
	if (getMyCmd() != 0) {
		getMyCmd()->viewangles.x = angles.x;
		getMyCmd()->viewangles.y = angles.y;
		getMyCmd()->viewangles.z = 0;
	} else {
		printf2("Problem!");
	}
}
void setViewAngles(float x, float y) {
	vec3 angl = {x,y,0};
	setViewAngles(angl);
}*/
float dx, dy, dz;
float GetDistance(vec3 c1, vec3 c2)
{
	float dx = c2.x - c1.x;
	float dy = c2.y - c1.y;
	float dz = c2.z - c1.z;

	return sqrt((float)((dx * dx) + (dy * dy) + (dz * dz)));
}
#define Angleoffset (0x3358)
#define BaseAngle (0xE0)
bool Aimbot = true;//true when aimbot enabled
bool Required = false;//true when you have to aim down sight
bool visibleOnly = true;//true if you want it to only check if they are visible
bool shootToEnable = false;//true if r1 makes it work
bool autoShoot = false;//makes you shoot when a player is visible
bool autoAim = false;//makes you aim when a client is visible
bool semiAutoMode = false;
bool isCurrentlyShooting = false;
bool UnfairAimbot = false;//overrides the rest. Kills closest person when you shoot
bool silentAimbot = false;//not really used YET
bool isAiming() {
	return (ButtonMonitoring::ButtonPressed(ButtonMonitoring::L1) && ButtonMonitoring::ButtonPressed(ButtonMonitoring::R1) || ButtonMonitoring::ButtonPressed(ButtonMonitoring::L1)) || (shootToEnable && ButtonMonitoring::ButtonPressed(ButtonMonitoring::R1)) || *(char*)0x0095afe0 == 1 || *(char*)*(int*)0x9FD590 == 1;
}
int GetHealth()
{
	int cg_s = *(int*)(0x915254);
	return *(char*)(cg_s + 0x153);
}
bool isFFA()
{
	int serverinfo = *(int*)(0x915258);
	char ffa = *(char*)(serverinfo + 0x21);
	if(ffa == 0x6D)
	{
		return true;
	}
	return false;
}
long ClActive()
{
	return *(long*)0x9FD590;
}
int Centity(int ent)
{
	int cent = *(int*)0x91527C;
	if (cent == 0) 
		return -1;
	return cent + (ent * 0x1F8);
};
//Thanks To Kurt & Milky4444 For Addresses In This Funcution
//Not Working, Call in Hook
opd_s SL_GSOS = {0x1FEE88/*0x200E38*/,TOC};
unsigned int(*SL_GetString)(const char *str,int user, int unk) = (unsigned int(*)(const char*,int,int))&SL_GSOS;
opd_s GCDObJ = {0x1E59A0,TOC};
int (*Com_GetClientDObj)(unsigned int handle, int localClientNum) = (int(*)(unsigned int,int))&GCDObJ;
opd_s DObjGWTP = {/*0x52738 NOT RIGHT ADDRESS*//*0x519A0*/0x052738,TOC};
bool (*CG_DObjGetWorldTagPos)(unsigned int targ_centity, unsigned int dobj, unsigned int tagIndex, float *pos) = (bool(*)(unsigned int,unsigned int,unsigned int,float*))&DObjGWTP;
opd_s gti = {0x1BE740,TOC};
int (*G_TagIndex)(char *tag) = (int(*)(char*))&gti;
bool AimTarget_GetTagPos(int targEnt, unsigned int targIndex,float *outPos)
{
	if (Centity(targEnt) == -1)
		return false;
	//printf2("Getting DOBJ...\n");
	unsigned int handle = *(unsigned int*)(Centity(targEnt) + 0xD0);
	//printf2("Handle: %i\n",(int)handle);
	unsigned int DObj = Com_GetClientDObj(handle ,0);
	if (DObj == 0)
		return false;
	//printf2("Got DOBJ %i. Getting tag pos...\n",DObj);
	return CG_DObjGetWorldTagPos(Centity(targEnt), DObj, targIndex, outPos);//crashes on this function
}
opd_s atgtp = {0x013460,TOC};
void (*AimTarget_GetTagPoss)(unsigned int centity, unsigned int tagName, float *pos) =  (void(*)(unsigned int,unsigned int, float *))&atgtp;
vec3 retttt;
int headTag = 0;
vec3 playerHeadCoords[20];
vec3 GetBonePos(int playerIndex/*, char* tagName*/)
{
	//if (headTag == 0) {
		//headTag = SL_GetString("j_neck",0,0);//G_TagIndex("j_neck");
		//printf2("Tag: %i\n",headTag);
	//}
	//if (headTag != 0) {
	if (headTag == 0) {
		headTag = /*0x0BE3;*/(int)(*(short*)(*(int*)0x71E82C+0x1AC));
		printf2("Head Tag: %i\n",headTag);
	}
	if (headTag != 0) {
		float out[3];
		if (AimTarget_GetTagPos(playerIndex, headTag/*SL_GetString(tagName)*/, out)) {
			//printf("Got tag pos\n");
			retttt.x = out[0];
			retttt.y = out[1];
			retttt.z = out[2];
		}
		
	} else {
		printf2("ERROR: Head tag = 0\n");
	}
	return retttt;
}
/*
//I believe this worked, but it's not that great
opd_s CG_CanSeeFriendlyHead_t = {0x00048600,TOC};
bool(*CG_CanSeeFriendlyHead)(int localClient, unsigned int centity) = (bool(*)(int,unsigned int))&CG_CanSeeFriendlyHead_t;
bool isPlayerVisible(int player) {
	return CG_CanSeeFriendlyHead(0,Centity(player));
}*/
struct trace_t{
    float fraction;
    float normal[3];
    int surfaceFlags;
    int contents;
    const char *material;
    char hitType;
    unsigned short hitId;
    unsigned short modelIndex;
    unsigned short partName;
    unsigned short partGroup;
    bool allsolid;
    bool startsolid;
    bool walkable;
};//size = 10?
opd_s glt = {0x096178/*G0x0188560*/,TOC};
void (*CG_LocationalTrace)(trace_t* trace, float *start, float *end, int passEntityNum, int contentmask/*, char *priorityMap*/) = (void(*)(trace_t*, float*, float*, int, int/*, char**/))&glt;
bool Trace(int clientNum, vec3 start, vec3 end){
    trace_t trace;
    CG_LocationalTrace(&trace, (float*)&start, (float*)&end, clientNum, /*0x2806831*//*0x800811*/0x2803001/*, 0*/);
	//printf2("Trace: %i\n",ServerDataStruct.loctrace);
	//if (trace.fraction > 0.9f)
		//printf2("Trace: %i percent\n",(int)(trace.fraction*100));
	return (trace.fraction >= 0.95f);
}
int GetStance(int ent)
{
	int stance = (int)(*(char*)(Centity(ent) + 0x63));
	//0x00 = standing
	//0x04 = crouch
	//0x08 = prone
}
float getHeight(int client) {
	int stance = GetStance(client);
	switch(stance) {
	case 0:
		return 56;
	case 4:
		return 21;
	case 8:
		return 15;
	default:
		return 0;
	}
	return 0;
}
float dropHeightArray[20];
float getDrop(int client) {
	int stance = GetStance(client);
	switch(stance) {
	case 0:
		return -10;
	case 4:
		return -25;
	case 8:
		return -40;
	default:
		return -10;
	}
	return -10;
}
bool isSameTeam(int cl1,int cl2)
{
		//Online Address
        //ClientInfo_t = 0x367F4E85
	    //Offline Address
        //ClientInfo_t = 0x36BE4E85
	    int cg_s = *(int*)(0x915254);
		int ent2 = *(char*)(cg_s + 0xF6E80 + ((cl2) * 0x544) + 0x2F);
	    int ent1 = *(char*)(cg_s + 0xF6E80 + ((cl1) * 0x544) + 0x2F);
	    if((ent1) == (ent2))
	    {
	        return true;
	    }
	    return false;
}
bool isAlive(int cl)
{
	if(*(char*)(Centity(cl) + 0x02) == 0x01)
	{
		return true;
	}
	return false;
}
vec3 getOrigin(int ent)
{
	int cent = Centity(ent);
	return *(vec3*)(cent + 0x18);
}

namespace Visible {

struct cTrace
{
    float Fraction;
    unsigned char szUnknown0[292];
};
struct tracearg_t {
	int unk1,unk2,unk3,unk4,unk5,unk6,unk7,unk8,unk9,unk10;
	char padding[100];
};
int CG_TraceAddress = 0x00095EC8;
opd_s trace_t = {CG_TraceAddress,TOC};
void (*CG_Trace)(cTrace *results, vec3 start, vec3 mins, vec3 maxs, vec3 end, int passEntityNum, int contentMask, tracearg_t* TraceArg, bool staticModels) = (void(*)(cTrace *, vec3, vec3 , vec3, vec3, int, int, tracearg_t*, bool))&trace_t;



tracearg_t TRACEARG;
 
bool IsVisible( vec3 v3EndPos, float nHeight )
{
	TRACEARG.unk5 = 1023;
	TRACEARG.unk6 = 1023;
    cTrace mTrace;
    v3EndPos.z += nHeight;
    vec3 v3Zero = { 0.0f, 0.0f, 0.0f };
    //CG_Trace( &mTrace, gRefDef->Location, v3EndPos,*(vec3*)0x71CEEC/*Found in AimTarget_IsTargetVisible*/ /**(vec3*)0x71E864*//*Used in CG_IsHeadVisible*/, v3Zero, 0x803003/*gGame->iLocalClient*/, 0x2801001/*0x2803001*/ ,0,0);
    CG_Trace( &mTrace, getOrigin(GetIndex()),v3Zero,v3Zero,v3EndPos,0x803003,0x2801001,&TRACEARG,0);
	return( mTrace.Fraction >= 0.95f );
}
/*
bool IsVisible2( vec3 End )
{
    cTrace t;
    vec3 Null = {0,0,0};
    CG_Trace( &t, getOrigin(GetIndex())/RefDef->Origin/,Null, Null,End,GetIndex()/Cg->ClientNumber/, 0x803003 ,0,0);
 
    return ( t.Fraction >= 0.97f );
}*/

}
bool playerVisibilities[20];
int GetNearestPlayer(int client, bool ignoreVisibleChecks = false)
{
	if (Centity(0) == -1)
		return -1;
	if (client == -1)
		return -1;
    int nearestClient = -1;
    double nearestDistance = 1E+08f;
	for (int i = 0; i < 18; i++)
    {
        if (i != client)
        {
            if (isAlive(i))
            {
				if (!isSameTeam(client, i) || isFFA())
				{
					if (ignoreVisibleChecks || playerVisibilities[i] == 1) {
						float Distance = GetDistance(getOrigin(client), getOrigin(i));
						if (Distance < nearestDistance)
						{
							nearestDistance = Distance;
							nearestClient = i;
						}
					}
				}
			}
        }
    }
	if (!visibleOnly && nearestClient == -1 && !ignoreVisibleChecks)//when visibleOnly is true, this won't happen
		return GetNearestPlayer(client,true);
	//int b = 2;
	//if (nearestClient != -1)
		//b = (int)playerVisibilities[nearestClient];
	//printf2("Aiming At Client %i Visible: %i\n",nearestClient,b);
	return nearestClient;
}









vec3 AimAngles = {0,0,0};
bool aimbothit = false;
//bool silentAim = true;


//vec3 playerHeadCoordinates[20];
void Aimthread(uint64_t)
{
	/*
	0x0095afe0 aim
	0x0095b080 shoot
	*/
	for(;;) {
		if (*(char*)0x01D17A8C && ClActive() >= 0x10000) {
			//printf2("\n\nStart\n");
			if (Aimbot && UnfairAimbot) {
				int targindex = GetNearestPlayer(GetIndex(),true);
				if (targindex != -1 && *(char*)0x0095b080 == 1) {
					killClient(targindex);
					sleep(100);
				}
			}
			else if(Aimbot && (!Required || isAiming()))
			{
				//printf2("Getting nearest player\n");
                int targindex = GetNearestPlayer(GetIndex());
				if (targindex != -1) {
					//printf2("retrieving head coords\n");
					vec3 Aim = {playerHeadCoords[targindex].x,playerHeadCoords[targindex].y,playerHeadCoords[targindex].z};//=getOrigin(targindex);
					/*Aim.x = playerHeadCoords[targindex].x;
					Aim.y = playerHeadCoords[targindex].y;
					Aim.z = playerHeadCoords[targindex].z;*/
					vec3 me=/**(vec3*)0x36af1198;*/getOrigin(GetIndex());
					/*me.x = playerHeadCoords[GetIndex()].x;
					me.y = playerHeadCoords[GetIndex()].y;
					me.z = playerHeadCoords[GetIndex()].z;*/
					//Aim.z+=getDrop(targindex);
					//printf2("Drop Height: %i\n",(int)dropHeightArray[targindex]);
					vec3 angles = {Aim.x - me.x,Aim.y - me.y,Aim.z - me.z/* - 12*//*+dropHeightArray[targindex]*/};
					/*
					#if CEX == 0
						float x = *(float*)read_process(ClActive() + BaseAngle,4);
						float y = *(float*)read_process(ClActive() + BaseAngle + 0x4,4);
						float z = *(float*)read_process(ClActive() + BaseAngle + 0x8,4);
					#else
						float x = *(float*)(ClActive() + BaseAngle);
						float y = *(float*)(ClActive() + BaseAngle + 0x4);
						float z = *(float*)(ClActive() + BaseAngle + 0x8);
					#endif
					*/
					//printf2("getting base angles");
					float x = 0; 
					float y = 0;
					if (ClActive() >= 0x10000) {
						x = *(float*)(ClActive() + BaseAngle);
						y = *(float*)(ClActive() + BaseAngle + 0x4);
						/*int a = (int)read_process(ClActive() + BaseAngle,4);
						if (a >= 0x10000)
							x = *(float*)a;
						a = (int)read_process(ClActive() + BaseAngle + 0x4,4);
						if (a >= 0x10000)
							y = *(float*)a;*/
					}
					//printf2("Got base angles\n");
					//float z = *(float*)(ClActive() + BaseAngle + 0x8);
					vec3 base = {x,y,0};
					vec3 cangle = vectoangles(angles);
					vec3 fin = {cangle.x - base.x,cangle.y - base.y,0};
					AimAngles.x = fin.x;
					AimAngles.y = fin.y;
					AimAngles.z = 0;
					aimbothit = true;
					if (!silentAimbot) {
						*(float*)(ClActive() + Angleoffset) = fin.x;
						*(float*)(ClActive() + Angleoffset + 0x4) = fin.y;
						*(float*)(ClActive() + Angleoffset + 0x8) = fin.z;
					}
					if (autoShoot/* && !silentAimbot*/) {
						if (playerVisibilities[targindex]) {
							if (!isCurrentlyShooting) {
								if(autoAim)
									*(char*)0x0095afe0 = 1;//aim
								*(char*)0x0095b080 = 1;
								if (semiAutoMode) {
									sleep(2);
									*(char*)0x0095b080 = 0;
								} else {
									isCurrentlyShooting = true;
								}
							}
						} else {
							if (isCurrentlyShooting || (autoAim && *(char*)0x0095afe0 == 1)) {
								isCurrentlyShooting = false;
								*(char*)0x0095b080 = 0;
								if(autoAim)
									*(char*)0x0095afe0 = 0;//unaim
							}
						}
					}
				} else {
					aimbothit = false;
					if (autoShoot/* && !silentAimbot*/) {
						//no current target so stop shooting
						if (isCurrentlyShooting) {//I am shooting
							isCurrentlyShooting = false;
							*(char*)0x0095b080 = 0;
							if(autoAim)
								*(char*)0x0095afe0 = 0;//unaim
						}
					}
				}
			}
			sleep(1);
		} else {
			sleep(200);
		}
	}
}

































/*
void NoSpread()
{
    // get playerState_s struct
    int playerStatePtr = (int)cgArray + 263836;
 
    // get weaponDef struct and our starting spread float value
    float spread;
    int weaponDefPtr = BG_GetWeaponDef(GetCurrentWeapon());
    spread = *(float*)((int)cgArray + 457488) / 255.0f;
 
    // get final spread float value
    float minSpread, maxSpread;
    BG_GetSpreadForWeapon(playerStatePtr, weaponDefPtr, &minSpread, &maxSpread);
    if (*(float*)(playerStatePtr + 360) == 1.0f) // if (fWeaponPosFrac == 1.0f) get minSpread from weaponDef
        spread = *(float*)(weaponDefPtr + 1736) + ((maxSpread - *(float*)(weaponDefPtr + 1736)) * spread);
    else
        spread = minSpread + ((maxSpread - minSpread) * spread);
 
    // get our view origin
    vec3 viewOrigin;
    if (!CG_GetPlayerViewOrigin(0, playerStatePtr, viewOrigin))
        return;
 
    // get our view axis
    vec3 viewAngles;
    vec3 viewAxis[3];
        viewAngles[0] = *(float*)((int)cgArray + 389012);
        viewAngles[1] = *(float*)((int)cgArray + 389016);
        viewAngles[2] = 0;
        AngleVectors(viewAngles, viewAxis[0], viewAxis[1], viewAxis[2]);
 
    // get the range
    float range;
    //if (*(int*)(weaponDefPtr + 32) == 3) // if (weapClass == WEAPCLASS_SPREAD)
    //    range = *(float*)(weaponDefPtr + 1964); // range = fMinDamageRange; (probably for shotguns)
    //else
        range = 8192.0f; // from bulletrange dvar
 
    // get the end vector in the game world of the spread and the direction vector too
    // we use the direction vector directly instead of the end vector
    vec3 spreadEndVec;
    vec3 spreadDirection;
    GetSpreadEndVec(viewOrigin, spreadEndVec, spread, *(int*)playerStatePtr, spreadDirection, viewAxis[0], viewAxis[1], viewAxis[2], range);
    
    // convert the spread direction to angles
    vectoangles(spreadDirection, viewAngles);
    
    // fix our angles
    usercmd_s* oldcmd = CL_GetUserCmd(CL_GetCurrentCmdNumber() - 1);
 
    // get the angle delta and write it to the user cmd
    // do -= because we want to get the inverse of the spread
    oldcmd->angles[0] -= ANGLE2SHORT(-(*(float*)((int)cgArray + 389012) - viewAngles[0]));
    oldcmd->angles[1] -= ANGLE2SHORT(-(*(float*)((int)cgArray + 389016) - viewAngles[1]));
 
    oldcmd->serverTime += 1;
}*/



opd_s CL_WritePacket_t = {0x000A1A88,TOC};
int(*CL_WritePacket)(int localClient) = (int(*)(int))&CL_WritePacket_t;
opd_s CL_CreateNewCommands_t = {0x000A3BB0,TOC};
int(*CL_CreateNewCommands)(int localClient) = (int(*)(int))&CL_CreateNewCommands_t;

//cmdnum*0x2c+0x66AA0+*(int*)0x00AE9780
int getCurrentCmd(int add) {
	//0x3462BD58 works too
	//128*0x28+0x3364+*(int*)0x9FD590
	return ((*(int*)(128*0x28+0x3364+ClActive()))+add) & 0x7f;
	//return *(int*)(0x6A4A4+*(int*)0x00AE9780);
}
int getCmdAddr(int cmdnum) {
	return cmdnum*0x28+0x3364+ClActive();//*(int*)0x9FD590
	//cmdnum*0x28+0x3364+*(int*)0x9FD590
}
/*int getCCmdAddr(int cmdnum) {
	return cmdnum*0x24+0x680A4+*(int*)0x00AE9780;
}*/
#define ANGLE2SHORT(x)   ((int)((x)*65536/360) & 65535)
struct vec3i {
	int x,y,z;
};
float normalize180(float num) {
	while (num < -180)
		num+=360;
	while (num > 180)
		num-=360;
	return num;
}
float normalize90(float num) {
	while (num < -90)
		num+=180;
	while (num > 90)
		num-=180;
	if (num > 89)
		num = 88;
	if (num < -89)
		num = -88;
	return num;
}

/*void calcViewAngles() {
	int targindex = GetNearestPlayer(GetIndex());
	if (targindex != -1) {
		vec3 Aim = {positions[targindex].x,positions[targindex].y,positions[targindex].z};
		vec3 *me=getViewOrigin();
		vec3 angles = {Aim.x - me->x,Aim.y - me->y,Aim.z - me->z};
		getBaseAngles();
		vec3 cangle = vectoangles(angles);
		vec3 fin = {cangle.x - baseAngleRet.x,cangle.y - baseAngleRet.y,0};
		AimAngles.x = fin.x;
		AimAngles.y = fin.y;
		AimAngles.z = 0;
		aimbothit = true;
	} else {
		aimbothit = false;
	}
}*/

int hkCL(int r3);
int wp_redo(int r3) {
	char bytes[16] = {0x7D, 0x80, 0x00, 0x26, 0x1D, 0x63, 0x0C, 0x90, 0x39, 0x6B, 0x0B, 0x40, 0x81, 0x22, 0xCA, 0x4C};
	write_process((void*)0x000A1A88,bytes,16);//crashes here
	int j = CL_WritePacket(r3);
	PatchInJump(0x000A1A88,(int)hkCL,false);
	return j;
}
int clcnc_redo(int r3) {
	char bytes[16] = {0xF8, 0x21, 0xFE, 0x31, 0x7C, 0x08, 0x02, 0xA6, 0xFB, 0xC1, 0x01, 0x78, 0xFB, 0x21, 0x01, 0x50};
	write_process((void*)0x000A3BB0,bytes,16);
	int j = CL_CreateNewCommands(r3);
	PatchInJump(0x000A3BB0,(int)hkCL,false);
	return j;
}




int oviewangles[3];
//int cviewangles[3];

//vec3i viewangles[128];

void DoSilentAim(bool bAdjust)
{
    int cmd = getCmdAddr(getCurrentCmd(0));
	int oldcmd = getCmdAddr(getCurrentCmd(-1));

	vec3i *oldcmdangles = (vec3i*)(oldcmd+0x8);
	vec3i *cmdangles = (vec3i*)(cmd+0x8);

    if (bAdjust) // Do adjustment
    {

        /* Backup servertime */
        int stime = *(int*)oldcmd;

        /* Copy current command data to old command */
        memcpy((void*)oldcmd, (void*)cmd, 0x28);

        /* Restore old servertime but add 1 to activate l33t h4x */
		*(int*)oldcmd = stime+1;

        /* Backup old viewangles */
        memcpy(oviewangles,oldcmdangles,4*3);


		int x = ANGLE2SHORT(/*normalize90(*/AimAngles.x/*)*/);
		int y = ANGLE2SHORT(/*normalize180(*/AimAngles.y/*)*/);

        /* Not ideal (see below) */
        oldcmdangles->x = x;
        oldcmdangles->y = y;

		//cmdangles->x = /*cmdangles->x + */x;
        //cmdangles->y = /*cmdangles->y + */y;

		//*(int*)(oldcmd+0x4) &= ~(1<<0);//unshoot old cmd
		//if(autoShoot)
			//*(int*)(cmd+0x4) |= (1<<0);//shoot    oldcmd does not work
		//*(int*)(cmd+0x4) |= (1<<11);//aim
		//printf2("Set Silent Aim Angles\n");
		/*for (int i = 0; i < 128; i++) {
			int cmd = getCmdAddr(getCurrentCmd(i));
			vec3i *angles = (vec3i*)(cmd+0x8);
			memcpy(angles,&(viewangles[i]),4*3);
			angles->x = x;
			angles->y = y;
		}*/
    }
    else // Fix angles
    {
        /* Restore old viewangles */
        memcpy(oldcmdangles,oviewangles, 4*3);
		//memcpy(cviewangles, cmdangles, 4*3);
		//*(int*)(cmd+0x4) &= ~(1<<0);//unshoot
		//*(int*)(cmd+0x4) &= ~(1<<11);//unaim
		/*for (int i = 0; i < 128; i++) {
			int cmd = getCmdAddr(getCurrentCmd(i));
			vec3i *angles = (vec3i*)(cmd+0x8);
			memcpy(&(viewangles[i]),angles,4*3);
		}*/
    }
} 
/*
bool AntiAimCmd(usercmd_t* c)
{
    c->buttons &= ~(1<<28);
    c->buttons &= ~(1<<11);
    return true;
}*/

int hkCL(int r3)
{
	int ret;
	//printf2("%i\n",aimbothit);
	//int ret = clcnc_redo(r3);
	//aimbothit = true;
	if (aimbothit && silentAimbot && Aimbot) {

		DoSilentAim(1); // Adjust angles

		ret = wp_redo(r3);

		DoSilentAim(0); // Fix angles
	} else {
		ret = wp_redo(r3);
	}
	//return wp_redo(r3);
	return ret;
} 

/*
bool tmpautoshoot = false;
void Aimthread(uint64_t)
{
	for(;;) {
		if(AimbotEnabled && isInGameOrLoading()) {
			if (amIAiming() || !RequireAiming) {
				calcViewAngles();
				if (aimbothit && !silentAim) {
					setViewAngles(AimAngles.x,AimAngles.y,AimAngles.z);
					if(autoShoot) {
						tmpautoshoot = true;
						*(char*)0x00AE1820 = 1;
					}
				} else {
					if(autoShoot && tmpautoshoot) {
						tmpautoshoot = false;
						*(char*)0x00AE1820 = 0;
					}
				}
			} else {
				if(autoShoot && tmpautoshoot) {
					tmpautoshoot = false;
					*(char*)0x00AE1820 = 0;
				}
			}
		}
		sleep(1);
	}
}*/