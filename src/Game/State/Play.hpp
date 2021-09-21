#pragma once
#include "State/Base.hpp"
#include "State/End_Round.hpp"
#include "State/Begin_Round.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Handle.hpp"
#include "SFML/Window.hpp"
#include "Box2D/Body.hpp"
#include "Box2D/Shape.hpp"
#include "Box2D/Body_Builder.hpp"
#include "Box2D/Fixture_Builder.hpp"
#include "System/Physics.hpp"
#include "Event/Push_State.hpp"
#include "Event/Pop_State.hpp"
#include "Event/Key_Pressed.hpp"
#include "Event/Key_Released.hpp"
#include "Event/Scored.hpp"
#include "Event/Reset.hpp"
#include "User_Data.hpp"
#include "Vector_2.hpp"
#include "Component/Score.hpp"
#include <iostream>


namespace State {
	
	
	
class Play : public State::Base {
	
public:

	Play(State::Machine& state_machine)
	:	Base {state_machine} {
		
	};

	void connect_event_listeners(EnTT::Event_Dispatcher& event_dispatcher) override {
		
		event_dispatcher.sink <Event::Key_Pressed> ().connect <&State::Play::on_key_pressed> (this);
		event_dispatcher.sink <Event::Scored> ().connect <&State::Play::on_scored> (this);
		event_dispatcher.sink <Event::Reset> ().connect <&State::Play::on_reset> (this);
		event_dispatcher.sink <Event::Launch_Ball> ().connect <&State::Play::on_launch_ball> (this);
	
	};
	
	void disconnect_event_listeners(EnTT::Event_Dispatcher& event_dispatcher) override {
		
		event_dispatcher.sink <Event::Key_Pressed> ().disconnect <&State::Play::on_key_pressed> (this);
		event_dispatcher.sink <Event::Scored> ().disconnect <&State::Play::on_scored> (this);
		event_dispatcher.sink <Event::Reset> ().disconnect <&State::Play::on_reset> (this);
		event_dispatcher.sink <Event::Launch_Ball> ().disconnect <&State::Play::on_launch_ball> (this);
	
	};
	
	void create_entities(EnTT::Registry& ecs) override {
		
		create_player(ecs);
		create_opponent(ecs);
		create_ball(ecs);
		create_border(ecs);
		create_scoreboard(ecs);
		
	};
	
	void destroy_entities(EnTT::Registry& ecs) override {

		(void) ecs;
		player.destroy();
		opponent.destroy();
		ball.destroy();
		border.destroy();
		scoreboard.destroy();
		
	};
	
	void update(const Time::Duration& timestep) override {
		
		(void) timestep;
	};
	
	void on_key_pressed(const Event::Key_Pressed& event) {
		
		auto& body = player.get <Component::Physics::Body> ();
		
		if (event.key == sf::Keyboard::W) {
			
			body.set_linear_velocity({0.f, -10.f});
			
		};
		
		if (event.key == sf::Keyboard::S) {
			
			body.set_linear_velocity({0.f, 10.f});
		
		};
		
	};
	
private:
	
	EnTT::Handle 
		player, 
		opponent,
		ball,
		border,
		scoreboard;
		
	User_Data 
		player_user_data {User_Data::Type::Player},
		opponent_user_data {User_Data::Type::Opponent},
		ball_user_data {User_Data::Type::Ball},
		border_user_data {User_Data::Type::Border};
		
	void create_player(EnTT::Registry& ecs) {

		player = {ecs, ecs.create()};
		auto window_size = state_machine.window.get_size();
		auto& body = player.emplace <Component::Physics::Body> (state_machine.physics_system.create_body(Box2D::Body_Builder{}
			.set_type(Box2D::Body::Type::Kinematic)
			.set_position({1.f, window_size.y / System::Physics::scale / 2.f})
			.build()));
		body.create_fixture(Box2D::Fixture_Builder{}
			.set_shape(Box2D::Shape::Polygon({
				{-0.125f, -1.25f},
				{0.125f, -1.25f},
				{0.2f, -0.25f},
				{0.2f, 0.25f},
				{0.125f, 1.25f},
				{-0.125f, 1.25f}}))
			.set_density(1.f)
			.set_friction(0.f)
			.set_user_data(&player_user_data)
			.build());
		auto& drawable = player.emplace <Component::Graphics::Drawable> (std::make_unique <sf::RectangleShape> (sf::Vector2f {0.25f, 2.5f}));
		drawable.transform.set_origin({0.125f, 1.25f});
		
	};
	
	void create_opponent(EnTT::Registry& ecs) {

		opponent = {ecs, ecs.create()};
		auto window_size = state_machine.window.get_size();
		auto& body = opponent.emplace <Component::Physics::Body> (state_machine.physics_system.create_body(Box2D::Body_Builder{}
			.set_type(Box2D::Body::Type::Kinematic)
			.set_position({window_size.x / System::Physics::scale - 1.f, window_size.y / System::Physics::scale / 2.f})
			.set_angle(180.f * (M_PI / 180.f))
			.build()));
		body.create_fixture(Box2D::Fixture_Builder{}
			.set_shape(Box2D::Shape::Polygon({
				{-0.125f, -1.25f},
				{0.125f, -1.25f},
				{0.2f, -0.25f},
				{0.2f, 0.25f},
				{0.125f, 1.25f},
				{-0.125f, 1.25f}}))
			.set_density(1.f)
			.set_friction(0.f)
			.set_user_data(&player_user_data)
			.build());
		auto& drawable = opponent.emplace <Component::Graphics::Drawable> (std::make_unique <sf::RectangleShape> (sf::Vector2f {0.25f, 2.5f}));
		drawable.transform.set_origin({0.125f, 1.25f});
	
	};
	
