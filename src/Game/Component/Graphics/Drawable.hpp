#pragma once
#include "SFML/Transform.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <memory>


namespace Component {
namespace Graphics {
	
	
	
struct Drawable {
	
	std::unique_ptr <sf::Drawable> pointer;
	SFML::Transform transform;
	
};
	
	
	
};};