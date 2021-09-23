#pragma once
#include "Time.hpp"
#include "State/Base.hpp"
#include "State/Play.hpp"
#include "State/Pause.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Handle.hpp"
#include "System/Physics.hpp"
#include "Event/Push_State.hpp"
#include "Event/Pop_State.hpp"
#include "Event/Key_Pressed.hpp"
#include "EnTT/Handle.hpp"
#include "Event/Launch_Ball.hpp"
#include <string>
#include <iostream>

namespace State {
	
	
	
class Begin_Round : public State::Base {
	
public:

	Begin_Round(State::Machine& state_machine, EnTT::Handle player, EnTT::Handle ball)
	:	Base {state_machine}, player {player}, ball {ball} {};

	void push() override {
		
		create_entities();
		
	};
	
	void pop() override {
		
		destroy_entities();
		
	};
	
	void enter() override {
		
		connect_event_listeners();
		
	};
	
	void exit() override {
		
		disconnect_event_listeners();
		
	};
	
	void update(const Time::Duration& timestep, System::Physics& physics_system) override {
		
		physics_system.update(timestep);
		physics_system.clear_forces();
		
		if (!countdown_counter) {
			
			state_machine.event_dispatcher.enqueue <Event::Launch_Ball> ();	
			state_machine.event_dispatcher.enqueue <Event::Pop_State> ();	
			
		} else {
			
			duration += timestep;
			if (duration >= 1.0s) {
				
				duration = 0.0s;
				countdown_counter--;
				
				if (countdown_counter) { 
				
					auto& text = static_cast <sf::Text&> (*countdown.get <Component::Graphics::Drawable> ().pointer);
					text.setString(std::to_string(countdown_counter));
					
				};
				
			};
			
		};
		
	};

private:

	int countdown_counter {3};
	Time::Duration duration {0.0s};
	EnTT::Handle countdown, player, ball;
	
	void connect_event_listeners() {
		
		state_machine.event_dispatcher.sink <Event::Key_Pressed> ().connect <&State::Begin_Round::on_key_pressed> (this);
		state_machine.event_dispatcher.sink <Event::Launch_Ball> ().connect <&State::Begin_Round::on_launch_ball> (this);
		
	};
	
	void disconnect_event_listeners() {
		
		state_machine.event_dispatcher.sink <Event::Key_Pressed> ().disconnect <&State::Begin_Round::on_key_pressed> (this);
		state_machine.event_dispatcher.sink <Event::Launch_Ball> ().disconnect <&State::Begin_Round::on_launch_ball> (this);
		
	};
	
	void on_key_pressed(const Event::Key_Pressed& event) {
		
		if (event.key == sf::Keyboard::Escape) {
			
			state_machine.event_dispatcher.enqueue <Event::Push_State> (std::make_unique <State::Pause> (state_machine));
			
		};
		
		
		if (event.key == sf::Keyboard::W) {
			
			auto& body = player.get <Component::Physics::Body> ();
			body.set_linear_velocity({0.f, -10.f});
			
		};
		
		if (event.key == sf::Keyboard::S) {
			
			auto& body = player.get <Component::Physics::Body> ();
			body.set_linear_velocity({0.f, 10.f});
		
		};
		
	};
	
	void on_launch_ball(const Event::Launch_Ball&) {
		
		auto& ball_body = ball.get <Component::Physics::Body> ();
		ball_body.set_linear_velocity({10.f, 0.f});
	
	};
	
	void create_entities() {
	
		create_countdown();
		
	};
	
	void destroy_entities() {
		
		countdown.destroy();
		
	};
	
	void create_countdown() {
		
		countdown = {state_machine.ecs, state_machine.ecs.create()};
		auto font = state_machine.font_cache.handle(EnTT::Hashed_String {"OpenSans-Regular.ttf"});
		auto& drawable = countdown.emplace <Component::Graphics::Drawable> (std::make_unique <sf::Text> ("3", font, 100));
		auto& text = static_cast <sf::Text&> (*drawable.pointer);
		text.setFillColor({255, 255, 255, 255});
		auto bounds = text.getLocalBounds();
		auto window_size = state_machine.window.get_size();
		drawable.transform.set_origin({bounds.width / 2.f, bounds.height / 2.f});
		drawable.transform.set_position({window_size.x / System::Physics::scale / 2.f, 3.f});
		//reverse physics scale to avoid blurry text
		drawable.transform.set_scale({1.f / System::Physics::scale, 1.f / System::Physics::scale});
	};
	
};
	
	
	
};