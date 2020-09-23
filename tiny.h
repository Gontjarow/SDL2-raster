#ifndef TINY_H
# define TINY_H

# include "libsdl/SDL.h"
# include "libsdl/SDL_image.h"
# include "libsdl/SDL_mixer.h"

# include <stdio.h>

# define WIN_WIDTH 300
# define WIN_HEIGHT 150

typedef struct	s_xyzw
{
	double x;
	double y;
	double z;
	double w;
}				t_xyzw;

typedef struct	s_cam
{
	t_xyzw	pos;
	t_xyzw	rot;
}				t_cam;

void			events();
void			mouse_move(SDL_MouseMotionEvent e);
void			keyboard(SDL_KeyboardEvent e);
void			render();

#endif
