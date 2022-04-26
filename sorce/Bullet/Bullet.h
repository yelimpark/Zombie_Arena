#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet {
private:
	const float fireLate = 10;
	Time lastFire;

public:
	Bullet();

	void Spawn();

	FloatRect GetGlobalBound() const;

	Vector2f GetPosition() const;

	void SetDirection(Vector2f dir);

	void Update(float dt);

	~Bullet();
};