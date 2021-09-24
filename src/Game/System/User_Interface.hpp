#pragma once
#include "Vector_2.hpp"
#include "Resource/Font/Cache.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Entity.hpp"
#include "EnTT/Event_Dispatcher.hpp"
#include "Event/Mouse_Pressed_Left.hpp"
#include "Event/Mouse_Moved.hpp"
#include "System/Physics.hpp"
#include "Component/Graphics/Drawable.hpp"
#include "Component/UI/Button.hpp"
#include "SFML/Button.hpp"
#include <unordered_map>


namespace System {
	
	
	
class User_Interface {
	
	EnTT::Registry& ecs;
	EnTT::Entity active_button {entt::null};
	
public:

	
	User_Interface(EnTT::Registry& ecs, EnTT::Event_Dispatcher& event_dispatcher)
	:	ecs {ecs} {

		ecs.on_construct <Component::UI::Button> ().connect <&System::User_Interface::on_construct_button> (this);
		event_dispatcher.sink <Event::Mouse_Moved> ().connect <&System::User_Interface::on_mouse_moved> (this);
		event_dispatcher.sink <Event::Mouse_Pressed_Left> ().connect <&System::User_Interface::on_mouse_pressed_left> (this);
	
	};

private:
	
	void on_construct_button(EnTT::Registry& ecs, EnTT::Entity entity) {
		
		auto& component = ecs.get <Component::UI::Button> (entity);
		auto& drawable = static_cast <SFML::Button&> (*ecs.emplace <Component::Graphics::Drawable> (entity, std::make_unique <SFML::Button> ()).pointer);
		drawable.set_position(component.position);
		drawable.set_size(component.size);
		drawable.set_color(component.color);
		drawable.set_string(component.string);
		drawable.set_font(component.font);
		drawable.set_font_size(component.font_size);
		drawable.set_font_color(component.font_color);		
		
	};
	

	void on_mouse_moved(const Event::Mouse_Moved& event) {
		
		if (active_button != entt::null && ecs.valid(active_button)) {
			
			auto& button = ecs.get <Component::UI::Button> (active_button);
			auto& drawable = static_cast <SFML::Button&> (*ecs.get <Component::Graphics::Drawable> (active_button).pointer);
			if (!drawable.contains(event.position)) {
				if (button.on_mouse_exit) button.on_mouse_exit();
				active_button = entt::null;
				return;
			};
			
		} else {
		
			auto view = ecs.view <Component::UI::Button> ();
			for (auto entity : view) {
				
				auto& button = ecs.get <Component::UI::Button> (entity);
				auto& drawable = static_cast <SFML::Button&> (*ecs.get <Component::Graphics::Drawable> (entity).pointer);
				if (drawable.contains(event.position)) {
					if (button.on_mouse_enter) button.on_mouse_enter();
					active_button = entity;
					return;
				};
		
			};
			
		};
		
	};
	
	void on_mouse_pressed_left(const Event::Mouse_Pressed_Left& event) {
		
		if (active_button == entt::null || !ecs.valid(active_button)) return;
		
		auto& button = ecs.get <Component::UI::Button> (active_button);
		auto& drawable = static_cast <SFML::Button&> (*ecs.get <Component::Graphics::Drawable> (active_button).pointer);
		if (drawable.contains(event.position)) {
			if (button.on_mouse_pressed_left) button.on_mouse_pressed_left();
		};
		
	};
	
};
	
	
	
}; 