#pragma once
#include "Vector_2.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


namespace SFML {
	
	
	
class Window {
	
public:

	template <typename... Args>
	Window(Args&&... args)
	:	sfml_window {std::forward <Args> (args)...} {
		
			sfml_window.setKeyRepeatEnabled(false);			
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

	void clear() {
		sfml_window.clear();
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

private:

	sf::RenderWindow sfml_window;
	sf::View view;
	
};
	
	
	
	
};