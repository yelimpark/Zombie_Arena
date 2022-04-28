#include "TitleScene.h"
#include "../utils/TextureHolder.h"
#include "../utils/FontHolder.h"
#include "../utils/InputManager.h"
#include "../Framework/Framework.h"

TitleScene::TitleScene(SceneManager& sceneManager)
	:Scene(sceneManager),
	resolution(Framework::GetResolution()),
	window(Framework::Getwindow())
{
}

bool TitleScene::Init()
{
	bg.setTexture(TextureHolder::getTexture("graphics/background.png"));
	text.setFont(FontHolder::getfont("fonts/zombiecontrol.ttf"));
	text.setString("PRESS ENTER TO PLAY");
	text.setPosition(resolution.x * 0.1f, resolution.y * 0.7f);
	text.setCharacterSize(100);
	text.setFillColor(Color::White);
	return true;
}

void TitleScene::Update(Time& dt)
{
	if (InputManager::GetKeyDown(Keyboard::Enter)) {
		sceneManager.ChangeScene(SceneType::STAGE);
	}
}

void TitleScene::Render()
{
	window.draw(bg);
	window.draw(text);
}

void TitleScene::Release()
{
}

TitleScene::~TitleScene()
{
}
