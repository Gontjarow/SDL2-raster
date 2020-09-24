#ifndef TINY_H
# define TINY_H

# include "libsdl/SDL.h"
# include "libsdl/SDL_image.h"
# include "libsdl/SDL_mixer.h"
# include "libft/libft.h"

# include <stdio.h>
# include <fcntl.h>
# include <assert.h>

# define WIN_WIDTH 300
# define WIN_HEIGHT 150
# define WIN_MIDWIDTH (WIN_WIDTH / 2)
# define WIN_MIDHEIGHT (WIN_HEIGHT / 2)

typedef struct	s_xy
{
	double x;
	double y;
}				t_xy;

typedef struct	s_xyz
{
	double x;
	double y;
	double z;
}				t_xyz;

typedef struct	s_xyzw
{
	double x;
	double y;
	double z;
	double w;
}				t_xyzw;

typedef struct	s_cam
{
	t_xyz	pos;
	t_xyz	rot;
}				t_cam;

# include "model.h"

void			events();
void			mouse_move(SDL_MouseMotionEvent e);
void			keyboard(SDL_KeyboardEvent e);
void			render();

void			draw(unsigned int *pixel, t_xy start, t_xy end, int color);

void			vec2p(t_xy v);
t_xy			vec2(double x, double y);
t_xyz			vec23(t_xy v, double z);
t_xy			vec2_add(t_xy a, t_xy b);
t_xy			vec2_sub(t_xy a, t_xy b);
t_xy			vec2_mul(t_xy v, double factor);
t_xy			vec2_div(t_xy v, double divisor);

void			vec4p(t_xyzw v);
t_xyzw			vec4(double x, double y, double z, double w);
t_xyz			vec43(t_xyzw v);
t_xyzw			vec4_add(t_xyzw a, t_xyzw b);
t_xyzw			vec4_sub(t_xyzw a, t_xyzw b);
t_xyzw			vec4_mul(t_xyzw v, double factor);
t_xyzw			vec4_div(t_xyzw v, double divisor);

void			vec3p(t_xyz v);
t_xyz			vec3(double x, double y, double z);
t_xy			vec32(t_xyz v);
t_xyzw			vec34(t_xyz v, double w);
t_xyz			vec3_add(t_xyz a, t_xyz b);
t_xyz			vec3_sub(t_xyz a, t_xyz b);
t_xyz			vec3_mul(t_xyz v, double scalar);
t_xyz			vec3_div(t_xyz v, double divisor);
double			vec3_mag(t_xyz v);
t_xyz			vec3_norm(t_xyz v);
double			vec3_dot(t_xyz a, t_xyz b);
t_xyz			vec3_cross(t_xyz a, t_xyz b);
double			vec3_dist(t_xyz a, t_xyz b);

#endif
