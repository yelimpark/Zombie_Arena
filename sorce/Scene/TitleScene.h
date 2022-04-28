#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>

class TitleScene : public Scene {
private:
	Sprite bg;
	Text text;

	const Vector2i& resolution;
	RenderWindow& window;

public:
	TitleScene(SceneManager& sceneManager);

	virtual bool Init();

	virtual void Update(Time& dt);

	virtual void Render();

	virtual void Release();

	virtual ~TitleScene();
};