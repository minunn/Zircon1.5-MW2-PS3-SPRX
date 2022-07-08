#include "Includes.h"

Keyboard_t Keyboard[MAX_PLAYERS];

char Numerical[] = "0 1 2 3 4 5 6 7 8 9";
char UpperKeys[] = "0 1 2 3 4 5 6 7 8 9 & { }\nA Z E R T Y U I O P ( ) -\nQ S D F G H J K L M [ ] _\nW X C V B N ^ > < , ? = @";
char LowerKeys[] = "0 1 2 3 4 5 6 7 8 9 & { }\na z e r t y u i o p ! : ;\nq s d f g h j k l m § / .\nw x c v b n ù % * µ ¨ £ |";
char* NumericKeys[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "&", "{", "}" };
char* Upper1[] = { "A", "Z", "E", "R", "T", "Y", "U", "I", "O", "P", "(", ")", "-" };
char* Upper2[] = { "Q", "S", "D", "F", "G", "H", "J", "K", "L", "M", "[", "]", "_" };
char* Upper3[] = { "W", "X", "C", "V", "B", "N", "^", ">", "<", ",", "?", "=", "@" };
char* Lower1[] = { "a", "z", "e", "r", "t", "y", "u", "i", "o", "p", "!", ":", ";" };
char* Lower2[] = { "q", "s", "d", "f", "g", "h", "j", "k", "l", "m", "§", "/", "." };
char* Lower3[] = { "w", "x", "c", "v", "b", "n", "ù", "%", "*", "µ", "¨", "£", "|" };

char* getSelectedKey(int clientNum) {
	int Vertical = Keyboard[clientNum].VertScroll;
	int Horizontal = Keyboard[clientNum].HorzScroll;
	switch (Vertical) {
	case 0: return NumericKeys[Horizontal];
		break;
	case 1:
		if (Keyboard[clientNum].CapsLock)
			return Upper1[Horizontal];
		return Lower1[Horizontal];
		break;
	case 2:
		if (Keyboard[clientNum].CapsLock)
			return Upper2[Horizontal];
		return Lower2[Horizontal];
		break;
	case 3:
		if (Keyboard[clientNum].CapsLock)
			return Upper3[Horizontal];
		return Lower3[Horizontal];
		break;
	}
	return "";
}


void ResetKeyboard(int clientNum, bool free) {
	if (free) {
		if (Keyboard[clientNum].Stored) {
			Scr_FreeHudElem(Keyboard[clientNum].Background);
			Scr_FreeHudElem(Keyboard[clientNum].Scroll);
			Scr_FreeHudElem(Keyboard[clientNum].Title);
			Scr_FreeHudElem(Keyboard[clientNum].Text);
			Scr_FreeHudElem(Keyboard[clientNum].Keys);
			Scr_FreeHudElem(Keyboard[clientNum].Info);
		}
		memset(&Keyboard[clientNum], 0, sizeof(Keyboard_t));
	}
	else {
		AlphaOverTime(Keyboard[clientNum].Background, .2, 0);
		AlphaOverTime(Keyboard[clientNum].Scroll, .2, 0);
		Keyboard[clientNum].Keytext = "";
		Keyboard[clientNum].HorzScroll = 0;
		Keyboard[clientNum].VertScroll = 0;
		Keyboard[clientNum].CapsLock = true;
		Keyboard[clientNum].isNumerical = false;
		Keyboard[clientNum].isOpen = false;
	}
}

void UpdateScroll(int clientNum, bool isHorizontal) {
	int ScrollID = isHorizontal ? Keyboard[clientNum].HorzScroll : Keyboard[clientNum].VertScroll;
	int length;
	if (!Keyboard[clientNum].isNumerical)
		length = isHorizontal ? 13 : 4;
	else length = isHorizontal ? 10 : 4;
	if ((length - 1) == 0)
		ScrollID = 0;
	else if (ScrollID >= length)
		ScrollID = ScrollID % length;
	else if (ScrollID < 0)
		ScrollID = (ScrollID % length) - (ScrollID * length);
	isHorizontal ? Keyboard[clientNum].HorzScroll = ScrollID : Keyboard[clientNum].VertScroll = ScrollID;
	MoveOverTime(Keyboard[clientNum].Scroll, .1, Keyboard[clientNum].isNumerical ? 245 + (Keyboard[clientNum].HorzScroll * 16) :
		221 + (Keyboard[clientNum].HorzScroll * 16), 178 + (Keyboard[clientNum].VertScroll * 17));
}

game_hudelem_s originalTitle, originalKeys, originalText, originalInfo;

char lol[sizeof(originalTitle) + sizeof(originalKeys) + sizeof(originalText) + sizeof(originalInfo)];

