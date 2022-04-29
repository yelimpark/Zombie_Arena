#include "HealthBar.h"
#include "../utils/utils.h"
#include "../utils/FontHolder.h"

HealthBar::HealthBar()
{
	utils::SetOrigin(rectShape, Pivots::LeftMiddle);

	gameoverText.setFont(FontHolder::getfont("fonts/zombiecontrol.ttf"));
	gameoverText.setFillColor(Color::White);
	gameoverText.setCharacterSize(50);
	gameoverText.setString("Press Enter To Continue");
	utils::SetOrigin(gameoverText, Pivots::Center);
}

void HealthBar::Init(int health, Vector2i res)
{
	rectShape.setPosition(res.x * 0.35f, res.y * 0.8f);
	rectShape.setFillColor(Color::Red);
	this->health = health;
	gameoverText.setPosition(res.x * 0.5f, res.y * 0.5f);
	setSize();
}

void HealthBar::Update(int health)
{
	this->health = health;
	setSize();
}

void HealthBar::Draw(RenderWindow& window)
{
	window.draw(rectShape);

	if (health <= 0) {
		window.draw(gameoverText);
	}
}

void HealthBar::setSize()
{
	float healthBarWidth = health * 3;
	float healthBarHeight = 30;

	Vector2f healthBarSize = Vector2f(healthBarWidth, healthBarHeight);
	rectShape.setSize(healthBarSize);
}
