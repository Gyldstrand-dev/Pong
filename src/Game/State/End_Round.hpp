#pragma once
#include "Time.hpp"
#include "State/Base.hpp"
#include "State/Play.hpp"
#include "State/Begin_Round.hpp"
#include "State/Pause.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Handle.hpp"
#include "System/Physics.hpp"
#include "Event/Push_State.hpp"
#include "Event/Pop_State.hpp"
#include "Event/Key_Pressed.hpp"
#include "Event/Reset.hpp"
#include <iostream>

namespace State {
	
	
	
class End_Round : public State::Base {
	
	EnTT::Handle player, opponent, ball, scoreboard;
	Time::Duration duration {3.0s}, current_duration {0.0s};
	
public:

	End_Round(State::Machine& state_machine, EnTT::Handle player, EnTT::Handle opponent, EnTT::Handle ball, EnTT::Handle scoreboard)
	:	Base {state_machine}, player {player}, opponent {opponent}, ball {ball}, scoreboard {scoreboard} {};

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
	
	void update(const Time::Duration& timestep, System::Physics&) override {
		
		current_duration += timestep;
		
		if (current_duration >= duration) {
			
			state_machine.event_dispatcher.enqueue <Event::Pop_State> ();
			state_machine.event_dispatcher.enqueue <Event::Reset> ();
			
		} else {
			
			auto& scoreboard_text = static_cast <sf::Text&> (*scoreboard.get <Component::Graphics::Drawable> ().pointer);
			unsigned char fade = static_cast <unsigned char> (255 - current_duration.count() * (255 / duration.count()));
			scoreboard_text.setFillColor({255, 255, 255, fade});
			
		};
	};

	
private:

	void connect_event_listeners() {
		
		state_machine.event_dispatcher.sink <Event::Key_Pressed> ().connect <&State::End_Round::on_key_pressed> (this);
		state_machine.event_dispatcher.sink <Event::Reset> ().connect <&State::End_Round::on_reset> (this);
		
	};
	
	void disconnect_event_listeners() {
		
		state_machine.event_dispatcher.sink <Event::Key_Pressed> ().disconnect <&State::End_Round::on_key_pressed> (this);
		state_machine.event_dispatcher.sink <Event::Reset> ().disconnect <&State::End_Round::on_reset> (this);
	
	};
	
	void create_entities() {};
	
	void destroy_entities() {};
	
	void on_key_pressed(const Event::Key_Pressed& event) {
		
		if (event.key == sf::Keyboard::Escape) {
			
			state_machine.event_dispatcher.enqueue <Event::Push_State> (std::make_unique <State::Pause> (state_machine));
			
		};
		
	};
	
	void on_reset(const Event::Reset&) {
		
		auto window_size = state_machine.window.get_size();
		auto& player_body = player.get <Component::Physics::Body> ();
		auto& opponent_body = opponent.get <Component::Physics::Body> ();
		auto& ball_body = ball.get <Component::Physics::Body> ();
		player_body.set_transform({1.f, window_size.y / System::Physics::scale / 2.f});
		player_body.set_linear_velocity({0.f, 0.f});
		opponent_body.set_transform({window_size.x / System::Physics::scale - 1.f, window_size.y / System::Physics::scale / 2.f}, opponent_body.get_angle());
		opponent_body.set_linear_velocity({0.f, 0.f});
		ball_body.set_transform({window_size.x / System::Physics::scale / 2.f, window_size.y / System::Physics::scale / 2.f});
		ball_body.set_linear_velocity({0.f, 0.f});
		ball_body.set_angular_velocity(0.f);
		auto& scoreboard_text = static_cast <sf::Text&> (*scoreboard.get <Component::Graphics::Drawable> ().pointer);
		scoreboard_text.setFillColor({255, 255, 255, 0});
		state_machine.event_dispatcher.enqueue <Event::Push_State> (std::make_unique <State::Begin_Round> (state_machine, player, ball));
	
	};

};
	
	
	
};