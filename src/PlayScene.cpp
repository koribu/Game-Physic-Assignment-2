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

	float VelocityPreviewLenght = launchSpeed;

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 0, 0, 255);

	SDL_RenderDrawLine(Renderer::Instance().getRenderer(), startingX, startingY - slideHeight, startingX + slideWidth, startingY);
	SDL_RenderDrawLine(Renderer::Instance().getRenderer(), startingX, startingY, startingX, startingY - slideHeight);
	SDL_RenderDrawLine(Renderer::Instance().getRenderer(), 0, startingY, 1000, startingY);
	if (!isLaunched)
	{

		SDL_RenderDrawLine(Renderer::Instance().getRenderer(), startingX, startingY, startingX + VelocityPreviewLenght * cos(Util::Deg2Rad * launchElevationAngle),
			startingY - VelocityPreviewLenght * sin(Util::Deg2Rad * launchElevationAngle));
	}
	else
	{
	
		SDL_RenderDrawLine(Renderer::Instance().getRenderer(), m_pCrate->getTransform()->position.x, m_pCrate->getTransform()->position.y,
			m_pCrate->getTransform()->position.x  + m_pCrate->getRigidBody()->velocity.x,
			m_pCrate->getTransform()->position.y + m_pCrate->getRigidBody()->velocity.y);
	}


	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
	spaceCoolDownCounter++;

	float dt = Game::Instance().getDeltaTime();



	if (isLaunched)
	{
		m_pCrate->getRigidBody()->velocity.y += accelerationGravity * dt;
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
				m_pCrate->getTransform()->position = glm::vec2(100,300);
				
			}
			else if (!isLaunched && spaceCoolDownCounter > 50)
			{
				spaceCoolDownCounter = 0;
				isLaunched = true;

				m_pCrate->getRigidBody()->velocity = glm::vec2(launchSpeed * cos(Util::Deg2Rad * launchElevationAngle),
					-launchSpeed * sin(Util::Deg2Rad * launchElevationAngle));
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

	m_pStormtrooper = new StormTrooper();
	addChild(m_pStormtrooper);

	m_pCrate = new Crate();
	addChild(m_pCrate);
	
	startingX = 100;
	startingY = 500;
	isLaunched = false;
	launchSpeed = 95;
	launchElevationAngle = 16.25;
	accelerationGravity = 10;



	slideHeight = 300;
	slideWidth = 400;



	//// Back Button
	//m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	//m_pBackButton->getTransform()->position = glm::vec2(300.0f, 400.0f);
	//m_pBackButton->addEventListener(CLICK, [&]()-> void
	//{
	//	m_pBackButton->setActive(false);
	//	TheGame::Instance().changeSceneState(START_SCENE);
	//});

	//m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	//{
	//	m_pBackButton->setAlpha(128);
	//});

	//m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	//{
	//	m_pBackButton->setAlpha(255);
	//});
	//addChild(m_pBackButton);

	//// Next Button
	//m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	//m_pNextButton->getTransform()->position = glm::vec2(500.0f, 400.0f);
	//m_pNextButton->addEventListener(CLICK, [&]()-> void
	//{
	//	m_pNextButton->setActive(false);
	//	TheGame::Instance().changeSceneState(END_SCENE);
	//});

	//m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	//{
	//	m_pNextButton->setAlpha(128);
	//});

	//m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	//{
	//	m_pNextButton->setAlpha(255);
	//});

	//addChild(m_pNextButton);

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
	ImGui::SliderFloat("Launch Elevation Angle", &launchElevationAngle, 0.0f, 360.0f, "%.3f");
	ImGui::SliderFloat("Launch Speed", &launchSpeed, -400.0f, 400.0f, "%.3f");
	ImGui::SliderFloat("Acceleration Gravity", &accelerationGravity, -400.0f, 400.0f, "%.3f");

	ImGui::SliderFloat("Slide Height", &slideHeight, 0.0f, 800.0f, "%.3f");
	ImGui::SliderFloat("Slide Width", &slideWidth, 0.0f, 800.0f, "%.3f");

	ImGui::End();
}
