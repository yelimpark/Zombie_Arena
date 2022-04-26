#include "Bullet.h"
#include "../utils/InputManager.h"
#include "../utils/utils.h"

Bullet::Bullet()
	:tileSize(0.f), isAvtive(false)
{
	position.x = -100;
	position.y = -100;

	shape.setSize(Vector2f(10, 10));
	shape.setPosition(position);
	shape.setFillColor(Color::Red);

	utils::SetOrigin(shape, Pivots::Center);
}

void Bullet::Spawn(Vector2f playerPos, Vector2i res, int tileSize)
{
	resolution = res;
	this->tileSize = tileSize;

	position.x = playerPos.x;
	position.y = playerPos.y;
	isAvtive = true;

	Vector2i mousePos = InputManager::GetMousePosition();
	direction.x = mousePos.x - position.x;
	direction.y = mousePos.y - position.y;

	utils::NomalizeVector(direction);
}

FloatRect Bullet::GetGlobalBound() const
{
	return shape.getGlobalBounds();
}

const RectangleShape& Bullet::GetShape() const
{
	return shape;
}

void Bullet::Update(float dt)
{
	if (!isAvtive) return;

	position += direction * speed * dt;
	shape.setPosition(position);

	if (!utils::IsRectInArea(this->GetGlobalBound(),
		tileSize, tileSize, resolution.x - tileSize * 2, resolution.y - tileSize * 2))
	{
		isAvtive = false;
	}
}

Bullet::~Bullet()
{
}
