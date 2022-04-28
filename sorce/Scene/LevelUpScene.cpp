#include "LevelUpScene.h"

#include "../utils/TextureHolder.h"
#include "../utils/InputManager.h"
#include "../Framework/Framework.h"
#include"../utils/SceneManager.h"

#include <iostream>
#include <sstream>

using namespace std;

LevelUpScene::LevelUpScene(SceneManager& sceneManager)
	:Scene(sceneManager),
	window(Framework::Getwindow()),
	resolution(Framework::GetResolution()),
	mainView(Framework::GetView())
{
}

bool LevelUpScene::Init()
{
	bg.setTexture(TextureHolder::getTexture("graphics/background.png"));

	textLevel.setFont(FontHolder::getfont("fonts/zombiecontrol.ttf"));
	textLevel.setCharacterSize(90);
	textLevel.setFillColor(Color::White);
	textLevel.setPosition(150, 260);

	// ������ �� ���� �ܼ� �ؽ�Ʈ�� ss ����� ������ ???
	// ���� ���ٸ� �׳� string ���ô�~~
	std::stringstream levelUpStream;
	levelUpStream <<
		"1- Increased rate of fire" <<
		"\n2- Increased clip size(next reload)" <<
		"\n3- Increased max health" <<
		"\n4- Increased run speed" <<
		"\n5- More and better health pickups" <<
		"\n6- More and better ammo pickups";
	textLevel.setString(levelUpStream.str());

	mainView.setCenter(resolution.x * 0.5f, resolution.y * 0.5f);

	return true;
}

void LevelUpScene::Update(Time& dt)
{
	if (InputManager::GetKeyDown(Keyboard::Num1)) {
		// �Ѿ� �߻� �ӵ� !!!
		sceneManager.ChangeScene(SceneType::STAGE);
	}
	if (InputManager::GetKeyDown(Keyboard::Num2)) {
		GameVal::megazine += 5;
		sceneManager.ChangeScene(SceneType::STAGE);
	}

	// .... ������ ó��

	//switch (event.type)
	//{
	//case Event::KeyPressed:
	//	switch (event.key.code)
	//	{
	//	case Keyboard::Num1:
	//		//Increased rate of fire
	//		//�Ѿ� �����÷��ֱ�
	//		sceneManager.ChangeScene(SceneType::STAGE);
	//		break;
	//	case Keyboard::Num2:
	//		//Increased clip size(next reload)
	//		//źâ�ø���
	//		sceneManager.ChangeScene(SceneType::STAGE);
	//		break;
	//	case Keyboard::Num3:
	//		//Increased max health
	//		/*Player.UpgradeMaxHealth();*/
	//		// �÷��̾� �ǰ� �÷��ֱ�
	//		sceneManager.ChangeScene(SceneType::STAGE);
	//		break;
	//	case Keyboard::Num4:
	//		//Increased run speed
	//		//���ǵ� �÷��ֱ�
	//		sceneManager.ChangeScene(SceneType::STAGE);
	//		break;
	//	case Keyboard::Num5:
	//		//More and better health pickup
	//		//health �����۴÷��ֱ�
	//		sceneManager.ChangeScene(SceneType::STAGE);
	//		break;
	//	case Keyboard::Num6:
	//		// More and better ammo pickups
	//		//ammo �����۴÷��ֱ�

	//		break;

	//	default:
	//		break;
	//	}
	//	break;
	//}
	//if (InputManager::GetKeyDown(Keyboard::Enter)) {
	//	sceneManager.ChangeScene(SceneType::STAGE);
	//}
}

void LevelUpScene::Render()
{
	window.draw(bg);
	window.draw(textLevel);
}

void LevelUpScene::Release()
{
}

LevelUpScene::~LevelUpScene()
{
}