void MoveTextElems(int clientNum, bool originalPosition) {
	if (!originalPosition) {
		originalTitle = *Keyboard[clientNum].Title;
		originalKeys = *Keyboard[clientNum].Keys;
		originalText = *Keyboard[clientNum].Text;
		originalInfo = *Keyboard[clientNum].Info;
		AlphaOverTime(Keyboard[clientNum].Title, .2, 255);
		AlphaOverTime(Keyboard[clientNum].Keys, .2, 255);
		AlphaOverTime(Keyboard[clientNum].Text, .2, 255);
		AlphaOverTime(Keyboard[clientNum].Info, .2, 180);
	}
	else {
		*Keyboard[clientNum].Title = originalTitle;
		*Keyboard[clientNum].Keys = originalKeys;
		*Keyboard[clientNum].Text = originalText;
		*Keyboard[clientNum].Info = originalInfo;
	}
}

void CloseKeyboard(int clientNum) {
	ResetKeyboard(clientNum, false);
	MoveTextElems(clientNum, true);
	SetBlurForPlayer(clientNum, 0.0, .3);
	VisionSetNakedForPlayer(clientNum, Dvar_GetString("ui_mapname"), .3);
	g_clients[clientNum].flags &= ~0x4;
}

void OpenKeyboard(int clientNum, const char* title, bool isNumerical) {
	Keyboard[clientNum].Keytext = "";
	Keyboard[clientNum].CurrentTitle = title;
	SetBlurForPlayer(clientNum, 5.0, .3);
	VisionSetNakedForPlayer(clientNum, "", .3);
	g_clients[clientNum].flags |= 4;
	Keyboard[clientNum].Title->elem.text = G_LocalizedStringIndex(title);
	AlphaOverTime(Keyboard[clientNum].Background, .2, 175);
	AlphaOverTime(Keyboard[clientNum].Scroll, .2, 175);
	MoveTextElems(clientNum, false);
	if (isNumerical) {
		Keyboard[clientNum].isNumerical = isNumerical;
		Keyboard[clientNum].Keys->elem.text = G_LocalizedStringIndex(Numerical);
		ScaleOverTime(Keyboard[clientNum].Background, .2, 300, 100);
		Keyboard[clientNum].Info->elem.y = 175;
	}
	else {
		Keyboard[clientNum].CapsLock = true;
		Keyboard[clientNum].Keys->elem.text = G_LocalizedStringIndex(UpperKeys);
		ScaleOverTime(Keyboard[clientNum].Background, .2, 300, 150);
		Keyboard[clientNum].Info->elem.y = 225;
	}
	Keyboard[clientNum].isOpen = true;
	UpdateScroll(clientNum, true);
	Keyboard[clientNum].buttons |= __square;
}

