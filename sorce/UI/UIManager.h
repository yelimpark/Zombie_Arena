#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class UIManager
{
private:
	const float START_COUNT_OF_BULLETS = 24;
	const float START_WAVE = 0;

	Text textScore;
	Text textBullet;
	Text textHighScore;
	Text zombieCount;
	Text waveNum;

	Sprite sprite;

	int numOfZombies;
	int score;
	int highScore;

	static bool isInitUIFontInfo;

public:
	UIManager();
	void Update(int numOfZombies, int bullets, Vector2i position);
	void Draw(RenderWindow& window);
};

