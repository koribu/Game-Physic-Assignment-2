#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"

#include "Crate.h"
#include "Stormtrooper.h"
#include "Button.h"
#include "Label.h"
#include "Background.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Crate* m_pCrate;
	StormTrooper* m_pStormtrooper;
	Background* m_pBG;

	bool isLaunched;
	float launchElevationAngle;
	float launchSpeed;
	float accelerationGravity;

	int spaceCoolDownCounter;

	float startingX;
	float startingY;


	float slideHeight;
	float slideWidth;




	//float v = 100;
	//float t = 0;
	//float a = 4;
	//float c = 200;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
	Label* m_pInstructionsLabel2;
};

#endif /* defined (__PLAY_SCENE__) */