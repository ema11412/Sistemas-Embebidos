cmake_minimum_required(VERSION 3.10)

project(test)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
	PRIVATE
		main.c
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		LINKER_LANGUAGE C
		C_STANDARD 11
		C_STANDARD_REQUIRED YES
		C_EXTENSIONS OFF
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		BUILD_WITH_INSTALL_RPATH TRUE
		INSTALL_RPATH "$\{ORIGIN\}" # use the same directory as the executable
)


target_compile_options(${PROJECT_NAME}
	PRIVATE
		$<$<C_COMPILER_ID:GNU>:
		-Werror
		-Wall
		-Wextra
		-Wduplicated-cond # warn about duplicated condition in conditional chains
		-Wduplicated-branches # warn about identical conditional branches
		-Wlogical-op # warn about possibly malformed logical expressions
		-fdelete-null-pointer-checks # test for exactly what it says on the tin
		-Wnull-dereference # further null checks
		-Wdouble-promotion # warn about floats implicitly getting promoted to double
		-Wshadow # warn when a local shadows a function argument or member
		-fstrict-aliasing
		-Wformat=2 # check C-style variadic arguments in function calls
		-pedantic
		>
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		gpiolib
)

include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT error)

if(ipo_supported)
	set_target_properties(${PROJECT_NAME}
		PROPERTIES
			INTERPROCEDURAL_OPTIMIZATION $<$<CONFIG:Release>:TRUE,FALSE>
	)
else()
	message(STATUS "IPO / LTO not supported: <${error}>")
endif()

add_custom_command(TARGET ${PROJECT_NAME}
	POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:gpiolib>
			$<TARGET_FILE_DIR:${PROJECT_NAME}>
)
