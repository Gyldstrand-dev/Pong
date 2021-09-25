#pragma once
#include "Vector_2.hpp"
#include "SFML/Event.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


namespace SFML {
	
	
	
class Window {
	
public:

	template <typename... Args>
	Window(Args&&... args)
	:	sfml_window {std::forward <Args> (args)...} {
		
			sfml_window.setKeyRepeatEnabled(false);
			default_view = sfml_window.getDefaultView();
			sfml_window.setView(default_view);
			//save original Default View
	};
	
	template <typename... Args>
	void create(Args&&... args) {

		sfml_window.create(std::forward <Args> (args)...);
		sfml_window.setKeyRepeatEnabled(false);
		sfml_window.setView(default_view);
		//set to original Default View to have everything resize after changing Video Mode
	};
	
	Vector_2 <unsigned int> get_size() {
		return {static_cast <unsigned int> (default_view.getSize().x), static_cast <unsigned int> (default_view.getSize().y)};
		//return original size to have everything resize after changing Video Mode
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
	
	Vector_2 <float> map_pixel(const Vector_2 <int>& coord) {
		return sfml_window.mapPixelToCoords(sf::Vector2i {coord.x, coord.y}, default_view);
		//map to original Default View to have everything resize after changing Video Mode
	};

private:

	sf::View default_view;
	sf::RenderWindow sfml_window;
	
};
	
	
	
};