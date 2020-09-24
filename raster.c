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
	assert(face->vert[0].y <= face->vert[1].y && face->vert[1].y <= face->vert[2].y);
}

// Raster-space bounding box
t_xy		bb_min(t_face face)
{
	int i;
	t_vert lowest;
	t_vert current;

	lowest = face.vert[0];
	i = 1;
	while (i < face.verts)
	{
		current = face.vert[i];
		if (current.y < lowest.y) lowest.y = current.y;
		if (current.x < lowest.x) lowest.x = current.x;
		++i;
	}
	return vec32(lowest);
}

// Raster-space bounding box
t_xy		bb_max(t_face face)
{
	int i;
	t_vert highest;
	t_vert current;

	highest = face.vert[0];
	i = 1;
	while (i < face.verts)
	{
		current = face.vert[i];
		if (current.y > highest.y) highest.y = current.y;
		if (current.x > highest.x) highest.x = current.x;
		++i;
	}
	return vec32(highest);
}
