project(Cpp20)
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX20_EXTENSION_COMPILE_OPTION "-std:c++latest")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("${CMAKE_SOURCE_DIR}/chapter3")

