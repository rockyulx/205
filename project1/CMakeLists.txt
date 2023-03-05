cmake_minimum_required(VERSION 3.12)

add_definitions(-DWITH_AVX2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3" CACHE STRING "C++ flags" FORCE)

set(CMAKE_CXX_STANDARD 11)

project(project1)

ADD_EXECUTABLE(${PROJECT_NAME} main.cpp matrix.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    message("OpenMP found.")
    target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
endif()
