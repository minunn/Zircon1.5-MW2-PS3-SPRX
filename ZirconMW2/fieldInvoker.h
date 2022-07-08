#ifndef __FIELDINVOKER_H__
#define __FIELDINVOKER_H__

enum fields_t {
	//Entity fields
	code_classname = 0,
	classname = 1,
	origin = 2,
	model = 3,
	spawnflags = 4,
	target = 5,
	targetname = 6,
	count = 7,
	health = 8,
	dmg = 9,
	angles = 10,
	birthtime = 11,
	script_linkname = 12,
	slidevelocity = 13,

	//Client fields
	name = 0x6000,
	sessionteam = 0x6001,
	sessionstate = 0x6002,
	maxhealth = 0x6003,
	score = 0x6004,
	deaths = 0x6005,
	statusicon = 0x6006,
	headicon = 0x6007,
	headiconteam = 0x6008,
	kills = 0x6009,
	assists = 0x600A,
	hasradar = 0x600B,
	isradarblocked = 0x600C,
	radarmode = 0x600D,
	forcespectatorclient = 0x600E,
	killcamentity = 0x600F,
	killcamentitylookat = 0x6010,
	archivetime = 0x6011,
	psoffsettime = 0x6012,
	pers = 0x6013,

	//Vehicle script fields
	veh_speed = 0x8000,
	veh_pathspeed = 0x8001,
	veh_transmission = 0x8002,
	veh_pathdir = 0x8003,
	veh_pathtype = 0x8004,
	veh_topspeed = 0x8005,
	veh_brake = 0x8006,
	veh_throttle = 0x8007,

	//Vehicle node fields
	veh_targetname = 0,
	veh_target = 1,
	veh_script_linkname = 2,
	veh_script_noteworthy = 3,
	veh_origin = 4,
	veh_angles = 5,
	speed = 6,
	lookahead = 7,

	//HElem Fields // < USAGE > setField(fieldId, entnum, CT_HUDELEM /* 1 */, value);
	x = 0,
	y = 1,
	z = 2,
	fontscale = 3,
	font = 4,
	alignx = 5,
	aligny = 6,
	horzalign = 7,
	vertalign = 8,
	color = 9,
	alpha = 10,
	label = 11,
	sort = 12,
	foreground = 13,
	lowresbackround = 14,
	hidewhendead = 15,
	hidewheninmenu = 16,
	splatter = 17,
	glowcolor = 18,
	glowalpha = 19,
	archived = 20,

};

template<typename T>
inline VariableValue* LocalPush(T value, VariableValue* tmpValue) {
	return 0;
}

template<>
inline VariableValue* LocalPush(short value, VariableValue* tmpValue) {
	tmpValue->type = VAR_INTEGER;
	tmpValue->u.intValue = value;
	return tmpValue;
}

template<>
inline VariableValue* LocalPush(int value, VariableValue* tmpValue) {
	tmpValue->type = VAR_INTEGER;
	tmpValue->u.intValue = value;
	return tmpValue;
}

template<>
inline VariableValue* LocalPush(bool value, VariableValue* tmpValue) {
	tmpValue->type = VAR_INTEGER;
	tmpValue->u.intValue = value;
	return tmpValue;
}

template<>
inline VariableValue* LocalPush(char* value, VariableValue* tmpValue) {
	tmpValue->type = VAR_STRING;
	tmpValue->u.stringValue = SL_GetString(value);
	return tmpValue;
}

template<>
inline VariableValue* LocalPush(const char* value, VariableValue* tmpValue) {
	tmpValue->type = VAR_STRING;
	tmpValue->u.stringValue = SL_GetString(value);
	return tmpValue;
}

template<>
inline VariableValue* LocalPush(float value, VariableValue* tmpValue) {
	tmpValue->type = VAR_FLOAT;
	tmpValue->u.floatValue = value;
	return tmpValue;
}

template<>
inline VariableValue* LocalPush(double value, VariableValue* tmpValue) {
	tmpValue->type = VAR_FLOAT;
	tmpValue->u.floatValue = value;
	return tmpValue;
}

template<>
inline VariableValue* LocalPush(float* value, VariableValue* tmpValue) {
	tmpValue->type = VAR_VECTOR;
	tmpValue->u.vectorValue = value;
	return tmpValue;
}

template<typename T>
inline T Return(VariableUnion &u) {
	Printf("Unsupported Return Type | Return(value)\n");
}

template<>
inline char* Return(VariableUnion &u) {
	return (char*)SL_ConvertToString(u.stringValue);
}

template<>
inline const char* Return(VariableUnion &u) {
	return SL_ConvertToString(u.stringValue);
}

template<>
inline float* Return(VariableUnion &u) {
	return u.vectorValue;
}

template<>
inline float Return(VariableUnion &u) {
	return u.floatValue;
}

template<>
inline bool Return(VariableUnion &u) {
	return (bool)u.intValue;
}

template<>
inline short Return(VariableUnion &u) {
	return (short)u.intValue;
}

template<>
inline int Return(VariableUnion &u) {
	return u.intValue;
}


namespace Fields {
	template<typename returnType>
	inline returnType getField(fields_t fieldId, int entnum, int classnum) {
		Scr_GetObjectField(classnum, entnum, fieldId);
		returnType retVal = Return<returnType>(gScrVmPub->top->u);
		Scr_ClearOutParams();
		return retVal;
	}

	template<typename Value>
	inline void setField(fields_t fieldId, int entnum, int classnum, Value value) {
		Push<Value>(value);
		Scr_SetNumParam(1);
		Scr_SetObjectField(classnum, entnum, fieldId);
		Scr_ClearOutParams();
	}
	
	namespace String {

		template <typename returnType>
		returnType getField(fields_t fieldId, const char* string, int entnum, int classnum) {
			Scr_GetObjectField(entnum, entnum, fieldId);
			int parentId = gScrVmPub->top->u.intValue;
			returnType retVal = Return<returnType>(*(VariableUnion*)GetVariableValueAddress(parentId, GetVariable(parentId, SL_GetString(string))));
			Scr_ClearOutParams();
			return retVal;
		}

		template <typename value>
		void setField(fields_t fieldId, const char* string, int entnum, int classnum, value P1) {
			/*Scr_GetObjectField(classnum, entnum, fieldId);

			int parentId = gScrVmPub->top->u.intValue;
			int childId = FindVariable(parentId, SL_GetString(string));
			
			VariableValue* setValue = (VariableValue*)0x10085000;
			setValue = LocalPush<value>(P1, setValue);
			printf("ChildID 0x%X -- EntityID 0x%X\n", childId, Scr_GetEntityId(entnum, classnum));
			SetVariableEntityFieldValue(Scr_GetEntityId(entnum, classnum) << 4, childId, setValue);
			Scr_ClearOutParams();*/
			//broken atm
		}
	}
}

#endif /* __FIELDINVOKER_H__ */