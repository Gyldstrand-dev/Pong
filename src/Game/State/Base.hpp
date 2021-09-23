#pragma once
#include "Time.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Event_Dispatcher.hpp"
#include "System/Physics.hpp"


namespace State {
	
	
	
class Machine;
	
	
class Base {
	
public:

	Base(State::Machine& state_machine) 
	:	state_machine {state_machine} {};

	
	virtual ~Base() {};
	virtual void push() = 0;
	virtual void pop() = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;
	virtual void update(const Time::Duration&, System::Physics&) = 0;
	
protected:

	State::Machine& state_machine;
};
	
	
	
};