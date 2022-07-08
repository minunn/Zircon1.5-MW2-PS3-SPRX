#ifndef __G_SCR_MP_H__
#define __G_SCR_MP_H__

int Scr_SetNumParam(unsigned int paramcount);
extern void(*Scr_ClearOutParams)();
extern void(*Scr_AddInt)(int);
extern void(*Scr_AddFloat)(float);
extern void(*Scr_AddString)(const char*);
extern void(*Scr_AddEntity)(gentity_s*);
extern void(*Scr_AddHudElem)(int);
extern void(*Scr_AddEntityNum)(int, unsigned int);
extern void(*Scr_AddObject)(unsigned int);
extern void(*Scr_AddVector)(float*);
extern void(*Scr_AddUndefined)();
extern void(*Scr_GetObject)(unsigned int);
extern int(*Scr_GetEntityId)(int, int);
extern scr_entref_t(*Scr_GetEntityRef)(int);
scr_entref_t* Scr_GetEntityIdRef(int entId);
extern void(*Scr_GetObjectField)(int, int, int);
extern void(*Scr_SetObjectField)(unsigned int, int, int);
extern void(*Scr_AddConstString)(int);
extern void(*Scr_NotifyNum)(int, unsigned int, short, unsigned int);
extern void(*VM_Notify)(int notifyListOwnerId, int stringValue, VariableValue* top, int paramcount);
extern void(*Scr_SetString)(short *to, short from);
extern uint16_t(*Scr_ExecEntThread)(gentity_s* ent, int32_t handle, uint32_t paramcount);
extern void(*Scr_FreeThread)(uint16_t thread);

extern void(*SetVariableFieldValue)(int, int, VariableValue*);
extern bool(*SetEntityFieldValue)(unsigned int classnum, int entnum, int offset, VariableValue *value);
extern void(*SetVariableEntityFieldValue)(unsigned int entId, unsigned int fieldName, VariableValue *value);
extern int(*GetVariable)(int, int);
extern int(*GetArrayVariable)(int parentId, int id);
extern VariableUnion*(*GetVariableValueAddress)(int parentId, int id);
extern int(*GetObjectType)(int id);
extern int(*GetArraySize)(int parentId);
extern int(*FindEntityId)(int entnum, int classnum);
extern int(*FindVariable)(int parentId, int name);
extern int(*FindArrayVariable)(int parentId, int index);
extern int(*GetValueType)(int childType, int id);
extern int(*Scr_GetSelf)(int threadId);
extern char*(*SL_ConvertToString)(int stringValue);
extern bool(*Sys_SpawnServerThread)(void(*function)(uint32_t arg));
extern void(*Sys_SetValue)(int index, void* data);
extern void*(*Sys_GetValue)(int index);
extern unsigned int(*Scr_GetConstLowercaseString)(unsigned int index, unsigned int ptr);
int SL_GetString(const char* string);
extern int(*FindFirstSibling)(unsigned int parentId);
extern int(*FindNextSibling)(unsigned int childType, unsigned int id);

#endif /* __G_SCR_MP_H__ */