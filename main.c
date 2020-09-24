#include "tiny.h"

int			g_quit = 0;
SDL_Window	*g_window = NULL;
SDL_Surface	*g_surface = NULL;
// const Uint8	*g_keystate; // Is this even needed if we poll events?

t_mesh		*g_debugmesh;
t_cam		g_camera = {0};

int main()
{
	t_mesh test = load_model("tiny-donut.obj");
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
}

void	render()
{
	// Uint32 time = SDL_GetTicks();

	SDL_memset(g_surface->pixels, 0, WIN_WIDTH * g_surface->pitch);

	// t_xy center = vec2(WIN_MIDWIDTH, WIN_MIDHEIGHT);
	// t_xy dir = vec2(cos(time * 0.01), sin(time * 0.01));
	// t_xy end = vec2_add(center, vec2_mul(dir, 100));
	// draw(g_surface->pixels, center, end, 0xFFFF00);

	for (int i = 0; i < g_debugmesh->faces; ++i)
	{
		// original
		t_face o = g_debugmesh->face[i];

		// face copy
		t_face f = init_face(3,
			o.vert[0],
			o.vert[1],
			o.vert[2]);

		// face normal
		t_xyz normal = vec3_norm(vec3_cross(
			vec3_sub(f.vert[2], f.vert[0]),
			vec3_sub(f.vert[1], f.vert[0])));

		// transformed
		t_face tf = init_face(3,
			vec3((f.vert[0].x+1) * WIN_MIDWIDTH, (f.vert[0].y+1) * WIN_MIDHEIGHT, 0),
			vec3((f.vert[1].x+1) * WIN_MIDWIDTH, (f.vert[1].y+1) * WIN_MIDHEIGHT, 0),
			vec3((f.vert[2].x+1) * WIN_MIDWIDTH, (f.vert[2].y+1) * WIN_MIDHEIGHT, 0));

		// Calculate how much face aligns with the light
		double light = vec3_dot(vec3(0,-1,0), normal);

		if (light > 0)
		{
			// Greyscale brighrness; Same value used for R, G, and B
			int color = 255 * light;
			color = color | color << 8 | color << 16;

			// Fix vertex order and draw
			sort_tri(&tf);
			draw_tri(g_surface->pixels, tf, color);
		}
		free_verts(&f);
		free_verts(&tf);
	}
}
