cmake_minimum_required(VERSION 2.8.12)
project (maxon_example)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
include_directories(include)
aux_source_directory(src DIR_SRCS)
set(srcs ${DIR_SRCS})
add_executable(${PROJECT_NAME} ${srcs})


target_link_libraries(${PROJECT_NAME} -lEposCmd)
