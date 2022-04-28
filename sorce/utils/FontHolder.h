#pragma once
#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class FontHolder {
public:
	FontHolder();

	static Font& getfont(string filename);

private:
	map<string, Font> mapFont;

	static FontHolder* instance;
};