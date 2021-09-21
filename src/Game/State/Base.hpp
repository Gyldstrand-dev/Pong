#pragma once
#include "Time.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Event_Dispatcher.hpp"
#include "SFML/Window.hpp"


namespace State {
	
	
class Machine;
	
	
class Base {
	
public:

	Base(State::Machine& state_machine) 
	:	state_machine {state_machine} {};

	
	virtual ~Base() {};
	virtual void connect_event_listeners(EnTT::Event_Dispatcher&) = 0;
	virtual void disconnect_event_listeners(EnTT::Event_Dispatcher&) = 0;
	virtual void create_entities(EnTT::Registry&) = 0;
	virtual void destroy_entities(EnTT::Registry&) = 0;
	virtual void update(const Time::Duration&) = 0;
	
protected:

	State::Machine& state_machine;
};
	
	
	
};