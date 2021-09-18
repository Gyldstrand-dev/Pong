#pragma once
#include <initializer_list>
#include <stdexcept>
#include <math.h>

template <typename T>
class Vector_2 {
	
public:
	
	Vector_2()
	:	x {0.f}, y {0.f} {};

	Vector_2(const T& x, const T& y)
	:	x {x}, y {y} {};
	
	Vector_2(std::initializer_list <T> init_list) {
		if (init_list.size() != 2) {
			throw(std::length_error("Vector_2(std::initializer_list) : size != 2"));
		};
		
		x = *(init_list.begin());
		y = *(init_list.begin() + 1);
	};
	
	Vector_2 operator* (const T& scalar) const {
		return Vector_2 <T> {
			x * scalar,
			y * scalar,
		};
	};
	
	Vector_2& operator*= (const T& scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	};	
	
	Vector_2 operator/ (const T& scalar) const {
		return Vector_2 <T> {
			x / scalar,
			y / scalar,
		};
	};
	
	Vector_2& operator/= (const T& scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	};	
	
	Vector_2& operator+ (const T& scalar) {
		x += scalar;
		y += scalar;
		return *this;
	};		
	
	Vector_2& operator- (const T& scalar) {
		x -= scalar;
		y -= scalar;
		return *this;
	};	
	
	template <typename Vector_Type>
	Vector_2(const Vector_Type& vector_type)
	:	x {vector_type.x}, y {vector_type.y} {};
	
	
	template <typename Vector_Type>
	Vector_2& operator= (const Vector_Type& vector_type) {
		x = vector_type.x;
		y = vector_type.y;
		return *this;
	};
	
	template <typename Vector_Type>
	Vector_2 operator+ (const Vector_Type& vector_type) const {
		return Vector_2 <T> {
			x + vector_type.x,
			y + vector_type.y,
		};
	};
	
	template <typename Vector_Type>
	Vector_2& operator+= (const Vector_Type& vector_type) {
		x += vector_type.x;
		y += vector_type.y;
		return *this;
	};	

	template <typename Vector_Type>
	Vector_2 operator- (const Vector_Type& vector_type) const {
		return Vector_2 <T> {
			x - vector_type.x,
			y - vector_type.y,
		};
	};
	
	template <typename Vector_Type>
	Vector_2& operator-= (const Vector_Type& vector_type) {
		x -= vector_type.x;
		y -= vector_type.y;
		return *this;
	};	
	
	template <typename Vector_Type>
	Vector_2 operator* (const Vector_Type& vector_type) const {
		return Vector_2 <T> {
			x * vector_type.x,
			y * vector_type.y,
		};
	};
	
	template <typename Vector_Type>
	Vector_2& operator*= (const Vector_Type& vector_type) {
		x *= vector_type.x;
		y *= vector_type.y;
		return *this;
	};	
	
	template <typename Vector_Type>
	Vector_2 operator/ (const Vector_Type& vector_type) const {
		return Vector_2 <T> {
			x / vector_type.x,
			y / vector_type.y,
		};
	};
	
	template <typename Vector_Type>
	Vector_2& operator/= (const Vector_Type& vector_type) {
		x /= vector_type.x;
		y /= vector_type.y;
		return *this;
	};
	
	float magnitude() {
		return std::abs(std::sqrt(x * x + y * y));
	};
	
	Vector_2 unit() {
		return *this / magnitude();
	};

	T x, y;
	
private:

	
};