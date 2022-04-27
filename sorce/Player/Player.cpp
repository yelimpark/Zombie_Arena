#include "Player.h"
#include "../utils/utils.h"
#include "../utils/InputManager.h"
#include "../utils/TextureHolder.h"
#include <iostream>
#include <algorithm>

using namespace sf;

Player::Player()
	:speed(START_SPEED), health(START_HEALTH), maxHealth(START_HEALTH),
	arena(), resolution(), tileSize(0.f), immuneMs(START_IMMUNE_MS), textureFilename("graphics/player.png"), distanceToMuzzle(45.0f)
{
	sprite.setTexture(TextureHolder::getTexture(textureFilename));
	
	utils::SetOrigin(sprite, Pivots::Center);

	for (int i = 0; i < BULLET_CACHE_SIZE; ++i) {
		unuseBullets.push_back(new Bullet());
	}
}

Player::~Player()
{
	for (auto bullet : unuseBullets) {
		delete bullet;
	}
	unuseBullets.clear();
	for (auto bullet : useBullets) {
		delete bullet;
	}
	useBullets.clear();

}

void Player::Shoot(Vector2f dir)
{
	dir  = utils::NomalizeVector(dir);
	Vector2f spawnPos = position + dir * distanceToMuzzle;

	if (unuseBullets.empty()) {
		for (int i = 0; i < BULLET_CACHE_SIZE; ++i) {
			unuseBullets.push_back(new Bullet());
		}
	}

	Bullet* bullet = unuseBullets.front();
	unuseBullets.pop_front();
	useBullets.push_back(bullet);
	bullet->Spawn(spawnPos, dir, resolution, tileSize);
}

void Player::Spawn(IntRect arena, Vector2i res, int tileSize)
{
	this->arena = arena;
	resolution = res;
	this->tileSize = tileSize;

	position.x = this->arena.width * 0.5f;
	position.y = this->arena.height * 0.5f;
}

bool Player::OnHitted(Time timeHit)
{
	if (lastHit.asMilliseconds() - timeHit.asMilliseconds() > immuneMs) {
		lastHit = timeHit;
		health -= 10;
		return true;
	}
	return false;
}

Time Player::GetLastTime() const
{
	return lastHit;
}

FloatRect Player::GetGlobalBound() const
{
	return sprite.getGlobalBounds();
}

Vector2f Player::GetPosition() const
{
	return position;
}

float Player::GetRotaion() const
{
	return sprite.getRotation();
}

Sprite Player::GetSprite() const
{
	return sprite;
}

int Player::GetHealth() const
{
	return health;
}

void Player::SetDirection(Vector2f dir)
{
	direction = dir;
}

void Player::Update(float dt)
{
	direction.x = InputManager::GetAxis(Axis::Horizonal);
	direction.y = InputManager::GetAxis(Axis::Vertical);

	float length = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (length > 1) {
		direction /= length;
	}

	// 이동
	position += direction * speed * dt;

	if (position.x > resolution.x - 100) {
		position.x = resolution.x - 100;
	}
	if (position.x < 50) {
		position.x = 50;
	}

	if (position.y > resolution.y - 100) {
		position.y = resolution.y - 100;
	}
	if (position.y < 50) {
		position.y = 50;
	}

	sprite.setPosition(position);

	// 회전
	Vector2i mousePos = InputManager::GetMousePosition();
	Vector2i mouseDir;
	mouseDir.x = mousePos.x - resolution.x * 0.5f;
	mouseDir.y = mousePos.y - resolution.y * 0.5f;

	float radian = atan2(mouseDir.y, mouseDir.x);
	float dgree = radian * 180.f / 3.141592f;

	sprite.setRotation(dgree);

	if (InputManager::GetMouseButton(Mouse::Button::Left)) {
		Shoot(Vector2f(mouseDir.x, mouseDir.y));
	}

	auto it = useBullets.begin();
	while (it != useBullets.end()) {
		Bullet* bullet = *it;
		bullet->Update(dt);

		if (!bullet->IsActive()) {
			it = useBullets.erase(it);
		}
		else {
			it++;
		}
	}
}

void Player::Draw(RenderWindow& window)
{
	window.draw(sprite);
	for (auto bullet : useBullets) {
		window.draw(bullet->GetShape());
	}
}

void Player::UpgradeSpeed()
{
	speed += START_SPEED * 0.2;
}

void Player::GetHealthItem(int amount)
{
	health += amount;
	if (health > maxHealth) {
		health = maxHealth;
	}
	if (health < 0) {
		health = 0;
	}
}

void Player::UpgradeMaxHealth(int amount)
{
	maxHealth += START_HEALTH * 0.2;
}
