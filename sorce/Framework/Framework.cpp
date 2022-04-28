#include "Framework.h"
#include <assert.h>

Framework* Framework::FrameInstance = 0;

Vector2i Framework::resolution(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
RenderWindow Framework::window(VideoMode(resolution.x, resolution.y), "Zombie Arena!", Style::Default);
View Framework::mainView(FloatRect(0, 0, resolution.x, resolution.y));
View Framework::uiView(FloatRect(0, 0, resolution.x, resolution.y));

Framework::Framework()
{
    assert(!FrameInstance);
    FrameInstance = this;
}

RenderWindow& Framework::Getwindow()
{
    return window;
}

const Vector2i& Framework::GetResolution()
{
    return resolution;
}

View& Framework::GetView()
{
    return mainView;
}

View& Framework::GetUIView()
{
    uiView.setCenter(Vector2f(resolution.x * 0.5f, resolution.y * 0.5f));
    return uiView;
}

void Framework::Init()
{
    InputManager::Init();
    sMgr.Init();
    crossCursor.Init();
}

int Framework::Run()
{
    while (window.isOpen())
    {
        Time dt = clock.restart();

        Event event;

        InputManager::ClearInput();

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            InputManager::ProcessInput(event);
        }

        InputManager::Update(dt.asSeconds(), window, mainView);
        sMgr.Update(dt);
        crossCursor.Update();

        window.clear();
        window.setView(mainView);
        sMgr.Render();
        crossCursor.Render();
        window.display();
    }

    return 0;
}

Framework::~Framework()
{
    assert(FrameInstance);
    FrameInstance = 0;
}
