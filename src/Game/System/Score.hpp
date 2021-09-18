#pragma once
#include "EnTT/Registry.hpp"
#include "EnTT/Entity.hpp"
#include "Component/Score.hpp"
#include "Component/Timer.hpp"
#include "Component/Graphics/Drawable.hpp"
#include <iostream>


namespace System {
	
	
	
class Score {
	
	
public:

	void update(EnTT::Registry& ecs) {
		auto view = ecs.view <Component::Timer, Component::Score, Component::Graphics::Drawable> ();
		for (auto entity : view) {
			auto [timer, score, drawable] = view.get <Component::Timer, Component::Score, Component::Graphics::Drawable> (entity);
			if (timer.duration < 0.0s) {
				ecs.erase <Component::Timer> (entity);
			} else {
				auto& text = static_cast <sf::Text&> (*drawable.pointer);
				text.setFillColor({255, 255, 255, timer.duration.count() * (255 / 5.f)});
			};
		};
	};

private:
	
	
};
	
	
	
};