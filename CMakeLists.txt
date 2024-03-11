cmake_minimum_required(VERSION 3.20)
project(QQL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    set(CMAKE_CXX_FLAGS "/W4 /WX")
else ()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_executable(qql src/main.cpp)

find_package(Boost REQUIRED COMPONENTS program_options)
target_include_directories(qql PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(qql PUBLIC ${Boost_LIBRARIES})
