cmake_minimum_required(VERSION 3.19)

if(APPLE AND NOT DEFINED CMAKE_OSX_ARCHITECTURES)
set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64"
CACHE STRING "Build universal macOS binaries")
endif()

string(REGEX REPLACE "(.*)/" "" THIS_FOLDER_NAME "${CMAKE_CURRENT_SOURCE_DIR}")
project(${THIS_FOLDER_NAME})

option(EXPORT_COMPILE_COMMANDS "Export compile commands for LSP" ON)
if (EXPORT_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif ()

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

# Generate a project for every folder in the "source/projects" folder

SUBDIRLIST(PROJECT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/source/projects)
foreach (project_dir ${PROJECT_DIRS})
    set(project_path ${CMAKE_CURRENT_SOURCE_DIR}/source/projects/${project_dir})
    # message("checking in: ${project_path}")
    if (EXISTS "${project_path}/CMakeLists.txt")
        # message("Generating: ${project_dir}")
        add_subdirectory(${project_path})
    endif ()
endforeach ()
