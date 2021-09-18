#pragma once
#include "Component/Vertices.hpp"
#include "Component/Primitive.hpp"
#define _USE_MATH_DEFINES
#include <cmath>


namespace Preset {
namespace Shape {
	
	
	
	/* struct Circle_Fan {
		
		Component::Vertices vertices;
		Component::Primitive primitive;
		
		Circle_Fan(const float& radius, const size_t& vertex_count = 34) {
			float radian_interval = (360.f / (vertex_count - 2)) * (M_PI / 180.f);
			primitive = sf::TriangleFan;
			vertices.resize(vertex_count);
			vertices.shrink_to_fit();
			vertices.at(0).position = {0.f, 0.f};
			vertices.at(vertex_count - 1).position = {radius, 0.f};
			for (size_t i {1}; i < vertex_count - 1; i++) {
				vertices.at(i).position = {radius * std::cos((i - 1) * radian_interval), radius * std::sin((i - 1) * radian_interval)};
			};
		};
	}; */
	
	
	
};};