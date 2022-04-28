#include "UIManager.h"
#include <iostream>
#include <sstream>
#include "../player/Player.h"
#include "../utils/FontHolder.h"
#include "../utils/TextureHolder.h"

bool UIManager::isInitUIFontInfo = false;

UIManager::UIManager()
	: score(0)
{
	FontHolder::getfont("fonts/zombiecontrol.ttf");

	if (!isInitUIFontInfo)
	{
		textScore.setFont(FontHolder::getfont("fonts/zombiecontrol.ttf"));
		textHighScore.setFont(FontHolder::getfont("fonts/zombiecontrol.ttf"));
		zombieCount.setFont(FontHolder::getfont("fonts/zombiecontrol.ttf"));
		waveNum.setFont(FontHolder::getfont("fonts/zombiecontrol.ttf"));
		textBullet.setFont(FontHolder::getfont("fonts/zombiecontrol.ttf"));
		sprite.setTexture(TextureHolder::getTexture("graphics/ammo_icon.png"));

		textScore.setFillColor(Color::White);
		textScore.setCharacterSize(60);

		textHighScore.setFillColor(Color::White);
		textHighScore.setCharacterSize(60);


		zombieCount.setFillColor(Color::White);
		zombieCount.setCharacterSize(50);


		waveNum.setFillColor(Color::White);
		waveNum.setCharacterSize(50);

		textBullet.setFillColor(Color::White);
		textBullet.setCharacterSize(50);
		FloatRect textRect = textBullet.getLocalBounds();
		textBullet.setOrigin(
			textRect.left + textRect.width * 0.5f,
			textRect.top + textRect.height * 0.5f
		);

		isInitUIFontInfo = true;
	}
}

void UIManager::Update(int score, int numOfZombies, int bullets, int wave, Vector2i position)
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
	sprite.setPosition(position.x * 0.18f, position.y * 0.8f);

	stringstream bs;
	bs << bullets << "/" << START_COUNT_OF_BULLETS;
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
