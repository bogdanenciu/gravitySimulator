#include "DrawAble.h"



DrawAble::DrawAble(std::string name, int x, int y)
{
	texture = IMG_Load(name.c_str());
	glGenTextures(1, &textureId);
	pos.x = x;
	pos.y = y;
	Rotation = 0.f;
}


DrawAble::~DrawAble()
{
}

void DrawAble::draw()
{
	glBindTexture(GL_TEXTURE_2D, textureId);

	// Set the texture's stretching properties
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// get the number of channels in the SDL surface
	nOfColors = texture->format->BytesPerPixel;
	if (nOfColors == 4)
	{   // alpha
		if (texture->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGR_EXT;

	}
	else if (nOfColors == 3)
	{             // no alpha
		if (texture->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR_EXT;
	}
	else
	{
		// 1 channel
		texture_format = GL_RED;
	}

	// Edit the texture object's image data using the information SDL_Surface 
	glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, texture->w, texture->h, 0,
		texture_format, GL_UNSIGNED_BYTE, texture->pixels);

	glEnable(GL_TEXTURE_2D);
	
	glRotatef(180.f, 0.0, 0.0, 1.0);

	//draw  Quad 
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(pos.x - texture->w/2, pos.y- texture->h / 2);
	glTexCoord2f(1, 0);
	glVertex2f(pos.x + texture->w/2, pos.y - texture->h / 2);
	glTexCoord2f(1, 1);
	glVertex2f(pos.x + texture->w/2, pos.y + texture->h/2);
	glTexCoord2f(0, 1);
	glVertex2f(pos.x - texture->w / 2, pos.y + texture->h/2);
	glEnd();
	glRotatef(-180.f, 0.0, 0.0, 1.0);
	glDisable(GL_TEXTURE_2D);

}