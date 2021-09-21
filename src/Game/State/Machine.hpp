#pragma once
#include "State/Base.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Event_Dispatcher.hpp"
#include "System/Physics.hpp"
#include "Resource/Font/Cache.hpp"
#include "Event/Push_State.hpp"
#include "Event/Pop_State.hpp"
#include <vector>


namespace State {
	
	
	
class Machine {
	
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
	
	void push_state(Event::Push_State& event) {
		states.push_back(std::move(event.state));
		states.back()->create_entities(ecs);
		states.back()->connect_event_listeners(event_dispatcher);
	};
	
	void pop_state(const Event::Pop_State& event) {
		
		(void) event;
		if (!states.empty()) {
			
			states.back()->disconnect_event_listeners(event_dispatcher);
			states.back()->destroy_entities(ecs);
			states.pop_back();
			
		};
	};
	
	void update_states(const Time::Duration& timestep) {
		for (auto& state : states) {
			state->update(timestep);
		};
	};

private:
	
	std::vector <std::unique_ptr <State::Base>> states;
	
};
	
	
	
};