#include "tiny.h"

int			g_quit = 0;
SDL_Window	*g_window = NULL;
SDL_Surface	*g_surface = NULL;
// const Uint8	*g_keystate; // Is this even needed if we poll events?

t_cam		g_camera = {0};

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	g_window = SDL_CreateWindow("tiny", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
	g_surface = SDL_GetWindowSurface(g_window);
	while (g_quit == 0)
	{
		//g_keystate = SDL_GetKeyboardState(NULL);
		uint32_t frame_start = SDL_GetTicks();

		events();
		render();

		uint32_t frame_ticks = SDL_GetTicks() - frame_start;
		if (frame_ticks < 1000/60)
			SDL_Delay(1000/60 - frame_ticks);
		printf("frame ticks %u\n", frame_ticks);
		SDL_UpdateWindowSurface(g_window);
	}
}

void	events()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_MOUSEMOTION)
			mouse_move(e.motion);
		else if (e.type == SDL_KEYDOWN)
			keyboard(e.key);
		else if (e.type == SDL_QUIT)
			g_quit = 1;
	}
}

void	mouse_move(SDL_MouseMotionEvent e)
{
	// todo
}

/*
** Note: This part already defines that we'll be using the RIGHT-HAND RULE.
** Everybody else does it. Let's not get creative.
*/
void	keyboard(SDL_KeyboardEvent e)
{
	if (e.keysym.scancode == SDL_SCANCODE_W) // fwd
		g_camera.pos.x += 0.1;
	if (e.keysym.scancode == SDL_SCANCODE_A) // left
		g_camera.pos.y += 0.1;
	if (e.keysym.scancode == SDL_SCANCODE_S) // back
		g_camera.pos.x -= 0.1;
	if (e.keysym.scancode == SDL_SCANCODE_D) // right
		g_camera.pos.y -= 0.1;
}

void	render()
{
	Uint32 time = SDL_GetTicks();

	SDL_memset(g_surface->pixels, 0, WIN_WIDTH * g_surface->pitch);

	t_xy center = vec2(WIN_MIDWIDTH, WIN_MIDHEIGHT);
	t_xy dir = vec2(cos(time * 0.01), sin(time * 0.01));
	t_xy end = vec2_add(center, vec2_mul(dir, 100));
	draw(g_surface->pixels, center, end, 0xFFFF00);
}
