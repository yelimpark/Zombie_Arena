#include "Bullet.h"
#include "../utils/InputManager.h"
#include "../utils/utils.h"
#include "../Zombie/Zombie.h"
#include "../Zombie/Blood.h"

using namespace sf;

Bullet::Bullet()
	:tileSize(0.f), isAvtive(false), distance(0)
{
	//position.x = -100;
	//position.y = -100;

	shape.setSize(Vector2f(20, 5));
	shape.setPosition(position);
	shape.setFillColor(Color::Red);

	utils::SetOrigin(shape, Pivots::Center);
}

void Bullet::Spawn(Vector2f playerPos, Vector2f dir, Vector2i res, int tileSize)
{
	isAvtive = true;
	position = playerPos;
	shape.setPosition(position);
	direction = utils::NomalizeVector(dir);
	float dgree = utils::GetAngle(position, position + direction);
	shape.setRotation(dgree);
}

FloatRect Bullet::GetGlobalBound() const
{
	return shape.getGlobalBounds();
}

bool Bullet::UpdateCollision(const std::vector<Zombie*>& zombies, std::vector<Blood*>& bloods)
{
	FloatRect bounds = shape.getGlobalBounds();

	for (auto zombie : zombies) {
		if (zombie->IsAlive() && bounds.intersects(zombie->GetGlobalBound())) {
			stop();
			Blood* blood = new Blood();
			blood->Spawn(zombie->GetPosition());
			if (zombie->OnHitted()) {
				bloods.push_back(blood);
				return true;
			}
			break;
		}
	}
	return false;
}

void Bullet::stop()
{
	isAvtive = false;
}

bool Bullet::IsActive()
{
	return isAvtive;
}

const RectangleShape& Bullet::GetShape() const
{
	return shape;
}

void Bullet::Update(float dt)
{
	position += direction * speed * dt;
	shape.setPosition(position);

	distance += speed * dt;

	if (distance > DEFAULT_DISTANCE) {
		stop();
	}
}

Bullet::~Bullet()
{
}
