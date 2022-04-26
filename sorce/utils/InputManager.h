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
};

class InputManager {
private:
	static std::map<Axis, AxisInfo> mapAxis;

	static list<Keyboard::Key> downKeys;
	static list<Keyboard::Key> ingKeys;
	static list<Keyboard::Key> upKeys;

public:
	static void Init();

	static int GetAxis(Axis axis);

	static int GetAxis(const list<Keyboard::Key>& positive, const list<Keyboard::Key>& nagative);

	static void ProcessInput(const Event& event);

	static bool GetKeyDown(Keyboard::Key key);
	static bool GetKey(Keyboard::Key key);
	static bool GetKeyUp(Keyboard::Key key);

	static void ClearInput();

	static Vector2i GetMousePosition();
};