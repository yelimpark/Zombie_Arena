#include "Pickup.h"
#include "../utils/TextureHolder.h"
#include "../utils/utils.h"
#include <iostream>

Pickup::Pickup(PickupTypes type) : type(type)
{
	std::string textureId;
	switch (this->type)
	{
	case PickupTypes::Ammo:
		textureId = "graphics/ammo_pickup.png";
		value = AMMO_START_VALUE;
		break;

	case PickupTypes::Health:
		textureId = "graphics/health_pickup.png";
		value = HEALTH_START_VALUE;
		break;
	default:
		break;
	}
	sprite.setTexture(TextureHolder::getTexture(textureId));
	utils::SetOrigin(sprite, Pivots::Center);

	Spawn(false);
}

void Pickup::Update(float dt)
{
	timer -= dt;
	if (timer < 0.f) {
		Spawn(!spawned);
	}
}

void Pickup::Spawn(bool spawn)
{
	spawned = spawn;
	if (spawned) {
		timer = START_SECOND_FOE_LIVE;
		//int x = utils::RandomRange(arena.left, arena.left + arena.width);
		//int y = utils::RandomRange(arena.top, arena.top + arena.height);
		int x = utils::RandomRange(0, 1920);
		int y = utils::RandomRange(0, 1080);

		sprite.setPosition(Vector2f(x, y));
	}
	else {
		timer = START_WAIT_TIME;
	}
}

int Pickup::GotIt()
{
	return value;
}

PickupTypes Pickup::GetType()
{
	return type;
}

void Pickup::SetArena(IntRect rect)
{
	arena = rect;
}

bool Pickup::IsSpawned()
{
	return spawned;
}

Sprite& Pickup::GetSprite()
{
	return sprite;
}
//--------------Pickip item Upgrade for LevelUpScene
void Pickup::AammoUpgrade()
{
	if (static_cast<int>(PickupTypes::Ammo) == 1)
	{
		value += (AMMO_START_VALUE * 10.f);
	}
}
//--------------Pickip item Upgrade for LevelUpScene
void Pickup::HealthUpgrade()
{
	if (static_cast<int>(PickupTypes::Health) == 1)
	{
		value += (HEALTH_START_VALUE * 10.f);
	}
}

const FloatRect Pickup::GetBlobalBounds()
{
	return sprite.getGlobalBounds();
}
