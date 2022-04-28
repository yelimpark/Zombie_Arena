#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class ReloadBar {
private:
	const float RELOAD_TIME = 3.f;
	RectangleShape timebar;
	float timeLeftToReload;
	int megazine;
	int leftBullet;

public:
	ReloadBar();

	void Init();

	void Update(Vector2f playerPos, float dt);

	void Reload(float dt);

	int GetLeftBullet();

	bool Shoot();

	RectangleShape& GetShape();
};