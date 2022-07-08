#ifndef __CSTRING_H__
#define __CSTRING_H__

int atoi(const char *str);
int memcmp(const void* s1, const void* s2, size_t n);
void* memcpy(void* dest, const void* src, size_t count);
void *memset(void *ptr, int value, size_t num);
size_t strlen(const char *str);
char* str_tok(char* src, char* deli);
char* strncpy(char *s, const char *ct, size_t n);
char* strtok(char* str, char* comp);
int strcmp(const char* str1, const char* str2);
int strncmp(const char* s1, const char* s2, size_t n);
char *strcat(char *destination, const char *source);
char* strstr(char *s1, const char *s2);
char chcat(char *destination, char source);
char* strcpy(char *dest, const char *src);
char* stolower(char* s);

#endif