#pragma once
#include "Time.hpp"
#include "State/Base.hpp"
#include "State/Play.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Handle.hpp"
#include "System/Physics.hpp"
#include "Event/Push_State.hpp"
#include "Event/Pop_State.hpp"
#include "Event/Launch_Ball.hpp"
#include <string>
#include <iostream>

namespace State {
	
	
	
class Begin_Round : public State::Base {
	
public:

	Begin_Round(State::Machine& state_machine)
	:	Base {state_machine} {};

	void connect_event_listeners(EnTT::Event_Dispatcher& event_dispatcher) override {
		
		(void) event_dispatcher;
		
	};
	
	void disconnect_event_listeners(EnTT::Event_Dispatcher& event_dispatcher) override {
		
		(void) event_dispatcher;
		
	};
	
	void create_entities(EnTT::Registry& ecs) override {
		
		(void) ecs;
		create_countdown(ecs);
		
	};
	
	void destroy_entities(EnTT::Registry& ecs) override {
		
		(void) ecs;
		countdown.destroy();
		
	};
	
	void update(const Time::Duration& timestep) override {
		
		if (!countdown_int) {
			
			state_machine.event_dispatcher.enqueue <Event::Pop_State> ();			
			state_machine.event_dispatcher.enqueue <Event::Launch_Ball> ();			
			
		} else {
			
			duration += timestep;
			if (duration >= 1.0s) {
				
				duration = 0.0s;
				countdown_int--;
				
				if (countdown_int) { 
				
					auto& text = static_cast <sf::Text&> (*countdown.get <Component::Graphics::Drawable> ().pointer);
					text.setString(std::to_string(countdown_int));
					
				};
			};
		};
		
	};
	
	void create_countdown(EnTT::Registry& ecs) {
		
		countdown = {ecs, ecs.create()};
		auto font = state_machine.font_cache.handle(EnTT::Hashed_String {"OpenSans-Regular.ttf"});
		auto& drawable = countdown.emplace <Component::Graphics::Drawable> (std::make_unique <sf::Text> ("3", font, 100));
		auto& text = static_cast <sf::Text&> (*drawable.pointer);
		text.setFillColor({255, 255, 255, 255});
		auto bounds = text.getLocalBounds();
		auto window_size = state_machine.window.get_size();
		drawable.transform.set_origin({bounds.width / 2.f, bounds.height / 2.f});
		drawable.transform.set_position({window_size.x / System::Physics::scale / 2.f, 3.f});
		//reverse physics scale to avoid blurry text
		drawable.transform.set_scale({1.f / System::Physics::scale, 1.f / System::Physics::scale});
	};

	
private:

	int countdown_int {3};
	EnTT::Handle countdown;
	Time::Duration duration {0.0s};
	
};
	
	
	
};