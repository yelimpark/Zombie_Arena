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

	static bool isMousePressed;

public:
	static void Init();

	static float GetAxis(Axis axis);

	static int GetAxisRaw(Axis axis);

	static int GetAxisRaw(const list<Keyboard::Key>& positive, const list<Keyboard::Key>& nagative);

	static void ProcessInput(const Event& event);

	static void Update(float dt);

	static bool GetKeyDown(Keyboard::Key key);
	static bool GetKey(Keyboard::Key key);
	static bool GetKeyUp(Keyboard::Key key);

	static void ClearInput();

	static bool GetMouseClick();

	static Vector2i GetMousePosition();
};