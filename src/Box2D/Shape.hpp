#pragma once
#include "Vector_2.hpp"
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_edge_shape.h>
#include <box2d/b2_chain_shape.h>
#include <box2d/b2_math.h>
#include <vector>


namespace Box2D {
namespace Shape {
	
	

inline b2CircleShape Circle(const float& radius, const Vector_2 <float>& position = {0.f, 0.f}) {
	b2CircleShape circle;
	circle.m_p = {position.x, position.y};
	circle.m_radius = radius;
	return circle;
};

inline b2PolygonShape Rectangle(const Vector_2 <float>& size, const Vector_2 <float>& center = {0.f, 0.f}, const float& angle = {0.f}) {
	b2PolygonShape rectangle;
	rectangle.SetAsBox(size.x / 2.f, size.y / 2.f, {center.x, center.y}, angle);
	return rectangle;
};

inline b2PolygonShape Polygon(const std::vector <b2Vec2>& points) {
	b2PolygonShape polygon;
	polygon.Set(&points[0], points.size());
	return polygon;
};

inline b2EdgeShape Edge_One_Sided(const b2Vec2& point_A, const b2Vec2& point_B, const b2Vec2& ghost_A, const b2Vec2& ghost_B) {
	b2EdgeShape edge;
	edge.SetOneSided(ghost_A, point_A, point_B, ghost_B);
	return edge;
};

inline b2EdgeShape Edge_Two_Sided(const b2Vec2& point_A, const b2Vec2& point_B) {
	b2EdgeShape edge;
	edge.SetTwoSided(point_A, point_B);
	return edge;
};

inline b2ChainShape Loop(const std::vector <b2Vec2>& points) {
	b2ChainShape loop;
	loop.CreateLoop(&points[0], points.size());
	return loop;
};

inline b2ChainShape Chain(const std::vector <b2Vec2>& points, const b2Vec2& ghost_A, const b2Vec2& ghost_B) {
	b2ChainShape chain;
	chain.CreateChain(&points[0], points.size(), ghost_A, ghost_B);
	return chain;
};



};};