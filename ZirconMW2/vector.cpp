#include "Includes.h"

//Vector2
vec2::vec2() {
	this->x = this->y = 0;
}

vec2::~vec2() {
	memset(&*this, 0, sizeof(*this));
}

vec2::vec2(float x) {
	this->x = x; this->y = 0;
}

vec2::vec2(float x, float y) {
	this->x = x; this->y = y;
}

vec2::vec2(float x, float y, float z) {
	this->x = x; this->y = y;
}

vec2::vec2(float vec[3]) {
	this->x = vec[0]; this->y = vec[1];
}

vec2 vec2::operator()(float x, float y, float z) {
	this->x = x; this->y = y;
}

vec2 vec2::operator+(const vec2 vec) {
	return vec2(this->x + vec.x, this->y + vec.y);
}

vec2 vec2::operator+(const float* vec) {
	return vec2(this->x + vec[0], this->y + vec[1]);
}

vec2 vec2::operator-(const vec2 vec) {
	return vec2(this->x - vec.x, this->y - vec.y);
}

vec2 vec2::operator-(const float* vec) {
	return vec2(this->x - vec[0], this->y - vec[1]);
}

vec2 vec2::operator*=(const vec2 vec) {
	return vec2(this->x * vec.x, this->y * vec.y);
}

vec2 vec2::operator*=(const float scalar) {
	return vec2(this->x * scalar, this->y * scalar);
}

bool vec2::operator==(const vec2 vec) {
	return (this->x == vec.x && this->y == vec.y);
}

bool vec2::operator==(const float value) {
	return (this->x == value && this->y == value);
}

bool vec2::operator!=(const vec2 vec) {
	return (this->x != vec.x && this->y != vec.y);
}

bool vec2::operator!=(const float value) {
	return (this->x != value && this->y != value);
}

vec2::operator float*() {
	return this->convert();
}

float* vec2::convert() {
	return (float*)&this[0];
}

void vec2::print() {
	printf("(%v)\n", this->convert());
}

//Vector3
vec3::vec3() {
	this->x = this->y = this->z = 0;
}

vec3::~vec3() {
	memset(&*this, 0, sizeof(*this));
}

vec3::vec3(float x) {
	this->x = x; this->y = this->z = 0;
}

vec3::vec3(float x, float y) {
	this->x = x; this->y = y; this->z = 0;
}

vec3::vec3(float x, float y, float z) {
	this->x = x; this->y = y; this->z = z;
}

vec3::vec3(float vec[3]) {
	this->x = vec[0]; this->y = vec[1]; this->z = vec[2];
}

vec3 vec3::operator()(float x, float y, float z) {
	this->x = x; this->y = y; this->z = z;
}

vec3 vec3::operator+(const vec3 vec) {
	return vec3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}

vec3 vec3::operator+(const float* vec) {
	return vec3(this->x + vec[0], this->y + vec[1], this->z + vec[2]);
}

vec3 vec3::operator-(const vec3 vec) {
	return vec3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
}

vec3 vec3::operator-(const float* vec) {
	return vec3(this->x - vec[0], this->y - vec[1], this->z - vec[2]);
}

vec3 vec3::operator*=(const vec3 vec) {
	return vec3(this->x * vec.x, this->y * vec.y, this->z * vec.z);
}

vec3 vec3::operator*=(const float scalar) {
	return vec3(this->x * scalar, this->y * scalar, this->z * scalar);
}

bool vec3::operator==(const vec3 vec) {
	return (this->x == vec.x && this->y == vec.y && this->z == vec.z);
}

bool vec3::operator==(const float value) {
	return (this->x == value && this->y == value && this->z == value);
}

bool vec3::operator!=(const vec3 vec) {
	return (this->x != vec.x && this->y != vec.y && this->z != vec.z);
}

bool vec3::operator!=(const float value) {
	return (this->x != value && this->y != value && this->z != value);
}

vec3::operator float*() {
	return this->convert();
}

float* vec3::convert() {
	return (float*)&this[0];
}

void vec3::print() {
	printf("(%v)\n", this->convert());
}