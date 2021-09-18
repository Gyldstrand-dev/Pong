#pragma once
#include "User_Data.hpp"
#include "EnTT/Event_Dispatcher.hpp"
#include "Event/Scored.hpp"
#include <box2d/b2_world_callbacks.h>
#include <box2d/b2_contact.h>
#include <iostream>

namespace Box2D {
	
	
class Contact_Listener : public b2ContactListener {

public:

	Contact_Listener(EnTT::Event_Dispatcher& event_dispatcher)
	:	event_dispatcher {event_dispatcher} {};

	void BeginContact (b2Contact* contact) {
		auto* fixture_A = contact->GetFixtureA();
		auto* fixture_B = contact->GetFixtureB();
		auto index_A = contact->GetChildIndexA();
		auto index_B = contact->GetChildIndexB();
		auto* user_data_a = reinterpret_cast <User_Data*> (fixture_A->GetUserData().pointer);
		auto* user_data_b = reinterpret_cast <User_Data*> (fixture_B->GetUserData().pointer);
		if (user_data_a && user_data_a->type == User_Data::Type::Border) {
			if (index_A == 0) {
				event_dispatcher.enqueue <Event::Scored> (User_Data::Type::Opponent);
			};
			if (index_A == 2) {
				event_dispatcher.enqueue <Event::Scored> (User_Data::Type::Player);
			};
		};
		
	};

private:

	EnTT::Event_Dispatcher& event_dispatcher;
};



};