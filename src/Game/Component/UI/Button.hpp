#pragma once
#include "Vector_2.hpp"
#include "SFML/Font.hpp"
#include "SFML/Color.hpp"
#include <string>
#include <functional>


namespace Component {
namespace UI {
	
	
	
struct Button {
	
	Vector_2 <float> position, size;
	std::string string;
	SFML::Font font;
	unsigned int font_size;
	SFML::Color color;
	SFML::Color font_color;
	
	std::function <void()> on_mouse_enter;
	std::function <void()> on_mouse_exit;
	std::function <void()> on_mouse_pressed_left;
	
};
		

	
	
	
};};