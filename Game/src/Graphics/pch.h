#ifndef _PCH_H_
#define _PCH_H_
#include <windows.h> 
#include "SDL.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <SDL_opengl.h>

//Windows Title
#define WINDOW_TITLE "Game"

//Windows Size
#define WIDTH  755
#define HEIGHT 600
// Z Distance from observator
#define VIEW_Z -725.0f

// Image folder
#define IMG_FOLDER "../Game/img/"

//Font used in game
#define GAME_FONT "../Game/fonts/stocky.ttf"

//Grill size
#define GRILL_SIZE 8

// Game Time
#define GAME_TIME 60

// Delay
#define GAME_DELAY 500

// Item size
#define ITEM_SIZE 40
#endif