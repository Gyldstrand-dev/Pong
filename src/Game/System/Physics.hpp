#pragma once
#include "Box2D/World.hpp"
#include "Box2D/Body.hpp"
#include "EnTT/Registry.hpp"
#include "EnTT/Entity.hpp"
#include "Component/Physics/Body.hpp"


namespace System {
	
	
	
class Physics : public Box2D::World {
	
	
public:

	static constexpr float scale {32.f};
	
	void connect(EnTT::Registry& ecs) {
		ecs.on_destroy <Component::Physics::Body> ().connect <&System::Physics::on_destroy> (this);
	};
	
private:
	
	void on_destroy(EnTT::Registry& ecs, EnTT::Entity entity) {
		auto& body = ecs.get <Component::Physics::Body> (entity);
		destroy_body(body.get());
	};
};
	
	
	
};