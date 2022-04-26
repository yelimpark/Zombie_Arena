#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet {
private:
	const float fireLate = 10;
	const float speed = 1000;

	Time fireTime;

	Vector2f position;
	RectangleShape shape;

	Vector2i resolution;
	int tileSize;

	Vector2f direction;

	bool isAvtive;

public:
	Bullet();

	void Spawn(Vector2f playerPos, Vector2i res, int tileSize);

	FloatRect GetGlobalBound() const;

//	Vector2f GetPosition() const;

//	void SetDirection(Vector2f dir);

	const RectangleShape& GetShape() const;

	void Update(float dt);

	~Bullet();
};