	void create_ball(EnTT::Registry& ecs) {
		
		ball = {ecs, ecs.create()};
		auto window_size = state_machine.window.get_size();
		auto& body = ball.emplace <Component::Physics::Body> (state_machine.physics_system.create_body(Box2D::Body_Builder{}
			.set_type(Box2D::Body::Type::Dynamic)
			.set_position({window_size.x / System::Physics::scale / 2.f, window_size.y / System::Physics::scale / 2.f})
			.build()));
		body.create_fixture(Box2D::Fixture_Builder{}
			.set_shape(Box2D::Shape::Circle(0.25f))
			.set_density(1.0f)
			.set_friction(0.f)
			.set_restitution(1.1f)
			.set_user_data(&ball_user_data)
			.build());
		auto& drawable = ball.emplace <Component::Graphics::Drawable> (std::make_unique <sf::CircleShape> (0.25f));
		drawable.transform.set_origin({0.25f, 0.25f});
	
	};
	
	void create_border(EnTT::Registry& ecs) {
		
		border = {ecs, ecs.create()};
		auto& body = border.emplace <Component::Physics::Body> (state_machine.physics_system.create_body(Box2D::Body_Builder{}
			.set_type(Box2D::Body::Type::Static)
			.build()));		
		auto window_size = state_machine.window.get_size();
		body.create_fixture(Box2D::Fixture_Builder{}
			.set_shape(Box2D::Shape::Loop({
				{0.f, 0.f},
				{0.f, window_size.y / System::Physics::scale},
				{window_size.x / System::Physics::scale, window_size.y / System::Physics::scale},
				{window_size.x / System::Physics::scale, 0.f}}))
			.set_density(1.f)
			.set_user_data(&border_user_data)
			.build());
	
	};
		
	void create_scoreboard(EnTT::Registry& ecs) {
		
		scoreboard = {ecs, ecs.create()};
		scoreboard.emplace <Component::Score> ();
		auto font = state_machine.font_cache.handle(EnTT::Hashed_String {"OpenSans-Regular.ttf"});
		auto& drawable = scoreboard.emplace <Component::Graphics::Drawable> (std::make_unique <sf::Text> ("0 | 0", font, 100));
		auto& text = static_cast <sf::Text&> (*drawable.pointer);
		text.setFillColor({255, 255, 255, 0});
		auto bounds = text.getLocalBounds();
		auto window_size = state_machine.window.get_size();
		drawable.transform.set_origin({bounds.width / 2.f, bounds.height / 2.f});
		drawable.transform.set_position({window_size.x / System::Physics::scale / 2.f, 3.f});
		//reverse physics scale to avoid blurry text
		drawable.transform.set_scale({1.f / System::Physics::scale, 1.f / System::Physics::scale});
	
	};
 	
	void on_launch_ball(const Event::Launch_Ball& event) {
		
		(void) event;
		auto& ball_body = ball.get <Component::Physics::Body> ();
		ball_body.set_linear_velocity({10.f, 0.f});
	
	};
		
	void on_scored(const Event::Scored& event) {
		
		auto& player_body = player.get <Component::Physics::Body> ();
		player_body.set_linear_velocity({0.f, 0.f});
		auto& opponent_body = opponent.get <Component::Physics::Body> ();
		opponent_body.set_linear_velocity({0.f, 0.f});
		auto& ball_body = ball.get <Component::Physics::Body> ();
		ball_body.set_linear_velocity({0.f, 0.f});
		auto& score = scoreboard.get <Component::Score> ();
		auto& text = static_cast <sf::Text&> (*scoreboard.get <Component::Graphics::Drawable> ().pointer);
		
		if (event.type == User_Data::Type::Player) {
			
			score.player++;
		
		};
		
		if (event.type == User_Data::Type::Opponent) {
			
			score.opponent++;
		
		};
		
		text.setString(std::to_string(score.player) + " | " + std::to_string(score.opponent));
		state_machine.event_dispatcher.sink <Event::Key_Pressed> ().disconnect <&State::Play::on_key_pressed> (this);
		state_machine.event_dispatcher.enqueue <Event::Push_State> (std::make_unique <State::End_Round> (state_machine, text));
	};
	
	void on_reset(const Event::Reset& event) {
		
		(void) event;
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
		state_machine.event_dispatcher.sink <Event::Key_Pressed> ().connect <&State::Play::on_key_pressed> (this);
		state_machine.event_dispatcher.enqueue <Event::Push_State> (std::make_unique <State::Begin_Round> (state_machine));
	
	};
};
	
	
	
};