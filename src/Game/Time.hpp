#pragma once
#include <iostream>
#include <chrono>
using namespace std::literals;


namespace Time {
	


using Clock = std::chrono::steady_clock;
using Duration = std::chrono::duration <double>;
using Point = std::chrono::time_point <Clock, Duration>;



};