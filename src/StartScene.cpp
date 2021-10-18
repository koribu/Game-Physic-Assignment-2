#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{

	TextureManager::Instance().load("../Assets/textures/crate.png", "crate");

	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pStudentNameLabel = new Label("Sinan Kolip", "Consolas", 80, blue, glm::vec2(400.0f, 40.0f));
	m_pStudentNameLabel->setParent(this);
	addChild(m_pStudentNameLabel);


	m_pStudentNumberLabel = new Label("101312965", "Consolas", 50, blue, glm::vec2(400.0f, 85.0f));
	m_pStudentNumberLabel->setParent(this);
	addChild(m_pStudentNumberLabel);

	m_pCloo = new Crate;
	m_pCloo->getTransform()->position = glm::vec2(400.0f, 300.0f); 
	addChild(m_pCloo); 

	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->getTransform()->position = glm::vec2(400.0f, 400.0f); 

	m_pStartButton->addEventListener(CLICK, [&]()-> void
	{
		m_pStartButton->setActive(false);
		TheGame::Instance().changeSceneState(PLAY_SCENE);
	});
	
	m_pStartButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pStartButton->setAlpha(128);
	});

	m_pStartButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pStartButton->setAlpha(255);
	});
	addChild(m_pStartButton);

	ImGuiWindowFrame::Instance().setDefaultGUIFunction();
}

