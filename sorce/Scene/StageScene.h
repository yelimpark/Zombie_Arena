#pragma once
#include "Scene.h"
#include "../Player/Player.h"
#include <list>
#include "../UI/HealthBar.h"
#include "../UI/UIManager.h"
#include "../Player/ReloadBar.h"

class Pickup;
class Zombie;
class Bullet;
class Blood;

class StageScene : public Scene {
private:
	Player player;

	HealthBar healthBar;

	UIManager ui;

	std::list<Pickup*> items;
	std::vector<Zombie*> zombies;
	std::vector<Bullet*> bullets;
	std::vector<Blood*> bloods;
	VertexArray tileMap;

	int zombieCount;
	
	const Vector2i& resolution;
	RenderWindow& window;
	View& mainView;
	View& uiView;

	IntRect arena;

	Time playTime;

	bool pause;

	void CreateZobies();
	void CreateBullets();
	void CreateBackground();

public:
	StageScene(SceneManager& sceneManager);

	virtual bool Init();

	virtual void Update(Time& dt);

	virtual void Render();

	virtual void Release();

	virtual ~StageScene();
};