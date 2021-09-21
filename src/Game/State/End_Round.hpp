#pragma once
#include "Time.hpp"
#include "State/Base.hpp"
#include "State/Play.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Handle.hpp"
#include "System/Physics.hpp"
#include "Event/Push_State.hpp"
#include "Event/Pop_State.hpp"
#include "Event/Reset.hpp"

namespace State {
	
	
	
class End_Round : public State::Base {
	
public:

	End_Round(State::Machine& state_machine, sf::Text& scoreboard_text)
:	Base {state_machine}, scoreboard_text {scoreboard_text} {};

	void connect_event_listeners(EnTT::Event_Dispatcher& event_dispatcher) override {
		
		(void) event_dispatcher;
		
	};
	
	void disconnect_event_listeners(EnTT::Event_Dispatcher& event_dispatcher) override {
		
		(void) event_dispatcher;
		
	};
	
	void create_entities(EnTT::Registry& ecs) override {
		
		(void) ecs;
	
	};
	
	void destroy_entities(EnTT::Registry& ecs) override {
		
		(void) ecs;
	};
	
	void update(const Time::Duration& timestep) override {
		
		current_duration += timestep;
		
		if (current_duration >= duration) {
			
			state_machine.event_dispatcher.enqueue <Event::Pop_State> ();
			state_machine.event_dispatcher.enqueue <Event::Reset> ();
			
		} else {
			
			unsigned char fade = static_cast <unsigned char> (255 - current_duration.count() * (255 / duration.count()));
			scoreboard_text.setFillColor({255, 255, 255, fade});
			
		};
	};

	
private:
	
	sf::Text& scoreboard_text;
	Time::Duration duration {3.0s}, current_duration {0.0s};
};
	
	
	
};