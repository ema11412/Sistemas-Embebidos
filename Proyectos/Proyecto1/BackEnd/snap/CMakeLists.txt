cmake_minimum_required(VERSION 3.10)

set(SNAP_LIB snaplib)

project(${SNAP_LIB})

find_package(OpenCV REQUIRED)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
	PRIVATE
		snap.cpp
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${OpenCV_INCLUDE_DIRS}
		${CMAKE_CURRENT_LIST_DIR}/../include
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
		LINKER_LANGUAGE CXX
		CXX_STANDARD 11
		CXX_STANDARD_REQUIRED YES
		CXX_EXTENSIONS OFF
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
		${OpenCV_LIBS}
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
