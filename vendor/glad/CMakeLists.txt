cmake_minimum_required(VERSION 3.21)
project(glad C)

add_library(${PROJECT_NAME})

target_sources(
	${PROJECT_NAME}
	PRIVATE
		include/glad/glad.h
		include/KHR/khrplatform.h

		src/glad.c
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
