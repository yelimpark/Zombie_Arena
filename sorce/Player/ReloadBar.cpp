#include "ReloadBar.h"
#include "../utils/utils.h"
#include "../utils/GameVal.h"

ReloadBar::ReloadBar()
	:megazine(GameVal::megazine), timeLeftToReload(RELOAD_TIME), leftBullet(megazine)
{
	timebar.setSize(Vector2f(0, 0));
	timebar.setFillColor(Color::Red);
}

void ReloadBar::Init()
{
	megazine = GameVal::megazine;
	timeLeftToReload = RELOAD_TIME;
	leftBullet = megazine;
	timebar.setSize(Vector2f(0, 0));
}

void ReloadBar::Update(Vector2f playerPos, float dt)
{
	timebar.setPosition(Vector2f(playerPos.x, playerPos.y + 50));
	if (leftBullet == 0) {
		Reload(dt);
	}
}

void ReloadBar::Reload(float dt)
{
	timeLeftToReload -= dt;
	timebar.setSize(Vector2f(timeLeftToReload * 50, 10));
	utils::SetOrigin(timebar, Pivots::Center);

	if (timeLeftToReload < 0) {
		timeLeftToReload = RELOAD_TIME;
		leftBullet = megazine;
	}
}

bool ReloadBar::Shoot()
{
	if (leftBullet > 0) {
		--leftBullet;
		return true;
	}
	return false;
}



RectangleShape& ReloadBar::GetShape()
{
	return timebar;
}
