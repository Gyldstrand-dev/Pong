#pragma once
#include "Vector_2.hpp"


namespace Event {
	
	
	
struct Mouse_Moved {
	
	Mouse_Moved(const Vector_2 <float>& position)
	:	position {position} {};
	
	Vector_2 <float> position;
	
};
	
	
	
};