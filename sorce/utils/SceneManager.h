#pragma once
#include <SFML/Graphics.hpp>
#include "GameVal.h"

class Scene;

enum class SceneType {
	TITLE,
	LEVELUP,
	STAGE,
	GAMEOVER,
	COUNT
};

class SceneManager {
private:
	static SceneManager* MgrInstance;

	SceneType currScene;
	Scene* scenes[(int)SceneType::COUNT];

	GameVal gameVal;

public:
	SceneManager();

	void Init();

	void Release();

	void Update(Time& dt);

	void Render();

	void ChangeScene(SceneType newScene);

	~SceneManager();
};