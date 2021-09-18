#pragma once
#include "Vector_2.hpp"
#include "Box2D/Body.hpp"


namespace Box2D {
	
	

class Body_Builder {
	
public:


	Body_Builder& set_type(const Body::Type& type) {
		body_definition.type = static_cast <b2BodyType> (type);
		return *this;
	};
	
	Body_Builder& set_position(const Vector_2 <float>& position) {
		body_definition.position.Set(position.x, position.y);
		return *this;
	};
	
	Body_Builder& set_linear_velocity(const Vector_2 <float>& velocity) {
		body_definition.linearVelocity.Set(velocity.x, velocity.y);
		return *this;
	};
	
	Body_Builder& set_angle(const float& radians) {
		body_definition.angle = radians;
		return *this;
	};

	Body_Builder& set_angular_velocity(const float& velocity) {
		body_definition.angularVelocity = velocity;
		return *this;
	};
	
	Body_Builder& set_angular_damping(const float& damping) {
		body_definition.angularDamping = damping;
		return *this;
	};
	
	Body_Builder& set_gravity_scale(const float& scale) {
		body_definition.gravityScale = scale;
		return *this;
	};

	Body_Builder& set_allow_sleep(const bool& is_allowed_sleep) {
		body_definition.allowSleep = is_allowed_sleep;
		return *this;
	};

	Body_Builder& set_awake(const bool& is_awake) {
		body_definition.awake = is_awake;
		return *this;
	};

	Body_Builder& set_fixed_rotation(const bool& is_rotation_fixed) {
		body_definition.fixedRotation = is_rotation_fixed;
		return *this;
	};
	
	Body_Builder& set_bullet(const bool& is_bullet) {
		body_definition.bullet = is_bullet;
		return *this;
	};

	const b2BodyDef& build() const {
		return body_definition;
	};
	
private:

	b2BodyDef body_definition;
};


};