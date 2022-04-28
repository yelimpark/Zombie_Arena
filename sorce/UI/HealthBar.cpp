#include "HealthBar.h"
#include "../utils/utils.h"
#include "../utils/FontHolder.h"

HealthBar::HealthBar()
{
	utils::SetOrigin(rectShape, Pivots::LeftMiddle);

	gameoverText.setFont(FontHolder::getfont("fonts/zombiecontrol.ttf"));
	gameoverText.setFillColor(Color::White);
	gameoverText.setCharacterSize(50);
	gameoverText.setPosition(650, 550);
	gameoverText.setString("Press Enter To Continue");
}

void HealthBar::Init(Vector2i position, int health)
{
	this->health = health;
	float healthBarWidth = health * 3;
	float healthBarHeight = 30;

	Vector2f healthBarSize = Vector2f(healthBarWidth, healthBarHeight);
	rectShape.setSize(healthBarSize);
	//FloatRect textRect = rectShape.getLocalBounds();
	//rectShape.setOrigin(
	//	textRect.left, textRect.top + textRect.height * 0.5f);
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
