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
	gameoverText.setPosition(res.x * 0.5, res.y * 0.5);
	this->health = health;
}

void HealthBar::Update(Vector2i position, int health)
{
	this->health = health;
	float healthBarWidth = health * 3;
	float healthBarHeight = 30;

	Vector2f healthBarSize = Vector2f(healthBarWidth, healthBarHeight);
	rectShape.setSize(healthBarSize);
	rectShape.setPosition(position.x * 0.35f, position.y * 0.8f);
	rectShape.setFillColor(Color::Red);
}

void HealthBar::Draw(RenderWindow& window)
{
	window.draw(rectShape);

	if (health <= 0) {
		window.draw(gameoverText);
	}
}
