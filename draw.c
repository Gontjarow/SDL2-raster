#include "tiny.h"

void draw(unsigned int *pixel, t_xy start, t_xy end, int color)
{
	t_xy	dir;
	t_xy	abs;
	float	step;
	int		i;
	int		index;

	dir = vec2_sub(end, start);
	abs = vec2(fabs(dir.x), fabs(dir.y));
	step = (abs.x > abs.y) ? abs.x : abs.y;
	dir = vec2_div(dir, step);
	i = 0;
	while (i <= step)
	{
		index = (int)start.x + (int)start.y * WIN_WIDTH;
		if ((int)start.x >= 0 && (int)start.x < WIN_WIDTH
		&& ((int)start.y >= 0 && (int)start.y < WIN_HEIGHT)
		&& (index >= 0 && index < WIN_WIDTH * WIN_HEIGHT))
			pixel[index] = color;
		start.x += dir.x;
		start.y += dir.y;
		++i;
	}
}

// Fixed, exactly 3-vert triangle.
// Note: wavefront.obj triangles have verts in counter-clockwise order.
void		draw_tri(unsigned int *pixel, t_face face, int color)
{
	t_vert v1 = face.vert[0];
	t_vert v2 = face.vert[1];
	t_vert v3 = face.vert[2];
	t_xy min = bb_min(face);
	t_xy max = bb_max(face);

	t_xy vs1 = vec32(vec3_sub(v2, v1));
	t_xy vs2 = vec32(vec3_sub(v3, v1));

	for (int y = min.y; y < max.y; ++y)
	for (int x = min.x; x < max.x; ++x)
	{
		t_xy q = vec2(x - v1.x, y - v1.y);

		double s = vec2_cross(q, vs2) / vec2_cross(vs1, vs2);
		double t = vec2_cross(vs1, q) / vec2_cross(vs1, vs2);

		if ((s>=0) && (t>=0) && (s+t<=1))
		{
			pixel[x + y * WIN_WIDTH] = color;
		}
	}
}

// Attempt at optimizing the above draw_tri, will replace if successful.
void		draw_tribary(unsigned int *pixel, t_face face, int color)
{
	t_xy v0 = vec32(face.vert[0]);
	t_xy min = bb_min(face);
	t_xy max = bb_max(face);

	for (int y = min.y; y < max.y; ++y)
	for (int x = min.x; x < max.x; ++x)
	{
		if (inside(vec2(x, y), face))
		{
			pixel[x + y * WIN_WIDTH] = color;
		}
	}
}
