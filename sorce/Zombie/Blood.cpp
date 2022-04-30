#include "Blood.h"
#include "../utils/TextureHolder.h"
#include "../utils/utils.h"

Blood::Blood()
	:timeAfterDeath(SHOW_TIME)
{
	sprite.setTexture(TextureHolder::getTexture("graphics/blood.png"));
	position = Vector2f(-100, -100);
	sprite.setPosition(position);
}

void Blood::Spawn(Vector2f pos)
{
	position = pos;
	sprite.setPosition(position);
}

void Blood::Update(float dt)
{
	timeAfterDeath -= dt;
	if (timeAfterDeath < 0) {
		position = Vector2f(-100, -100);
		sprite.setPosition(position);
	}
}

void Blood::Draw(RenderWindow& window)
{
	window.draw(sprite);
}
