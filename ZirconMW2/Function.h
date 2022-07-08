/* Addresses */
enum Addresses
{
	AddrMaterialRegisterHandle = 0x4C6D28,
	AddrUI_DrawText_t = 0x23A138,
	AddrUI_GetFont_t = 0x239D88,
	AddrGetScrPos_t = 0xDB9B0,
	AddrUI_DrawRec_t = 0x229FA0,
	AddrUI_DrawEmptyRec_t = 0x23B928,
	AddrCbuf_AddText = 0x1D9EC0,
	AddrCG_GameMessage = 0x5EF68,
	AddrSV_ClientStats = 0x0021A0A0
};
/* Defines */
#define TOC (0x724C38)

bool Draw = false;
const char* print_s = "";
struct opd_s
{
	int Sub;
	int Toc;
};
namespace FuncDefs
{
	opd_s RegisterHandle_t = { AddrMaterialRegisterHandle, TOC };
	opd_s UI_DrawText_t = { AddrUI_DrawText_t, TOC };
	opd_s UI_GetFont_t = { AddrUI_GetFont_t, TOC };
	opd_s GetScrPos_t = { AddrGetScrPos_t, TOC };
	opd_s UI_DrawRec_t = { AddrUI_DrawRec_t, TOC };
	opd_s UI_DrawEmptyRec_t = { AddrUI_DrawEmptyRec_t, TOC };
	opd_s Cbuf_AddText = { AddrCbuf_AddText, TOC };
	opd_s CG_GameMessage = { AddrCG_GameMessage, TOC };
	opd_s SV_ClientStats_t = { AddrSV_ClientStats, TOC };
};
namespace Function
{
	bool InGame()
	{
		if(*(char*)0x01D17A8C == 1)
			return true;
		else
			return false;
	}
	void Print(const char* s)
	{
		print_s = s;
		Draw = true;
		PS3::sleep(20);
		Draw = false;
	}
	struct Font_s
	{
		int fontName;
		float pixelHeight;
		int glyphCount;
		int material;
		int glowMaterial;
		int glyphs;
	};
	struct ScreenPlacement
	{
		int64_t	 scaleVirtualToReal;
		int64_t scaleVirtualToFull;
		int64_t scaleRealToVirtual;
		int64_t virtualViewableMin;
		int64_t virtualViewableMax;
		int64_t virtualTweakableMin;
		int64_t virtualTweakableMax;
		int64_t realViewportBase;
		int64_t realViewportSize;
		int64_t realViewportMid;
		int64_t realViewableMin;
		int32_t realViewableMaxX;
		int32_t realViewableMaxY;
		int64_t realTweakableMin;
		int64_t realTweakableMax;
		int64_t subScreen;
	};
	void(*CG_GameMessage)(int Client, const char* Message) = (void(*)(int, const char*))&FuncDefs::CG_GameMessage;
	void(*Cbuf_AddText)(int Client, const char* Command) = (void(*)(int, const char*))&FuncDefs::Cbuf_AddText;
	void(*UI_DrawRec)(ScreenPlacement *ScrPl, float X, float Y, float Width, float Height, int HorzAlign, int VertAlign, const float* Colour) = (void(*)(ScreenPlacement*, float, float, float, float, int, int, const float*))&FuncDefs::UI_DrawRec_t;
	void(*UI_DrawEmptyRec)(ScreenPlacement *ScrPl, float X, float Y, float Width, float Height, int HorzAlign, int VertAlign, float Size, const float* Colour) = (void(*)(ScreenPlacement*, float, float, float, float, int, int, float, const float*))&FuncDefs::UI_DrawEmptyRec_t; 
	void*(*Material_Register)(const char * Font, int ImageTrac) = (void*(*)(const char *, int))&FuncDefs::RegisterHandle_t;
	void(*UI_DrawText)(ScreenPlacement* ScrPl, const char *Text, int MaxChars, Font_s* Font, float X, float Y, int HorzAlign, int VertAlign, float Scale, const float *Colour, int Style) = (void(*)(ScreenPlacement*,const char*, int, Font_s*, float, float, int, int, float, const float*, int))&FuncDefs::UI_DrawText_t;
	Font_s*(*UI_GetFontHandle)(ScreenPlacement* ScrPl, int FontEnum, float Scale) = (Font_s*(*)(ScreenPlacement*, int, float))&FuncDefs::UI_GetFont_t;
	void(*Sv_ClientStats)(int Client, int Type, const char* Command) = (void(*)(int, int, const char*))&FuncDefs::SV_ClientStats_t;

	void ClientStats(int Client, char Index, char Value)
	{
		char* Space = " ";
		Sv_ClientStats(Client, 1, "N " + Index + (char)Space + Value);
	}
	void Prestige(char Value)
	{
		ClientStats(-1, 2064, Value);
	}
}