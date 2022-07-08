#ifndef __BOTS_MP_H__
#define __BOTS_MP_H__

extern gentity_s*(*SV_AddTestClient)();
void SetTeam(int botNum, handle_t* handle, handleCall_t type);
void SetClass(int botNum, handle_t* handle, handleCall_t type);
void SpawnBots(int botAmount);
void spawnBots(int arg, handle_t* handle, handleCall_t type);
void setupBot(int botNum, handle_t* handle, handleCall_t type);
bool IsBot(int clientNum);

#endif /* __BOTS_MP_H__ */