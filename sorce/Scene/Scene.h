#pragma once
#include "../utils/SceneManager.h"

class Scene {
protected:
	SceneManager& sceneManager;

public:
	Scene(SceneManager& sceneManager);

	virtual bool Init() = 0;

	virtual void Update(Time& dt) = 0;

	virtual void Render() = 0;

	virtual void Release() = 0;

	virtual ~Scene();
};