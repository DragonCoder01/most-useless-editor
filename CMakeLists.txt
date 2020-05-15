cmake_minimum_required(VERSION 3.12)

project(mu-edit)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32 OR MSVC)
	add_subdirectory(PDCurses)
	set(CURSES_LIBRARY PDcurses)
else()
	find_package(Curses REQUIRED)
	include_directories(${CURSES_INCLUDE_DIR})
endif()

add_executable(
	mu-edit
	src/main.cpp
)

target_link_libraries(
	mu-edit
	${CURSES_LIBRARY}
)
