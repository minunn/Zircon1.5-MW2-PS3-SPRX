#include "includes.h"

void AngleVectors(const float* angles, float* forward, float* right, float* up) {
	float angle;
	static float sr, sp, sy, cr, cp, cy;
	// static to help MS compiler fp bugs

	angle = angles[YAW] * (M_PI * 2 / 360);
	sy = sinf(angle);
	cy = cosf(angle);
	angle = angles[PITCH] * (M_PI * 2 / 360);
	sp = sinf(angle);
	cp = cosf(angle);
	angle = angles[ROLL] * (M_PI * 2 / 360);
	sr = sinf(angle);
	cr = cosf(angle);

	if (forward) {
		forward[0] = cp * cy;
		forward[1] = cp * sy;
		forward[2] = -sp;
	}
	if (right) {
		right[0] = (-1 * sr * sp * cy + -1 * cr * -sy);
		right[1] = (-1 * sr * sp * sy + -1 * cr * cy);
		right[2] = -1 * sr * cp;
	}
	if (up) {
		up[0] = (cr * sp * cy + -sr * -sy);
		up[1] = (cr * sp * sy + -sr * cy);
		up[2] = cr * cp;
	}
}

void vectoangles(vec3_t vec, vec3_t angles)
{
	float forward;
	float yaw, pitch;
	if (!vec[X] && !vec[Y])
	{
		yaw = 0;
		if (vec[Z] > 0)
			pitch = 90.00;
		else
			pitch = 270.00;
	}
	else
	{
		if (vec[X] != -1)
			yaw = (float)(atan2((double)vec[Y], (double)vec[X]) * 180.00 / M_PI);
		else if (vec[Y] > 0)
			yaw = 90.00;
		else
			yaw = 270;
		if (yaw < 0)
			yaw += 360.00;

		forward = (float)f_sqrtf((double)(vec[X] * vec[X] + vec[Y] * vec[Y]));
		pitch = (float)(atan2((double)vec[Z], (double)forward) * 180.00 / M_PI);
		if (pitch < 0)
			pitch += 360.00;
	}
	angles[X] = -pitch;
	angles[Y] = yaw;
	angles[Z] = 0;
}

void anglesToForward(float out[3], float angles[3], float start[3], vec_t scale) {
	vec3_t forward;
	AngleVectors(angles, forward, NULL, NULL);
	VectorMA(start, scale, forward, out);
}