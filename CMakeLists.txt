cmake_minimum_required(VERSION 3.16)

#if(UNIX)
#    set(username "$ENV{USER}")

#    if(CMAKE_BUILD_TYPE MATCHES "Debug")
#        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../../bin/unix/debug")
#    elseif(CMAKE_BUILD_TYPE MATCHES "Release")
#        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../../bin/unix/release")
#    endif()
#elseif(WIN32)
#    if(CMAKE_BUILD_TYPE MATCHES "Debug")
#        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../../bin/win32/debug")
#    elseif(CMAKE_BUILD_TYPE MATCHES "Release")
#        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../../bin/win32/release")
#    endif()
#endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

link_directories("${CMAKE_RUNTIME_OUTPUT_DIRECTORY}") # for qwt linking

# project flags ================================================================
set(project_name "tanks")

project("${project_name}" LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# other ========================================================================
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # sourcetrail

# project ======================================================================
set(APP_VER_MAJ 0)
set(APP_VER_MIN 1)
set(APP_VER_PAT 0)
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(APP_BUILD_TYPE d)
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
    set(APP_BUILD_TYPE r)
endif()
set(APP_NAME            "tanks")
set(APP_NAME_PRINT      "Tanks")
set(APP_NAME_ORG        "FooBar")
set(APP_NAME_ORG_PRINT  "FooBar")

execute_process (
    COMMAND git rev-parse --short HEAD
    OUTPUT_VARIABLE app_git_version
)
string(REPLACE "\n" "" app_git_version "${app_git_version}")
set(APP_GIT_REVISION "${app_git_version}")

execute_process (
    COMMAND git rev-list --count HEAD
    OUTPUT_VARIABLE app_git_commit
)
string(REPLACE "\n" "" app_git_commit "${app_git_commit}")
set(APP_GIT_COMMIT "${app_git_commit}")

find_package(SDL2 REQUIRED)

# messages =====================================================================
get_property(link_dirs DIRECTORY PROPERTY LINK_DIRECTORIES)
message("=====================================================================")
message(APP_VER_MAJ: "${APP_VER_MAJ}")
message(APP_VER_MIN: "${APP_VER_MIN}")
message(APP_VER_PAT: "${APP_VER_PAT}")
message(APP_BUILD_TYPE: "${APP_BUILD_TYPE}")
message(APP_NAME: "${APP_NAME}")
message(APP_NAME_PRINT: "${APP_NAME_PRINT}")
message(APP_NAME_ORG: "${APP_NAME_ORG}")
message(APP_NAME_ORG_PRINT: "${APP_NAME_ORG_PRINT}")
message(APP_GIT_REVISION: "${APP_GIT_REVISION}")
message(APP_GIT_COMMIT: "${APP_GIT_COMMIT}")
message(CMAKE_RUNTIME_OUTPUT_DIRECTORY: "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(LINK_DIRECTORIES: "${link_dirs}")
message("")
message(CMAKE_BUILD_TYPE: "${CMAKE_BUILD_TYPE}")
message(CMAKE_C_COMPILER: "${CMAKE_C_COMPILER}")
message(CMAKE_CXX_COMPILER: "${CMAKE_CXX_COMPILER}")
message("=====================================================================")

# include directories ==========================================================
include_directories("${PROJECT_BINARY_DIR}")
include_directories(src)
include_directories(/usr/include)

set(SOURCES
    src/app.cpp
    src/app_state/game.cpp
    src/app_state/menu.cpp
    src/app_state/scores.cpp
    src/appconfig.cpp
    src/engine/engine.cpp
    src/engine/renderer.cpp
    src/engine/spriteconfig.cpp
    src/main.cpp
    src/objects/bonus.cpp
    src/objects/brick.cpp
    src/objects/bullet.cpp
    src/objects/eagle.cpp
    src/objects/enemy.cpp
    src/objects/object.cpp
    src/objects/player.cpp
    src/objects/tank.cpp
)

set(RESOURCE_FILES
    resources/font/prstartk.ttf
    resources/levels
    resources/png/texture.png
)
file(COPY ${RESOURCE_FILES} DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# configure file ===============================================================
configure_file (
    "${PROJECT_SOURCE_DIR}/src/version_config.h.in"
    "${PROJECT_BINARY_DIR}/version_config.h"
)

add_executable("${project_name}" WIN32 "${SOURCES}") # WIN32 to prevent open separate console window

target_link_libraries("${project_name}" PRIVATE SDL2 SDL2_image SDL2_ttf)
