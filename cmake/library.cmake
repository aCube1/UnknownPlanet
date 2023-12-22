include_guard()

function(set_libraries target)
	set(VENDOR_DIR ${CMAKE_SOURCE_DIR}/vendor)

	find_package(
		SFML 2.6.1
		COMPONENTS
			window graphics audio system
		REQUIRED
	)

	option(SPDLOG_USE_STD_FORMAT ON)
	option(SPDLOG_ENABLE_PCH ON)
	add_subdirectory(${VENDOR_DIR}/spdlog)

	target_link_libraries(
		${target}
		PRIVATE
			spdlog::spdlog
			sfml-window sfml-graphics sfml-audio sfml-system
	)
endfunction()
