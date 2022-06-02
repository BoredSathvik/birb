cmake_minimum_required(VERSION 3.23.0)
project(Birb VERSION 1.0 LANGUAGES CSharp CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Injector)
add_subdirectory(client)