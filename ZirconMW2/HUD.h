/* Engine Huds */
Function::ScreenPlacement* (*GetScreenPlacement)(int) = (Function::ScreenPlacement* (*)(int))&FuncDefs::GetScrPos_t;
Function::ScreenPlacement* CalcScreen()
{
	 Function::ScreenPlacement* ret = GetScreenPlacement(0);
	 return ret;
}
void DrawFillRect_UI(float X, float Y, float Width, float Height, const float* Colour)
{
	Function::ScreenPlacement* Scr = CalcScreen();
	Function::UI_DrawRec(Scr, X, Y, Width, Height, 0, 0, Colour);
}
void DrawRect_UI(float X, float Y, float Width, float Height, float Size, const float* Colour)
{
	Function::ScreenPlacement* Scr = CalcScreen();
	Function::UI_DrawEmptyRec(Scr, X, Y, Width, Height, 0, 0, Size, Colour);
}
void DrawText_UI(const char *Text, int Font, float X, float Y, float Scale, const float *Colour)
{
	Function::ScreenPlacement* Scr = CalcScreen();
    Function::Font_s* font_p = Function::UI_GetFontHandle(Scr, Font, Scale);
	Function::UI_DrawText(Scr, Text, 0x7FFFFFFF, font_p, X, Y, 0, 0, Scale, Colour, 0);
}
