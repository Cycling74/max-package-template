include(${CMAKE_CURRENT_SOURCE_DIR}/../../max-sdk-base/script/max-pretarget.cmake)

#############################################################
# MAX EXTERNAL
#############################################################

include_directories( 
	"${MAX_SDK_INCLUDES}"
	"${MAX_SDK_MSP_INCLUDES}"
	"${MAX_SDK_JIT_INCLUDES}"

    # Add any additional includes here
    # "${CMAKE_CURRENT_SOURCE_DIR}/../../include"  # e.g. if you put your includes in /source/include
)

set(PROJECT_SRC
    # Add any files you need to compile
    "example.c"
)

add_library( 
	${PROJECT_NAME} 
	MODULE
	${PROJECT_SRC}
)

# note: to include third-party libraries or headers,
# you should add target_link_library or target_include_directories commands at this point in the file
# you can use ${PROJECT_NAME} as the target name -- the target is not defined
# until after the add_library command

include(${CMAKE_CURRENT_SOURCE_DIR}/../../max-sdk-base/script/max-posttarget.cmake)
