#include "tiny.h"

int			g_quit = 0;
SDL_Window	*g_window = NULL;
SDL_Surface	*g_surface = NULL;
// const Uint8	*g_keystate; // Is this even needed if we poll events?

t_mesh		*g_debugmesh;
t_cam		g_camera = {0};

int main()
{
	t_mesh test = load_model("tiny-monk.obj");
	g_debugmesh = &test;
	printf("test model: faces %d, data %p\n", test.faces, test.face);
	int i = 0;
	while (i < test.faces)
	{
		int v = 0;
		while (v < test.face[i].verts)
		{
			vec3p(test.face[i].vert[v]);
			++v;
		}
		++i;
	}

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
		// printf("frame ticks %u\n", frame_ticks);
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

	// t_xy center = vec2(WIN_MIDWIDTH, WIN_MIDHEIGHT);
	// t_xy dir = vec2(cos(time * 0.01), sin(time * 0.01));
	// t_xy end = vec2_add(center, vec2_mul(dir, 100));
	// draw(g_surface->pixels, center, end, 0xFFFF00);

	for (int i = 0; i < g_debugmesh->faces; ++i)
	for (int v = 0; v < g_debugmesh->face[i].verts - 1; ++v)
	{
		t_vert v1 = g_debugmesh->face[i].vert[v];
		v1 = vec3_add(v1, vec3(2,1,0));
		v1 = vec3_mul(v1, 80);

		t_vert v2 = g_debugmesh->face[i].vert[v + 1];
		v2 = vec3_add(v2, vec3(2,1,0));
		v2 = vec3_mul(v2, 80);

		draw(g_surface->pixels, vec32(v1), vec32(v2), 0xFF8000);
	}
}
