#include "tiny.h"

t_xy	vec2(double x, double y)
{
	return ((t_xy){x, y});
}

t_xyz	vec23(t_xy v, double z)
{
	return vec3(v.x, v.y, z);
}

t_xy	vec2_add(t_xy a, t_xy b)
{
	return vec2(
		a.x + b.x,
		a.y + b.y
	);
}

t_xy	vec2_sub(t_xy a, t_xy b)
{
	return vec2(
		a.x - b.x,
		a.y - b.y
	);
}

t_xy	vec2_mul(t_xy v, double factor)
{
	return vec2(
		v.x * factor,
		v.y * factor
	);
}

t_xy	vec2_div(t_xy v, double divisor)
{
	return vec2_mul(v, 1 / divisor);
}
