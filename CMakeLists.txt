cmake_minimum_required(VERSION 3.5)

# set this to the plugin slug!
set(PLUGIN_NAME QRX)

project(VCVRack${PLUGIN_NAME}Plugin)

set(CMAKE_CXX_STANDARD 14)

if ("${PLUGIN_SLUG}" STREQUAL "")
  message(WARNING "Plugin Slug is missing! Add -DPLUGIN_SLUG=<SLUG> to the cmake call.")
endif ()

if (NOT "${PLUGIN_NAME}" STREQUAL "${PLUGIN_SLUG}")
  message(WARNING "Plugin Slug '${PLUGIN_SLUG}' doesn't match defined PLUGIN_NAME variable '${PLUGIN_NAME}'")
endif ()

message(STATUS "Plugin Slug: '${PLUGIN_SLUG}'")

# Do not change the LIB_NAME!
set(LIB_NAME plugin)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.hpp)

file(GLOB_RECURSE CVWIZARD_SOURCES src/CVWizard/*.cpp)
file(GLOB_RECURSE CVWIZARD_HEADERS include/CVWizard/*.hpp)

source_group("Header Files" FILES ${HEADERS})
source_group("CVWizard Header Files" FILES ${CVWIZARD_HEADERS})

add_library(${LIB_NAME} MODULE ${SOURCES} ${CVWIZARD_SOURCES})

target_include_directories(${LIB_NAME} PRIVATE include)

target_link_libraries(${LIB_NAME} ${CONAN_LIBS})

if (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  set_target_properties(${LIB_NAME} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
  set_target_properties(${LIB_NAME} PROPERTIES SUFFIX ".dylib")
endif ()

set_target_properties(${LIB_NAME} PROPERTIES PREFIX "")

file(GLOB LICENSE LICENSE*)
file(INSTALL plugin.json res ${LICENSE} DESTINATION dist/${PLUGIN_NAME})
install(DIRECTORY ${PROJECT_BINARY_DIR}/lib/ DESTINATION ${PROJECT_BINARY_DIR}/dist/${PLUGIN_NAME} OPTIONAL)
install(DIRECTORY ${PROJECT_BINARY_DIR}/dist/${PLUGIN_NAME}/ DESTINATION ${PLUGIN_NAME})
