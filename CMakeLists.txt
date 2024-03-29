cmake_minimum_required(VERSION 3.0)
# if compiling on mac os, use the objc and objc++ languages
if(APPLE)
	project(42CC LANGUAGES C CXX OBJC OBJCXX)
else()
	project(42CC LANGUAGES C CXX)
endif()
set (CMAKE_CXX_STANDARD 20)

# Create an option to switch between a system sdl library and a vendored sdl library
option(42CC_VENDORED "Use vendored libraries" ON)
# No shared libs as we only static build
set(BUILD_SHARED_LIBS OFF)
if (WIN32)
	set(FILETYPE ".exe")
endif()

# add the SDL2 and SDL2_image libraries to the project if the 42CC_VENDORED option is set to ON
# otherwise, look for the SDL2 and SDL2_image libraries and fail if they can't be found
if(42CC_VENDORED)
	add_subdirectory(dependencies/SDL EXCLUDE_FROM_ALL)
	add_subdirectory(dependencies/SDL_image EXCLUDE_FROM_ALL)
else()
	# 1. Look for a SDL3 package, 2. look for the SDL3 component and 3. fail if none can be found
	find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)
	find_package(SDL3_image REQUIRED CONFIG REQUIRED COMPONENTS SDL3_image)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_compile_definitions(DEBUG)
endif()


# Build the resource compiler in build-tools/42cc_resource_compiler.cpp into build-tools/42cc_resource_compiler
# and use it to compile the resources into a .42CC file
set(ASSETS assets/duck.png assets/deer_gpl.obj)
add_executable(42cc_resource_compiler build-tools/42cc_resource_compiler.cpp)
add_custom_target(resources.42CC
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		COMMAND ${CMAKE_BINARY_DIR}/42cc_resource_compiler${FILETYPE} ${ASSETS} ${CMAKE_BINARY_DIR}/resources.42CC
		DEPENDS 42cc_resource_compiler
		COMMENT "Compiling resources"
		VERBATIM
)

# Create game executable
add_executable(42CC
		src/main.cpp src/window.cpp src/game.cpp src/resources.cpp src/objects/sprite2d.cpp src/objects/player.cpp src/engine/engine_base_objects.cpp src/objects/object3d.cpp src/engine/math.cpp src/objects/wavefront.cpp src/engine/exceptions/stackexception.cpp src/engine/error_handler.cpp)

# Add the resources.42CC file as a dependency for the game executable
add_dependencies(42CC resources.42CC)

include_directories(dependencies/SDL_image/include)
# Link to the static SDL3 library SDL3::SDL3-static.
target_link_libraries(42CC PRIVATE SDL3::SDL3-static)
target_link_libraries(42CC PRIVATE SDL3_image)

# Add include directories for the includes folder
target_include_directories(42CC PRIVATE includes)
