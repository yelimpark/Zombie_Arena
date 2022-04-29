#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class HealthBar
{
private:
	RectangleShape rectShape;
	Vector2f healthBarSize;

	Text gameoverText;

	int health;
	int healthMax;

public:
	HealthBar();
	void Init(int health, Vector2i res);
	void Update(int health);
	void Draw(RenderWindow& window);
	void setSize();
};

