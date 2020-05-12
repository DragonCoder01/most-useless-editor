cmake_minimum_required(VERSION 3.12)

project(mu-edit)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_subdirectory(PDCurses)
add_compile_options(
	-std=c++17
)

add_executable(
	mu-edit
	src/main.cpp
)

target_link_libraries(
	mu-edit
	PDcurses
)