#include "ReloadBar.h"
#include "../utils/utils.h"

ReloadBar::ReloadBar()
	:timeLeftToReload(RELOAD_TIME), leftBullet(MAGAZINE)
{
	timebar.setSize(Vector2f(0, 0));
	timebar.setFillColor(Color::Red);
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
		leftBullet = MAGAZINE;
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
