#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Blood {
private:
	Vector2f position;
	Sprite sprite;
	const float SHOW_TIME = 5.f;
	float timeAfterDeath;

public:
	Blood();

	void Spawn(Vector2f pos);
	void Update(float dt);
	void Draw(RenderWindow& window);
};