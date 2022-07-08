#ifndef __G_HUDELEM_H__
#define __G_HUDELEM_H__

enum he_type_t {
	HE_TYPE_FREE = 0x0,
	HE_TYPE_TEXT = 0x1,
	HE_TYPE_VALUE = 0x2,
	HE_TYPE_PLAYERNAME = 0x3,
	HE_TYPE_MATERIAL = 0x6,
	HE_TYPE_TIMER_DOWN = 0x5,
	HE_TYPE_TIMER_UP = 0x5,
	HE_TYPE_TIMER_STATIC = 0x7,
	HE_TYPE_TENTHS_TIMER_DOWN = 0x8,
	HE_TYPE_TENTHS_TIMER_UP = 0x9,
	HE_TYPE_TENTHS_TIMER_STATIC = 0xA,
	HE_TYPE_CLOCK_DOWN = 0xB,
	HE_TYPE_CLOCK_UP = 0xC,
	HE_TYPE_WAYPOINT = 0xD,
	HE_TYPE_COUNT = 0xE,
};

enum he_font_t {
	HE_FONT_DEFAULT = 0x0,
	HE_FONT_BIGFIXED = 0x1,
	HE_FONT_SMALLFIXED = 0x2,
	HE_FONT_OBJECTIVE = 0x3,
	HE_FONT_BIG = 0x4,
	HE_FONT_SMALL = 0x5,
	HE_FONT_HUDBIG = 0x6,
	HE_FONT_HUDSMALL = 0x7,
	HE_FONT_COUNT = 0x8,
};

union hudelem_color_t
{
	struct
	{
		char r;
		char g;
		char b;
		char a;
	};
	int rgba;
	hudelem_color_t() {

	}
	hudelem_color_t(char R, char G, char B, char A) {
		this->r = R; this->g = G; this->b = B; this->a = A;
	}
};

struct hudelem_s {
	he_type_t type;               // 0x00-0x04
	float y;                      // 0x04-0x08
	float x;                      // 0x08-0x0C
	float z;                      // 0x0C-0x10
	int targetEntNum;            // 0x10-0x14
	float fontScale;              // 0x14-0x18
	float fromFontScale;          // 0x18-0x1C
	int fontScaleStartTime;      // 0x1C-0x20
	int fontScaleTime;            // 0x20-0x24
	int label;                    // 0x24-0x28
	int font;                    // 0x28-0x2C
	int alignOrg;                // 0x2C-0x30
	int alignScreen;              // 0x30-0x34
	hudelem_color_t color;        // 0x34-0x38
	hudelem_color_t fromColor;    // 0x38-0x3C
	int fadeStartTime;            // 0x3C-0x40
	int fadeTime;                // 0x40-0x44
	int height;                  // 0x44-0x48
	int width;                    // 0x48-0x4C
	int materialIndex;            // 0x4C-0x50
	int fromHeight;              // 0x50-0x54
	int fromWidth;                // 0x54-0x58
	int scaleStartTime;          // 0x58-0x5C
	int scaleTime;                // 0x5C-0x60
	float fromY;                  // 0x60-0x64
	float fromX;                  // 0x64-0x68
	int fromAlignOrg;            // 0x68-0x6C
	int fromAlignScreen;          // 0x6C-0x70
	int moveStartTime;            // 0x70-0x74
	int moveTime;                // 0x74-0x78
	float value;                  // 0x78-0x7C
	int time;                    // 0x7C-0x80
	int duration;                // 0x80-0x84
	int text;                    // 0x84-0x88
	float sort;                  // 0x88-0x8C
	hudelem_color_t glowColor;    // 0x8C-0x90
	int fxBirthTime;              // 0x90-0x94
	int fxLetterTime;            // 0x94-0x98
	int fxDecayStartTime;        // 0x98-0x9C
	int fxDecayDuration;          // 0x9C-0xA0
	int soundID;                  // 0xA0-0xA4
	int flags;                    // 0xA4-0xA8
};

struct game_hudelem_s
{
	hudelem_s elem;              // 0x00-0xA8
	int clientNum;                // 0xA8-0xAC
	int teamNum;                  // 0xAC-0xB0
	int archived;                // 0xB0-0xB4
};

extern int(*G_LocalizedStringIndex)(const char* string);
extern int(*G_MaterialIndex)(const char* material);
extern game_hudelem_s*(*HudElem_Alloc)(int clientNum, int teamNum);
void Scr_FreeHudElem(game_hudelem_s* hud);
game_hudelem_s* NewHudElem();
game_hudelem_s* NewTeamHudElem(int teamNum);
game_hudelem_s* NewClientHudElem(int clientNum);
void setText(game_hudelem_s* elem, const char* text);
void setShader(game_hudelem_s* elem, const char* material);
game_hudelem_s* drawText(int clientNum, const char* text, int font, float fontscale,
	float x, float y, int align, float sort, hudelem_color_t color, hudelem_color_t glowColor);
game_hudelem_s* drawShader(int clientNum, const char* material, int width, int height, float x, float y, int align, float sort, hudelem_color_t color);
void FadeOverTime(game_hudelem_s* elem, float time, hudelem_color_t color);
void GlowOverTime(game_hudelem_s* elem, float time, hudelem_color_t color);
void AlphaOverTime(game_hudelem_s* elem, float time, char A);
void FontScaleOverTime(game_hudelem_s* elem, float time, float fontScale);
void ScaleOverTime(game_hudelem_s* elem, float time, int width, int height);
void MoveOverTime(game_hudelem_s *elem, float time, float x, float y);
void Typewriter(game_hudelem_s* elem, float time);

extern game_hudelem_s* g_hudelems;

#endif /* __G_HUDELEM_H__ */