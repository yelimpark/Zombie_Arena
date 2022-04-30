#include "Player.h"
#include "../utils/utils.h"
#include "../utils/InputManager.h"
#include "../utils/TextureHolder.h"
#include "../Pickup/Pickup.h"
#include <iostream>
#include <algorithm>

using namespace sf;

Player::Player()
	:speed(START_SPEED), health(START_HEALTH), maxHealth(START_HEALTH),
	arena(), resolution(), tileSize(0.f), immuneMs(START_IMMUNE_MS), textureFilename("graphics/player.png"),
	distanceToMuzzle(45.0f)
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

	health = START_HEALTH;
	speed = START_SPEED;
	maxHealth = START_HEALTH;
	immuneMs = START_IMMUNE_MS;
	rebar.Init();
}

bool Player::OnHitted(Time timeHit)
{
	if (timeHit.asMilliseconds() - lastHit.asMilliseconds() > immuneMs) {
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


	if (position.x > arena.left + arena.width - tileSize) {
		position.x = arena.left + arena.width - tileSize;
	}
	if (position.x < tileSize) {
		position.x = tileSize;
	}

	if (position.y > arena.top + arena.height - tileSize) {
		position.y = arena.top + arena.height - tileSize;
	}
	if (position.y < tileSize) {
		position.y = tileSize;
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
	rebar.Update(position, dt);

	if (InputManager::GetMouseButttonDown(Mouse::Button::Left) && rebar.Shoot()) {
		Shoot(Vector2f(mouseDir.x, mouseDir.y));
	}

	auto it = useBullets.begin();
	while (it != useBullets.end()) {
		Bullet* bullet = *it;
		bullet->Update(dt);

		if (!bullet->IsActive()) {
			it = useBullets.erase(it);
			unuseBullets.push_back(bullet);
		}
		else {
			++it;
		}
	}
}

void Player::Draw(RenderWindow& window)
{
	window.draw(sprite);
	for (auto bullet : useBullets) {
		window.draw(bullet->GetShape());
	}
	window.draw(rebar.GetShape());
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

bool Player::UpdateCollision(const std::vector<Zombie*>& zombies)
{
	bool isCollied = false;

	for (auto bullet : useBullets) {
		if (bullet->UpdateCollision(zombies)) {
			isCollied = true;
		}
	}
	return isCollied;
}

bool Player::UpdateCollision(const std::list<Pickup*>& items)
{
	FloatRect bounds = sprite.getGlobalBounds();
	bool isCollied = false;

	for (auto item : items) {
		if (bounds.intersects(item->GetBlobalBounds())) {
			item->GotIt();
			isCollied = true;

		}
	}
	return isCollied;
}

int Player::GetLeftBullets()
{
	return rebar.GetLeftBullet();
}