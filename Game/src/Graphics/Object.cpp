#include "pch.h"
#include "Position.h"
#include "Object.h"
#include <string>
#include "Ai.h"

//Constructors
Object::Object()
{
}
// Load object by image
Object::Object(char *name)
{
	File = name;
	Rotation = 0;

	// Have OpenGL generate a texture object handle for us
	glGenTextures( 1, &texture );
	glGenTextures( 1, &textureOnPress );

	// set everything to false
	isSelected = false;
	isPress = false;
	isPlay = false;
	isQuit = false;
	isItem = false;
	isText = false;
	isScore = false;
	isBack = false;
	isInvisible = false;
}

//Load texture by name
void Object::Load(char *name)
{

	File = name;

	// Load normal image
	image.Load_Image(name);
	char *name2 = (char*)malloc(strlen(name)+strlen("OnPress.jpg"));
	strcpy(name2,name);
	strcat(name2,"OnPress.jpg");

	// Load image when object is press ( name"OnPress.jpg")
	imageOnPress.Load_Image(name2);
}

// Load Object 
void Object::Load()
{
	//if is text load font
	if(isText)
	{
		font = TTF_OpenFont(GAME_FONT, 36);
		return;
	}
	//else load normal
	image.Load_Image(File);
	char *name2 = (char*)malloc(strlen(File)+strlen("OnPress.jpg"));
	strcpy(name2,File);
	strcat(name2,"OnPress.jpg");
	imageOnPress.Load_Image(name2);
}
// Set Position
void Object::SetPosition(Position p) 
{ 
	position = p;
}
//Set text
void Object::SetText(char * txt) 
{ 
	text = txt;
}
// Set Rotation
void Object::SetRotation(float R) 
{ 
	Rotation = R;
}

//Draw Object
void Object::Draw() 
{ 
	//if invisible don;t draw
	if(isInvisible)
		return;

	// Bind the texture object
	if(isPress)
		glBindTexture( GL_TEXTURE_2D, textureOnPress );
	else
		glBindTexture( GL_TEXTURE_2D, texture );

	// Set the texture's stretching properties
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// Image 
	Image Img;
	// if is press load correct texture
	if(isPress)
		Img = imageOnPress;
	else
		Img = image;

	// if is text load text surface 
	if(isText)
	{
		SDL_Color text_color = {255, 0, 0};
		SDL_Color text_color1 = {255, 255, 255};
		surface = TTF_RenderText(font,text,text_color,text_color1);
	}
	else 
		// else load image
	{  
		surface = Img.GetTexture();
	}

	// get the number of channels in the SDL surface
	nOfColors = surface->format->BytesPerPixel;
	if (nOfColors == 4) 
	{   // alpha
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGR_EXT;

	} 
	else if(nOfColors == 3)
	{             // no alpha
		if (surface->format->Rmask == 0x000000ff)
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
	glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
		texture_format, GL_UNSIGNED_BYTE, surface->pixels );

	glEnable(GL_TEXTURE_2D);
	// rotate the object
	glRotatef(Rotation, 1.0, 0.0, 0.0);

	//draw  Quad 
	glBegin(GL_QUADS); 
	glTexCoord2f(0, 0); 
	glVertex2f(position.x, position.y); 
	glTexCoord2f(1, 0); 
	glVertex2f(position.x + surface->w, position.y); 
	glTexCoord2f(1, 1); 
	glVertex2f(position.x + surface->w, position.y + surface->h); 
	glTexCoord2f(0, 1); 
	glVertex2f(position.x, position.y + surface->h); 
	glEnd(); 

	glRotatef(-Rotation, 1.0, 0.0, 0.0);
	glDisable(GL_TEXTURE_2D);

} 

// Convert 3D position to 2D screen position
Position ToScreen(Position p)
{
	// Get Model , View , Projection
	GLdouble model_view[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, model_view);

	GLdouble projection[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	GLdouble pos3D_x, pos3D_y, pos3D_z;
	// Get postion 
	gluProject(p.x,p.y, 0, model_view, projection, viewport, &pos3D_x, &pos3D_y, &pos3D_z);

	return Position(pos3D_x,pos3D_y);
} 
// On mouse event
void Object::OnMouseEvent(SDL_Event event)
{

	// is object selectable ?
	if(Selectable){

		// Get screen coordonates
		float x = event.button.x;

		float y = isItem ?event.button.y : HEIGHT -event.button.y;

		// Get 2D Points for texture corners
		Position P1 = ToScreen(position);
		Position P2 = ToScreen(Position(position.x + image.GetWidth(), position.y));
		Position P3 = ToScreen(Position(position.x + image.GetWidth(), position.y + image.GetHeight()));
		Position P4 = ToScreen(Position(position.x, position.y + image.GetHeight()));

		// if not press and event of mouse down
		if(!isPress && event.type == SDL_MOUSEBUTTONDOWN)
			// if (x,y) is in object area
				if(( P1.x < x && x  < P2.x )  && ( P3.y < y && y < P2.y ) )
					isPress = true;

		// if object press and event of mouse release
		if(isPress && event.type == SDL_MOUSEBUTTONUP)
			// if (x,y) is in object area
				if(( P1.x < x && x  < P2.x )  && ( P3.y < y && y < P2.y ) )
				{
					//if not item remove on press effect
					if(!isItem )
					{
						isPress = false;

					}
					//if item & can be selected
					else if( AI::CanSelect())
					{
						//set it selected
						AI::Select(indxi,indxj);
						isPress = false;
						isSelected = true;
					}
					// set it unpress
					else
					{
						isPress = false;
					}
					//Object is selected now
					isSelected = true;
				}
				else 
				{
					//if item & can be selected
					if(!isItem )
					{
						isPress = false;

					}
					//if item & can be selected
					else if( AI::CanSelect())
					{
						AI::Select(indxi,indxj);
						isPress = false;
						isSelected = true;
					}
					// set it unpress
					else
					{
						isPress = false;
					}
				}
	}
}

