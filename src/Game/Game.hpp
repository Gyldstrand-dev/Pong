#pragma once
#include "Time.hpp"
#include "Vector_2.hpp"
#include "User_Data.hpp"
#include "Box2D/World.hpp"
#include "Box2D/Debug_Draw.hpp"
#include "Box2D/Shape.hpp"
#include "Box2D/Body.hpp"
#include "Box2D/Body_Builder.hpp"
#include "Box2D/Fixture_Builder.hpp"
#include "Box2D/Contact_Listener.hpp"
#include "SFML/Window.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Entity.hpp"
#include "EnTT/Handle.hpp"
#include "EnTT/Event_Dispatcher.hpp"
#include "Component/Physics/Body.hpp"
#include "Component/Graphics/Drawable.hpp"
#include "Component/Score.hpp"
#include "Component/Timer.hpp"
#include "System/Physics.hpp"
#include "System/Graphics.hpp"
#include "System/Timer.hpp"
#include "System/Score.hpp"
#include "Event/Scored.hpp"
#include <SFML/Graphics/Font.hpp>
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>

#include <iostream>


class Game {

	Time::Duration timestep, rollover_time, run_time;
	Time::Point end_loop;
	SFML::Window window {sf::VideoMode {1200, 800}, "Window"};
	EnTT::Registry ecs;
	EnTT::Event_Dispatcher event_dispatcher;
	EnTT::Handle 
		player {ecs, ecs.create()}, 
		opponent {ecs, ecs.create()},
		ball {ecs, ecs.create()},
		border {ecs, ecs.create()},
		scoreboard {ecs, ecs.create()};
	System::Physics physics_system;
	System::Graphics graphics_system {physics_system.scale};
	System::Timer timer_system;
	System::Score score_system;
	Box2D::Debug_Draw debug_draw {physics_system, window};
	User_Data player_user_data {User_Data::Type::Player};
	User_Data opponent_user_data {User_Data::Type::Opponent};
	User_Data ball_user_data {User_Data::Type::Ball};
	User_Data border_user_data {User_Data::Type::Border};
	Box2D::Contact_Listener contact_listener {event_dispatcher};
	sf::Font font;
	
public:

