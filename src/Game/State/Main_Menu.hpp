#pragma once
#include "State/Base.hpp"
#include "State/Play.hpp"
#include "State/Options.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Handle.hpp"
#include "System/Physics.hpp"
#include "System/User_Interface.hpp"
#include "Component/UI/Button.hpp"
#include "Event/Push_State.hpp"
#include "Event/Pop_State.hpp"
#include "Event/Exit.hpp"


namespace State {
	
	
	
class Main_Menu : public State::Base {
	
	EnTT::Handle play_button, options_button, exit_button;

public:

	Main_Menu(State::Machine& state_machine)
	:	Base {state_machine} {};

	void push() override {};
	
	void pop() override {};
	
	void enter() override {
		
		connect_event_listeners();
		create_entities();
		
	};
	
	void exit() override {
		
		disconnect_event_listeners();
		destroy_entities();
		
	};
	
	void update(const Time::Duration&, System::Physics&) {};

private:

	void connect_event_listeners() {};
	
	void disconnect_event_listeners() {};
	
	void create_entities() {
		
		auto window_size = state_machine.window.get_size();
		
		play_button = {state_machine.ecs, state_machine.ecs.create()};
		play_button.emplace <Component::UI::Button> ( 
			Vector_2 <float> {window_size.x / 2.f, window_size.y / 2.f - 150.f},
			Vector_2 <float> {100.f, 60.f},
			std::string {"Play"},
			state_machine.font_cache.handle(EnTT::Hashed_String {"OpenSans-Regular.ttf"}),
			std::uint8_t {15},
			SFML::Color {255, 255, 255, 255},
			SFML::Color {0, 0, 0, 255},
			[&] () {
				auto& button = static_cast <SFML::Button&> (*play_button.get <Component::Graphics::Drawable> ().pointer);
				button.set_color({200, 200, 200, 255});
			},
			[&] () {
				auto& button = static_cast <SFML::Button&> (*play_button.get <Component::Graphics::Drawable> ().pointer);
				button.set_color({255, 255, 255, 255});
			},
			[&] () {
				state_machine.event_dispatcher.enqueue <Event::Pop_State> ();
				state_machine.event_dispatcher.enqueue <Event::Push_State> (std::make_unique <State::Play> (state_machine));
			}
		);
		
		options_button = {state_machine.ecs, state_machine.ecs.create()};
		options_button.emplace <Component::UI::Button> ( 
			Vector_2 <float> {window_size.x / 2.f, window_size.y / 2.f},
			Vector_2 <float> {100.f, 60.f},
			std::string {"Options"},
			state_machine.font_cache.handle(EnTT::Hashed_String {"OpenSans-Regular.ttf"}),
			std::uint8_t {15},
			SFML::Color {255, 255, 255, 255},
			SFML::Color {0, 0, 0, 255},
			[&] () {
				auto& button = static_cast <SFML::Button&> (*options_button.get <Component::Graphics::Drawable> ().pointer);
				button.set_color({200, 200, 200, 255});
			},
			[&] () {
				auto& button = static_cast <SFML::Button&> (*options_button.get <Component::Graphics::Drawable> ().pointer);
				button.set_color({255, 255, 255, 255});
			},
			[&] () {
				state_machine.event_dispatcher.enqueue <Event::Pop_State> ();
				state_machine.event_dispatcher.enqueue <Event::Push_State> (std::make_unique <State::Options> (state_machine));
			}
		);
		
		exit_button = {state_machine.ecs, state_machine.ecs.create()};
		exit_button.emplace <Component::UI::Button> ( 
			Vector_2 <float> {window_size.x / 2.f, window_size.y / 2.f + 150.f},
			Vector_2 <float> {100.f, 60.f},
			std::string {"Exit"},
			state_machine.font_cache.handle(EnTT::Hashed_String {"OpenSans-Regular.ttf"}),
			std::uint8_t {15},
			SFML::Color {255, 255, 255, 255},
			SFML::Color {0, 0, 0, 255},
			[&] () {
				auto& button = static_cast <SFML::Button&> (*exit_button.get <Component::Graphics::Drawable> ().pointer);
				button.set_color({200, 200, 200, 255});
			},
			[&] () {
				auto& button = static_cast <SFML::Button&> (*exit_button.get <Component::Graphics::Drawable> ().pointer);
				button.set_color({255, 255, 255, 255});
			},
			[&] () {
				state_machine.event_dispatcher.trigger <Event::Exit> ();
			}
		);
	};
	
	void destroy_entities() {
		
		play_button.destroy();
		options_button.destroy();
		exit_button.destroy();
	
	};
	
	
};
	
	
	
};