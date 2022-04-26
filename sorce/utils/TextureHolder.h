#pragma once
#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class TextureHolder {
public :
	TextureHolder();

	static Texture& getTexture(string filename);

private:
	map<string, Texture> mapTexture;

	static TextureHolder* instance;
};