cmake_minimum_required(VERSION 3.13.4)
project(list)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

if ( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set (COMPILER_SETTINGS  -g -Wall  -Wextra -Wpedantic)
    
else ()
    set (COMPILER_SETTINGS -Wall  -Wextra -Wpedantic)

endif ()

add_compile_options(${COMPILER_SETTINGS})

add_executable(${PROJECT_NAME}   
  sources/main.cpp sources/list.cpp sources/list_unit_test.cpp sources/stack.cpp sources/hash.cpp 
)

target_include_directories(${PROJECT_NAME} PRIVATE includes)