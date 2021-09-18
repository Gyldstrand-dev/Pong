#pragma once
#include "Component/Vertices.hpp"
#include "Component/Primitive.hpp"


namespace Preset {
namespace Shape {
	
	
	
	/* struct Rectangle_Fan {
		
		Component::Vertices vertices;
		Component::Primitive primitive;
		
		Rectangle_Fan(const float& width, const float& height) {
			const float half_width {width / 2.f};
			const float half_height {height / 2.f};
			primitive = sf::TriangleFan;
			vertices.resize(6);
			vertices.shrink_to_fit();
			vertices.at(0).position = {0.f, 0.f};
			vertices.at(1).position = {-half_width, -half_height};
			vertices.at(2).position = {half_width, -half_height};
			vertices.at(3).position = {half_width, half_height};
			vertices.at(4).position = {-half_width, half_height};
			vertices.at(5).position = {-half_width, -half_height};
			
		};
	}; */
	
	
	
};};