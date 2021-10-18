#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"


PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 0, 0, 255);

	SDL_RenderDrawLine(Renderer::Instance().getRenderer(), startingX, startingY - slideHeight, startingX + slideWidth, startingY);
	SDL_RenderDrawLine(Renderer::Instance().getRenderer(), startingX, startingY, startingX, startingY - slideHeight);
	SDL_RenderDrawLine(Renderer::Instance().getRenderer(), 0, startingY, 1000, startingY);
	//if (!isLaunched)
	//{

	//	SDL_RenderDrawLine(Renderer::Instance().getRenderer(), startingX, startingY, startingX + VelocityPreviewLenght * cos(Util::Deg2Rad * launchElevationAngle),
	//		startingY - VelocityPreviewLenght * sin(Util::Deg2Rad * launchElevationAngle));
	//}
	//else
	//{
	//
	//	SDL_RenderDrawLine(Renderer::Instance().getRenderer(), m_pCrate->getTransform()->position.x, m_pCrate->getTransform()->position.y,
	//		m_pCrate->getTransform()->position.x  + m_pCrate->getRigidBody()->velocity.x,
	//		m_pCrate->getTransform()->position.y + m_pCrate->getRigidBody()->velocity.y);
	//}


	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
	spaceCoolDownCounter++;

	float dt = Game::Instance().getDeltaTime();

	if (isLaunched)
	{
			
			m_pCrate->getRigidBody()->acceleration = glm::vec2(force.x + friction.x, force.y + friction.y);
			m_pCrate->getRigidBody()->velocity = glm::vec2(m_pCrate->getRigidBody()->velocity.x + m_pCrate->getRigidBody()->acceleration.x * dt, m_pCrate->getRigidBody()->velocity.y + m_pCrate->getRigidBody()->acceleration.y * dt);
		
			if (m_pCrate->getTransform()->position.y >= startingY)
			{
				m_pCrate->getRigidBody()->velocity = glm::vec2(Util::magnitude(m_pCrate->getRigidBody()->velocity), 0);
				force = glm::vec2(0.0f, 0.0f);
				friction = glm::vec2(-mass * gravity * frictionConef, 0);
			}
			if (Util::magnitude(m_pCrate->getRigidBody()->velocity) < Util::magnitude(friction))
			{
				m_pCrate->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
			}
				m_pCrate->getTransform()->position += m_pCrate->getRigidBody()->velocity * dt;
	}
	else
	{
		m_pCrate->getTransform()->position.x = startingX;
		m_pCrate->getTransform()->position.y = startingY - slideHeight;
	}	

}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();


	if (SDL_NumJoysticks() < 1)
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE))
		{		
			if (isLaunched	&& spaceCoolDownCounter >50)
			{
				spaceCoolDownCounter = 0;
				isLaunched = false;

				m_pCrate->getRigidBody()->velocity = glm::vec2(0, 0);
				m_pCrate->getRigidBody()->acceleration = glm::vec2(0, 0);
				m_pCrate->getTransform()->position = glm::vec2(100,300);
				friction = glm::vec2(0, 0);
				
			}
			else if (!isLaunched && spaceCoolDownCounter > 50)
			{
				spaceCoolDownCounter = 0;
				isLaunched = true;

				float angleCos = (slideHeight / sqrt(pow(slideHeight, 2.0f) + pow(slideWidth, 2.0f)));
				float angleSin = (slideWidth / sqrt(pow(slideHeight, 2.0f) + pow(slideWidth, 2.0f)));
				float forceAmount = mass * gravity * angleCos;

				force = glm::vec2(forceAmount * angleSin, forceAmount * angleCos);
		
			}

			

		}
		else if(EventManager::Instance().isKeyDown(SDL_SCANCODE_SPACE) && isLaunched)
			TheGame::Instance().changeSceneState(START_SCENE);
	
	}
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance().changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance().changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

		TextureManager::Instance().load("../Assets/textures/crate.png", "crate");
	
	m_pBG = new Background();
	addChild(m_pBG);


	m_pCrate = new Crate();
	addChild(m_pCrate);
	
	startingX = 100;
	startingY = 500;
	isLaunched = false;
	gravity = 10;


	mass = 12.8;
	slideHeight = 30;
	slideWidth = 40;
	glm::vec2 friction = glm::vec2(-1.0f, 0.0f);
	frictionConef = .42f;



	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 50);

	addChild(m_pInstructionsLabel);

	m_pInstructionsLabel2 = new Label("Press the Space Key to throw detonator and press again to reset", "Consolas");
	m_pInstructionsLabel2->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 70);

	addChild(m_pInstructionsLabel2);

	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function() /*const*/
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Controls", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::SliderFloat("Starting X Coordinate", &startingX, 0.0f, 800.0f, "%.3f");
	ImGui::SliderFloat("Starting Y Coordinate", &startingY, 0.0f, 600.0f, "%.3f");
	ImGui::SliderFloat("Gravity", &gravity, -400.0f, 400.0f, "%.3f");
	ImGui::SliderFloat("Coefficient of kinetic friction", &frictionConef, 0.0f, 3.0f, "%.03f");
	ImGui::SliderFloat("Slide Height", &slideHeight, 0.0f, 800.0f, "%.3f");
	ImGui::SliderFloat("Slide Width", &slideWidth, 0.0f, 800.0f, "%.3f");

	ImGui::End();
}
