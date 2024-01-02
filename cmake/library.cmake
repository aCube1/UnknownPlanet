include_guard()

function(set_libraries target)
	set(VENDOR_DIR ${CMAKE_SOURCE_DIR}/vendor)

	find_package(
		SDL2 2.28 CONFIG
		COMPONENTS
			SDL2
		REQUIRED
	)

	add_subdirectory(${VENDOR_DIR}/glad)
	add_subdirectory(${VENDOR_DIR}/cglm)

	target_link_libraries(
		${target}
		PRIVATE
			cglm
			glad
			SDL2::SDL2
)
endfunction()
