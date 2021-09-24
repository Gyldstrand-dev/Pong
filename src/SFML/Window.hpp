#pragma once
#include "Vector_2.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


namespace SFML {
	
	
	
class Window {
	
public:

	template <typename... Args>
	Window(Args&&... args)
	:	sfml_window {std::forward <Args> (args)...} {
		
			sfml_window.setKeyRepeatEnabled(false);
	};
	
	template <typename... Args>
	void create(Args&&... args) {

		sfml_window.create(std::forward <Args> (args)...);
	};
	
	Vector_2 <unsigned int> get_size() {
		return sfml_window.getSize();
	};	
	
	bool is_open() {
		return sfml_window.isOpen();
	};
	
	bool poll_event(sf::Event& event) {
		return sfml_window.pollEvent(event);
	};

	void clear(const sf::Color& color = {0, 0, 0, 255}) {
		sfml_window.clear(color);
	};
	
	template <typename... Args>
	void draw(Args&&... args) {
		sfml_window.draw(std::forward <Args> (args)...);
	};
	
	void display() {
		sfml_window.display();
	};	
	
	void close() {
		sfml_window.close();
	};
	
	Vector_2 <float> map_pixel_to_coords(const Vector_2 <float>& pixel) {
		auto coords = sfml_window.mapPixelToCoords({pixel.x, pixel.y});
		return {coords.x * 1.f, coords.y * 1.f};
	};

private:

	sf::RenderWindow sfml_window;
	
};
	
	
	
};