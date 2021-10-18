#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include "Scene.h"
#include "Label.h"
#include "ship.h"
#include "Button.h"
#include "Crate.h"

class StartScene final : public Scene
{
public:
	StartScene();
	~StartScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	
private:
	Label* m_pStudentNameLabel{};
	Label* m_pStudentNumberLabel;
	Label* m_pInstructionsLabel{};

	Crate* m_pCloo{};

	Button* m_pStartButton;
};

#endif /* defined (__START_SCENE__) */