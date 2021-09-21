#pragma once
#include "Time.hpp"
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_draw.h>


namespace Box2D {
	
	
	
class World {

public:

	b2Body* create_body(const b2BodyDef& body_definition) {
		return world.CreateBody(&body_definition);
	};
	
	void destroy_body(b2Body* body) {
		world.DestroyBody(body);
	};
	
	void set_contact_listener(b2ContactListener* listener) {
		world.SetContactListener(listener);
	};
	
	void set_debug_draw(b2Draw* debug_draw) {
		world.SetDebugDraw(debug_draw);
	};
	
	void draw() {
		world.DebugDraw();
	};
	
	void update(const Time::Duration& timestep) {
		world.Step(timestep.count(), 8, 4);
	};
	
	void clear_forces() {
		world.ClearForces();
	};

private:
	
	b2World world {{0.f, 0.f}};
	
};



};