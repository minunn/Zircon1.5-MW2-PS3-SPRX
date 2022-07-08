#ifndef Q_MATH_H
#define Q_MATH_H

typedef float vec_t;
typedef vec_t vec3_t[3];

#define PITCH       0   // up / down
#define YAW         1   // left / right
#define ROLL        2   // fall over
#define X			0
#define Y			1
#define Z			2

#define DotProduct(x,y)			((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
#define VectorSubtract(a,b,c)	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define VectorAdd(a,b,c)    	((c)[0]=(a)[0]+(b)[0],(c)[1]=(a)[1]+(b)[1],(c)[2]=(a)[2]+(b)[2])
#define VectorCopy(a,b)			((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])
#define	VectorScale(v, s, o)	((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define	VectorMA(v, s, b, o)	((o)[0]=(v)[0]+(b)[0]*(s),(o)[1]=(v)[1]+(b)[1]*(s),(o)[2]=(v)[2]+(b)[2]*(s))
#define VectorDistanceSq(a, b)	((((a)[0]-(b)[0])*((a)[0]-(b)[0]))+(((a)[1]-(b)[1])*((a)[1]-(b)[1]))+(((a)[2]-(b)[2])*((a)[2]-(b)[2])))
#define VectorDistance(a, b)	(sqrt(VectorDistanceSq(a, b)))

#define VectorClear(a)			((a)[0]=(a)[1]=(a)[2]=0)
#define VectorNegate(a,b)		((b)[0]=-(a)[0],(b)[1]=-(a)[1],(b)[2]=-(a)[2])
#define VectorSet(v, x, y, z)	((v)[0]=(x), (v)[1]=(y), (v)[2]=(z))
#define Vector4Copy(a,b)		((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2],(b)[3]=(a)[3])

void AngleVectors(const float* angles, float* forward, float* right, float* up);
void vectoangles(vec3_t vec, vec3_t angles);
void anglesToForward(float out[3], float angles[3], float start[3], vec_t scale);

#endif