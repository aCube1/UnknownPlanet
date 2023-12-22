cmake_minimum_required(VERSION 3.21)
project(
	uplanet
	VERSION 0.1.0
	LANGUAGES CXX
)

include(cmake/base.cmake)
include(cmake/library.cmake)
include(cmake/warnings.cmake)

add_executable(${PROJECT_NAME})

target_compile_features(
	${PROJECT_NAME}
	PRIVATE
		cxx_std_20
)

target_sources(
	${PROJECT_NAME}
	PRIVATE
		src/main.cpp
)

target_include_directories(
	${PROJECT_NAME}
	PRIVATE
		${CMAKE_SOURCE_DIR}/include
)

set_libraries(${PROJECT_NAME})
set_options(${PROJECT_NAME})
set_default_warnings(${PROJECT_NAME})
