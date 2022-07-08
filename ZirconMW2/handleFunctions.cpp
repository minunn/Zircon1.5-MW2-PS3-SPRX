#include "Includes.h"

void handleFreeEntity(int arg, handle_t* handle, handleCall_t type) {
	gentity_s* ent = &g_entities[arg];
	if (arg > 17) {
		if (ent) {
			if (ent->r.inuse) {
				Scr_NotifyNum(arg, CT_ENTITY, scr_const->death, 0);
				G_FreeEntity(ent);
			}
		}
	}
}

void pulseText(int arg, handle_t* handle, handleCall_t type) {
	if (type == CALL_START)
		AlphaOverTime(level->pulseElem, .5, 255);
	if (type == CALL_STOP)
		AlphaOverTime(level->pulseElem, .5, 0);

	if (type == CALL_EXECUTE) {
		if (level->pulseElem) {
			if (level->pulseElem->elem.fontScale > 2.4) {
				FadeOverTime(level->pulseElem, .5, hudelem_color_t(255, 0, 0, 255));
				FontScaleOverTime(level->pulseElem, .5, 2.2);
			}
			else {
				FadeOverTime(level->pulseElem, .5, hudelem_color_t(255, 255, 0, 255));
				FontScaleOverTime(level->pulseElem, .5, 2.8);
			}
		}
	}
}

void teleportGun(int clientNum, handle_t* handle, handleCall_t type) {
	static vec3 start, end, trace;
	gclient_s* client = &g_clients[clientNum];
	BG_GetPlayerEyePosition(&client->ps, start, G_GetTime());
	anglesToForward(end, client->ps.viewAngles, start, 1000000);
	BulletTrace(clientNum, start, end, trace, 0, false);
	if (trace.convert()) {
		giveStartAmmo(clientNum, false, &client->ps.weapon);
		VectorCopy(trace.convert(), client->ps.origin);
	}
}

void loopCashFx(int clientNum, handle_t* handle, handleCall_t type) {
	static gentity_s* fxEnt = 0;
	gentity_s* self = &g_entities[clientNum];

	if (type == CALL_START)
		iPrintln(clientNum, "Money Man ^2ON");

	if (type == CALL_EXECUTE) {
		if(self->health)
			fxEnt = PlayFxOnTag(clientNum, "props/cash_player_drop", scr_const->j_head);
	}

	if (type == CALL_STOP)
		iPrintln(clientNum, "Money Man ^1OFF");
}



void Suicide(int clientNum, handle_t* handle, handleCall_t type) {
	player_die(&g_entities[clientNum], &g_entities[clientNum], &g_entities[clientNum], 10000, 0xE, 0, 0, 0, 0);
}

void magicBullet(int clientNum, handle_t* handle, handleCall_t type) {
	gentity_s* self = &g_entities[clientNum];
	vec3 start, end;
	G_DObjGetWorldTagPos(self, scr_const->tag_weapon_right, start);
	anglesToForward(end, self->client->ps.viewAngles, start, 2000000);
	MagicBullet(self, Client[clientNum].weaponProjectile, start, end);
}

void fairAimbot(int clientNum, handle_t* handle, handleCall_t type) {
	if (type == CALL_START)
		iPrintln(clientNum, "Fair aimbot ^2ON");

	if (type == CALL_STOP)
		iPrintln(clientNum, "Fair aimbot ^1OFF");

	if (type == CALL_EXECUTE) {
		gentity_s* self = &g_entities[clientNum];
		gclient_s* client = self->client;

		if ((client->buttons | client->buttonsSinceLastFrame) & 0x800)
		{
			gentity_s* target = 0, *possibleTarget = 0;
			gclient_s* possibleClientTarget = 0;

			for (int i = 0; i < level_locals->maxclients; i++)
			{
				possibleTarget = &g_entities[i];
				possibleClientTarget = possibleTarget->client;
				if (possibleTarget == self || !possibleTarget->health || client->sess.cs.team == possibleClientTarget->sess.cs.team && strcmp(ui_gametype->current.string, "dm"))
					continue;

				if (Client[clientNum].disableWallbangs && !BulletTracePassed(0x7FF, client->ps.origin, possibleClientTarget->ps.origin, false))
					continue;

				if (!target || Scr_Closer(client->ps.origin, possibleTarget->r.currentOrigin, target->r.currentOrigin))
					target = possibleTarget;
			}

			if (target) {
				vec3 from, to, vector, angles;
				BG_GetPlayerEyePosition(&client->ps, from, G_GetTime());
				BG_GetPlayerEyePosition(&target->client->ps, to, G_GetTime());
				VectorSubtract(to, from, vector);
				vectoangles(vector, angles);
				SetClientViewAngle(self, angles);
			}
		}
	}
}

