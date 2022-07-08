#ifndef __STDIO_H__
#define __STDIO_H__

#ifndef NULL
#define NULL 0
#endif

typedef void* PVOID;
#define HAVE_UNSIGNED_LONG_LONG_INT
#define HAVE_STDINT_H
#define HAVE_INTTYPES_H
#define HAVE_STDDEF_H
#define HAVE_LONG_LONG_INT

#define VA_START(ap, last) va_start(ap, last)
#define VA_SHIFT(ap, value, type) 

#ifdef HAVE_INTTYPES_H
#include <inttypes.h>	
#endif	

#ifdef HAVE_STDDEF_H
#include <stddef.h>	
#endif	

#ifdef HAVE_STDINT_H
#include <stdint.h>	
#endif	
#define INT_MAX		0x7fffffff
#ifndef ULONG_MAX	
#ifdef UINT_MAX
#define ULONG_MAX UINT_MAX
#else
#define ULONG_MAX INT_MAX
#endif	
#endif	
#ifdef ULLONG
#undef ULLONG
#endif	
#ifdef HAVE_UNSIGNED_LONG_LONG_INT
#define ULLONG unsigned long long int
#ifndef ULLONG_MAX
#define ULLONG_MAX ULONG_MAX
#endif	
#else
#define ULLONG unsigned long int
#ifdef ULLONG_MAX
#undef ULLONG_MAX
#endif	
#define ULLONG_MAX ULONG_MAX
#endif	

#ifdef UINTMAX_T
#undef UINTMAX_T
#endif	
#if HAVE_UINTMAX_T || defined(uintmax_t)
#define UINTMAX_T uintmax_t
#ifndef UINTMAX_MAX
#define UINTMAX_MAX ULLONG_MAX
#endif	
#else
#define UINTMAX_T ULLONG
#ifdef UINTMAX_MAX
#undef UINTMAX_MAX
#endif	
#define UINTMAX_MAX ULLONG_MAX
#endif	


#ifndef LDOUBLE
#if HAVE_LONG_DOUBLE
#define LDOUBLE long double
#else
#define LDOUBLE double
#endif	
#endif	

#ifndef LLONG
#ifdef HAVE_LONG_LONG_INT
#define LLONG long long int
#else
#define LLONG long int
#endif	
#endif	

#ifndef INTMAX_T
#if HAVE_INTMAX_T || defined(intmax_t)
#define INTMAX_T intmax_t
#else
#define INTMAX_T LLONG
#endif	
#endif

#ifndef UINTPTR_T
#if HAVE_UINTPTR_T || defined(uintptr_t)
#define UINTPTR_T uintptr_t
#else
#define UINTPTR_T unsigned long int
#endif	
#endif

#ifndef PTRDIFF_T
#if HAVE_PTRDIFF_T || defined(ptrdiff_t)
#define PTRDIFF_T ptrdiff_t
#else
#define PTRDIFF_T long int
#endif	
#endif	

#ifndef UPTRDIFF_T
#define UPTRDIFF_T PTRDIFF_T
#endif	

#ifndef SSIZE_T
#define SSIZE_T size_t
#endif	


#ifdef MAX_CONVERT_LENGTH
#undef MAX_CONVERT_LENGTH
#endif	
#define MAX_CONVERT_LENGTH      43

/* Format read states. */
#define PRINT_S_DEFAULT         0
#define PRINT_S_FLAGS           1
#define PRINT_S_WIDTH           2
#define PRINT_S_DOT             3
#define PRINT_S_PRECISION       4
#define PRINT_S_MOD             5
#define PRINT_S_CONV            6

/* Format flags. */
#define PRINT_F_MINUS           (1 << 0)
#define PRINT_F_PLUS            (1 << 1)
#define PRINT_F_SPACE           (1 << 2)
#define PRINT_F_NUM             (1 << 3)
#define PRINT_F_ZERO            (1 << 4)
#define PRINT_F_QUOTE           (1 << 5)
#define PRINT_F_UP              (1 << 6)
#define PRINT_F_UNSIGNED        (1 << 7)
#define PRINT_F_TYPE_G          (1 << 8)
#define PRINT_F_TYPE_E          (1 << 9)

/* Conversion flags. */
#define PRINT_C_CHAR            1
#define PRINT_C_SHORT           2
#define PRINT_C_LONG            3
#define PRINT_C_LLONG           4
#define PRINT_C_LDOUBLE         5
#define PRINT_C_SIZE            6
#define PRINT_C_PTRDIFF         7
#define PRINT_C_INTMAX          8

#ifndef MAX
#define MAX(x, y) ((x >= y) ? x : y)
#endif	
#ifndef CHARTOINT
#define CHARTOINT(ch) (ch - '0')
#endif	
#ifndef ISDIGIT
#define ISDIGIT(ch) ('0' <= (unsigned char)ch && (unsigned char)ch <= '9')
#endif	
#ifndef ISNAN
#define ISNAN(x) (x != x)
#endif	
#ifndef ISINF
#define ISINF(x) (x != 0.0 && x + x == x)
#endif	

#define OUTCHAR(str, len, size, ch)                                          \
do {                                                                         \
	if (len + 1 < size)                                                  \
		str[len] = ch;                                               \
	(len)++;                                                             \
} while (0)

int vsnprintf(char *str, size_t size, const char *format, va_list args);
void fmtstr(char *str, size_t *len, size_t size, const char *value, int width, int precision, int flags);
void fmtint(char *str, size_t *len, size_t size, long long int value, int base, int width, int precision, int flags);
void fmtflt(char *str, size_t *len, size_t size, double fvalue, int width, int precision, int flags, int *overflow);
void printsep(char *str, size_t *len, size_t size);
int getnumsep(int digits);
int getexponent(double value);
int convert(unsigned long long int value, char *buf, size_t size, int base, int caps);
unsigned long long int cast(double value);
unsigned long long myround(double value);
double mypow10(int exponent);
int vsprintf(char *buf, const char *fmt, va_list args);
int sprintf(char *buffer, const char *fmt, ...);
int snprintf(char *buffer, size_t len, const char *fmt, ...);
int printf(const char *fmt, ...);
int TTY_WRITE(const char *fmt);
const char *va(const char *fmt, ...);

#endif