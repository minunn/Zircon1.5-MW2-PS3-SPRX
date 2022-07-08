#include "Includes.h"

int atoi(const char *str) {
	int res = 0;
	for (int i = 0; str[i] != '\0'; ++i)
		res = res * 10 + str[i] - '0';
	return res;
}

int memcmp(const void* s1, const void* s2, size_t n) {
	const unsigned char *p1 = (const unsigned char*)s1, *p2 = (const unsigned char*)s2;
	while (n--)
		if (*p1 != *p2)
			return *p1 - *p2;
		else
			*p1++, *p2++;
	return 0;
}

void* memcpy(void* dest, const void* src, size_t count) {
	char* dst8 = (char*)dest;
	char* src8 = (char*)src;
	--src8;
	--dst8;

	while (count--) {
		*++dst8 = *++src8;
	}
	return dest;
}

void *memset(void *m, int c, size_t n) {
	char *s = (char*)m;
	while (n-- != 0) {
		*s++ = (char)c;
	}
	return m;
}

size_t strlen(const char *s) {
	const char *p = s;
	while (*s) ++s;
	return s - p;
}

char* str_tok(char* src, char* deli) {
	static char* sr;

	if (src)
		sr = src;

	char *temp = sr, *t;
	int i = 0;

	for (; *temp; temp++)
	{
		for (i = 0; deli[i]; i++)
		{
			if (deli[i] == *temp)
				break;
		}
		if (deli[i])
		{
			*temp = 0;
			if (temp == sr)
				sr++;
			else
			{
				++temp;
				break;
			}
		}
	}

	if (!(*sr))
		return 0;
	t = sr;
	sr = temp;
	return t;
}

char* strncpy(char *s, const char *ct, size_t n) {
	char *saver = s;
	while (n--)
		*saver++ = *ct++;
	*saver = '\0';
	return s;
}

int strncmp(const char* s1, const char* s2, size_t n) {
		for (; n--; ++s1, ++s2) {
		if (*s1 != *s2) {
			return *s1 - *s2;
		}
	}
}

int strcmp(const char* s1, const char* s2) {
	while (*s1 && (*s1 == *s2))
		s1++, s2++;
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

char *strcat(char *destination, const char *source) {
	char *ret = destination;
	while (*destination)
		destination++;
	while (*destination++ = *source++);
	return ret;
}

char* strtok(char* str, char* comp)
{
	static int pos;
	static char *s;
	int i = 0, start = pos;

	if (str != NULL)
		s = str;

	i = 0;
	int j = 0;
	while (s[pos] != '\0')
	{
		j = 0;
		while (comp[j] != '\0')
		{
			if (s[pos] == comp[j])
			{
				s[pos] = '\0';
				pos = pos + 1;
				if (s[start] != '\0')
					return (&s[start]);
				else
				{
					start = pos;
					pos--;
					break;
				}
			}
			j++;
		}
		pos++;
	}
	s[pos] = '\0';
	if (s[start] == '\0')
		return NULL;
	else
		return &s[start];
}

char* strstr(char *s1, const char *s2) {
	if (!s1||!s2)
		return 0;

	for (; *s1; s1++) {
		const char *h, *n;
		for (h = s1, n = s2; *h && *n && (*h == *n); ++h, ++n) {

		}
		if (*n == '\0') {
			return s1;
		}
	}
	return 0;
}


char chcat(char *destination, char source) {
	if (*destination != '\0')
		while (*(++destination));
	return (*(destination++) = source);
}

char* strcpy(char *dest, const char *src) {
	char *orig = dest;
	while ((*dest++ = *src++) != '\0')
		;
	return orig;
}

#include <ctype.h>
char* stolower(char* s) {
	for(; *s; s++)
		tolower(*s);
	return s;
}