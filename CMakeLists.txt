cmake_minimum_required(VERSION 3.21)
project(
	uplanet
	VERSION 0.1.0
	LANGUAGES C
)

include(cmake/base.cmake)
include(cmake/library.cmake)
include(cmake/warnings.cmake)

add_executable(${PROJECT_NAME})

target_compile_features(
	${PROJECT_NAME}
	PRIVATE
		c_std_17
)

target_sources(
	${PROJECT_NAME}
	PRIVATE
		include/core/gfx/opengl.h
		include/core/gfx/render.h
		include/core/glfw/window.h
		include/core/engine.h
		include/common.h
		include/config.h
		include/log.h
		include/types.h

		src/core/gfx/opengl.c
		src/core/gfx/render.c
		src/core/glfw/window.c
		src/core/engine.c
		src/common.c
		src/log.c
		src/main.c
)

target_include_directories(
	${PROJECT_NAME}
	PRIVATE
		${CMAKE_SOURCE_DIR}/include
)

set_libraries(${PROJECT_NAME})
set_options(${PROJECT_NAME})
set_default_warnings(${PROJECT_NAME})
