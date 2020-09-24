#include "tiny.h"

void		swap_xyz(t_xyz *a, t_xyz *b)
{
	t_xyz c;
	c = *a;
	*a = *b;
	*b = c;
}

// Height-based vertex sorting, required by draw_tri.
void		sort_tri(t_face *face)
{
	if (face->vert[1].y < face->vert[0].y)
		swap_xyz(&face->vert[0], &face->vert[1]);
	if (face->vert[2].y < face->vert[1].y)
		swap_xyz(&face->vert[1], &face->vert[2]);
	if (face->vert[1].y < face->vert[0].y)
		swap_xyz(&face->vert[0], &face->vert[1]);
}
