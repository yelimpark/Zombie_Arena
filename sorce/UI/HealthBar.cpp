#include "HealthBar.h"
#include "../utils/utils.h"

HealthBar::HealthBar()
{
	utils::SetOrigin(rectShape, Pivots::LeftMiddle);
}

void HealthBar::Init(Vector2i position)
{
	rectShape.setPosition(position.x * 0.35f, position.y * 0.8f);
	rectShape.setFillColor(Color::Red);

	//FloatRect textRect = rectShape.getLocalBounds();
	//rectShape.setOrigin(
	//	textRect.left, textRect.top + textRect.height * 0.5f);
}

void HealthBar::Update(int health)
{
	float healthBarWidth = health * 3;
	float healthBarHeight = 30;

	Vector2f healthBarSize = Vector2f(healthBarWidth, healthBarHeight);
	rectShape.setSize(healthBarSize);
}



void HealthBar::Draw(RenderWindow& window)
{
	window.draw(rectShape);
}
