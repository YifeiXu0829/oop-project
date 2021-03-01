cmake_minimum_required(VERSION 2.8.9)

if(POLICY CMP0048)
      cmake_policy(SET CMP0048 NEW)
endif()

project (hw3 VERSION "1.0.0")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(MAKE_DIRECTORY build)
add_executable(hw3 hw3.cpp)
