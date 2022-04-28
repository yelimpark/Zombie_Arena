#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class CrossCursor {
private:
	Sprite sprite;

	RenderWindow& window;

public:
	CrossCursor();

	void Init();

	void Update();

	void Render();

	~CrossCursor();
};;