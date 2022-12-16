cmake_minimum_required(VERSION 3.16)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version")
project(QRX)

set(CMAKE_CXX_STANDARD 17)

set(PLUGIN_NAME ${PROJECT_NAME})
set(ADDITIONAL_PLUGIN_DISTRIBUTABLES "")
include(RackSDK.cmake)

include(thirdparty/sml/SML.cmake)
include(thirdparty/sigslot/SigSlot.cmake)
include(thirdparty/fakeit/FakeIt.cmake)
include(CTest)

target_compile_options(${RACK_PLUGIN_LIB} PRIVATE "-fuse-ld=gold" "-flto")

add_subdirectory(src)
#add_subdirectory(test)
