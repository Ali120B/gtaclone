cmake_minimum_required(VERSION 3.22)
project(OpenCityClone LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(OPEN_CITY_ENABLE_WARNINGS "Enable compile warnings" ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Bullet REQUIRED)
find_package(assimp REQUIRED)
find_package(OpenAL REQUIRED)

file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(open_city ${ENGINE_SOURCES})

target_include_directories(open_city PRIVATE
    src
    ${BULLET_INCLUDE_DIRS}
)

target_link_libraries(open_city PRIVATE
    OpenGL::GL
    glfw
    glm::glm
    BulletDynamics
    BulletCollision
    LinearMath
    assimp::assimp
    OpenAL::OpenAL
)

if(OPEN_CITY_ENABLE_WARNINGS)
    target_compile_options(open_city PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
    )
endif()

add_custom_target(download_assets
    COMMAND ${CMAKE_COMMAND} -E env bash ${CMAKE_SOURCE_DIR}/scripts/download_assets.sh
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Downloading open assets"
)
