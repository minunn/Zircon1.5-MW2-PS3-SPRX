#include "Includes.h"

string::string() {

}

string::operator char*() {
	return _string;
}
string::operator const char*() {
	return _string;
}
string::string(char* a) {
	strcpy(_string, a);
}

int string::length() {
	return strlen(_string);
}

string string::operator +(const string str2) {
	char out[sizeof(_string) + sizeof(str2._string)];
	strcpy(out, _string);
	strcat(out, str2._string);
	strcpy(_string, out);
	return *this;
}

string string::operator +=(const string str2) {
	return *this + str2;
}
string string::operator =(const string str2) {
	strcpy(_string, str2._string);
	return *this;
}
bool string::operator ==(const string str2) {
	return !strcmp(_string, str2._string);
}
bool string::operator ==(const char* str2) {
	return !strcmp(_string, str2);
}
bool string::contains(const string str2) {
	return strstr(_string, str2._string);
}

char* string::c_str() {
	return (char*)&this->_string;
}


/*
string::string() {
int length = 1;
this->pStr = (char*)malloc(length);
this->pStr[0] = '\0';
}

string::string(const char* string) {
int length = strlen(string) + 1;
this->pStr = (char*)malloc(length);
strcpy(this->pStr, string);
}

string::string(char* string) {
int length = strlen(string) + 1;
this->pStr = (char*)malloc(length);
strcpy(this->pStr, string);
}

string::~string() {
free(this->pStr);
}

string::operator char *() {
return this->pStr;
}

string::operator const char *() {
return this->pStr;
}

string string::operator=(const string str) {
if (!strlen(str.pStr)) {
char* new_string = (char*)malloc(1);
free(this->pStr);
this->pStr = new_string;
this->pStr[0] = '\0';
}
else {
char* new_string = (char*)malloc(strlen(str.pStr) + 1);
free(this->pStr);
this->pStr = new_string;
strcpy(this->pStr, str.pStr);
}
}

string string::operator=(char* str) {
if (!strlen(str)) {
char* new_string = (char*)malloc(1);
free(this->pStr);
this->pStr = new_string;
this->pStr[0] = '\0';
}
else {
char* new_string = (char*)malloc(strlen(str) + 1);
free(this->pStr);
this->pStr = new_string;
strcpy(this->pStr, str);
}
}

string string::operator=(const char* str) {
if (!strlen(str)) {
char* new_string = (char*)malloc(1);
free(this->pStr);
this->pStr = new_string;
this->pStr[0] = '\0';
}
else {
char* new_string = (char*)malloc(strlen(str) + 1);
free(this->pStr);
this->pStr = new_string;
strcpy(this->pStr, str);
}
}

string string::operator+=(const string str) {
char* saver = this->pStr;
this->pStr = (char*)malloc(strlen(saver) + strlen(str.pStr) + 1);
strcpy(this->pStr, saver);
strcat(this->pStr, str.pStr);
free(saver);
}

string string::operator+=(char* str) {
char* saver = this->pStr;
this->pStr = (char*)malloc(strlen(saver) + strlen(str) + 1);
strcpy(this->pStr, saver);
strcat(this->pStr, str);
free(saver);
}

string string::operator+=(const char* str) {
char* saver = this->pStr;
this->pStr = (char*)malloc(strlen(saver) + strlen(str) + 1);
strcpy(this->pStr, saver);
strcat(this->pStr, str);
free(saver);
}

string string::operator+(const string str) {
char* out = (char*)malloc(strlen(this->pStr) + strlen(str.pStr) + 1);
sprintf(out, "%s%s", this->pStr, str.pStr);
printf("%s\n", out);
free(this->pStr);
this->pStr = out;
return *this;
}

string string::operator+(char* str) {
char* out = (char*)malloc(strlen(this->pStr) + strlen(str) + 1);
sprintf(out, "%s%s", this->pStr, str);
printf("%s\n", out);
free(this->pStr);
this->pStr = out;
return *this;
}

char* string::c_str() {
return this->pStr;
}*/

/*string::string() {

}

string::~string() {
	free(this->pStr);
}

string::string(char* str) {
	this->pStr = (char*)malloc(strlen(str) + 1);
	strcpy(this->pStr, str);
}

string::string(const char* str) {
	this->pStr = (char*)malloc(strlen(str) + 1);
	strcpy(this->pStr, str);
}

string::operator char*() {
	return this->pStr;
}

string::operator const char*() {
	return this->pStr;
}

string::operator int() {
	return atoi(this->pStr);
}

string string::operator=(const string str) {
	this->pStr = (char*)malloc(strlen(str.pStr) + 1);
	strcpy(this->pStr, str.pStr);
}

string string::operator=(char* str) {
	if(strlen(str) <= 0) {
		memset(this->pStr, 0, strlen(this->pStr) + 1);
	}
	else {
		memset(this->pStr, 0, strlen(this->pStr) + 1);
		this->pStr = (char*)malloc(strlen(str) + 1);
		strcpy(this->pStr, str);
	}
}

string string::operator=(const char* str) {
	if (strlen(str) <= 0) {
		memset(this->pStr, 0, strlen(this->pStr) + 1);
	}
	else {
		memset(this->pStr, 0, strlen(this->pStr) + 1);
		this->pStr = (char*)malloc(strlen(str) + 1);
		strcpy(this->pStr, str);
	}
}

string string::operator+=(const string str) {
	char* saver = this->pStr;
	this->pStr = (char*)malloc(strlen(saver) + strlen(str.pStr) + 1);
	strcpy(this->pStr, saver);
	strcat(this->pStr, str.pStr);
	free(saver);
}

string string::operator+=(char* str) {
	char* saver = this->pStr;
	this->pStr = (char*)malloc(strlen(saver) + strlen(str) + 1);
	strcpy(this->pStr, saver);
	strcat(this->pStr, str);
	free(saver);
}

string string::operator+=(const char* str) {
	char* saver = this->pStr;
	this->pStr = (char*)malloc(strlen(saver) + strlen(str) + 1);
	strcpy(this->pStr, saver);
	strcat(this->pStr, str);
	free(saver);
}*/