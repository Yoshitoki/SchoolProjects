#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>
#include <sstream>

#include "MyApp.h"

int main (int argc, char* args[])
{
	atexit(SDL_Quit);

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		std::cerr << "[SDL inditasa] Hiba az SDL inicializalasa kozben: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	SDL_Window *win = SDL_CreateWindow("Oktaederek", 150, 100, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (!win)
	{
		std::cerr << "[Ablak letrehozasa] Hiba az SDL inicializalasa kozben: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_GLContext	context = SDL_GL_CreateContext(win);
	if (!context)
	{
		std::cerr << "[OGL context letrehozasa] Hiba az SDL inicializalasa kozben: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_GL_SetSwapInterval(1);

	GLenum error = glewInit();
	if (GLEW_OK != error)
	{
		std::cerr << "[GLEW] Hiba az inicializalas soran!" << std::endl;
		return 1;
	}

	int glVersion[2] = { -1, -1 };
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
	std::cout << "OpenGL verzio: " << glVersion[0] << "." << glVersion[1] << std::endl;

	if (glVersion[0] == -1 && glVersion[1] == -1)
	{
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(win);

		std::cerr << "[OGL context létrehozása] Nem sikerült létrehozni az OpenGL context-et! Lehet, hogy az SDL_GL_SetAttribute(...) hívásoknál az egyik beállítás helytelen." << std::endl;

		return 1;
	}

	std::stringstream window_title;
	window_title << "Oktaederek - OpenGL " << glVersion[0] << "." << glVersion[1];
	SDL_SetWindowTitle(win, window_title.str().c_str());

	bool quit = false;

	SDL_Event ev;

	CMyApp app;

	if (!app.Init())
	{
		SDL_DestroyWindow(win);
		std::cerr << "[app.Init] Az alkalmazas inicializalasa kozben hiba tortent!" << std::endl;
		return 1;
	}

	while (!quit)
	{
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					quit = ev.key.keysym.sym == SDLK_ESCAPE;
					app.KeyboardDown(ev.key);
					break;
				case SDL_KEYUP:
					app.KeyboardUp(ev.key);
					break;
				case SDL_MOUSEBUTTONDOWN:
					app.MouseDown(ev.button);
					break;
				case SDL_MOUSEBUTTONUP:
					app.MouseUp(ev.button);
					break;
				case SDL_MOUSEWHEEL:
					app.MouseWheel(ev.wheel);
					break;
				case SDL_MOUSEMOTION:
					app.MouseMove(ev.motion);
					break;
				case SDL_WINDOWEVENT:
					if (ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
						app.Resize(ev.window.data1, ev.window.data2);
					break;
			}
		}

		app.Update();
		app.Render();

		SDL_GL_SwapWindow(win);
	}

	app.Clean();

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);

	return 0;
}