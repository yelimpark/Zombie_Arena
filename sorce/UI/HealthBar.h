#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class HealthBar
{
private:
	RectangleShape rectShape;
	Vector2f healthBarSize;


	int health;
	int healthMax;

public:
	HealthBar();
	void Init(Vector2i position);
	void Update(int health);
	void Draw(RenderWindow& window);
};

