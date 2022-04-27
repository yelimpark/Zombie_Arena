#pragma once
#include "Scene.h"

class TitleScene : public Scene {
private:

public:
	TitleScene(SceneManager& sceneManager);

	virtual bool Init();

	virtual void Update(float dt);

	virtual void Render(sf::RenderWindow& window);

	virtual void Release();

	virtual ~TitleScene();
};