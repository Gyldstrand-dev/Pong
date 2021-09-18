#pragma once
#include "Vector_2.hpp"
#include "Box2D/World.hpp"
#include "SFML/Window.hpp"
#include "SFML/Transform.hpp"
#include <box2d/b2_draw.h>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>


namespace Box2D {
	
	

class Debug_Draw : public b2Draw {
	
public:
	
	Debug_Draw(Box2D::World& world, SFML::Window& window) : window {window} {
		world.set_debug_draw(this);
		SetFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);
		world_to_screen.set_scale({32.f, 32.f});
	};
	
	virtual void DrawPolygon(const b2Vec2* vertices, int vertex_count, const b2Color& color) {
		(void) color;
		sf::ConvexShape polygon {static_cast <size_t> (vertex_count)};
		polygon.setFillColor({0, 0, 0, 0});
		polygon.setOutlineColor({255, 0, 0, 255});
		polygon.setOutlineThickness(1.f / 32.f);
		for (int i {0}; i < vertex_count; i++) {
			polygon.setPoint(i, {vertices[i].x, vertices[i].y});
		};
		window.draw(polygon, world_to_screen.get());
	};

	virtual void DrawSolidPolygon(const b2Vec2* vertices, int vertex_count, const b2Color& color) {
		(void) color;
		sf::ConvexShape polygon {static_cast <size_t> (vertex_count)};
		polygon.setFillColor({150, 0, 0, 150});
		for (int i {0}; i < vertex_count; i++) {
			polygon.setPoint(i, {vertices[i].x, vertices[i].y});
		};
		window.draw(polygon, world_to_screen.get());
	};

	virtual void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {
		(void) color;
		sf::CircleShape circle {radius};
		circle.setOrigin(radius, radius);
		circle.setPosition(center.x, center.y);
		circle.setFillColor({0, 0, 0, 0});
		circle.setOutlineColor({255, 0, 0, 255});
		circle.setOutlineThickness(1.f / 32.f);
		window.draw(circle, world_to_screen.get());
	};

	virtual void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {
		(void) color; (void) axis;
		sf::CircleShape circle {radius};
		circle.setOrigin(radius, radius);
		circle.setPosition(center.x, center.y);
		circle.setFillColor({150, 0, 0, 150});
		window.draw(circle, world_to_screen.get());
	};
	
	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
		(void) color;
		std::vector <sf::Vertex> line;
		line.push_back({{p1.x, p1.y}, {0, 255, 0, 255}});
		line.push_back({{p2.x, p2.y}, {0, 255, 0, 255}});
		window.draw(&line[0], 2, sf::Lines, world_to_screen.get());
	};

	virtual void DrawTransform(const b2Transform& transform) {
		float line_length = 0.4;

		Vector_2 <float> x_axis {transform.p + line_length * transform.q.GetXAxis()};
		sf::Vertex red_line[] = 
		{
			sf::Vertex({{transform.p.x, transform.p.y}, sf::Color::Yellow}),
			sf::Vertex({{x_axis.x, x_axis.y}, sf::Color::Yellow})
		};

		Vector_2 <float> y_axis = transform.p + line_length * transform.q.GetYAxis();
		sf::Vertex green_line[] = 
		{
			sf::Vertex({{transform.p.x, transform.p.y}, sf::Color::Yellow}),
			sf::Vertex({{y_axis.x, y_axis.y}, sf::Color::Yellow})
		};

		window.draw(red_line, 2, sf::Lines, world_to_screen.get());
		window.draw(green_line, 2, sf::Lines, world_to_screen.get());
	};

	virtual void DrawPoint(const b2Vec2& p, float size, const b2Color& color) {
		(void) size; (void) color;
		std::vector <sf::Vertex> point;
		point.push_back({{p.x, p.y}, {0, 0, 255, 255}});
		window.draw(&point[0], 1, sf::Points, world_to_screen.get());
	};

private:

	SFML::Window& window;
	SFML::Transform world_to_screen;

};



};