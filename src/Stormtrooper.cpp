#include "StormTrooper.h"
#include "TextureManager.h"



StormTrooper::StormTrooper()
{
	TextureManager::Instance().load("../Assets/textures/trooper.png", "Stormtrooper");

	auto size = TextureManager::Instance().getTextureSize("Stormtrooper");
	setWidth(size.x);
	setHeight(size.y);

}

StormTrooper::~StormTrooper()
= default;

void StormTrooper::draw()
{
	TextureManager::Instance().draw("Stormtrooper", 585 , 500 , 0, 255, true);
}

void StormTrooper::update()
{
}

void StormTrooper::clean()
{
}
