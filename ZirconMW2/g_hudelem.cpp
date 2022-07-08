#include "includes.h"

game_hudelem_s* g_hudelems = (game_hudelem_s*)g_hudelem_s_a;

opd_s Scr_FreeHudElem_t = { Scr_FreeHudElem_a, TOC };
opd_s G_LocalizedStringIndex_t = { G_LocalizedStringIndex_a, TOC };
opd_s G_MaterialIndex_t = { G_MaterialIndex_a , TOC };

int(*G_LocalizedStringIndex)(const char* string) = (int(*)(const char*))G_LocalizedStringIndex_a;
int(*G_MaterialIndex)(const char* material) = (int(*)(const char*))G_MaterialIndex_a;
game_hudelem_s*(*HudElem_Alloc)(int clientNum, int teamNum) = (game_hudelem_s*(*)(int, int))0;

void Scr_FreeHudElem(game_hudelem_s* hud) {
	void(*Scr_FreeHudElem)(game_hudelem_s*) = (void(*)(game_hudelem_s*))&Scr_FreeHudElem_t;
	hud->elem.type = HE_TYPE_FREE;
	Scr_FreeHudElem(hud);
}

game_hudelem_s* NewHudElem() {
	return HudElem_Alloc(0x7FF, 0);
}

game_hudelem_s* NewTeamHudElem(int teamNum) {
	return HudElem_Alloc(0x7FF, teamNum);
}

game_hudelem_s* NewClientHudElem(int clientNum) {
	return HudElem_Alloc(clientNum, 0);
}

void setText(game_hudelem_s* elem, const char* text) {
	elem->elem.type = HE_TYPE_TEXT;
	elem->elem.text = G_LocalizedStringIndex(text);
}

void setShader(game_hudelem_s* elem, const char* material) {
	level_locals->initializing = 1;
	elem->elem.type = HE_TYPE_MATERIAL;
	elem->elem.materialIndex = G_MaterialIndex(material);
	level_locals->initializing = 0;
}

game_hudelem_s* drawText(int clientNum, const char* text, int font, float fontscale,
	float x, float y, int align, float sort, hudelem_color_t color, hudelem_color_t glowColor) {
    *(int*)0x131689C = 1; //Allows to use precached Shaders
	game_hudelem_s* elem = NewClientHudElem(clientNum);
	elem->elem.font = font;
	elem->elem.fontScale = fontscale;
	elem->elem.x = x;
	elem->elem.y = y;
	elem->elem.alignOrg = align;
	elem->elem.alignScreen = 1;
	elem->elem.sort = sort;
	elem->elem.color = color;
	elem->elem.glowColor = glowColor;
	setText(elem, text);
	elem->clientNum = clientNum;
	return elem;
}

game_hudelem_s* drawShader(int clientNum, const char* material, int width, int height, float x, float y, int align, float sort, hudelem_color_t color) {
	game_hudelem_s* elem = NewClientHudElem(clientNum);
	elem->elem.width = width;
	elem->elem.height = height;
	elem->elem.x = x;
	elem->elem.y = y;
	elem->elem.color = color;
	setShader(elem, material);
	elem->clientNum = clientNum;
	return elem;
}

void FadeOverTime(game_hudelem_s* elem, float time, hudelem_color_t color) {
	elem->elem.fromColor = elem->elem.color;
	elem->elem.fadeStartTime = G_GetTime();
	elem->elem.fadeTime = (int)f_floorf(time * 1000.0 + 0.5);
	elem->elem.color.r = color.r;
	elem->elem.color.g = color.g;
	elem->elem.color.b = color.b;
	elem->elem.color.a = color.a;
}

void GlowOverTime(game_hudelem_s* elem, float time, hudelem_color_t color) {
	elem->elem.fromColor = elem->elem.glowColor;
	elem->elem.fadeStartTime = G_GetTime();
	elem->elem.fadeTime = (int)f_floorf(time * 1000.0 + 0.5);
	elem->elem.glowColor.r = color.r;
	elem->elem.glowColor.g = color.g;
	elem->elem.glowColor.b = color.b;
	elem->elem.glowColor.a = color.a;
}

void AlphaOverTime(game_hudelem_s* elem, float time, char A) {
	elem->elem.fromColor = elem->elem.color;
	elem->elem.fadeStartTime = G_GetTime();
	elem->elem.fadeTime = (int)f_floorf(time * 1000.0 + 0.5);
	elem->elem.color.r = elem->elem.color.r;
	elem->elem.color.g = elem->elem.color.g;
	elem->elem.color.b = elem->elem.color.b;
	elem->elem.color.a = A;
}

void FontScaleOverTime(game_hudelem_s* elem, float time, float fontScale) {
	elem->elem.fromFontScale = elem->elem.fontScale;
	elem->elem.fontScaleStartTime = G_GetTime();
	elem->elem.fontScaleTime = (int)f_floorf(time * 1000 + 0.5);
	elem->elem.fontScale = fontScale;
}

void ScaleOverTime(game_hudelem_s* elem, float time, int width, int height) {
	elem->elem.fromWidth = elem->elem.width;
	elem->elem.fromHeight = elem->elem.height;
	elem->elem.scaleStartTime = G_GetTime();
	elem->elem.scaleTime = (int)f_floorf(time * 1000 + 0.5);
	elem->elem.width = width;
	elem->elem.height = height;
}

void MoveOverTime(game_hudelem_s* elem, float time, float x, float y) {
	elem->elem.fromX = elem->elem.x;
	elem->elem.fromY = elem->elem.y;
	elem->elem.fromAlignOrg = elem->elem.alignOrg;
	elem->elem.fromAlignScreen = elem->elem.alignScreen;
	elem->elem.moveStartTime = G_GetTime();
	elem->elem.moveTime = (int)f_floorf(time * 1000 + 0.5);
	elem->elem.x = x;
	elem->elem.y = y;
}

void Typewriter(game_hudelem_s* elem, float time) {
	elem->elem.color.a = 255;
	elem->elem.flags |= 0x400;
	elem->elem.fxBirthTime = G_GetTime();
	elem->elem.fxLetterTime = (int)f_floorf(time * 1000.0 + 0.5);
	elem->elem.fxDecayStartTime = 3500;
	elem->elem.fxDecayDuration = 700;
}
