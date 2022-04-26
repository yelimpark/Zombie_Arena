#include "Player.h"
#include "../utils/utils.h"
#include "../utils/InputManager.h"

Player::Player()
	:speed(START_SPEED), accel(0), health(START_HEALTH), maxHealth(START_HEALTH),
	arena(), resolution(), tileSize(0.f), immuneMs(START_IMMUNE_MS)
{
	texture.loadFromFile("graphics/player.png");
	sprite.setTexture(texture);
	
	utils::SetOrigin(sprite, Pivots::Center);
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

	if (length != 0) {
		direction /= length;
	}

	if (accel == 0) {
		accelDir.x = direction.x;
		accelDir.y = direction.y;
	}

	if (direction.x != accelDir.x || direction.y != accelDir.y) {
		accel -= dt*400;
		if (accel < 0) {
			accel = 0;
		}
	}
	else {
		accel += dt*400;
		if (accel > MAX_ACCEL) {
			accel = MAX_ACCEL;
		}
	}

	// 이동
	position += direction * speed * dt + accelDir * accel * dt;

	sprite.setPosition(position);

	// 회전
	Vector2i mousePos = InputManager::GetMousePosition();
	Vector2i mouseDir;
	mouseDir.x = mousePos.x - position.x;
	mouseDir.y = mousePos.y - position.y;

	float radian = atan2(mouseDir.y, mouseDir.x);
	float dgree = radian * 180.f / 3.141592f;

	sprite.setRotation(dgree);
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
