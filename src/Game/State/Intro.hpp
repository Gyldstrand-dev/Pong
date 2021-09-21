#pragma once
#include "State/Base.hpp"
#include "State/Main_Menu.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Handle.hpp"
#include "System/Physics.hpp"
#include "Event/Key_Pressed.hpp"
#include "Event/Push_State.hpp"
#include "Event/Pop_State.hpp"

namespace State {
	
	
	
class Intro : public State::Base {
	
public:

	Intro(State::Machine& state_machine)
	:	Base {state_machine} {};

	void connect_event_listeners(EnTT::Event_Dispatcher& event_dispatcher) override {
		
		event_dispatcher.sink <Event::Key_Pressed> ().connect <&State::Intro::enter_main_menu> (this);
	
	};
	
	void disconnect_event_listeners(EnTT::Event_Dispatcher& event_dispatcher) override {
		
		event_dispatcher.sink <Event::Key_Pressed> ().disconnect <&State::Intro::enter_main_menu> (this);
	
	};
	
	void create_entities(EnTT::Registry& ecs) override {
		
		intro_text = {ecs, ecs.create()};
		auto font = state_machine.font_cache.handle(EnTT::Hashed_String {"OpenSans-Regular.ttf"});
		auto& drawable = intro_text.emplace <Component::Graphics::Drawable> (std::make_unique <sf::Text> ("INTRO", font, 100));
		//reverse physics scale to avoid blurry text
		drawable.transform.set_scale({1.f / System::Physics::scale, 1.f / System::Physics::scale});
	
	};
	
	void destroy_entities(EnTT::Registry& ecs) override {
		
		(void) ecs;
		intro_text.destroy();
	
	};
	
	void update(const Time::Duration& timestep) override {
		
		(void) timestep;
		
	};
	
	void enter_main_menu(const Event::Key_Pressed& event) {
		
		(void) event;
		state_machine.event_dispatcher.enqueue <Event::Pop_State> ();
		state_machine.event_dispatcher.enqueue <Event::Push_State> (std::make_unique <State::Main_Menu> (state_machine));
	};
	
private:
	
	EnTT::Handle intro_text;
};
	
	
	
};