#include "Player.h"

Player::Player()
	:speed(START_SPEED), health(START_HEALTH), maxHealth(START_HEALTH)
{
	texture.loadFromFile("grapics/player.png");
	sprite.setTexture(texture);
}

void Player::Spawn(IntRect arena, Vector2f res, int tileSize)
{
}

bool Player::OnHitted(Time timeHit)
{
	return false;
}

Time Player::GetLastTime() const
{
	return Time();
}

FloatRect Player::GetGlobalBound() const
{
	return FloatRect();
}

Vector2f Player::GetPosition() const
{
	return Vector2f();
}

float Player::GetRotaion() const
{
	return 0.0f;
}

Sprite Player::GetSprite() const
{
	return Sprite();
}

int Player::GetHealth() const
{
	return 0;
}

void Player::SetDirection(Vector2f dir)
{
}

void Player::Update(float dt, Vector2i mousePos)
{
}

void Player::UpgradeSpeed()
{
}

void Player::GetHealthItem()
{
}

void Player::UpgradeMaxHealth(int amount)
{
}
