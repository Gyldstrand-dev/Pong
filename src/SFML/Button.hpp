#pragma once
#include "Vector_2.hpp"
#include "SFML/Drawable.hpp"
#include "SFML/Rectangle.hpp"
#include "SFML/Font.hpp"
#include "SFML/Text.hpp"
#include "SFML/Color.hpp"


namespace SFML {
	
	
	
class Button : public sf::Drawable {
	
public:

	void set_position(const Vector_2 <float>& position) {
		rect.setPosition({position.x, position.y});
		center_text();
		
	};
	
	void set_size(const Vector_2 <float>& size) {
		
		rect.setSize({size.x, size.y});
		rect.setOrigin({size.x / 2.f, size.y / 2.f});
		center_text();
		
	};
	
	void set_color(const SFML::Color& color) {
		rect.setFillColor(color);
	};
	
	void set_string(const std::string& string) {
		text.setString(string);
		center_text();
		
	};
	
	void set_font(const SFML::Font& font) {
		text.setFont(font);
		center_text();
		
	};
	
	void set_font_size(const unsigned int& size) {
		text.setCharacterSize(size);
		center_text();
	
	};
	
	void set_font_color(const SFML::Color& color) {
		text.setFillColor(color);
	};
	
	bool contains(const Vector_2 <float>& point) {
		return rect.getGlobalBounds().contains(point.x, point.y);
	};

private:

	SFML::Rectangle rect;
	SFML::Text text;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(rect);
		target.draw(text);
		
	};
	
	void center_text() {
		
		auto bounds = text.getLocalBounds();
		auto size = rect.getSize();
		text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
		text.setPosition(rect.getPosition());
		//text.move(size.x / 2.f, size.y / 2.5f);
		
	};
};
	
	
	
};