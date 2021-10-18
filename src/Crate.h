#pragma once
#ifndef __THROWINGOBJECT__
#define __THROWINGOBJECT__

#include "Sprite.h"

class Crate final : public Sprite
{
public:
	Crate();
	~Crate();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
};

#endif /* defined */
