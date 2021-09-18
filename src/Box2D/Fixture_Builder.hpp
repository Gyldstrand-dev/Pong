#pragma once
#include "Vector_2.hpp"
#include <box2d/b2_fixture.h>
#include <box2d/b2_shape.h>


namespace Box2D {
	
	

class Fixture_Builder {
	
public:


	Fixture_Builder& set_shape(const b2Shape& shape) {
		fixture_definition.shape = &shape;
		return *this;
	};

	Fixture_Builder& set_friction(const float& friction) {
		fixture_definition.friction = friction;
		return *this;
	};

	Fixture_Builder& set_restitution(const float& restitution) {
		fixture_definition.restitution = restitution;
		return *this;
	};

	Fixture_Builder& set_restitution_threshold(const float& restitution_threshold) {
		fixture_definition.restitutionThreshold = restitution_threshold;
		return *this;
	};

	Fixture_Builder& set_density(const float& density) {
		fixture_definition.density = density;
		return *this;
	};

	Fixture_Builder& set_frictions(const bool& is_sensor) {
		fixture_definition.isSensor = is_sensor;
		return *this;
	};
	
	Fixture_Builder& set_user_data(void* data) {
		fixture_definition.userData.pointer = reinterpret_cast <uintptr_t> (data);
		return *this;
	};

	const b2FixtureDef& build() const {
		return fixture_definition;
	};
	
private:

	b2FixtureDef fixture_definition;
};


};