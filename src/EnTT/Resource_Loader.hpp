#pragma once
#include <entt/resource/loader.hpp>


namespace EnTT {
	
	
template <typename Loader, typename Resource>
using Resource_Loader = entt::resource_loader <Loader, Resource>;
	
	
	
};