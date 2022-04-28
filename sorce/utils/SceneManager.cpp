#include "SceneManager.h"
#include "../Scene/StageScene.h"
#include "../Scene/TitleScene.h"
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
	scenes[(int)SceneType::TITLE] = new TitleScene(*this);
	scenes[(int)SceneType::STAGE] = new StageScene(*this);

	scenes[(int)currScene]->Init();
}

void SceneManager::Release()
{
	// 씬  다 구현한 후엔 반복문으로 수정
	delete scenes[(int)SceneType::TITLE];
	delete scenes[(int)SceneType::STAGE];
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
