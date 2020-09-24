#include "tiny.h"

int			g_quit = 0;
SDL_Window	*g_window = NULL;
SDL_Surface	*g_surface = NULL;
// const Uint8	*g_keystate; // Is this even needed if we poll events?

t_mesh		*g_debugmesh;
t_cam		g_camera = {0};

int main(int argc, char **argv)
{
	if (argc == 1) return (0);

	t_mesh test = load_model(argv[1]);
	g_debugmesh = &test;
	printf("test model: faces %d, data %p\n", test.faces, test.face);
	// int i = 0;
	// while (i < test.faces)
	// {
	// 	int v = 0;
	// 	while (v < test.face[i].verts)
	// 	{
	// 		vec3p(test.face[i].vert[v]);
	// 		++v;
	// 	}
	// 	++i;
	// }
	printf("End of init output.\n");

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
	(void)e; // todo
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
	if (e.keysym.scancode == SDL_SCANCODE_ESCAPE)
		exit(0);
}

/*
** Note: In screen-space coordinates, +Z or "up" is towards the viewer.
** Note: +X is left, +Y is down. Nothing special there.
*/
void	render()
{
	SDL_memset(g_surface->pixels, 0, WIN_WIDTH * g_surface->pitch);

	int i = 0;
	while (i < g_debugmesh->faces)
	{
		// Vertex array (Currently assuming exactly 3 verts.)
		t_vert *v = g_debugmesh->face[i++].vert;

		// Face-normal
		t_xyz normal = vec3_norm(vec3_cross(
			vec3_sub(v[2], v[0]),
			vec3_sub(v[1], v[0])));

		// How much the face aligns with the camera (backface culling)
		double facing = vec3_dot(vec3(0,0,-1), normal); //? Doesn't this contradict "+Z towards camera"
		if (facing > 0)
		{
		// How much the face aligns with the light
		double light = vec3_dot(vec3(0,0,-1), normal);
			if (light > 0)
		{
			// Greyscale brightness; Same value used for R, G, and B
				int color = 255 * light; if (color < 0) color = 0;
			color = color | color << 8 | color << 16;

			// Transformed face (moved and scaled to window size)
				double s = 1.5;
			t_face tf = init_face(3,
				vec3((v[0].x + s) * WIN_MIDWIDTH / s, (v[0].y + s) * WIN_MIDHEIGHT / s, 0),
				vec3((v[1].x + s) * WIN_MIDWIDTH / s, (v[1].y + s) * WIN_MIDHEIGHT / s, 0),
				vec3((v[2].x + s) * WIN_MIDWIDTH / s, (v[2].y + s) * WIN_MIDHEIGHT / s, 0));

			draw_tri(g_surface->pixels, tf, color);
			free_verts(&tf);

				SDL_UpdateWindowSurface(g_window);
				SDL_Delay(15);
		}
	}
}
}
