#pragma once
#include "Scene.h"
#include "../Player/Player.h"
#include "../Pickup/Pickup.h"
#include "../utils/SceneManager.h"
#include <SFML/Graphics.hpp>

class LevelUpScene : public Scene {
private:
	Sprite bg;
	Text textLevel;

	Player player;
	Pickup spickup;

	const Vector2i& resolution;
	RenderWindow& window;
	View& mainView;

public:
	LevelUpScene(SceneManager& sceneManager);

	virtual bool Init();

	virtual void Update(Time& dt);

	virtual void Render();

	virtual void Release();

	virtual ~LevelUpScene();
};

