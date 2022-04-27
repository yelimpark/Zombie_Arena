#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <map>

using namespace sf;
using namespace std;

enum class Axis {
	Horizonal,
	Vertical
};

struct AxisInfo
{
	Axis axis;
	list<Keyboard::Key> positiveKeys;
	list<Keyboard::Key> negativeKeys;

	float sensi; // sensitivity
	float limit;
	float value; // -1.0 ~ 1.0
};

class InputManager {
private:
	static std::map<Axis, AxisInfo> mapAxis;

	static list<Keyboard::Key> downKeys;
	static list<Keyboard::Key> ingKeys;
	static list<Keyboard::Key> upKeys;

	static list<Mouse::Button> downButtons;
	static list<Mouse::Button> ingButtons;
	static list<Mouse::Button> upButtons;

	static Vector2i mousePosition;
	static Vector2f mousePositionWorld;

public:
	static void Init();

	static float GetAxis(Axis axis);

	static int GetAxisRaw(Axis axis);

	static int GetAxisRaw(const list<Keyboard::Key>& positive, const list<Keyboard::Key>& nagative);

	static void ProcessInput(const Event& event);

	static void Update(float dt, RenderWindow& window, View& mainview);

	static bool GetKeyDown(Keyboard::Key key);
	static bool GetKey(Keyboard::Key key);
	static bool GetKeyUp(Keyboard::Key key);

	static void ClearInput();

	static bool GetMouseButttonDown(Mouse::Button button);

	static bool GetMouseButton(Mouse::Button button);

	static bool GetMouseButtonUp(Mouse::Button button);

	static Vector2i GetMousePosition();
	static Vector2f GetMouseWorldPosition();
};