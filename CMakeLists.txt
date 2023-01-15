cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
set(NAME NutshellEngine-WindowModule)
project(${NAME} VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NTSHENGN_DEFINES "")

add_subdirectory(external/Module)
add_subdirectory(external/Common)

list(APPEND NTSHENGN_DEFINES NTSHENGN_CURRENT_MODULE_WINDOW)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(MODULE_SOURCES
	src/ntshengn_window_module.cpp src/qtwindow.cpp)	
set(MODULE_HEADERS
	src/ntshengn_window_module.h src/qtwindow.h)

set(SOURCES ${MODULE_SOURCES})
set(HEADERS ${MODULE_HEADERS})

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE NutshellEngine::Module NutshellEngine::Common Qt5::Core Qt5::Gui Qt5::Widgets)

target_compile_options(${PROJECT_NAME} PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
	$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Werror>)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	${NTSHENGN_DEFINES}
	PUBLIC
	$<$<CONFIG:Debug>:NTSHENGN_DEBUG>
	$<$<CONFIG:MinSizeRel>:NTSHENGN_RELEASE>
	$<$<CONFIG:Release>:NTSHENGN_RELEASE>
	$<$<CONFIG:RelWithDebInfo>:NTSHENGN_DEBUG>)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    DEFINE_SYMBOL "NutshellEngineModule_EXPORTS")

set(NTSHENGN_MODULES_DIRECTORY "" CACHE PATH "Give the option to install the built module into NutshellEngine\'s modules directory.")
if(EXISTS ${NTSHENGN_MODULES_DIRECTORY})
	message(STATUS "Found NutshellEngine\'s modules directory at ${NTSHENGN_MODULES_DIRECTORY}.")
	set(CMAKE_INSTALL_PREFIX ${NTSHENGN_MODULES_DIRECTORY})
	if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
		install(TARGETS ${PROJECT_NAME}
			RUNTIME
			DESTINATION ${NTSHENGN_MODULES_DIRECTORY})
	else()
		install(TARGETS ${PROJECT_NAME}
			LIBRARY
			DESTINATION ${NTSHENGN_MODULES_DIRECTORY})
	endif()
elseif(NOT NTSHENGN_MODULES_DIRECTORY STREQUAL "")
	message(WARNING "Could not find NutshellEngine\'s modules directory at ${NTSHENGN_MODULES_DIRECTORY}.")
endif()