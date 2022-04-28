#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Player;

class UIManager
{
private:
	const float START_COUNT_OF_BULLETS = 24;
	const float START_WAVE = 0;

	Font font;
	Text textScore;
	Text textBullet;
	Text textHighScore;
	Text zombieCount;
	Text waveNum;

	Texture texture;
	Sprite sprite;

	int numOfZombies;
	int score;
	int highScore;
	int wave;

	int curBullets;
public:
	UIManager();
	void Update(int score, int numOfZombies, Vector2i position);
	void Draw(RenderWindow& window);
};

