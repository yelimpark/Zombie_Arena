#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class ReloadBar {
private:
	const float RELOAD_TIME = 3.f;
	RectangleShape timebar;
	float timeLeftToReload;
	int MAGAZINE;
	int leftBullet;

public:
	ReloadBar();

	void Update(Vector2f playerPos, float dt);

	void Reload(float dt);

	bool Shoot();

	RectangleShape& GetShape();
};