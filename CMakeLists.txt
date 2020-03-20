cmake_minimum_required(VERSION 3.10)
project(HW3)

set(CMAKE_CXX_STANDARD 17)

add_executable(prime_calc
	src/main.cpp
	src/PCalc.cpp
	src/PCalc_SP.cpp
	src/PCalc_T.cpp)

target_include_directories(prime_calc PRIVATE include)

TARGET_LINK_LIBRARIES(prime_calc pthread)

