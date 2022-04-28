#pragma once
#include "Scene.h"
#include "../Player/Player.h"
#include <list>
#include "../UI/HealthBar.h"

class Pickup;
class Zombie;
class Bullet;

class StageScene : public Scene {
private:
	Player player;

	HealthBar healthBar;

	std::list<Pickup*> items;
	std::vector<Zombie*> zombies;
	std::vector<Bullet*> bullets;
	VertexArray tileMap;

	int zombieCount;
	int score;
	
	const Vector2i& resolution;
	RenderWindow& window;
	View& mainView;

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