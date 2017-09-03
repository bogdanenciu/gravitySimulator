#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::init()
{
    // config -> readobjects
	DrawAble dr("../Game/img/ball.jpg",100,0);
	DrawAble dr2("../Game/img/Bkground.jpg", 0, 0);
	DrawAble dr3("../Game/img/arrow.jpg", 50, 0);
	objects.push_back(dr);
	objects.push_back(dr3);
	objects.push_back(dr2);
}

void GameManager::draw()
{
	for (DrawAble d : objects)
	{
		d.draw();
	}
}

float GameManager::getWidth()
{
	//return configManager->getWidth();
	return 1200;
}
float GameManager::getHeight()
{
	//return configManager->getHeight();
	return 600;
}
std::string GameManager::getTitle()
{
	//return configManager->getTitle();
	return "Gravity Simulator";
}
