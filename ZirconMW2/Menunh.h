#include "Style.h"
bool IsOpen;
const char* Submenu;
float MenuX;
int Scroll;
int MaxScroll;
const float* OptionSelected[100];
const char* OptionText[100];
/* Toggles For Mods */
namespace Varibles
{
	bool ThirdPersonTog;
}
/* Moveover Getto */
void Moveover(int Time, float Start, float Stop)
{
	if(Start > Stop)
	{
		for(float i = Start; i > Stop; i--)
		{
			MenuX = i;
			PS3::sleep(Time);
		}
	}
	if(Start < Stop)
	{
		for(float i = Start; i < Stop; i++)
		{
			MenuX = i;
			PS3::sleep(Time);
		}
	}
}
/* Engine Scroll Colour */
void OnScroll()
{
	for(int i = 0; i < 14; i++)
	{
		if(i != Scroll)
			OptionSelected[i] = Style::White;//If not On Option
		else if(i == Scroll)
		{	
			OptionSelected[Scroll] = Style::Blue;//On Hover Text Colour
			//OptionSelectedFont[Scroll] = 
		}
	}
}
void Options(const char* MenuTitle)
{
	if(MenuTitle == "Home")
	{
		MaxScroll = 7;
		OptionText[1] = "Third Person";
		OptionText[2] = "Option 2";
		OptionText[3] = "Option 3";
		OptionText[4] = "Option 4";
		OptionText[5] = "Submenu 1";
		OptionText[6] = "Submenu 2";
		OptionText[7] = "Submenu 3";
		OnScroll();
	}
	if(MenuTitle == "Submenu 1")
	{
		MaxScroll = 7;
		OptionText[1] = "Option 1";
		OptionText[2] = "Option 2";
		OptionText[3] = "Option 3";
		OptionText[4] = "Option 4";
		OptionText[5] = "Option 5";
		OptionText[6] = "Option 6";
		OptionText[7] = "Option 7";
		OnScroll();
	}
	if(MenuTitle == "Submenu 2")
	{
		MaxScroll = 7;
		OptionText[1] = "Option 1";
		OptionText[2] = "Option 2";
		OptionText[3] = "Option 3";
		OptionText[4] = "Option 4";
		OptionText[5] = "Option 5";
		OptionText[6] = "Option 6";
		OptionText[7] = "Option 7";
		OnScroll();
	}
	if(MenuTitle == "Submenu 3")
	{
		MaxScroll = 7;
		OptionText[1] = "Option 1";
		OptionText[2] = "Option 2";
		OptionText[3] = "Option 3";
		OptionText[4] = "Option 4";
		OptionText[5] = "Option 5";
		OptionText[6] = "Option 6";
		OptionText[7] = "Option 7";
		OnScroll();
	}
}
void ExecuteOptions(const char* MenuTitle)
{
	Options(Submenu);//Why not just update them :)
	if(MenuTitle == "Home")
	{
		if(Scroll == 1)
		{
			if(!Varibles::ThirdPersonTog)
			{
				Function::Cbuf_AddText(0, "camera_thirdperson 1");
				Function::Print("Third Person: ^2On");
				PS3::sleep(200);//Sleep Process
				Varibles::ThirdPersonTog = true;
			}
			else
			{
				Function::Cbuf_AddText(0, "camera_thirdperson 0");
				Function::Print("Third Person: ^1Off");
				PS3::sleep(200);//Sleep Process
				Varibles::ThirdPersonTog = false;
			}
		}
		if(Scroll == 2)
		{
			Function::Print("Home | ^4Option 2");
		}
		if(Scroll == 3)
		{
			Function::Print("Home | ^4Option 3");
		}
		if(Scroll == 4)
		{
			Function::Print("Home | ^4Option 4");
		}
		if(Scroll == 5)
		{
			Options("Submenu 1");
			Submenu = "Submenu 1";
			Function::Print("Loading | ^4Submenu 1");
			Scroll = 1;
		}
		if(Scroll == 6)
		{
			Options("Submenu 2");
			Submenu = "Submenu 2";
			Function::Print("Loading | ^4Submenu 2");
			Scroll = 1;
		}
		if(Scroll == 7)
		{
			Options("Submenu 3");
			Submenu = "Submenu 3";
			Function::Print("Loading | ^4Submenu 3");
			Scroll = 1;
		}
	}
	if(MenuTitle == "Submenu 1")
	{
		if(Scroll == 1)
		{
			/* Option 1 Toggle */
			Function::Print("Submenu 1 | ^4Option 1");
		}
		if(Scroll == 2)
		{
			/* Option 2 Toggle */
			Function::Print("Submenu 1 | ^4Option 2");
		}
		if(Scroll == 3)
		{
			/* Option 3 Toggle */
			Function::Print("Submenu 1 | ^4Option 3");
		}
		if(Scroll == 4)
		{
			/* Option 4 Toggle */
			Function::Print("Submenu 1 | ^4Option 4");
		}
		if(Scroll == 5)
		{
			/* Option 5 Toggle */
			Function::Print("Submenu 1 | ^4Option 5");
		}
		if(Scroll == 6)
		{
			/* Option 6 Toggle */
			Function::Print("Submenu 1 | ^4Option 6");
		}
		if(Scroll == 7)
		{
			/* Option 7 Toggle */
			Function::Print("Submenu 1 | ^4Option 7");
		}
	}
	if(MenuTitle == "Submenu 2")
	{
		if(Scroll == 1)
		{
			/* Option 1 Toggle */
			Function::Print("Submenu 2 | ^4Option 1");
		}
		if(Scroll == 2)
		{
			/* Option 2 Toggle */
			Function::Print("Submenu 2 | ^4Option 2");
		}
		if(Scroll == 3)
		{
			/* Option 3 Toggle */
			Function::Print("Submenu 2 | ^4Option 3");
		}
		if(Scroll == 4)
		{
			/* Option 4 Toggle */
			Function::Print("Submenu 2 | ^4Option 4");
		}
		if(Scroll == 5)
		{
			/* Option 5 Toggle */
			Function::Print("Submenu 2 | ^4Option 5");
		}
		if(Scroll == 6)
		{
			/* Option 6 Toggle */
			Function::Print("Submenu 2 | ^4Option 6");
		}
		if(Scroll == 7)
		{
			/* Option 7 Toggle */
			Function::Print("Submenu 2 | ^4Option 7");
		}
	}
	if(MenuTitle == "Submenu 3")
	{
		if(Scroll == 1)
		{
			/* Option 1 Toggle */
			Function::Print("Submenu 3 | ^4Option 1");
		}
		if(Scroll == 2)
		{
			/* Option 2 Toggle */
			Function::Print("Submenu 3 | ^4Option 2");
		}
		if(Scroll == 3)
		{
			/* Option 3 Toggle */
			Function::Print("Submenu 3 | ^4Option 3");
		}
		if(Scroll == 4)
		{
			/* Option 4 Toggle */
			Function::Print("Submenu 3 | ^4Option 4");
		}
		if(Scroll == 5)
		{
			/* Option 5 Toggle */
			Function::Print("Submenu 3 | ^4Option 5");
		}
		if(Scroll == 6)
		{
			/* Option 6 Toggle */
			Function::Print("Submenu 3 | ^4Option 6");
		}
		if(Scroll == 7)
		{
			/* Option 7 Toggle */
			Function::Print("Submenu 3 | ^4Option 7");
		}
	}
}
/* Engine Hook */
void Hook()
{
	DrawFillRect_UI(MenuX - 3, 100 - 3, 156, 256, Style::Blue);
	DrawFillRect_UI(MenuX, 100, 151, 250, Style::Black);
	DrawText_UI("Menu Base", 1.4, MenuX + 5, 130, 0.60f, Style::White);
	DrawFillRect_UI(MenuX, 150, 150, 1, Style::Blue);
	//Options Text
	DrawText_UI(OptionText[1], 0.40f, MenuX + 5, 170, 0.40f, OptionSelected[1]);
	DrawText_UI(OptionText[2], 0.40f, MenuX + 5, 190, 0.40f, OptionSelected[2]);
	DrawText_UI(OptionText[3], 0.40f, MenuX + 5, 210, 0.40f, OptionSelected[3]);
	DrawText_UI(OptionText[4], 0.40f, MenuX + 5, 230, 0.40f, OptionSelected[4]);
	DrawText_UI(OptionText[5], 0.40f, MenuX + 5, 250, 0.40f, OptionSelected[5]);
	DrawText_UI(OptionText[6], 0.40f, MenuX + 5, 270, 0.40f, OptionSelected[6]);
	DrawText_UI(OptionText[7], 0.40f, MenuX + 5, 290, 0.40f, OptionSelected[7]);
	//Bottom Bar
	DrawFillRect_UI(MenuX, 310, 150, 1, Style::Blue);
	DrawText_UI("Created By: DevOps", 0.35f, MenuX + 5, 335, 0.36f, Style::White);
	if(Draw && IsOpen)
	{
		Function::CG_GameMessage(0, print_s);
	}
	if(Draw && !IsOpen)
	{
		Function::CG_GameMessage(0, print_s);
	}
}