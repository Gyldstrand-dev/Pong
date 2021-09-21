#pragma once


struct User_Data {
	
	enum class Type {Player, Opponent, Ball, Border};
	
	User_Data(const User_Data::Type& type) 
	: 	type {type} {};
	
	User_Data::Type type;
	
};