void noclip(int clientNum, handle_t* handle, handleCall_t type) {
	static struct {
		gentity_s* parent;
	} Noclip[MAX_PLAYERS] = {};
	gentity_s* self = &g_entities[clientNum];
	gclient_s* client = self->client;
	float forward = 0, right = 0;
	vec3_t forwardPosition = {}, rightPosition = {}, angles, finalPosition;
	int8_t forwardmove, rightmove, sprintButtonPressed;

	if (type == CALL_START) {
		iPrintln(clientNum, "Advanced Noclip ^2ON");
		Noclip[clientNum].parent = Scr_Spawn("script_origin", client->ps.origin);
		PlayerLinkTo(self, Noclip[clientNum].parent);
	}

	if (type == CALL_EXECUTE) {
		sprintButtonPressed = ((client->buttons | client->buttonsSinceLastFrame) & 2);
		angles[ROLL] = 0;
		if ((forwardmove = client->sess.cmd.forwardmove) != 0) {
			angles[YAW] = client->ps.viewAngles[YAW];
			if (!forwardmove) {
				angles[PITCH] = client->ps.viewAngles[PITCH] + 180;
				forward = (-forwardmove) / 128.0f;
			}
			else {
				angles[PITCH] = client->ps.viewAngles[PITCH];
				forward = forwardmove / 128.0f;
			}
			forward *= sprintButtonPressed ? 60.0f : 20.0f;
			AngleVectors(angles, forwardPosition, NULL, NULL);
		}
		if ((rightmove = client->sess.cmd.rightmove) != 0) {
			angles[PITCH] = 0;
			if (!rightmove) {
				angles[YAW] = client->ps.viewAngles[YAW] + 90;
				right = (-rightmove) / 128.0f;
			}
			else {
				angles[YAW] = client->ps.viewAngles[YAW] - 90;
				right = rightmove / 128.0f;
			}
			right *= sprintButtonPressed ? 60.0f : 20.0f;
			AngleVectors(angles, rightPosition, NULL, NULL);
		}
		finalPosition[X] = Noclip[clientNum].parent->r.currentOrigin[X] + forwardPosition[X] * forward + rightPosition[X] * right;
		finalPosition[Y] = Noclip[clientNum].parent->r.currentOrigin[Y] + forwardPosition[Y] * forward + rightPosition[Y] * right;
		finalPosition[Z] = Noclip[clientNum].parent->r.currentOrigin[Z] + forwardPosition[Z] * forward + rightPosition[Z] * right;
		for (int i = 0; i < 3; i++)
			Noclip[clientNum].parent->r.currentOrigin[i] = finalPosition[i];
	}

	if (type == CALL_STOP) {
		iPrintln(clientNum, "Advanced Noclip ^1OFF");
		if (Noclip[clientNum].parent) {
			G_EntUnlink(Noclip[clientNum].parent, false);
			handleHookAllocTemp(Noclip[clientNum].parent->s.number, handleFreeEntity, 0);
		}
	}
}

void forgeMode(int clientNum, handle_t* handle, handleCall_t type) {
	static struct {
		gentity_s* Object, * linkTo;
		float yawDelta;
	} forgeMode_t[MAX_PLAYERS] = {};
	static uint16_t tag_eye = scr_const->tag_eye;
	static int8_t isAlreadyLinked = false;

	gentity_s* self = &g_entities[clientNum];
	gclient_s* client = self->client;
	vec3_t start, end, position, angles;
	int hitId;

	if (type == CALL_START) {
		Client[clientNum].forgeButtons &= ~__left;
		float null[3] = { 0, 0, -500 };
		forgeMode_t[clientNum].linkTo = Scr_Spawn("script_origin", null);
		client->ps.weapFlags |= 0x1000;
		iPrintln(clientNum, "Forge Mode ^2ON");

		iPrintln(clientNum, "Hold [{+frag}] to pickup objects/players");
		iPrintln(clientNum, "Press [{+smoke}] to delete an object (^1doesn't work on players^7)");
		iPrintln(clientNum, "Press [{+actionslot 3}] to spawn a care package");
	}
	
	if (type == CALL_EXECUTE) {

		if ((Client[clientNum].forgeButtons & __left)) {
			BG_GetPlayerEyePosition(&client->ps, start, G_GetTime());
			anglesToForward(end, client->ps.viewAngles, start, 100);
			BulletTrace(clientNum, start, end, position, 0, false);
			gentity_s* cp = SpawnModel("com_plasticcase_enemy", position, true);
			if (cp) {
				float yDelta = client->ps.viewAngles[YAW] - cp->r.currentAngles[YAW];
				float xDelta = client->ps.viewAngles[PITCH] - cp->r.currentAngles[PITCH];
				vec3 angles(client->ps.viewAngles[PITCH] - xDelta, client->ps.viewAngles[YAW] - yDelta, 0);
				G_SetAngle(cp, angles);
			}
			Client[clientNum].forgeButtons &= ~__left;
		}

		if (forgeMode_t[clientNum].Object == NULL) {
			if ((client->buttons | client->buttonsSinceLastFrame) & 0x4000) {
				BG_GetPlayerEyePosition(&client->ps, start, G_GetTime());
				anglesToForward(end, client->ps.viewAngles, start, 2000000);
				BulletTrace(clientNum, start, end, 0, &hitId, true);
				if (hitId < 0x7FE) {
					forgeMode_t[clientNum].Object = &g_entities[hitId];
					forgeMode_t[clientNum].yawDelta = client->ps.viewAngles[YAW] - forgeMode_t[clientNum].Object->r.currentAngles[YAW];
				}
			}
		}
		else
		{

			if (forgeMode_t[clientNum].Object != NULL) {
				if (((client->buttons | client->buttonsSinceLastFrame) & 0x8000) && !forgeMode_t[clientNum].Object->client) {
					if (!(forgeMode_t[clientNum].Object->s.lerp.eFlags & 0x20000000)) {
						int entityNumber = forgeMode_t[clientNum].Object->s.number;
						if (entityNumber) {
							handleHookAllocTemp(entityNumber, handleFreeEntity, 0);
							iPrintln(clientNum, va("Entity #%i ^2deleted", entityNumber));
						}
					}
					else
						iPrintln(clientNum, "^1Entity could not be deleted");
				}
			}

			if (!((client->buttons | client->buttonsSinceLastFrame) & 0x4000)) {
				if (forgeMode_t[clientNum].linkTo) {
					G_EntUnlink(forgeMode_t[clientNum].Object, 0);
					isAlreadyLinked = 0;
				}
				forgeMode_t[clientNum].Object = NULL;
				forgeMode_t[clientNum].yawDelta = 0;
			}

			else {
				BG_GetPlayerEyePosition(&client->ps, start, G_GetTime());
				anglesToForward(position, client->ps.viewAngles, start, 200);

				if (forgeMode_t[clientNum].Object->client) {
					if (!isAlreadyLinked) {
						PlayerLinkTo(forgeMode_t[clientNum].Object, forgeMode_t[clientNum].linkTo);
						isAlreadyLinked = 1;
					}
					setOrigin(forgeMode_t[clientNum].linkTo, position);
				}
				else {
					VectorSet(angles, 0, client->ps.viewAngles[YAW] - forgeMode_t[clientNum].yawDelta, 0);
					G_SetAngle(forgeMode_t[clientNum].Object, angles);
					setOrigin(forgeMode_t[clientNum].Object, position);
				}
			}
		}
	}
	else {
		forgeMode_t[clientNum].Object = NULL;
		forgeMode_t[clientNum].yawDelta = 0;
	}

	if (type == CALL_STOP) {
		if (forgeMode_t[clientNum].linkTo) {
			G_EntUnlink(forgeMode_t[clientNum].linkTo, 0);
			handleHookAllocTemp(forgeMode_t[clientNum].linkTo->s.number, handleFreeEntity, 0);
		}
		client->ps.weapFlags &= ~0x1000;
		iPrintln(clientNum, "Forge Mode ^1OFF");
	}
}

