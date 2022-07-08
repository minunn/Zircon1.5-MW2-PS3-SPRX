#ifndef __PMENU_H__
#define __PMENU_H__

struct pMenu_t {
	int ScrollIndex;
	int8_t isOpen, L1, R1, L2, R2, Left, Right, Square, L3, R3, DisabledControlText, setName, customCmd, forceHost, teamForceHost;
	Color bgColor, lineColor, textColor[9], glowColor[9], titleColor, titleGlow;
	int currentLevel, currentPrestige;
};

void pregameThread(uint64_t arg);
void Menu_PaintAll_s(...);
void Menu_PaintAll_h(uint64_t a1, uint64_t a2);

extern pMenu_t* pMenu;

#endif /* __PMENU_H__ */