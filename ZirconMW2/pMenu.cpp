#include "Includes.h"

pMenu_t* pMenu = (pMenu_t*)0x10089000;

void ScrollEffect() {
	for (int i = 0; i < 9; i++) {
		pMenu->glowColor[i].rgba[3] = 0;
		pMenu->textColor[i].rgba[3] = .2;
	}
	pMenu->glowColor[pMenu->ScrollIndex].rgba[3] = .1;
	pMenu->textColor[pMenu->ScrollIndex].rgba[3] = 1;
}

void SelectOption() {
	switch (pMenu->ScrollIndex) {
	case 0: DrawKeyboard("Change your name", "", 32, CELL_OSKDIALOG_PANELMODE_ALPHABET, KeyboardCallback);
		pMenu->setName = true;
		break;
	case 1: doLevels();
		break;
	case 2: doPrestige();
		break;
	case 3:
		memcpy((void*)0x01FFA0C7, &UnlockAll, 3120);
		for (int i = 0; i < 9; i++)
			*(char*)(0x1FF9E47 + (0x40 * i)) = 0x01;
		break;
	case 4: Cbuf_AddText(0, "defaultStatsInit;uploadStats;");
		break;
	case 5: DrawKeyboard("Custom Command", "", 100, CELL_OSKDIALOG_PANELMODE_ALPHABET, KeyboardCallback);
		pMenu->customCmd = true;
		break;
	case 6: pMenu->forceHost ^= true;
		toggleFFAFH();
		break;
	case 7: 
		pMenu->teamForceHost ^= true;
		if (!pMenu->teamForceHost)
			teamBasedForceHost(true);
		break;
	case 8: 
		int value = *(int*)0x1F96708;
		value = value == 1 ? 3 : 1;
		*(int*)0x1F96708 = value;
		break;
	}
}

void pregameThread(uint64_t arg) {
	for (int i = 0; i < 9; i++) {
		pMenu->textColor[i] = Color(1, 1, 1, 0);
		pMenu->glowColor[i] = Color(1, 0, 0, 0);
	}
	pMenu->titleColor = Color(1, 1, 1, 0);
	pMenu->titleGlow = Color(1, 0, 0, .1);
	pMenu->lineColor = Color(0.7, 0, 0, 0);
	pMenu->currentLevel = 1;
	int nop[] = { 0x60000000 };
	WriteProcessMemory(0x2383A8, nop, 4);

	for (;;) {
		if (!cl_ingame->current.enabled) {
			updateButtons(); 
			sleep(1);
		}
		else
			sleep(1000);
	}
}

void Menu_PaintAll_s(...) {
	__asm("li %r3, 5;");
}

void Menu_PaintAll_h(uint64_t a1, uint64_t a2) {
	if (!cl_ingame->current.enabled) {
		DrawMenu();
		if (!pMenu->isOpen) {
			if (pMenu->L3) {
				pMenu->bgColor.rgba[3] = .5;
				pMenu->lineColor.rgba[3] = 1;
				pMenu->titleColor.rgba[3] = 1;
				ScrollEffect();
				pMenu->isOpen = true;
				UI_PlayLocalSoundAliasByName(0, "mp_suitcase_pickup");
			}
		}
		else {
			if (pMenu->R3) {
				SelectOption();
			}
			if (pMenu->Square) {
				pMenu->bgColor.rgba[3] = 0;
				pMenu->lineColor.rgba[3] = 0;
				pMenu->titleColor.rgba[3] = 0;
				for (int i = 0; i < 9; i++) 
					pMenu->textColor[i].rgba[3] = 0;
				pMenu->isOpen = false;
				if (!pMenu->DisabledControlText)
					pMenu->DisabledControlText = true;
			}

			if (pMenu->L2 || pMenu->R2) {
				if (pMenu->ScrollIndex == 1) {
					pMenu->currentLevel += pMenu->R2;
					pMenu->currentLevel -= pMenu->L2;
					if (pMenu->currentLevel > 70)
						pMenu->currentLevel = 1;
					if (pMenu->currentLevel < 1)
						pMenu->currentLevel = 70;
				}
				else if (pMenu->ScrollIndex == 2) {
					pMenu->currentPrestige += pMenu->R2;
					pMenu->currentPrestige -= pMenu->L2;
					if (pMenu->currentPrestige > 11)
						pMenu->currentPrestige = 0;
					if (pMenu->currentPrestige < 0)
						pMenu->currentPrestige = 11;
				}
			}

			if (pMenu->L1 || pMenu->R1) {
				pMenu->ScrollIndex += pMenu->R1;
				pMenu->ScrollIndex -= pMenu->L1;
				if (pMenu->ScrollIndex > 8)
					pMenu->ScrollIndex = 0;
				if (pMenu->ScrollIndex < 0)
					pMenu->ScrollIndex = 8;
				ScrollEffect();
			}
		}
		updateButtons(true);
	}
	Menu_PaintAll_s(a1, a2);
}