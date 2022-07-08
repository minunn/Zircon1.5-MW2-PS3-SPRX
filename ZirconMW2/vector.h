#ifndef __VECTOR_H__
#define __VECTOR_H__

class vec2 {
public:
	float x, y;

	//constructors
	vec2();
	~vec2();
	vec2(float x);
	vec2(float x, float y);
	vec2(float x, float y, float z);
	vec2(float vect[2]);

	//operators
	vec2 operator()(float x, float y, float z);
	vec2 operator+(const vec2 vec);
	vec2 operator+(const float* vec);
	vec2 operator-(const vec2 vec);
	vec2 operator-(const float* vec);
	vec2 operator*=(const vec2 vec);
	vec2 operator*=(const float scalar);
	bool operator==(const vec2 vec);
	bool operator==(const float value);
	bool operator!=(const vec2 vec);
	bool operator!=(const float value);
	operator float*();

	//functions
	float* convert();
	void print();
};

class vec3 {
public:
	float x, y, z;

	//constructors
	vec3();
	~vec3();
	vec3(float x);
	vec3(float x, float y);
	vec3(float x, float y, float z);
	vec3(float vect[3]);

	//operators
	vec3 operator()(float x, float y, float z);
	vec3 operator+(const vec3 vec);
	vec3 operator+(const float* vec);
	vec3 operator-(const vec3 vec);
	vec3 operator-(const float* vec);
	vec3 operator*=(const vec3 vec);
	vec3 operator*=(const float scalar);
	bool operator==(const vec3 vec);
	bool operator==(const float value);
	bool operator!=(const vec3 vec);
	bool operator!=(const float value);
	operator float*();

	//functions
	float* convert();
	void print();
};

#endif /* __VECTOR_H__ */