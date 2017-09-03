#pragma once
#include <string>
#include "pch.h"
#include "Position.h"

class DrawAble
{
public:
	DrawAble(std::string name, int x, int y);
	virtual ~DrawAble();
	SDL_Surface *texture;
	GLuint textureId;
	Position pos;
	// Format of the textures
	GLenum texture_format;
	// Number of channels from textures
	GLint  nOfColors;
	// Rotation
	float Rotation;

	void draw();
};

