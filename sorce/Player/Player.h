#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	const float START_SPEED = 1000;
	const float START_HEALTH = 100;
	const float START_IMMUNE_MS = 200;
	const float MAX_ACCEL = 2000;

	Vector2f position;

	Sprite sprite;
	std::string textureFilename;

	Vector2i resolution;
	IntRect arena;

	int tileSize;

	Vector2f direction;
	float speed;

	Vector2f accelDir;
	float accel;

	int health;
	int maxHealth;
	float immuneMs;

	Time lastHit;

public:
	Player();

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

	void UpgradeSpeed();

	void GetHealthItem(int amount);

	void UpgradeMaxHealth(int amount);

};

