#pragma once
#include "State/Base.hpp"
#include "State/Play.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Handle.hpp"
#include "System/Physics.hpp"
#include "Event/Key_Pressed.hpp"
#include "Event/Push_State.hpp"
#include "Event/Pop_State.hpp"
#include <iostream>


namespace State {
	
	
	
class Pause : public State::Base {
	
public:

	Pause(State::Machine& state_machine)
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
	
	EnTT::Handle pause_text;

	void connect_event_listeners() {
		
		state_machine.event_dispatcher.sink <Event::Key_Pressed> ().connect <&State::Pause::on_key_pressed> (this);
		
	};
	
	void disconnect_event_listeners() {
		
		state_machine.event_dispatcher.sink <Event::Key_Pressed> ().disconnect <&State::Pause::on_key_pressed> (this);
		
	};
	
	void on_key_pressed(const Event::Key_Pressed& event) {
		
		if (event.key == sf::Keyboard::Escape) {
			
			state_machine.event_dispatcher.enqueue <Event::Pop_State> ();			
			
		};
		
	};
	
	void create_entities() {
		
		pause_text = {state_machine.ecs, state_machine.ecs.create()};
		auto font = state_machine.font_cache.handle(EnTT::Hashed_String {"OpenSans-Regular.ttf"});
		auto& drawable = pause_text.emplace <Component::Graphics::Drawable> (std::make_unique <sf::Text> ("PAUSE", font, 100));
		//reverse physics scale to avoid blurry text
		drawable.transform.set_scale({1.f / System::Physics::scale, 1.f / System::Physics::scale});
	
	};
	
	void destroy_entities() {
		
		pause_text.destroy();
		
	};
	
	
};
	
	
	
};