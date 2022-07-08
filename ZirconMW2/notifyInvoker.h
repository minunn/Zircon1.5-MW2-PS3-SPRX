#ifndef __NOTIFY_H__ 
#define __NOTIFY_H__

struct NotifyReturn {
	int entnum;
	unsigned int classnum;
	unsigned int stringValue;
	const char* string;
	VariableValue* top;
};

extern NotifyReturn* notifyReturn;

inline int getNotifyParams() {
	int count = 0;
	for (int i = (int)notifyReturn->top; *(int*)(i + 4) != VAR_PRECODEPOS; i -= 8)
		count++;
	return count;
}

inline void parseLocalNotifies(int notifyListOwnerId, unsigned int stringValue, VariableValue* top) {
	notifyReturn->entnum = Scr_GetSelf(notifyListOwnerId);
	notifyReturn->classnum = Scr_GetEntityIdRef(notifyListOwnerId)->classnum;
	notifyReturn->stringValue = stringValue;
	notifyReturn->string = SL_ConvertToString(stringValue);
	notifyReturn->top = top;
}

inline bool OnLevelNotify(const char* string) {
	return !strcmp(notifyReturn->string, string);
}

inline VariableStruct* OnNotifyRaw(const char* string, int entnum, unsigned int classnum, int paramcount) {
	if (!strcmp(notifyReturn->string, string) && notifyReturn->entnum == entnum && notifyReturn->classnum == classnum) {
		memset((void*)0x10035000, 0, 0x1500);
		int pointerType, arraySize, parentId;
		VariableStruct* ret = (VariableStruct*)0x10035000;
		VariableUnion* retUnion;
		parentId = gScrVmPub->top->u.intValue;
		arraySize = paramcount;

		for (int i = 0; i < arraySize; i++) {
			retUnion = &gScrVmPub->top->u;
			pointerType = gScrVmPub->top->type;
			switch (pointerType) {
			case VAR_UNDEFINED:
				ret[i].intValue = 0;
				break;
			case VAR_POINTER:
				if (GetObjectType(retUnion->pointerValue) == 0x16) {
					ret[i].objectClassnum = Scr_GetEntityIdRef(retUnion->entityOffset)->classnum;
					ret[i].objectNum = Scr_GetSelf(retUnion->entityOffset);
					switch (ret[i].objectClassnum) {
					case CT_ENTITY:
						ret[i].objectOffset = gentity_s_a + (gentity_s_size * ret[i].objectNum);
						break;
					case CT_HUDELEM:
						ret[i].objectOffset = g_hudelem_s_a + (g_hudelem_s_size * ret[i].objectNum);
						break;
					}
				}
				break;
			case VAR_STRING:
				ret[i].stringValue = retUnion->stringValue;
				ret[i].string = SL_ConvertToString(retUnion->stringValue);
				break;
			case VAR_ISTRING:
				ret[i].stringValue = retUnion->stringValue;
				ret[i].string = SL_ConvertToString(retUnion->stringValue);
				break;
			case VAR_VECTOR:
				ret[i].vectorValue = retUnion->vectorValue;
				break;
			case VAR_FLOAT:
				ret[i].floatValue = retUnion->floatValue;
				break;
			case VAR_INTEGER:
				ret[i].intValue = retUnion->intValue;
				break;
			}
			ret[i].type = pointerType;
			ret[i].arraySize = arraySize;
		}
		return ret;
	}
	return 0;
}

inline VariableStruct* OnNotify(const char* string, int entnum, unsigned int classnum) {
	return OnNotifyRaw(string, entnum, classnum, getNotifyParams());
}

#endif /* __NOTIFY_H__ */