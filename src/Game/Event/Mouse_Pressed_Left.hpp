#pragma once
#include "Vector_2.hpp"


namespace Event {
	
	
	
struct Mouse_Pressed_Left {
	
	Mouse_Pressed_Left(const Vector_2 <float>& position)
	:	position {position} {};
	
	Vector_2 <float> position;
	
};
	
	
	
};