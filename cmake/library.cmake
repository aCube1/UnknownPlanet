include_guard()

function(set_libraries target)
	set(VENDOR_DIR ${CMAKE_SOURCE_DIR}/vendor)

	find_package(glfw3 3.3 REQUIRED)

	add_subdirectory(${VENDOR_DIR}/glad)
	add_subdirectory(${VENDOR_DIR}/cglm)

	target_link_libraries(
		${target}
		PRIVATE
			glfw
			glad
			cglm
)
endfunction()
