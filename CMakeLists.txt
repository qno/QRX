cmake_minimum_required(VERSION 3.16)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version")
project(QRX)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

set(PLUGIN_NAME ${PROJECT_NAME})
set(ADDITIONAL_PLUGIN_DISTRIBUTABLES "")
include(RackSDK.cmake)

include(thirdparty/sml/SML.cmake)
include(thirdparty/sigslot/SigSlot.cmake)

add_subdirectory(src)

# Unit Test dependencies handled with Conan Package Manager (https://conan.io)
if (EXISTS ${CMAKE_BINARY_DIR}/conaninfo.txt)
include(CTest)
add_subdirectory(test)
endif ()