	Game() {
		physics_system.set_contact_listener(&contact_listener);
		event_dispatcher.sink <Event::Scored> ().connect <&Game::on_scored> (this);
		font.loadFromFile("C:/DEV/projects/SFML/Pong/src/Game/Resource/Font/OpenSans-Regular.ttf");
		
		initialize_time();
		create_player();
		create_opponent();
		create_ball();
		create_border();
		create_scoreboard();
		reset();
		
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

	void reset() {
		auto window_size = window.get_size();
		auto& player_body = player.get <Component::Physics::Body> ();
		auto& opponent_body = opponent.get <Component::Physics::Body> ();
		auto& ball_body = ball.get <Component::Physics::Body> ();
		player_body.set_transform({1.f, window_size.y / physics_system.scale / 2.f});
		player_body.set_linear_velocity({0.f, 0.f});
		opponent_body.set_transform({window_size.x / physics_system.scale - 1.f, window_size.y / physics_system.scale / 2.f}, opponent_body.get_angle());
		opponent_body.set_linear_velocity({0.f, 0.f});
		ball_body.set_transform({window_size.x / physics_system.scale / 2.f, window_size.y / physics_system.scale / 2.f});
		ball_body.set_linear_velocity({0.f, 0.f});
		ball_body.set_angular_velocity(0.f);
	};

	void create_player() {

		auto window_size = window.get_size();
		auto& body = player.emplace <Component::Physics::Body> (physics_system.create_body(Box2D::Body_Builder{}
			.set_type(Box2D::Body::Type::Kinematic)
			.set_position({1.f, window_size.y / physics_system.scale / 2.f})
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
	
	void create_opponent() {

		auto window_size = window.get_size();
		auto& body = opponent.emplace <Component::Physics::Body> (physics_system.create_body(Box2D::Body_Builder{}
			.set_type(Box2D::Body::Type::Kinematic)
			.set_position({window_size.x / physics_system.scale - 1.f, window_size.y / physics_system.scale / 2.f})
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
	
	void create_ball() {
		
		auto window_size = window.get_size();
		auto& body = ball.emplace <Component::Physics::Body> (physics_system.create_body(Box2D::Body_Builder{}
			.set_type(Box2D::Body::Type::Dynamic)
			.set_position({window_size.x / physics_system.scale / 2.f, window_size.y / physics_system.scale / 2.f})
			.set_linear_velocity({10.f, 0.f})
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
	
	void create_border() {
		
		auto& body = border.emplace <Component::Physics::Body> (physics_system.create_body(Box2D::Body_Builder{}
			.set_type(Box2D::Body::Type::Static)
			.build()));		
		auto window_size = window.get_size();
		body.create_fixture(Box2D::Fixture_Builder{}
			.set_shape(Box2D::Shape::Loop({
				{0.f, 0.f},
				{0.f, window_size.y / physics_system.scale},
				{window_size.x / physics_system.scale, window_size.y / physics_system.scale},
				{window_size.x / physics_system.scale, 0.f}}))
			.set_density(1.f)
			.set_user_data(&border_user_data)
			.build());
	};	
	
	void create_scoreboard() {
		scoreboard.emplace <Component::Score> ();
		auto& drawable = scoreboard.emplace <Component::Graphics::Drawable> (std::make_unique <sf::Text> ("0 | 0", font, 100));
		auto& text = static_cast <sf::Text&> (*drawable.pointer);
		text.setFillColor({255, 255, 255, 0});
		auto bounds = text.getLocalBounds();
		auto window_size = window.get_size();
		drawable.transform.set_origin({bounds.width / 2.f, bounds.height / 2.f});
		drawable.transform.set_position({window_size.x / physics_system.scale / 2.f, 3.f});
		//reverse physics scale to avoid blurry text
		drawable.transform.set_scale({1.f / physics_system.scale, 1.f / physics_system.scale});
	};

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
		
		event_dispatcher.update();
		
		sf::Event event;
		while (window.poll_event(event)) {
			
			if (event.type == sf::Event::Closed) {
				window.close();
			};	
			
			if (event.type == sf::Event::KeyPressed) {
				
				if (event.key.code == sf::Keyboard::W) {
					auto& player_body = player.get <Component::Physics::Body> ();
					player_body.set_linear_velocity({0.f, -10.f});
				};
				
				if (event.key.code == sf::Keyboard::S) {
					auto& player_body = player.get <Component::Physics::Body> ();
					player_body.set_linear_velocity({0.f, 10.f});
				};
				
				if (event.key.code == sf::Keyboard::Space) {
					auto& ball_body = ball.get <Component::Physics::Body> ();
					ball_body.set_linear_velocity({-10.f, 0.f});
				};				
			};		
		};

		auto& opponent_body = opponent.get <Component::Physics::Body> ();
		auto& ball_body = ball.get <Component::Physics::Body> ();
		auto opponent_position = opponent_body.get_position();
		auto ball_position = ball_body.get_position();
		if (ball_position.y > opponent_position.y) {
			opponent_body.set_linear_velocity({0.f, 10.f});
		};
		if (ball_position.y < opponent_position.y) {
			opponent_body.set_linear_velocity({0.f, -10.f});
		};
		
	};	
	
	void before_physics() {
		auto& body = player.get <Component::Physics::Body> ();
		auto position = body.get_position();
		if (position.y < 0.f) {
			body.set_transform({1.f, 0.f});
		};
		if (position.y > window.get_size().y / physics_system.scale) {
			body.set_transform({1.f, window.get_size().y / physics_system.scale});
		};
	};
	
	void physics() {
		while (rollover_time >= timestep) {
			run_time += timestep;
			rollover_time -= timestep;
			timer_system.update(ecs, timestep);
			physics_system.update(timestep);
			physics_system.clear_forces();			
		};
	};
	
	void after_physics() {
		graphics_system.update_transforms_from_bodies(ecs);
		score_system.update(ecs);
	};
	
	void before_render() {
		const double alpha = rollover_time / timestep;
		(void) alpha;
	};
	
	void render() {
		window.clear();
		graphics_system.draw(ecs, window);
		//physics_system.draw();
		window.display();
	};
	
	void on_scored(const Event::Scored& scored) {
		scoreboard.emplace <Component::Timer> (5.0s);
		auto& score = scoreboard.get <Component::Score> ();
		auto& text = static_cast <sf::Text&> (*scoreboard.get <Component::Graphics::Drawable> ().pointer);
		if (scored.type == User_Data::Type::Player) {
			score.player++;
		};
		if (scored.type == User_Data::Type::Opponent) {
			score.opponent++;
		};
		text.setString(std::to_string(score.player) + " | " + std::to_string(score.opponent));
		
		reset();
	};
	
};














