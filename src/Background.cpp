#include "Background.h"
#include "TextureManager.h"



Background::Background()
{
	TextureManager::Instance().load("../Assets/textures/BG.jpg", "BG");

	//auto size = TextureManager::Instance().getTextureSize("BG");
	//setWidth(800);
	//setHeight(600);

}

Background::~Background()
= default;

void Background::draw()
{
	TextureManager::Instance().draw("BG", 400, 310, 0, 255, true);
}

void Background::update()
{
}

void Background::clean()
{
}
