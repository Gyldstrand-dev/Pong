#pragma once
#include "EnTT/Registry.hpp"
#include "EnTT/Entity.hpp"
#include "SFML/Window.hpp"
#include "SFML/Transform.hpp"
#include "Component/Graphics/Drawable.hpp"
#include "Component/Physics/Body.hpp"
#include "Component/UI/Button.hpp"


namespace System {
	
	
	
class Graphics {
	
	SFML::Transform transform;
	
public:

	Graphics(const float& physics_scale) {
		
		transform.set_scale({physics_scale, physics_scale});
		
	};
	
	void update_transforms_from_bodies(EnTT::Registry& ecs) {
		
		auto view = ecs.view <Component::Graphics::Drawable, Component::Physics::Body> ();
		for (auto entity : view) {
			
			auto [drawable, body] = view.get <Component::Graphics::Drawable, Component::Physics::Body> (entity);
			drawable.transform.set_position(body.get_position());
		
		};
	
	};

	void draw(EnTT::Registry& ecs, SFML::Window& window) {
		
		auto view = ecs.view <Component::Graphics::Drawable> (entt::exclude <Component::UI::Button>);
		for (auto entity : view) {
			
			auto& drawable = view.get <Component::Graphics::Drawable> (entity);
			window.draw(*drawable.pointer, transform.get() * drawable.transform.get());
		
		};	
		
		auto ui_view = ecs.view <Component::UI::Button> ();
		for (auto entity : ui_view) {
			
			auto& drawable = ecs.get <Component::Graphics::Drawable> (entity);
			window.draw(*drawable.pointer);
		
		};
		
	};
	
};
	
	
	
};