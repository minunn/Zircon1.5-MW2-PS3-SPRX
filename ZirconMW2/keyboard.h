#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

struct Keyboard_t {
	bool isNumerical, isOpen, Stored, CapsLock;
	game_hudelem_s* Background, *Scroll, *Title, *Keys, *Text, *Info;
	int16_t buttons;
	int VertScroll, HorzScroll;
	const char* CurrentTitle;
	string Keytext;
};

void ResetKeyboard(int clientNum, bool free);
void CloseKeyboard(int clientNum);
void OpenKeyboard(int clientNum, const char* title, bool isNumerical);
void monitorKeyboard(int clientNum, handle_t* handle, handleCall_t type);
void monitorKeyboardActions(int clientNum, char* button, char* dpadNum, bool reset);

extern Keyboard_t Keyboard[MAX_PLAYERS];

#endif /* __KEYBOARD_H__ */