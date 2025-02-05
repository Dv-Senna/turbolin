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
set(CMAKE_CXX_STANDARD ${PROJECT_CPP_DIALECT})

option(BUILD_TESTS "BUILD_TESTS" OFF)

add_compile_definitions("${PROJECT_ACRONYM_UPPERCASE}_$<IF:$<CONFIG:Debug>,DEBUG,RELEASE>")

include_directories(include)# vendors/TestItNow/include)

file(GLOB_RECURSE TURBOLIN_HEADER include/*.hpp include/*.inl)
file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

add_compile_options(-march=native)

add_executable(${PROJECT_NAME} ${TURBOLIN_HEADER} ${TEST_SOURCES})
