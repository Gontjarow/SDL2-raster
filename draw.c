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

// Fixed, exactly 3-vert triangle, assumes height-sorted order.

void		draw_tri(unsigned int *pixel, t_face face, int color)
{
	t_xyz	slope;
	double	scanline;
	double	x1;
	double	x2;

	// printf("tri\n");
	slope.x = vec2_invslope(vec32(face.vert[1]), vec32(face.vert[0])); // A->B
	slope.z = vec2_invslope(vec32(face.vert[2]), vec32(face.vert[0])); // A->C
	slope.y = vec2_invslope(vec32(face.vert[2]), vec32(face.vert[1])); // B->C
	scanline = face.vert[0].y;
	x2 = face.vert[0].x;
	x1 = (face.vert[0].y == face.vert[1].y) ? face.vert[1].x : face.vert[0].x;
	// printf("tri verts:"); vec3p(face.vert[0]); vec3p(face.vert[1]); vec3p(face.vert[2]);
	// printf("x1: %f x2: %f line: %f\n", x1, x2, scanline);
	while (scanline < face.vert[2].y)
	{
		// printf("scanline %f\n", scanline);
		draw(pixel, vec2(x1, scanline), vec2(x2, scanline), color);
		x1 += (scanline < face.vert[1].y) ? slope.x : slope.y;
		x2 += slope.z;
		++scanline;
	}
}
