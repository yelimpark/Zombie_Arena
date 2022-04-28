#include "FontHolder.h"
#include <assert.h>

FontHolder* FontHolder::instance;

FontHolder::FontHolder()
{
    assert(instance == nullptr);
    instance = this;
}

Font& FontHolder::getfont(string filename)
{
	auto& map = instance->mapFont;
	auto it = map.find(filename);
	if (it == map.end()) {
		auto& texture = map[filename];
		texture.loadFromFile(filename);
	}

	return map[filename];
}
