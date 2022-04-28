#include "Zombie.h"
#include "../utils/TextureHolder.h"
#include "../utils/utils.h"
#include "../Player/Player.h"
#include <iostream>

std::vector<ZombieInfo> Zombie::zombieInfo;
bool Zombie::isInitzombieInfo = false;

Zombie::Zombie()
	:status(zombieStatus::INACTIVE), timeAfterDeath(SHOW_DEAD_ZOMBIE)
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
	health--;
	if (health <= 0)
	{
		sprite.setTexture(TextureHolder::getTexture("graphics/blood.png"));
		status = zombieStatus::DEAD;
		return true;
	}
	return false;
}

bool Zombie::IsAlive()
{
	return zombieStatus::ALIVE == status;
}

void Zombie::Spawn(float x, float y, ZombieTypes type)
{
	status = zombieStatus::ALIVE;
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
	switch (status)
	{
	case zombieStatus::DEAD:
		timeAfterDeath -= dt;
		if (timeAfterDeath < 0) {
			status = zombieStatus::INACTIVE;
		}
		return;
	case zombieStatus::INACTIVE:
		return;
	default:
		break;
	}

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

	sprite.setPosition(position);

	float radian = atan2(direction.y, direction.x);
	float dgree = radian * 180.f / 3.141592f;
	sprite.setRotation(dgree);
}

bool Zombie::UpdateCollision(Player& player, Time time)
{
	if (status == zombieStatus::ALIVE && sprite.getGlobalBounds().intersects(player.GetGlobalBound())) {
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

void Zombie::Draw(RenderWindow& window, IntRect& arena)
{
	FloatRect fArena;
	switch (status)
	{
	case zombieStatus::ALIVE:
	case zombieStatus::DEAD:
		fArena.width = arena.width;
		fArena.height = arena.height;
		if (sprite.getGlobalBounds().intersects(fArena))
			window.draw(sprite);
		break;
	default:
		break;
	}
}