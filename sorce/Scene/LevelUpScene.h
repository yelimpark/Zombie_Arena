#pragma once
#include "Scene.h"
#include "../Player/Player.h"
#include "../Pickup/Pickup.h"
#include "../utils/SceneManager.h"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

#define MAX_NUMBER_OF_ITEMS 6

class LevelUpScene : public Scene {
private:
	Sprite bg;
	
	Text menu[MAX_NUMBER_OF_ITEMS];

	int selectIndex;

	Player player;
	Pickup pickup;

	const Vector2i& resolution;
	RenderWindow& window;
	View& mainView;

public:
	LevelUpScene(SceneManager& sceneManager);

	virtual bool Init();

	virtual void Update(Time& dt);

	virtual void Render();

	virtual void MoveUp();

	virtual void MoveDown();

	virtual int GetPressedMenu();

	virtual void Release();

	virtual ~LevelUpScene();
};

