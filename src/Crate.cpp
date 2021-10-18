#include "Crate.h"
#include "TextureManager.h"

Crate::Crate()
{


	auto size = TextureManager::Instance().getTextureSize("crate");
	setWidth(size.x);
	setHeight(size.y);

}

Crate::~Crate()
= default;

void Crate::draw()
{
	TextureManager::Instance().draw("crate", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void Crate::update()
{
}

void Crate::clean()
{
}
