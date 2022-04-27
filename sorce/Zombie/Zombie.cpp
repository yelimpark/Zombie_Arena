#include "Zombie.h"
#include "../utils/TextureHolder.h"
#include "../utils/utils.h"
#include "../Player/Player.h"
#include <iostream>

std::vector<ZombieInfo> Zombie::zombieInfo;
bool Zombie::isInitzombieInfo = false;

Zombie::Zombie()
	:alive(false)
{
	if (!isInitzombieInfo) {
		zombieInfo.resize((int)ZombieTypes::COUNT);
		{
			auto& info = zombieInfo[(int)ZombieTypes::BLOATER];
			info.type = ZombieTypes::BLOATER;
			info.textureFilename = "graphics/bloater.png";
			info.speed = 40.f;
			info.health = 5;
		}
		{
			auto& info = zombieInfo[(int)ZombieTypes::CHASER];
			info.type = ZombieTypes::BLOATER;
			info.textureFilename = "graphics/chaser.png";
			info.speed = 70.f;
			info.health = 1;
		}
		{
			auto& info = zombieInfo[(int)ZombieTypes::CRAWLER];
			info.type = ZombieTypes::BLOATER;
			info.textureFilename = "graphics/crawler.png";
			info.speed = 20.f;
			info.health = 3;
		}

		isInitzombieInfo = true;
	}
}

bool Zombie::OnHitted()
{
	sprite.setTexture(TextureHolder::getTexture("graphics/blood.png"));
	alive = false;
	return false;
}

bool Zombie::IsAlive()
{
	return alive;
}

void Zombie::Spawn(float x, float y, ZombieTypes type)
{
	alive = true;
	auto& info = zombieInfo[(int)type];
	sprite.setTexture(TextureHolder::getTexture(info.textureFilename));
	speed = info.speed;
	health = info.health;

	position.x = x;
	position.y = y;

	utils::SetOrigin(sprite, Pivots::Center);
	sprite.setPosition(position);
}

void Zombie::Update(float dt, Vector2f playerPosition)
{
	if (!alive) return;

	Vector2f direction(playerPosition - position);

	float length = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (length > 0) {
		direction /= length;
	}

	if (length < speed * dt * 0.5f) {
		position = playerPosition;
	}
	else {
		position += direction * speed * dt;
	}

	if (position.x > 1920 - 100) {
		position.x = 1920 - 100;
	}
	if (position.x < 50) {
		position.x = 50;
	}

	if (position.y > 1080 - 100) {
		position.y = 1080 - 100;
	}
	if (position.y < 50) {
		position.y = 50;
	}

	sprite.setPosition(position);

	// ȸ��
	float radian = atan2(direction.y, direction.x);
	float dgree = radian * 180.f / 3.141592f;
	sprite.setRotation(dgree);
}

bool Zombie::UpdateCollision(Player& player, Time time)
{
	if (sprite.getGlobalBounds().intersects(player.GetGlobalBound())) {
		player.OnHitted(time);
		return true;
	}
	return false;
}

FloatRect Zombie::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

Sprite Zombie::Getsprite()
{
	return sprite;
}
