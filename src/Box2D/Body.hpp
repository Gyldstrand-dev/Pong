#pragma once
#include "Vector_2.hpp"
#include <box2d/b2_body.h>


namespace Box2D {
	
	
class Body {
	
public:

	enum class Type {Static = b2_staticBody, Dynamic = b2_dynamicBody, Kinematic = b2_kinematicBody};

	Body(b2Body* body) 
	: 	body {body} {};
	
	b2Fixture* create_fixture(const b2FixtureDef& fixture_definition) {
		return body->CreateFixture(&fixture_definition);
	};
	
	b2Fixture* create_fixture(const b2Shape& shape, const float& density) {
		return body->CreateFixture(&shape, density);
	};

	Type get_type() const {
		return static_cast <Type> (body->GetType());
	};
	
	void set_transform(const Vector_2 <float>& position, const float& angle = 0.f) {
		body->SetTransform({position.x, position.y}, angle);
	};
	
	Vector_2 <float> get_position() const {
		return body->GetPosition();
	};

	float get_angle() const {
		return body->GetAngle();
	};
	void set_linear_velocity(const Vector_2 <float>& velocity) {
		body->SetLinearVelocity({velocity.x, velocity.y});
	};

	void apply_force(const Vector_2 <float>& force, const Vector_2 <float>& point, bool wake = true) {
		body->ApplyForce({force.x, force.y}, {point.x, point.y}, wake);
	};
	
	void apply_force_center(const Vector_2 <float>& force, bool wake = true) {
		body->ApplyForceToCenter({force.x, force.y}, wake);
	};

	void apply_impulse(const Vector_2 <float>& impulse, const Vector_2 <float>& point, bool wake = true) {
		body->ApplyLinearImpulse({impulse.x, impulse.y}, {point.x, point.y}, wake);
	};
	
	void apply_impulse_center(const Vector_2 <float>& impulse, bool wake = true) {
		body->ApplyLinearImpulseToCenter({impulse.x, impulse.y}, wake);
	};	

	void set_angular_velocity(const float& velocity) {
		body->SetAngularVelocity(velocity);
	};
	
	void apply_angular_impulse(const float& impulse, bool wake = true) {
		body->ApplyAngularImpulse(impulse, wake);
	};
	
	void apply_torque(const float& torque, bool wake = true) {
		body->ApplyTorque(torque, wake);
	};
	
	const b2Body* get() const {
		return body;
	};

private:

	b2Body* body {nullptr};
};

	
};