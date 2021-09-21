#pragma once
#include "State/Base.hpp"
#include <memory>


namespace Event {
	
	
	
struct Push_State {
	
	std::unique_ptr <State::Base> state;
	
};
	
	
	
};