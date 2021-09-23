#pragma once
#include "State/Base.hpp"
#include "State/Main_Menu.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Handle.hpp"
#include "System/Physics.hpp"
#include "Event/Key_Pressed.hpp"
#include "Event/Push_State.hpp"
#include "Event/Pop_State.hpp"
#include <iostream>

namespace State {
	
	
	
class Intro : public State::Base {
	
public:

	Intro(State::Machine& state_machine)
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
	
	void update(const Time::Duration&, System::Physics&) override {};
	
	
private:
	
	EnTT::Handle intro_text;

	void connect_event_listeners() {
		
		state_machine.event_dispatcher.sink <Event::Key_Pressed> ().connect <&State::Intro::on_key_pressed> (this);
	
	};
	
	void disconnect_event_listeners() {
		
		state_machine.event_dispatcher.sink <Event::Key_Pressed> ().disconnect <&State::Intro::on_key_pressed> (this);
	
	};
	
	void create_entities() {
		
		intro_text = {state_machine.ecs, state_machine.ecs.create()};
		auto font = state_machine.font_cache.handle(EnTT::Hashed_String {"OpenSans-Regular.ttf"});
		auto& drawable = intro_text.emplace <Component::Graphics::Drawable> (std::make_unique <sf::Text> ("INTRO", font, 100));
		//reverse physics scale to avoid blurry text
		drawable.transform.set_scale({1.f / System::Physics::scale, 1.f / System::Physics::scale});
	
	};
	
	void destroy_entities() {
		
		intro_text.destroy();
	
	};
	
	void on_key_pressed(const Event::Key_Pressed&) {
		
		state_machine.event_dispatcher.enqueue <Event::Pop_State> ();
		state_machine.event_dispatcher.enqueue <Event::Push_State> (std::make_unique <State::Main_Menu> (state_machine));
		
	};
};
	
	
	
};