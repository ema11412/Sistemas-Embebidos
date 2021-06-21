cmake_minimum_required(VERSION 3.10)

set(GPIO_LIB gpiolib)

project(${GPIO_LIB})

add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME}
	PRIVATE
		gpio.c
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/../include
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		LINKER_LANGUAGE C
		C_STANDARD 90
		C_STANDARD_REQUIRED YES
		C_EXTENSIONS OFF
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

target_compile_definitions(${PROJECT_NAME}
  PRIVATE
    _DEFAULT_SOURCE
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
