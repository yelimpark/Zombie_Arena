#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

// ref 일때 전방선언으로 해결
class Zombie;
class Blood;

class Bullet {
private:
	const float fireLate = 10;
	const float speed = 1000;
	const float DEFAULT_DISTANCE = 2500.f;

	Time fireTime;

	Vector2f position;
	RectangleShape shape;

	Vector2i resolution;
	int tileSize;

	Vector2f direction;

	bool isAvtive;
	float distance;

public:
	Bullet();

	void Spawn(Vector2f playerPos, Vector2f dir, Vector2i res, int tileSize);

	FloatRect GetGlobalBound() const;

	bool UpdateCollision(const std::vector<Zombie*>& zombies, std::vector<Blood*>& bloods);

	void stop();

	bool IsActive();

	const RectangleShape& GetShape() const;

	void Update(float dt);

	~Bullet();
};