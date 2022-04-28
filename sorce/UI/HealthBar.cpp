#include "HealthBar.h"

HealthBar::HealthBar()
{
}

void HealthBar::Init(Vector2i position, int health)
{
	float healthBarWidth = health*5;
	float healthBarHeight = 30;

	Vector2f healthBarSize = Vector2f(healthBarWidth, healthBarHeight);
	rectShape.setSize(healthBarSize);

	Vector2f healthBarPos = Vector2f(position.x * 0.5f - healthBarWidth * 0.5f, position.y * 0.8f);
	rectShape.setPosition(healthBarPos);
	rectShape.setFillColor(Color::Red);

}

void HealthBar::Draw(RenderWindow& window)
{
	window.draw(rectShape);
}
