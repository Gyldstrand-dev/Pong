#pragma once
#include "Time.hpp"
#include "Vector_2.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Entity.hpp"
#include "EnTT/Handle.hpp"
#include "EnTT/Event_Dispatcher.hpp"
#include "EnTT/Hashed_String.hpp"
#include "Box2D/World.hpp"
#include "Box2D/Debug_Draw.hpp"
#include "SFML/Window.hpp"
#include "System/Physics.hpp"
#include "System/Collision.hpp"
#include "System/Graphics.hpp"
#include "Resource/Font/Loader.hpp"
#include "Resource/Font/Cache.hpp"
#include "State/Machine.hpp"
#include "State/Intro.hpp"
#include "Event/Key_Pressed.hpp"
#include "Event/Key_Released.hpp"
#include "Event/Push_State.hpp"
#include "Event/Pop_State.hpp"
#include "Event/Mouse_Moved.hpp"
#include "Event/Mouse_Pressed_Left.hpp"
#include "Event/Exit.hpp"

#include <iostream>


class Game {

	Time::Duration timestep, rollover_time, run_time;
	Time::Point end_loop;
	Resource::Font::Cache font_cache;
	EnTT::Registry ecs;
	EnTT::Event_Dispatcher event_dispatcher;
	SFML::Window window {sf::VideoMode {1200, 800}, "Window"};
	System::Physics physics_system;
	System::Collision collision_system {event_dispatcher};
	System::Graphics graphics_system {System::Physics::scale};
	System::User_Interface user_interface {ecs, event_dispatcher};
	State::Machine state_machine {ecs, event_dispatcher, font_cache, physics_system, window};
	Box2D::Debug_Draw debug_draw {physics_system, window};
	
public:

	void close(const Event::Exit& event) {
		window.close();
	};

	Game() {
		
		initialize_time();
		physics_system.set_contact_listener(&collision_system);
		physics_system.connect(ecs);
		font_cache.load <Resource::Font::Loader> (EnTT::Hashed_String {"OpenSans-Regular.ttf"}, "OpenSans-Regular.ttf");
		event_dispatcher.sink <Event::Exit> ().connect <&Game::close> (this);
		event_dispatcher.enqueue <Event::Push_State> (std::make_unique <State::Intro> (state_machine));
		
	};

	
	void run() {
		
		while (window.is_open()) {
			
			time();
			input();
			before_physics();
			physics();
			after_physics();
			before_render();
			render();
			
		};
		
	};

private:

	void initialize_time() {
		
		timestep = 1.0s / 60;
		rollover_time = 0.0s;
		run_time = 0.0s;
		
	};
	
	void time() {
		
		Time::Point start_loop = Time::Clock::now();
		Time::Duration loop_time = start_loop - end_loop;
		if (loop_time > 0.25s) loop_time = 0.25s;
		end_loop = start_loop;
		rollover_time += loop_time;
		
	};
	
	void input() {		
		
		
		sf::Event event;
		while (window.poll_event(event)) {
			
			if (event.type == sf::Event::Closed) {
				
				event_dispatcher.trigger <Event::Exit> ();
				
			};
			
			if (event.type == sf::Event::Resized) {
				std::cout << "RESIZED \n";
			};
			
			if (event.type == sf::Event::KeyPressed) {
				
				event_dispatcher.trigger <Event::Key_Pressed> (event.key.code);
				
			};
			
			if (event.type == sf::Event::KeyReleased) {
				
				event_dispatcher.trigger <Event::Key_Released> (event.key.code);
				
			};	
			
			if (event.type == sf::Event::MouseMoved) {
				
				event_dispatcher.trigger <Event::Mouse_Moved> (Vector_2 <float> {event.mouseMove.x, event.mouseMove.y});
				
			};
			
			if (event.type == sf::Event::MouseButtonPressed) {
				
				if (event.mouseButton.button == sf::Mouse::Left) {
					event_dispatcher.trigger <Event::Mouse_Pressed_Left> (Vector_2 <float> {event.mouseButton.x, event.mouseButton.y});
				};
			
			};
					
		};

		event_dispatcher.update();
	};	
	
	void before_physics() {};
	
	void physics() {
		
		while (rollover_time >= timestep) {
			
			run_time += timestep;
			rollover_time -= timestep;
			//physics_system.update(timestep);
			//physics_system.clear_forces();
			state_machine.update_state(timestep, physics_system);
			
		};
		
	};
	
	void after_physics() {
		
		graphics_system.update_transforms_from_bodies(ecs);
		
	};
	
	void before_render() {
		
		//const double alpha {rollover_time / timestep};
		
	};
	
	void render() {
		
		window.clear();
		graphics_system.draw(ecs, window);
		//physics_system.draw();
		window.display();
		
	};
	
	
};














