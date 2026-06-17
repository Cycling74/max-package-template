cmake_minimum_required(VERSION 3.25)

set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "macOS architecture")

option(EXPORT_COMPILE_COMMANDS "Export compile commands for LSP" ON)
if (EXPORT_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif ()

include(FetchContent)

message(STATUS "Fetching max-sdk-base")
FetchContent_Declare(
    max-sdk-base
    GIT_REPOSITORY https://github.com/Cycling74/max-sdk-base.git
    GIT_TAG main
)
FetchContent_MakeAvailable(max-sdk-base)

string(REGEX REPLACE "(.*)/" "" THIS_FOLDER_NAME "${CMAKE_CURRENT_SOURCE_DIR}")
project(${THIS_FOLDER_NAME})

MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(PROJECT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/source/projects)
foreach (project_dir ${PROJECT_DIRS})
    set(project_path ${CMAKE_CURRENT_SOURCE_DIR}/source/projects/${project_dir})
    if (EXISTS "${project_path}/CMakeLists.txt")
        add_subdirectory(${project_path})
    endif ()
endforeach ()
