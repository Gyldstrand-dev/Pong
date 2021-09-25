#pragma once
#include "SFML/Transform.hpp"
#include "SFML/Drawable.hpp"
#include <memory>


namespace Component {
namespace Graphics {
	
	
	
struct Drawable {
	
	std::unique_ptr <SFML::Drawable> pointer {nullptr};
	SFML::Transform transform {};
	
};
	
	
	
};};