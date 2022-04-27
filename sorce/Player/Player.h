#pragma once
#include <SFML/Graphics.hpp>
#include "../Bullet/Bullet.h"
#include <list>

using namespace sf;

class Player
{
private:
	const float START_SPEED = 1000;
	const float START_HEALTH = 100;
	const float START_IMMUNE_MS = 200;

	Vector2f position;

	Sprite sprite;
	std::string textureFilename;

	Vector2i resolution;
	IntRect arena;

	int tileSize;

	Vector2f direction;
	float speed;

	int health;
	int maxHealth;
	float immuneMs;

	Time lastHit;

	const int BULLET_CACHE_SIZE = 1000;
	std::list<Bullet*> unuseBullets;
	std::list<Bullet*> useBullets;
	float distanceToMuzzle;

public:
	Player();
	~Player();

	void Shoot(Vector2f dir);

	void Spawn(IntRect arena, Vector2i res, int tileSize);

	bool OnHitted(Time timeHit);

	Time GetLastTime() const;

	FloatRect GetGlobalBound() const;

	Vector2f GetPosition() const;

	float GetRotaion() const;

	Sprite GetSprite() const;

	int GetHealth() const;

	void SetDirection(Vector2f dir);

	void Update(float dt);

	void Draw(RenderWindow& window);

	void UpgradeSpeed();

	void GetHealthItem(int amount);

	void UpgradeMaxHealth(int amount);

};

