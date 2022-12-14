cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
set(NAME NutshellWindowModule)
project(${NAME} VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NTSH_DEFINES "")

add_subdirectory(external/Module)
add_subdirectory(external/Common)

list(APPEND NTSH_DEFINES NTSH_CURRENT_MODULE_WINDOW)

set(MODULE_SOURCES
	src/ntsh_window_module.cpp)	
set(MODULE_HEADERS
	src/ntsh_window_module.h)

set(SOURCES ${MODULE_SOURCES})
set(HEADERS ${MODULE_HEADERS})

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE NutshellEngine::Module NutshellEngine::Common)

target_compile_options(${PROJECT_NAME} PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
	$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Werror>)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	${NTSH_DEFINES}
	PUBLIC
	$<$<CONFIG:Debug>:NTSH_DEBUG>
	$<$<CONFIG:MinSizeRel>:NTSH_RELEASE>
	$<$<CONFIG:Release>:NTSH_RELEASE>
	$<$<CONFIG:RelWithDebInfo>:NTSH_DEBUG>)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    DEFINE_SYMBOL "NutshellModule_EXPORTS")

set(NTSH_ENGINE_MODULES_DIRECTORY "" CACHE PATH "Give the option to install the built module into NutshellEngine\'s modules directory.")
if(EXISTS ${NTSH_ENGINE_MODULES_DIRECTORY})
	message(STATUS "Found NutshellEngine\'s modules directory at ${NTSH_ENGINE_MODULES_DIRECTORY}.")
	set(CMAKE_INSTALL_PREFIX ${NTSH_ENGINE_MODULES_DIRECTORY})
	if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
		install(TARGETS ${PROJECT_NAME}
			RUNTIME
			DESTINATION ${NTSH_ENGINE_MODULES_DIRECTORY})
	else()
		install(TARGETS ${PROJECT_NAME}
			LIBRARY
			DESTINATION ${NTSH_ENGINE_MODULES_DIRECTORY})
	endif()
elseif(NOT NTSH_ENGINE_MODULES_DIRECTORY STREQUAL "")
	message(WARNING "Could not find NutshellEngine\'s modules directory at ${NTSH_ENGINE_MODULES_DIRECTORY}.")
endif()