#pragma once
#include "State/Base.hpp"
#include "State/Options_Resolution.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Handle.hpp"
#include "System/Physics.hpp"
#include "Event/Push_State.hpp"
#include "Event/Pop_State.hpp"
#include "Event/Exit.hpp"


namespace State {
	
class Main_Menu;
	
class Options : public State::Base {
	
	EnTT::Handle resolution_button, back_button, exit_button;

public:

	Options(State::Machine& state_machine)
	:	Base {state_machine} {};

	void push() override {
		
		create_entities();

	};
	
	void pop() override {
	
		destroy_entities();
	
	};
		
	void enter() override {

		
	};
	
	void exit() override {

		
	};
	
	void update(const Time::Duration&, System::Physics&) {};

private:

	void connect_event_listeners() {};
	
	void disconnect_event_listeners() {};
	
	void create_entities() {
		
		
		auto window_size = state_machine.window.get_size();
		
		resolution_button = {state_machine.ecs, state_machine.ecs.create()};
		resolution_button.emplace <Component::UI::Button> ( 
			Vector_2 <float> {window_size.x / 2.f, window_size.y / 2.f - 150.f},
			Vector_2 <float> {100.f, 30.f},
			std::string {"Resolution"},
			state_machine.font_cache.handle(EnTT::Hashed_String {"Raleway-Regular.ttf"}),
			std::uint8_t {15},
			SFML::Color {255, 255, 255, 255},
			SFML::Color {0, 0, 0, 255},
			[&resolution_button = resolution_button] () {
				auto& button = static_cast <SFML::Button&> (*resolution_button.get <Component::Graphics::Drawable> ().pointer);
				button.set_color({200, 200, 200, 255});
			},
			[&resolution_button = resolution_button] () {
				auto& button = static_cast <SFML::Button&> (*resolution_button.get <Component::Graphics::Drawable> ().pointer);
				button.set_color({255, 255, 255, 255});
			},
			[&state_machine = state_machine] () {
				state_machine.event_dispatcher.enqueue <Event::Pop_State> ();
				state_machine.event_dispatcher.enqueue <Event::Push_State> (std::make_unique <State::Options_Resolution> (state_machine));
			}
		);
		
		back_button = {state_machine.ecs, state_machine.ecs.create()};
		back_button.emplace <Component::UI::Button> ( 
			Vector_2 <float> {window_size.x / 2.f, window_size.y / 2.f},
			Vector_2 <float> {100.f, 30.f},
			std::string {"Back"},
			state_machine.font_cache.handle(EnTT::Hashed_String {"Raleway-Regular.ttf"}),
			std::uint8_t {15},
			SFML::Color {255, 255, 255, 255},
			SFML::Color {0, 0, 0, 255},
			[&back_button = back_button] () {
				auto& button = static_cast <SFML::Button&> (*back_button.get <Component::Graphics::Drawable> ().pointer);
				button.set_color({200, 200, 200, 255});
			},
			[&back_button = back_button] () {
				auto& button = static_cast <SFML::Button&> (*back_button.get <Component::Graphics::Drawable> ().pointer);
				button.set_color({255, 255, 255, 255});
			},
			[&state_machine = state_machine] () {
				state_machine.event_dispatcher.enqueue <Event::Pop_State> ();
			}
		);	
		
		exit_button = {state_machine.ecs, state_machine.ecs.create()};
		exit_button.emplace <Component::UI::Button> ( 
			Vector_2 <float> {window_size.x / 2.f, window_size.y / 2.f + 150.f},
			Vector_2 <float> {100.f, 30.f},
			std::string {"Exit"},
			state_machine.font_cache.handle(EnTT::Hashed_String {"Raleway-Regular.ttf"}),
			std::uint8_t {15},
			SFML::Color {255, 255, 255, 255},
			SFML::Color {0, 0, 0, 255},
			[&exit_button = exit_button] () {
				auto& button = static_cast <SFML::Button&> (*exit_button.get <Component::Graphics::Drawable> ().pointer);
				button.set_color({200, 200, 200, 255});
			},
			[&exit_button = exit_button] () {
				auto& button = static_cast <SFML::Button&> (*exit_button.get <Component::Graphics::Drawable> ().pointer);
				button.set_color({255, 255, 255, 255});
			},
			[&state_machine = state_machine] () {
				state_machine.event_dispatcher.trigger <Event::Exit> ();
			}
		);
		
	};
	
	void destroy_entities() {
		
		resolution_button.destroy();
		back_button.destroy();
		exit_button.destroy();
	
	};
	
	
};
	
	
	
};