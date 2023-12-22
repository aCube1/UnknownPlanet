include_guard()

# Generate compile_commands.json for tooling that uses it.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set CMAKE modules path
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

# Set output directory layout.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

option(ENABLE_SANITIZER_ASAN "Enable Address Sanitizer" ON)

# Ensure a CMAKE_BUILD_TYPE is set.
if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type specified. Defaulting to Debug.")
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type." FORCE)
endif()

# Create a list of valid CMAKE_BUILD_TYPES for cmake-gui and ccmake.
set_property(
	CACHE
		CMAKE_BUILD_TYPE
	PROPERTY
		STRINGS
			"Debug"
			"Release"
			"RelWithDebInfo"
			"MinSizeRel"
)

function(set_options target)
	# Enable CCACHE.
	find_program(CCACHE_PROGRAM ccache)
	if(CCACHE_PROGRAM)
		message(STATUS "CCache found!")

		set_target_properties(
			${target}
			PROPERTIES
				CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}"
				CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}"
		)
	endif()

	# Use address sanitizer flags.
	if (ENABLE_SANITIZER_ASAN)
		message(STATUS "Using Address Sanitizer.")

		target_compile_options(
			${target}
			PRIVATE
				$<$<COMPILE_LANGUAGE:C,CXX>:
				-fsanitize=address
				-fsanitize=leak
				-fsanitize=undefined
				-fno-omit-frame-pointer>
		)
		target_link_options(
			${target}
			PRIVATE
				$<$<COMPILE_LANGUAGE:C,CXX>:
				-fsanitize=address
				-fsanitize=leak
				-fsanitize=undefined
				-fno-omit-frame-pointer>
		)
	endif()
endfunction()
