#pragma once
#include <SFML/Graphics/Transformable.hpp>


namespace SFML {
	
	
	
class Transform {
	
public:

	void set_origin(const Vector_2 <float>& origin) {
		sfml_transformable.setOrigin(origin.x, origin.y);
	};
	
	void set_position(const Vector_2 <float>& position) {
		sfml_transformable.setPosition(position.x, position.y);
	};
	
	void set_rotation(const float& degrees) {
		sfml_transformable.setRotation(degrees);
	};
	
	void set_scale(const Vector_2 <float>& scale) {
		sfml_transformable.setScale(scale.x, scale.y);
	};
	
	Vector_2 <float> get_position() const {
		return sfml_transformable.getPosition();
	};
	
	float get_rotation() const {
		return sfml_transformable.getRotation();
	};
	
	Vector_2 <float> get_scale() const {
		return sfml_transformable.getScale();
	};
	
	const sf::Transform& get() const {
		return sfml_transformable.getTransform();
	};

private:

	sf::Transformable sfml_transformable;
	
};
	
	
	
	
};