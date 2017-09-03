#pragma once
#include <vector>
#include <string>
#include "DrawAble.h"

class GameManager
{
private:
	std::vector<DrawAble> objects;
	
public:
	GameManager();
	virtual ~GameManager();

	void draw();
	void init();
	float getWidth();
	float getHeight();
	std::string getTitle();

};

