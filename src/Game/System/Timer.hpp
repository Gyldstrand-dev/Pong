#pragma once
#include "EnTT/Registry.hpp"
#include "EnTT/Entity.hpp"
#include "Component/Timer.hpp"


namespace System {
	
	
	
class Timer {
	
	
public:

	void update(EnTT::Registry& ecs, const Time::Duration& timestep) {
		auto view = ecs.view <Component::Timer> ();
		for (auto entity : view) {
			auto& timer = view.get <Component::Timer> (entity);
			timer.duration -= timestep;
		};
	};

private:
	
	
};
	
	
	
};