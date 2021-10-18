#pragma once
#ifndef __STORMTROOPER__
#define __STORMTROOPER__

#include "Sprite.h"
class StormTrooper final : public Sprite
{
public:

	StormTrooper();
	~StormTrooper();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
};

#endif

