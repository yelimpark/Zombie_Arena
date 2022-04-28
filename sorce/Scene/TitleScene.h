#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>

class TitleScene : public Scene {
private:
	Sprite bg;

	Font font;

	Text text;

	RenderWindow& window;

public:
	TitleScene(SceneManager& sceneManager);

	virtual bool Init();

	virtual void Update(Time& dt);

	virtual void Render();

	virtual void Release();

	virtual ~TitleScene();
};