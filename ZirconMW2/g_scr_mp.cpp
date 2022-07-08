#include "includes.h"

opd_s SL_ConvertToString_t = { SL_ConvertToString_a, TOC };
opd_s SL_GetString_t = { SL_GetString_a, TOC };
opd_s Scr_ClearOutParams_t = { Scr_ClearOutParams_a, TOC };
opd_s Scr_Notify_t = { Scr_Notify_a, TOC };
opd_s Scr_NotifyNum_t = { Scr_NotifyNum_a, TOC };
opd_s Scr_GetSelf_t = { Scr_GetSelf_a, TOC };
opd_s Scr_AddInt_t = { Scr_AddInt_a, TOC };
opd_s Scr_AddEntity_t = { Scr_AddEntity_a, TOC };
opd_s Scr_AddEntityNum_t = { Scr_AddEntityNum_a, TOC };
opd_s Scr_GetEntityIdRef_t = { Scr_GetEntityIdRef_a, TOC };
opd_s Scr_GetEntityId_t = { 0x204570, TOC };
opd_s Scr_AddString_t = { Scr_AddString_a, TOC };
opd_s Scr_AddFloat_t = { Scr_AddFloat_a, TOC };
opd_s Scr_AddVector_t = { Scr_AddVector_a, TOC };
opd_s Scr_AddConstString_t = { Scr_AddConstString_a, TOC };
opd_s Scr_ExecEntThread_t = { Scr_ExecEntThread_a, TOC };
opd_s Scr_FreeThread_t = { Scr_FreeThread_a, TOC };
opd_s Scr_AddUndefined_t = { Scr_AddUndefined_a, TOC };
opd_s Scr_SetString_t = { Scr_SetString_a, TOC };

opd_s GetVariable_t = { 0x204390, TOC };
opd_s GetObjectType_t = { GetObjectType_a, TOC };
opd_s GetArraySize_t = { GetArraySize_a, TOC };
opd_s GetVariableValueAddress_t = { GetVariableValueAddress_a, TOC };
opd_s GetArrayVariable_t = { GetArrayVariable_a, TOC };
opd_s GetValueType_t = { GetValueType_a, TOC }; //GetObjectType_a
opd_s Scr_GetObjectField_t = { Scr_GetObjectField_a, TOC };
opd_s Scr_SetObjectField_t = { 0x1B80A0, TOC };
opd_s FindVariable_t = { 0x202118, TOC };
opd_s SetEntityFieldValue_t = { 0x20C0F0, TOC };
opd_s SetVariableFieldValue_t = { 0x205E08, TOC };
opd_s SetVariableEntityFieldValue_t = { 0x204968, TOC };
opd_s Sys_SpawnServerThread_t = { Sys_SpawnServerThread_a, TOC };

int Scr_SetNumParam(unsigned int params) {
	return *(int*)(&gScrVmPub->outparamcount) = params;
}

