#ifndef __DVAR_H__
#define __DVAR_H__

/* dvar->flags */
#define DVAR_ARCHIVE		1
#define DVAR_LATCH		2
#define DVAR_CHEAT		4
#define DVAR_USER_CREATED	0x100
#define DVAR_SAVED		0x200
#define DVAR_SERVERINFO		0x400
#define DVAR_INIT		0x800
#define DVAR_CHANGEABLE_RESET	0x1000
#define DVAR_ROM		0x2000
#define DVAR_EXTERNAL		0x4000
#define DVAR_AUTOEXEC		0x8000

/* dvar->type */
#define DVAR_TYPE_BOOL		0
#define DVAR_TYPE_FLOAT		1
#define DVAR_TYPE_FLOAT_2	2
#define DVAR_TYPE_FLOAT_3	3
#define DVAR_TYPE_FLOAT_4	4
#define DVAR_TYPE_INT		5
#define DVAR_TYPE_ENUM		6
#define DVAR_TYPE_STRING	7
#define DVAR_TYPE_COLOR		8
#define DVAR_TYPE_FLOAT_3_COLOR	9
#define DVAR_TYPE_COUNT		10

union DvarLimits
{
	struct {
		int stringCount;
		const char **strings;
	} enumeration;

	struct {
		int min;
		int max;
	} integer;

	struct {
		float min;
		float max;
	} value, vector;
}; //0x8

union DvarValue
{
	bool enabled;
	int integer;
	unsigned int unsignedInt;
	float value;
	float vector[4];
	const char *string;
	char color[4];
}; //0x10


struct dvar_s
{
	const char *name; //0x0
	const char *description; //0x4
	unsigned short flags; //0x8
	char type; //0xA
	bool modified; //0xB
	DvarValue current; //0xC
	DvarValue latched; //0x1C
	DvarValue reset; //0x2C
	DvarLimits domain; //0x3C
	dvar_s * next; //0x44
};

#endif /* __DVAR_H__ */