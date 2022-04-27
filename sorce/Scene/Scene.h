#pragma once
#include "../utils/SceneManager.h"

class Scene {
private:
	SceneManager& sceneManager;

public:
	Scene(SceneManager& sceneManager);

	virtual bool Init() = 0;

	virtual void Update(float dt) = 0;

	virtual void Render(sf::RenderWindow& window) = 0;

	virtual void Release() = 0;

	virtual ~Scene();
};