void(*Scr_ClearOutParams)() = (void(*)())&Scr_ClearOutParams_t;
void(*Scr_AddInt)(int) = (void(*)(int))&Scr_AddInt_t;
void(*Scr_AddFloat)(float) = (void(*)(float))&Scr_AddFloat_t;
void(*Scr_AddString)(const char*) = (void(*)(const char*))&Scr_AddString_t;
void(*Scr_AddEntity)(gentity_s*) = (void(*)(gentity_s*))&Scr_AddEntity_t;
void(*Scr_AddEntityNum)(int, unsigned int) = (void(*)(int, unsigned int))&Scr_AddEntityNum_t;
void(*Scr_AddVector)(float*) = (void(*)(float*))&Scr_AddVector_t;
void(*Scr_AddUndefined)() = (void(*)())&Scr_AddUndefined_t;
void(*Scr_AddConstString)(int stringValue) = (void(*)(int))&Scr_AddConstString_t;
void(*Scr_GetObjectField)(int, int, int) = (void(*)(int, int, int))&Scr_GetObjectField_t;
int(*Scr_GetEntityId)(int entnum, int classnum) = (int(*)(int, int))&Scr_GetEntityId_t;
void(*Scr_SetObjectField)(unsigned int classnum, int entnum, int offset) = (void(*)(unsigned int, int, int))&Scr_SetObjectField_t;
void(*Scr_SetString)(short* to, short from) = (void(*)(short*, short))&Scr_SetString_t;
int(*GetVariable)(int, int) = (int(*)(int, int))&GetVariable_t;
int(*GetArrayVariable)(int parentId, int id) = (int(*)(int, int))&GetArrayVariable_t;
VariableUnion*(*GetVariableValueAddress)(int parentId, int id) = (VariableUnion*(*)(int, int))&GetVariableValueAddress_t;
int(*GetObjectType)(int id) = (int(*)(int))&GetObjectType_t;
int(*GetArraySize)(int parentId) = (int(*)(int))&GetArraySize_t;
void(*Scr_NotifyNum)(int, unsigned int, short, unsigned int) = (void(*)(int, unsigned int, short, unsigned int))&Scr_NotifyNum_t;
int(*Scr_GetSelf)(int threadId) = (int(*)(int))&Scr_GetSelf_t;
char*(*SL_ConvertToString)(int stringValue) = (char*(*)(int))&SL_ConvertToString_t;
int(*FindVariable)(int parentId, int name) = (int(*)(int, int))&FindVariable_t;
bool(*SetEntityFieldValue)(unsigned int classnum, int entnum, int offset, VariableValue *value) = (bool(*)(unsigned int, int, int, VariableValue*))&SetEntityFieldValue_t;
void(*SetVariableFieldValue)(int id, int, VariableValue*) = (void(*)(int, int, VariableValue*))&SetVariableFieldValue_t;
void(*SetVariableEntityFieldValue)(unsigned int entId, unsigned int fieldName, VariableValue *value) = (void(*)(unsigned int, unsigned int, VariableValue*))&SetVariableEntityFieldValue_t;
uint16_t(*Scr_ExecEntThread)(gentity_s* ent, int32_t handle, uint32_t paramcount) = (uint16_t(*)(gentity_s*, int32_t, uint32_t))&Scr_ExecEntThread_t;
void(*Scr_FreeThread)(uint16_t thread) = (void(*)(uint16_t))&Scr_FreeThread_t;
bool(*Sys_SpawnServerThread)(void(*function)(uint32_t arg)) = (bool(*)(void(*)(uint32_t arg)))&Sys_SpawnServerThread_t;
void(*Sys_SetValue)(int index, void* data) = (void(*)(int, void*))0x7098C8;
void*(*Sys_GetValue)(int index) = (void*(*)(int))0x7098D0;

int SL_GetString(const char* string) {
	int(*SL_GetString)(const char* string, int user) = (int(*)(const char*, int))&SL_GetString_t;
	return SL_GetString(string, 0);
}

scr_entref_t* Scr_GetEntityIdRef(int entId) {
	scr_entref_t entref;
	scr_entref_t*(*Scr_GetEntityIdRef)(scr_entref_t* entref, int entId) = (scr_entref_t*(*)(scr_entref_t*, int))&Scr_GetEntityIdRef_t;
	return Scr_GetEntityIdRef(&entref, entId);
}

opd_s FindFirstSibling_t = { FindFirstSibling_a, TOC };
opd_s FindNextSibling_t = { FindNextSibling_a, TOC };

int(*GetValueType)(int childType, int id) = (int(*)(int, int))&GetValueType_t;
int(*FindFirstSibling)(unsigned int parentId) = (int(*)(unsigned int))&FindFirstSibling_t;
int(*FindNextSibling)(unsigned int childType, unsigned int id) = (int(*)(unsigned int, unsigned int))&FindNextSibling_t;