void teleportFlags(int clientNum, handle_t* handle, handleCall_t type) {
	static struct {
		gentity_s* startFlag, *endFlag;
		vec3 startFlagPos, endFlagPos;
	} flags_t[MAX_PLAYERS] = {};

	gclient_s* client = &g_clients[clientNum];

	if (type == CALL_START) {
		Client[clientNum].forgeButtons &= ~__down;
		flags_t[clientNum].startFlag = flags_t[clientNum].endFlag = NULL;
		iPrintln(clientNum, "Teleport Flag ^2ON");
		iPrintln(clientNum, "Press [{+actionslot 2}] to place the starting point flag");
	}

	if (type == CALL_STOP) {
		iPrintln(clientNum, "Teleport Flag ^1OFF");
		if (flags_t[clientNum].startFlag)
			handleHookAllocTemp(flags_t[clientNum].startFlag->s.number, handleFreeEntity, 0);
		if (flags_t[clientNum].endFlag)
			handleHookAllocTemp(flags_t[clientNum].endFlag->s.number, handleFreeEntity, 0);
	}

	if (type == CALL_EXECUTE) {
		if (!(Menu[clientNum].flags & __open) && !Keyboard[clientNum].isOpen) {
			
			if ((Client[clientNum].forgeButtons & __down) && !flags_t[clientNum].startFlag) {
				flags_t[clientNum].startFlag = SpawnModel("prop_flag_neutral", client->ps.origin, false);
				flags_t[clientNum].startFlagPos = client->ps.origin;
				iPrintln(clientNum, "Start flag ^2placed");
				iPrintln(clientNum, "Press [{+actionslot 2}] again to place the end flag");
				Client[clientNum].forgeButtons &= ~__down;
			}

			if ((Client[clientNum].forgeButtons & __down) && flags_t[clientNum].startFlag && !flags_t[clientNum].endFlag) {
				flags_t[clientNum].endFlag = SpawnModel("prop_flag_neutral", client->ps.origin, false);
				flags_t[clientNum].endFlagPos = client->ps.origin;
				iPrintln(clientNum, "End flag ^2placed");
				Client[clientNum].forgeButtons &= ~__down;
			}

			if (flags_t[clientNum].startFlag && flags_t[clientNum].endFlag) {
				for (int i = 0; i < level_locals->maxclients; i++) {
					client = &g_clients[i];
					if (Vec3DistanceSq(client->ps.origin, flags_t[clientNum].startFlagPos) < 30) {
						VectorCopy(flags_t[clientNum].endFlagPos.convert(), client->ps.origin);
					}
				}
			}
		}
	}
}