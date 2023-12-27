include_guard()

function(set_libraries target)
	set(VENDOR_DIR ${CMAKE_SOURCE_DIR}/vendor)

	find_package(
		SDL2 2.28 CONFIG
		COMPONENTS
			SDL2
		REQUIRED
	)

	target_link_libraries(
		${target}
		PRIVATE
			SDL2::SDL2
)
endfunction()
