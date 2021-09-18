#pragma once


struct User_Data {
	enum class Type {Player, Opponent, Ball, Border};
	
	Type type;
	
	User_Data(const Type& type) 
	: 	type {type} {};
	
};