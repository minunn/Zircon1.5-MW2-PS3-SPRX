#ifndef __PFUNCTIONS_H__
#define __PFUNCTIONS_H__

struct Color {
	float rgba[4];
	Color(){}
	Color(float r, float g, float b, float a) { 
		this->rgba[0] = r; 
		this->rgba[1] = g;
		this->rgba[2] = b;
		this->rgba[3] = a;
	}
	Color operator =(const Color &col) {
		this->rgba[0] = col.rgba[0];
		this->rgba[1] = col.rgba[1];
		this->rgba[2] = col.rgba[2];
		this->rgba[3] = col.rgba[3];
		return *this;
	}
};

enum Buttons {
	Cross = 0x01,
	O = 0x02,
	Square = 0x03,
	Triangle = 0x04,
	L1 = 0x05,
	R1 = 0x06,
	L2 = 0x12,
	R2 = 0x13,
	R3 = 0x11,
	L3 = 0x10,
	Dpad_Up = 0x14,
	Dpad_Down = 0x15,
	Dpad_Left = 0x16,
	Dpad_Right = 0x17,
	Start = 0x0E,
	Select = 0x0F,
};

#define HIWORD(l) ((short)(((int)(l) >> 16) & 0xFFFF)) 
typedef void(*UI_KeyboardCallback)(int localClientNum, bool ifExecuted, const char *text);

extern void(*R_AddCmdDrawStretchPic)(float x, float y, float width, float height, float xScale, float yScale, float xay, float yay, const float *color, void *material);
extern void(*R_AddCmdDrawStretchPicRotateXY)(float, float, float, float, float, float, float, float, float, float*, void*);
extern void(*R_AddCmdDrawText)(const char *text, int maxChars, void *font, float x, float y, float xScale, float yScale, float rotation, const float *color, int style);
extern void(*R_AddCmdDrawTextWithEffect)(const char *text, int maxChars, void *font, float x, float y, float xScale, float yScale, float rotation, const float *color, int style, const float *glowColor, void *fxMaterial, void *fxMaterialGlow, int fxBirthTime, int fxLetterTime, int fxDecayStartTime, int fxDecayDuration);
extern void*(*R_RegisterFont)(const char * font, int imageTrac);
extern void*(*Material_Register)(const char * Font, int ImageTrac);
extern int(*Key_IsDown)(int localClientNum, int keyNum);
extern void(*UI_PlayLocalSoundAliasByName)(int localClientNum, const char* aliasName);

void DrawKeyboard(const char *title, const char *presetMessage, size_t size, uint32_t panelMode, UI_KeyboardCallback function);
void KeyboardCallback(int localClientNum, bool ifExecuted, const char *text);
void DrawText(const char *text, const char *fontName, float x, float y, float scale, Color color);
void DrawShader(float x, float y, float width, float height, Color color, const char *material);
void DrawMenu();
void doLevels();
void doPrestige();
void toggleFFAFH();
void teamBasedForceHost(bool reset = false);
void updateButtons(bool reset = false);

extern unsigned char UnlockAll[];

#endif /* __PFUNCTIONS_H__ */