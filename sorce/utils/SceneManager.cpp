#include "SceneManager.h"
#include "../Scene/StageScene.h"
#include "../Scene/TitleScene.h"
#include "../Scene/LevelUpScene.h"
#include <assert.h>

SceneManager* SceneManager::MgrInstance;

SceneManager::SceneManager()
	:currScene((SceneType)0)
{
	assert(!MgrInstance);
	MgrInstance = this;
}

void SceneManager::Init()
{
	GameVal::Init();

	scenes[(int)SceneType::TITLE] = new TitleScene(*this);
	scenes[(int)SceneType::LEVELUP] = new LevelUpScene(*this);
	scenes[(int)SceneType::STAGE] = new StageScene(*this);

	scenes[(int)currScene]->Init();
}

void SceneManager::Release()
{
	for (int i = 0; i < (int)SceneType::COUNT; i++) {
		delete scenes[i];
	}
}

void SceneManager::Update(Time& dt)
{
	scenes[(int)currScene]->Update(dt);
}

void SceneManager::Render()
{
	scenes[(int)currScene]->Render();
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
	assert(MgrInstance);
	MgrInstance = 0;
}
