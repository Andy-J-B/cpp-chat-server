cmake_minimum_required(VERSION 3.14)

project(GroupChatServer VERSION 1.0 DESCRIPTION "GroupChatServer" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(client src/client.cpp)
add_executable(server src/server.cpp)

target_include_directories(server PRIVATE include)
target_include_directories(client PRIVATE include)
