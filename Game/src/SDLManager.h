#pragma once
#include <windows.h>
#include <memory>
#include "SDL.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <SDL_opengl.h>


#include "GameManager.h"

/* This class is an abstractization for SDL primitives */

class SDLManager
{
private:
	// SDL stuff
	SDL_Window *window;
	SDL_GLContext mainGLContext;
	const Uint8 *keys;

	//Game stuff
	GameManager* gameManager;

	void init();
	void release();
	void preDraw();
	void postDraw();

public:
	SDLManager();
	virtual ~SDLManager();
	void run();

};
