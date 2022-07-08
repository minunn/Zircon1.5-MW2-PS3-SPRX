#ifndef __STRING_H__
#define __STRING_H__

/*class string {
private:
	char* pStr;
public:
	string();
	string(const char* string);
	string(char* string);
	~string(void);

	operator char*();
	operator const char*();
	string operator=(const string str);
	string operator=(char* str);
	string operator=(const char* str);
	string operator+=(const string str);
	string operator+=(char* str);
	string operator+=(const char* str);
	string operator+(const string str);
	string operator+(char* str);

	char* c_str();
};*/

typedef class string {
private:
	char _string[0x400];
public:
	string();
	string(char* a);
	int length();
	operator char*();
	operator const char*();
	string operator +(const string str2);
	string operator +=(const string str2);
	string operator =(const string str2);
	bool operator ==(const string str2);
	bool operator ==(const char* str2);
	bool contains(const string str2);
	char* c_str();
};

/*class string {
public:
	char* pStr;

	//constructors
	string();
	~string();
	string(char* str);
	string(const char* str);
	string(int num);

	//operators
	operator char*();
	operator const char*();
	operator int();
	string operator=(const string str);
	string operator=(char* str);
	string operator=(const char* str);
	string operator+=(const string str);
	string operator+=(char* str);
	string operator+=(const char* str);
};*/

#endif /* __STRING_H__ */

