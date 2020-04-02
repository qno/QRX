cmake_minimum_required(VERSION 3.8)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version")

# set this to the plugin slug!
set(PLUGIN_NAME QRX)

project(VCVRack${PLUGIN_NAME}Plugin)

include(thirdparty/tinyfsm/TinyFSM.cmake)
include(thirdparty/fakeit/FakeIt.cmake)
include(CTest)

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

if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  message(STATUS "conanbuildinfo.cmake detected, configure project with Conan")
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup()
else ()
  message(STATUS "conanbuildinfo.cmake not detected, try to configure project with RACK_SDK variable")
  if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    if ("${RACK_SDK}" STREQUAL "")
      message(FATAL_ERROR "Path to Rack SDK missing! Add -DRACK_SDK=<path to Rack SDK> to the cmake call.")
    else ()
      message(STATUS "Use Rack SDK: ${RACK_SDK}")
      include_directories("${RACK_SDK}/include" "${RACK_SDK}/dep/include")
      link_directories(${RACK_SDK})
      add_definitions(-DARCH_WIN)
      set (CONAN_LIBS "Rack")
      set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    endif ()
  else ()
    message(FATAL_ERROR "Configure project with RACK_SDK variable is only supported on Windows platform!")
  endif ()
endif ()

add_subdirectory(src)
add_subdirectory(test)

file(GLOB LICENSE LICENSE*)
file(INSTALL plugin.json res ${LICENSE} DESTINATION dist/${PLUGIN_NAME})
install(TARGETS ${LIB_NAME} LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/dist/${PLUGIN_NAME} OPTIONAL)
install(DIRECTORY ${PROJECT_BINARY_DIR}/dist/${PLUGIN_NAME}/ DESTINATION ${PLUGIN_NAME})
