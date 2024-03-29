cmake_minimum_required(VERSION 3.9)
project(bomberman DESCRIPTION "bomberman executable and libraries")

set(PROJECT_ROOT ./)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(GNUInstallDirs)

##############################
# bomberman executable
##############################
set(SRC_FILES
    ${PROJECT_ROOT}/src/main.cpp
    ${PROJECT_ROOT}/src/globalScope.cpp
    ${PROJECT_ROOT}/src/UIScenes.cpp
    ${PROJECT_ROOT}/lib/Lib.cpp
    ${PROJECT_ROOT}/lib/std/DLLoader.cpp
    ${PROJECT_ROOT}/lib/std/Exception.cpp
    ${PROJECT_ROOT}/lib/std/Stopwatch.cpp
    ${PROJECT_ROOT}/ECS/World.cpp
    ${PROJECT_ROOT}/ECS/GameManager.cpp
    ${PROJECT_ROOT}/ECS/managers/EntityManager.cpp
    ${PROJECT_ROOT}/ECS/managers/SystemManager.cpp
    ${PROJECT_ROOT}/ECS/systems/CountdownSystem.cpp
    ${PROJECT_ROOT}/ECS/systems/AnimatorSystem.cpp
    ${PROJECT_ROOT}/ECS/systems/ButtonSystem.cpp
    ${PROJECT_ROOT}/ECS/systems/MouseInputSystem.cpp
    ${PROJECT_ROOT}/ECS/systems/ControllerInputSystem.cpp
    ${PROJECT_ROOT}/ECS/systems/CubemapSystem.cpp
    ${PROJECT_ROOT}/ECS/systems/CollisionSystem.cpp
    ${PROJECT_ROOT}/ECS/systems/PlayerBombSystem.cpp
    ${PROJECT_ROOT}/ECS/systems/BombSystem.cpp
    ${PROJECT_ROOT}/ECS/systems/ExplosionParticleSystem.cpp
    ${PROJECT_ROOT}/ECS/systems/EndGameSystem.cpp
    ${PROJECT_ROOT}/ECS/systems/AISystem.cpp
)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
    set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()

set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

add_executable(bomberman ${SRC_FILES})
target_include_directories(bomberman PRIVATE ${PROJECT_ROOT}/include/)
target_link_libraries(bomberman raylib)

if (MSVC)
    target_compile_options(bomberman PRIVATE "/ZM" "/Wall" "/std:c++17" "/gdwarf-2" "/g3" "/ggdb")
    set_target_properties(bomberman PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "../../"
    )
else()
    target_compile_options(bomberman PRIVATE -W -Wall -Wextra -Wno-missing-field-initializers -g3)
    set_target_properties(bomberman PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "../"
    )
endif()

# TARGET_LINK_LIBRARIES(bomberman raylib)
# if (NOT raylib_FOUND)
#     INCLUDE(FetchContent)
#     FetchContent_Declare(raylib URL https://github.com/raysan5/raylib/archive/master.tar.gz)
#     FetchContent_GetProperties(raylib)
#     if (NOT raylib_POPULATED)
#         SET(FETCHCONTENT_QUIET NO)
#         FetchContent_Populate(raylib)
#         SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#         ADD_SUBDIRECTORY(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
#         SET(raylib_FOUND TRUE)
#     endif()
# endif()
