cmake_minimum_required(VERSION 3.28)
project(QuadTree-SFML)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)
set(SFML_STATIC_LIBRARIES TRUE)

file(GLOB_RECURSE SRC src/*.cpp src/*.h)

add_executable(${PROJECT_NAME} ${SRC})

if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)