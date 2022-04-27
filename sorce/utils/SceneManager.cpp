#include "SceneManager.h"

SceneManager::SceneManager()
	:currScene((SceneType)0)
{

}

void SceneManager::Init()
{
	// scenes[(int)SceneType::TITLE] = new ...
}

void SceneManager::Release()
{
}

void SceneManager::Update(float dt)
{
	scenes[(int)currScene]->Update(dt);
}

void SceneManager::Render(sf::RenderWindow& window)
{
	scenes[(int)currScene]->Render(window);
}

void SceneManager::ChangeScene(SceneType newScene)
{
	scenes[(int)currScene]->Release();
	currScene = newScene;
	scenes[(int)currScene]->Init();
}

SceneManager::~SceneManager()
{
	Release();
}
