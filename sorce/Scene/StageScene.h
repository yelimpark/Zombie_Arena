#pragma once
#include "Scene.h"
#include <list>

class Pickup;
class Zombie;
class Bullet;

class StageScene : public Scene {
private:
	Player player;

	std::list<Pickup*> items;

	std::vector<Zombie*> zombies;

	std::vector<Bullet*> bullets;



public:
	StageScene(SceneManager& sceneManager);

	virtual bool Init();

	virtual void Update(float dt);

	virtual void Render(sf::RenderWindow& window);

	virtual void Release();

	virtual ~StageScene();
};