#pragma once
#include "EnTT/Resource_Loader.hpp"
#include "SFML/Font.hpp"
#include <memory>
#include <string>

namespace Resource {
namespace Font {
	
	
	
struct Loader : EnTT::Resource_Loader <Resource::Font::Loader, SFML::Font> {
	
	std::shared_ptr <SFML::Font> load(const std::string& file) const {
		auto font = std::make_shared <SFML::Font> ();
		font->loadFromFile(directory + file);
		return font;
	};
	
private:

	const std::string directory {"C:/DEV/projects/SFML/Pong/src/Game/Resource/Font/"};
	
};
	
	
	
};};