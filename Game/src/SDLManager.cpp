#include "SDLManager.h"


// Z Distance from observator
#define VIEW_Z -725.0f



SDLManager::SDLManager()
	: gameManager(std::move(new GameManager()))
{
	
}
SDLManager::~SDLManager()
{

}

void SDLManager::init()
{
	// Initialize
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	// Enable double-buffering
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	// Create a OpenGL window
	window = SDL_CreateWindow(WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		gameManager->getWidth(), gameManager->getHeight(),
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	// Create OpenGL Context
	mainGLContext = SDL_GL_CreateContext(window);

	// error 
	if (!window)
	{
		printf("Couldn't set %dx%d GL video mode: %s\n", gameManager->getWidth(), gameManager->getHeight(), SDL_GetError());
		SDL_Quit();
		exit(2);
	}

	// Initialize SDL_ttf library
	if (TTF_Init() != 0)
	{

		SDL_Quit();
		exit(1);
	}

	// Initialize the OpenGL context
	// Set up the OpenGL state
	glClearColor(255.0, 255.0, 255.0, 0.0);
	// Respond to a window resize event

	glViewport(0, 0, gameManager->getWidth(), gameManager->getHeight());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Calculate the aspect ratio of the screen, and set up the
	// projection matrix (i.e., update the camera)
	gluPerspective(30.f, (GLdouble)gameManager->getWidth()/ gameManager->getHeight(), 0.1f, 3000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, 0);


	gameManager->init();

}
void SDLManager::preDraw()
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Translate everything to VIEW_Z
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, VIEW_Z);
}
void SDLManager::postDraw()
{
	glFlush();
	// Swap the buffers (if double-buffered) to show the rendered image
	SDL_GL_SwapWindow(window);
}
void SDLManager::run()
{
	init();
	// The main loop
	while (true)
	{
		SDL_Event event;

		// Respond to any events that occur
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
				
				break;

			case SDL_QUIT:
				//
				break;
			}
		}

		// Check for escape
		keys = SDL_GetKeyboardState(NULL);
		if (keys[SDLK_ESCAPE]) {
			// keys manager
			
		}

		preDraw();
		gameManager->draw();
		postDraw();
	}
	release();
}
void SDLManager::release()
{
	//TODO release memory
}