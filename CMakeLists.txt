cmake_minimum_required(VERSION 3.21)
project(UnknownPlanet CXX)

include(cmake/base.cmake)
include(cmake/libraries.cmake)
include(cmake/warnings.cmake)
include(cmake/debug.cmake)

add_executable(${PROJECT_NAME})

target_compile_features(
	${PROJECT_NAME}
	PRIVATE
		cxx_std_17
)

target_sources(
	${PROJECT_NAME}
	PRIVATE
		src/main.cpp
		src/Engine.cpp
		src/ResourceManager.cpp
)

target_include_directories(
	${PROJECT_NAME}
	PRIVATE
		${PROJECT_SOURCE_DIR}/include
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set_debug_options(${PROJECT_NAME})
endif()


set_default_warnings(${PROJECT_NAME})
link_default_libraries(${PROJECT_NAME})
