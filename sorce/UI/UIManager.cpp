#include "UIManager.h"
#include <iostream>
#include <sstream>
#include "../player/Player.h"

UIManager::UIManager()
	: curBullets(START_COUNT_OF_BULLETS), wave(START_WAVE), score(0)
{
	font.loadFromFile("fonts/zombiecontrol.ttf");
	textScore.setFont(font);
	textScore.setFillColor(Color::White);
	textScore.setCharacterSize(60);

	textHighScore.setFont(font);
	textHighScore.setFillColor(Color::White);
	textHighScore.setCharacterSize(60);

	zombieCount.setFont(font);
	zombieCount.setFillColor(Color::White);
	zombieCount.setCharacterSize(50);

	waveNum.setFont(font);
	waveNum.setFillColor(Color::White);
	waveNum.setCharacterSize(50);

	textBullet.setFont(font);
	textBullet.setFillColor(Color::White);
	textBullet.setCharacterSize(50);
	FloatRect textRect = textBullet.getLocalBounds();
	textBullet.setOrigin(
		textRect.left + textRect.width * 0.5f,
		textRect.top + textRect.height * 0.5f
	);
	texture.loadFromFile("graphics/ammo_icon.png");
}

void UIManager::Update(int score, int numOfZombies, Vector2i position)
{

	//--------------점수--------------
	stringstream ss;
	ss << "Score = " << score;
	textScore.setString(ss.str());
	textScore.setPosition(position.x * 0.18f, position.y * 0.1f);

	stringstream hs;
	hs << "High Score = " << score;
	textHighScore.setString(hs.str());
	textHighScore.setPosition(position.x * 0.7f, position.y * 0.1f);

	//------------좀비카운트------------
	stringstream zs;
	zs << "Zombies : " << numOfZombies;
	zombieCount.setString(zs.str());
	zombieCount.setPosition(position.x * 0.8f, position.y * 0.8f);

	//--------------웨이브--------------
	stringstream ws;
	ws << "Wave : " << wave;
	waveNum.setString(ws.str());
	waveNum.setPosition(position.x * 0.65f, position.y * 0.8f);

	//--------------잔탄수--------------
	sprite.setTexture(texture);
	sprite.setPosition(position.x * 0.18f, position.y * 0.8f);

	stringstream bs;
	bs << curBullets << "/" << START_COUNT_OF_BULLETS;
	textBullet.setString(bs.str());
	textBullet.setPosition(position.x * 0.22f, position.y * 0.8f);


}

void UIManager::Draw(RenderWindow& window)
{
	window.draw(textScore);
	window.draw(textHighScore);
	window.draw(zombieCount);
	window.draw(waveNum);
	window.draw(sprite);
	window.draw(textBullet);
}
