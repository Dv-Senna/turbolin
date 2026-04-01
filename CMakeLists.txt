set(CMAKE_PROJECT_MINIMUM_VERSION 3.20)
cmake_minimum_required(VERSION 3.20)

project(turbolin
	VERSION 0.1.0
	LANGUAGES CXX
)

add_library(turbolin INTERFACE)
add_library(turbolin::turbolin ALIAS turbolin)

target_include_directories(turbolin INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(turbolin INTERFACE "TL_$<IF:$<CONFIG:Debug>,DEBUG,RELEASE>")
target_compile_features(turbolin INTERFACE cxx_std_23)
