cmake_minimum_required(VERSION 3.14)

if(POLICY CMP0167)
  cmake_policy(SET CMP0167 NEW)
endif()

project(GroupChatServer VERSION 1.0 DESCRIPTION "GroupChatServer" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")

option(ENABLE_SANITIZERS "Enable Address and Undefined Behavior Sanitizers" OFF)
if(ENABLE_SANITIZERS)
    add_compile_options(-fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address -fsanitize=undefined)
endif()

find_package(Threads REQUIRED)

find_package(Boost 1.83.0 REQUIRED CONFIG )

add_executable(client src/client.cpp)
add_executable(server src/server.cpp)

target_include_directories(server PRIVATE include)
target_include_directories(client PRIVATE include)

target_link_libraries(server PRIVATE 
    Boost::boost 
    Threads::Threads
)

target_link_libraries(client PRIVATE 
    Boost::boost 
    Threads::Threads
)
