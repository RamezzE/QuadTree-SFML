cmake_minimum_required(VERSION 3.16)
project(QuadTree LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(CMAKE_CXX_STANDARD 17) # Sets the version of C++ used in the project

include(FetchContent)

# Windows-specific configurations
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(QuadTree
        main.cpp
        src/cpp/Button.cpp
        src/cpp/Common.cpp
        src/cpp/Game.cpp
        src/cpp/MainScreen.cpp
        src/cpp/Particle.cpp
        src/cpp/TextBox.cpp
)

target_link_libraries(QuadTree PRIVATE sfml-graphics)
target_compile_features(QuadTree PRIVATE cxx_std_17)

add_custom_command(
        TARGET QuadTree
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:QuadTree>
        VERBATIM)

install(TARGETS QuadTree)