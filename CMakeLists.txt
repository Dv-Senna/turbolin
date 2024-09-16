set(CMAKE_PROJECT_MINIMUM_VERSION 3.20)
cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(turbolin
	VERSION 0.0.0
	LANGUAGES CXX
)

set(PROJECT_ACRONYM tl)
string(TOUPPER ${PROJECT_ACRONYM} PROJECT_ACRONYM_UPPERCASE)
set(PROJECT_CPP_DIALECT 23)

option(BUILD_TESTS "BUILD_TESTS" OFF)

add_compile_definitions("${PROJECT_ACRONYM_UPPERCASE}_$<IF:$<CONFIG:Debug>,DEBUG,RELEASE>")

add_subdirectory(lib)
add_subdirectory(sandbox)
if (BUILD_TESTS)
	add_subdirectory(tests)
endif()
