#include "TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::instance;

TextureHolder::TextureHolder()
{
	assert(instance == nullptr);
	instance = this;
}

Texture& TextureHolder::getTexture(string filename)
{
	auto& map = instance->mapTexture;
	auto it = map.find(filename);
	if (it == map.end()) {
		auto& texture = map[filename];
		texture.loadFromFile(filename);
	}

	return map[filename];
}
