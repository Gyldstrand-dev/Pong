#pragma once
#include "State/Base.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Event_Dispatcher.hpp"
#include "System/Physics.hpp"
#include "System/User_Interface.hpp"
#include "Resource/Font/Cache.hpp"
#include "Event/Push_State.hpp"
#include "Event/Pop_State.hpp"
#include <vector>
#include <iostream>


namespace State {
	
	
	
class Machine {
	
	
	std::vector <std::unique_ptr <State::Base>> states;
	
public:

	EnTT::Registry& ecs;
	EnTT::Event_Dispatcher& event_dispatcher;
	Resource::Font::Cache& font_cache;
	System::Physics& physics_system;
	SFML::Window& window;

	Machine(EnTT::Registry& ecs, EnTT::Event_Dispatcher& event_dispatcher, Resource::Font::Cache& font_cache, System::Physics& physics_system, SFML::Window& window) 
	:	ecs {ecs}, event_dispatcher {event_dispatcher}, font_cache {font_cache}, physics_system {physics_system}, window {window} {

			event_dispatcher.sink <Event::Push_State> ().connect <&State::Machine::push_state> (this);
			event_dispatcher.sink <Event::Pop_State> ().connect <&State::Machine::pop_state> (this);
	
	};
	
	void update_state(const Time::Duration& timestep, System::Physics& physics_system) {
		
		if (!states.empty()) {
			
			states.back()->update(timestep, physics_system);
			
		};
		
	};


private:
	
	void push_state(Event::Push_State& event) {
		
		if (!states.empty()) {
			
			states.back()->exit();
			
		};
		
		states.push_back(std::move(event.state));
		states.back()->push();
		states.back()->enter();
	};
	
	void pop_state(const Event::Pop_State&) {
		
		if (!states.empty()) {
			
			states.back()->exit();
			states.back()->pop();
			states.pop_back();
			
			if (!states.empty()) {
			
				states.back()->enter();
				
			};
			
		};
		
	};
	
	
};
	
	
	
};