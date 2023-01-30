cmake_minimum_required(VERSION 3.0)
project(42CC LANGUAGES C CXX OBJC OBJCXX)
set (CMAKE_CXX_STANDARD 20)

# Create an option to switch between a system sdl library and a vendored sdl library
option(42CC_VENDORED "Use vendored libraries" ON)


if(42CC_VENDORED)
	add_subdirectory(dependencies/SDL EXCLUDE_FROM_ALL)
else()
	# 1. Look for a SDL3 package, 2. look for the SDL3 component and 3. fail if none can be found
	find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
endif()

# Create your game executable target as usual 
add_executable(42CC src/main.cpp src/window.cpp)

# Link to the actual SDL3 library. SDL3::SDL3 is the shared SDL library, SDL3::SDL3-static is the static SDL libarary.
target_link_libraries(42CC PRIVATE SDL3::SDL3)

target_include_directories(42CC PRIVATE includes)