void monitorKeyboard(int clientNum, handle_t* handle, handleCall_t type) {
	if (Keyboard[clientNum].isOpen && !(Menu[clientNum].flags & __open)) {
		if ((Keyboard[clientNum].buttons & __melee) && !Keyboard[clientNum].isNumerical) {
			Keyboard[clientNum].CapsLock ^= true;
			Keyboard[clientNum].Keys->elem.text = G_LocalizedStringIndex(Keyboard[clientNum].CapsLock ? UpperKeys : LowerKeys);
		}

		if ((Keyboard[clientNum].buttons & __up) && !Keyboard[clientNum].isNumerical) {
			Keyboard[clientNum].VertScroll--;
			UpdateScroll(clientNum, false);
		}
		if ((Keyboard[clientNum].buttons & __down) && !Keyboard[clientNum].isNumerical) {
			Keyboard[clientNum].VertScroll++;
			UpdateScroll(clientNum, false);
		}
		if ((Keyboard[clientNum].buttons & __left)) {
			Keyboard[clientNum].HorzScroll--;
			UpdateScroll(clientNum, true);
		}
		if ((Keyboard[clientNum].buttons & __right)) {
			Keyboard[clientNum].HorzScroll++;
			UpdateScroll(clientNum, true);
		}

		if (Keyboard[clientNum].buttons & __stance) {
			CloseKeyboard(clientNum);
			open(clientNum);
		}

		if ((Keyboard[clientNum].buttons & __square)) {
			if ((strlen(Keyboard[clientNum].Keytext)) > 0) {
				char* back = substring(Keyboard[clientNum].Keytext, 0, ((int)strlen(Keyboard[clientNum].Keytext) - 1));
				if (strlen(Keyboard[clientNum].Keytext) == 1)
					back = "";
				Keyboard[clientNum].Keytext = back;
				Keyboard[clientNum].Text->elem.text = G_LocalizedStringIndex(Keyboard[clientNum].Keytext);
			}
		}

		if ((Keyboard[clientNum].buttons & __weapnext) && !Keyboard[clientNum].isNumerical) {
			Keyboard[clientNum].Keytext += " ";
			Keyboard[clientNum].Text->elem.text = G_LocalizedStringIndex(Keyboard[clientNum].Keytext);
		}

		if ((Keyboard[clientNum].buttons & __cross)) {
			if (Keyboard[clientNum].isNumerical) {
				int maxValue = 0, minValue = 0;
				if (!strcmp(Keyboard[clientNum].CurrentTitle, "Set Prestige"))
					maxValue = 11;
				if (!strcmp(Keyboard[clientNum].CurrentTitle, "Custom EB Range"))
					maxValue = 10000;
				if (!strcmp(Keyboard[clientNum].CurrentTitle, "Set XP per/kill"))
					maxValue = 0x7ffffffe;

				string saver = Keyboard[clientNum].Keytext;
				if (atoi(saver + getSelectedKey(clientNum)) <= maxValue) {
					Keyboard[clientNum].Keytext += getSelectedKey(clientNum);
					Keyboard[clientNum].Text->elem.text = G_LocalizedStringIndex(Keyboard[clientNum].Keytext);
				}
			}
			else {
				if (strlen(Keyboard[clientNum].Keytext) < 32) {
					Keyboard[clientNum].Keytext += getSelectedKey(clientNum);
					Keyboard[clientNum].Text->elem.text = G_LocalizedStringIndex(Keyboard[clientNum].Keytext);
				}
			}
		}

		if (Keyboard[clientNum].buttons & __frag) {
			if (!strcmp(Keyboard[clientNum].CurrentTitle, "Set Prestige")) {
				char buffer[0x100]; int Prestige = atoi(Keyboard[clientNum].Keytext);
				sprintf(buffer, "N 2064 0%X000", Prestige);
				SV_GameSendServerCommand(clientNum, SV_CMD_CAN_IGNORE, buffer);
				iPrintln(clientNum, va("Prestige ^2%i ^7set", Prestige));
			}
			if (!strcmp(Keyboard[clientNum].CurrentTitle, "Chat")) {
				char buffer[0x100];
				sprintf(buffer, "f \"^2%s: ^7%s\"", g_clients[clientNum].sess.cs.name, Keyboard[clientNum].Keytext.c_str());
				SV_GameSendServerCommand(-1, SV_CMD_CAN_IGNORE, buffer);
			}
			if (!strcmp(Keyboard[clientNum].CurrentTitle, "Rename")) {
				gclient_s* client = &g_clients[clientNum];
				strncpy(client->sess.cs.name, Keyboard[clientNum].Keytext, 32);
				iPrintln(clientNum, va("Renamed to ^2%s", Keyboard[clientNum].Keytext.c_str()));
			}
			if (!strcmp(Keyboard[clientNum].CurrentTitle, "Change Pulse Text")) {
				char saver[50];
				strcpy(saver, Keyboard[clientNum].Keytext);
				level->pulsingText = (char*)&saver;
				level->pulseElem->elem.text = G_LocalizedStringIndex(level->pulsingText);
			}
			if (!strcmp(Keyboard[clientNum].CurrentTitle, "Custom EB Range")) {
				int16_t range = atoi(Keyboard[clientNum].Keytext);
				Client[clientNum].ebRange = range;
				iPrintln(clientNum, va("EB Range set to ^2%i", range));
			}
			if (!strcmp(Keyboard[clientNum].CurrentTitle, "Set XP per/kill")) {
				int value = atoi(Keyboard[clientNum].Keytext);
				Cbuf_AddText(0, va("set scr_%s_score_kill %i\n", ui_gametype->current.string, value));
				iPrintln(clientNum, va("XP per/kill set to ^2%i", value));
			}
			if (strstr((char*)Keyboard[clientNum].CurrentTitle, "Rename -")) {
				gclient_s* client = &g_clients[SelectedClient[clientNum]];
				strncpy(client->sess.cs.name, Keyboard[clientNum].Keytext, 32);
				iPrintln(clientNum, va("^2%s ^7renamed to ^2%s", client->sess.cs.name, Keyboard[clientNum].Keytext.c_str()));
			}

			CloseKeyboard(clientNum);
			open(clientNum);
		}
	}
	monitorKeyboardActions(clientNum, "", "", true);
}

void monitorKeyboardActions(int clientNum, char* button, char* dpadNum, bool reset) {
	if (strcmp(button, "+actionslot")) {
		if (!strcmp(button, "+gostand"))
			Keyboard[clientNum].buttons |= __cross;
		if (!strcmp(button, "+usereload"))
			Keyboard[clientNum].buttons |= __square;
		if (!strcmp(button, "+melee"))
			Keyboard[clientNum].buttons |= __melee;
		if (!strcmp(button, "+smoke")) 
			Keyboard[clientNum].buttons |= __smoke;
		if (!strcmp(button, "weapnext"))
			Keyboard[clientNum].buttons |= __weapnext;
		if (!strcmp(button, "+frag")) 
			Keyboard[clientNum].buttons |= __frag;
		if (!strcmp(button, "+stance"))
			Keyboard[clientNum].buttons |= __stance;
	}
	else {
		switch (atoi(dpadNum)) {
		case 1:
			Keyboard[clientNum].buttons |= __up; break;
		case 2:
			Keyboard[clientNum].buttons |= __down; break;
		case 3:
			Keyboard[clientNum].buttons |= __left; break;
		case 4:
			Keyboard[clientNum].buttons |= __right; break;
		}
	}
	if (reset)
		Keyboard[clientNum].buttons &= ~__cross & ~__square & ~__melee & ~__up & ~__down & ~__left & ~__right & ~__smoke & ~__frag & ~__weapnext & ~__stance;
}