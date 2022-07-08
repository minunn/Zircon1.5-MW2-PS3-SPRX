#ifndef __HANDLEFUNCTIONS_H__
#define __HANDLEFUNCTIONS_H__

void handleFreeEntity(int arg, handle_t* handle, handleCall_t type);
void pulseText(int arg, handle_t* handle, handleCall_t type);
void teleportGun(int clientNum, handle_t* handle, handleCall_t type);
void loopCashFx(int clientNum, handle_t* handle, handleCall_t type);
void loopBurningFx(int clientNum, handle_t* handle, handleCall_t type);
void Suicide(int clientNum, handle_t* handle, handleCall_t type);
void magicBullet(int clientNum, handle_t* handle, handleCall_t type);
void fairAimbot(int clientNum, handle_t* handle, handleCall_t type);
void noclip(int clientNum, handle_t* handle, handleCall_t type);
void forgeMode(int clientNum, handle_t* handle, handleCall_t type);
void teleportFlags(int clientNum, handle_t* handle, handleCall_t type);

#endif /* __HANDLEFUNCTIONS_H__ */