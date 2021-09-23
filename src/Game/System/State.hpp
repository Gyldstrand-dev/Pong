#pragma once
#include "EnTT/Registry.hpp"
#include "EnTT/Entity.hpp"
#include "EnTT/Handle.hpp"


namespace System {
	
	
	
class State {
	
	
public:

	void draw(EnTT::Registry& ecs, SFML::Window& window) {
		
		auto view = ecs.view <Component::State> ();
		for (auto entity : view) {
			
			auto& state = view.get <Component:State> (entity);
			window.draw(*drawable.pointer, transform.get() * drawable.transform.get());
		
		};
		
	};
	
private:
	
	
};
	
	
	
};