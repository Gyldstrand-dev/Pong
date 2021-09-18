cmake_minimum_required(VERSION 3.12.0)
project(Pong)

set(SFML_DIR "C:/DEV/lib/SFML-2.5.1/build/GCC_10.3.0/32")
find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)


add_executable(Pong main.cpp)

target_include_directories(
	Pong 
	PRIVATE 
		C:/DEV/lib/Box2D/include
		C:/DEV/lib/EnTT/single_include
		C:/DEV/lib/EnTT/src
)

target_include_directories(
	Pong
	PRIVATE
		src
		src/Game)

target_compile_features(Pong PUBLIC cxx_std_17)
target_compile_options(Pong PRIVATE -Wall -Wextra)

target_link_libraries(Pong sfml-system sfml-window sfml-graphics sfml-audio sfml-network
	C:/DEV/lib/Box2D/build/bin/libbox2d.a
	
)

