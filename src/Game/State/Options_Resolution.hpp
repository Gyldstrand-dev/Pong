#pragma once
#include "State/Base.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Handle.hpp"
#include "System/Physics.hpp"
#include "Event/Push_State.hpp"
#include "Event/Pop_State.hpp"
#include "Event/Exit.hpp"
#include <string>
#include <vector>
#include <iostream>

namespace State {
	
class Options;
	
class Options_Resolution : public State::Base {
	
	std::vector <EnTT::Handle> buttons;

public:

	Options_Resolution(State::Machine& state_machine)
	:	Base {state_machine} {};

	void push() override {};
	
	void pop() override {};
	
	void enter() override {
		
		create_entities();
		
	};
	
	void exit() override {
		
		destroy_entities();
		
	};
	
	void update(const Time::Duration&, System::Physics&) {};

private:

	void connect_event_listeners() {};
	
	void disconnect_event_listeners() {};
	
	void create_entities() {
		
		
		auto window_size = state_machine.window.get_size();
		auto& resolutions = sf::VideoMode::getFullscreenModes();
		buttons.resize(resolutions.size() + 1);
		buttons.shrink_to_fit();
		
		for (size_t i {0}; i < resolutions.size(); i++) {
					
			buttons.at(i) = {state_machine.ecs, state_machine.ecs.create()};
			buttons.at(i).emplace <Component::UI::Button> ( 
				Vector_2 <float> {window_size.x / 2.f, (window_size.y - (buttons.size() * 32.f)) / 2.f + i * 32.f},
				Vector_2 <float> {100.f, 30.f},
				std::to_string(resolutions[i].width) + " x " + std::to_string(resolutions[i].height),
				state_machine.font_cache.handle(EnTT::Hashed_String {"Raleway-Regular.ttf"}),
				std::uint8_t {12},
				SFML::Color {255, 255, 255, 255},
				SFML::Color {0, 0, 0, 255},
				[i = i, &buttons = buttons] () {
					auto& button = static_cast <SFML::Button&> (*buttons.at(i).get <Component::Graphics::Drawable> ().pointer);
					button.set_color({200, 200, 200, 255});
				},
				[i = i,  &buttons = buttons] () {
					auto& button = static_cast <SFML::Button&> (*buttons.at(i).get <Component::Graphics::Drawable> ().pointer);
					button.set_color({255, 255, 255, 255});
				},
				[i = i, &state_machine = state_machine, this] () {
					state_machine.window.create(sf::VideoMode::getFullscreenModes().at(i), "Window");
					state_machine.event_dispatcher.enqueue <Event::Pop_State> ();
					state_machine.event_dispatcher.enqueue <Event::Push_State> (std::make_unique <State::Options> (state_machine));
				}
			);
			
		};
		
		buttons.back() = {state_machine.ecs, state_machine.ecs.create()};
		buttons.back().emplace <Component::UI::Button> ( 
			Vector_2 <float> {window_size.x / 2.f, (window_size.y - (buttons.size() * 32.f)) / 2.f + buttons.size() * 32.f},
			Vector_2 <float> {100.f, 30.f},
			std::string {"Back"},
			state_machine.font_cache.handle(EnTT::Hashed_String {"Raleway-Regular.ttf"}),
			std::uint8_t {12},
			SFML::Color {255, 255, 255, 255},
			SFML::Color {0, 0, 0, 255},
			[&buttons = buttons] () {
				auto& button = static_cast <SFML::Button&> (*buttons.back().get <Component::Graphics::Drawable> ().pointer);
				button.set_color({200, 200, 200, 255});
			},
			[&buttons = buttons] () {
				auto& button = static_cast <SFML::Button&> (*buttons.back().get <Component::Graphics::Drawable> ().pointer);
				button.set_color({255, 255, 255, 255});
			},
			[&state_machine = state_machine] () {
				state_machine.event_dispatcher.enqueue <Event::Pop_State> ();
			}
		);
		
		
	};
	
	void destroy_entities() {
		
		for (auto& button : buttons) {
			button.destroy();
		};
		
		buttons.clear();
	
	};
	
};
	
	
	
};