#include "HealthBar.h"

HealthBar::HealthBar()
{
}

void HealthBar::Init(Vector2f position)
{
	float healthBarWidth = 200;
	float healthBarHeight = 30;

	Vector2f healthBarSize = Vector2f(healthBarWidth, healthBarHeight);
	rectShape.setSize(healthBarSize);

	Vector2f healthBarPos = Vector2f(position.x * 0.5f - healthBarWidth * 0.5f, position.y * 0.8f);
	rectShape.setPosition(healthBarPos);
	rectShape.setFillColor(Color::Red);

}

void HealthBar::Update(int health)
{
	healthBarSize.x = health;
	rectShape.setSize(healthBarSize);

}

void HealthBar::Draw(RenderWindow& window)
{
	window.draw(rectShape);
}
