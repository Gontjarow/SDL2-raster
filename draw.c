#include "tiny.h"

void draw(unsigned int *pixel, t_xy start, t_xy end, int color)
{
	t_xy	dir;
	t_xy	abs;
	int		step;
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
