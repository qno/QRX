option(ENABLE_COVERAGE "Enable code coverage analysis" OFF)

find_package(Catch2 REQUIRED)
include(FakeIt/FakeIt.cmake)

set(UT_EXE PluginUnittests)

set(SRC ${PROJECT_SOURCE_DIR}/src)
set(SOURCES ${SRC}/QRXPlugin.cpp
            ${SRC}/PluginSettings.cpp
            ${SRC}/CVWizard/CVWizard.cpp
            ${SRC}/CVWizard/CVWizardModule.cpp
            ${SRC}/CVWizard/CVWizardWidget.cpp)

set(TESTS_SOURCES QRXPluginTest.cpp
                  PluginJsonTest.cpp
                  PluginSettingsTest.cpp
                  CVWizard/CVWizardTest.cpp
                  CVWizard/ModuleSettingsTest.cpp)

add_library(RackSDKFakeImplementation STATIC RackSDKFakeImplementation.cpp)
target_compile_definitions(RackSDKFakeImplementation PRIVATE QRX_UNITTESTS_ASSET_DIR=${CMAKE_CURRENT_BINARY_DIR})

add_executable(${UT_EXE} CatchMain.cpp ${TESTS_SOURCES} ${SOURCES})
target_include_directories(${UT_EXE} PRIVATE ${PROJECT_SOURCE_DIR}/include include)
target_compile_options(${UT_EXE} PRIVATE "-fuse-ld=gold" "-flto")
target_compile_definitions(${UT_EXE} PRIVATE QRX_UNITTESTS
                                     PRIVATE PLUGIN_JSON_FILE=${PROJECT_SOURCE_DIR}/plugin.json)
target_link_libraries(${UT_EXE} PRIVATE RackSDKFakeImplementation ${CONAN_LIBS_JANSSON} FakeIt Catch2::Catch2)

if (ENABLE_COVERAGE)
  message (STATUS "code coverage analysis is enabled")
  target_compile_options(${UT_EXE} PRIVATE "--coverage" "-g")
  #target_link_options(${UT_EXE} PRIVATE "--coverage") # only possible since CMake 3.13
  set_target_properties(${UT_EXE} PROPERTIES LINK_FLAGS "--coverage")
endif ()

include(Catch)
catch_discover_tests(${UT_EXE})

file(GLOB JSON_FILES fixtures/*.json)
file(INSTALL ${JSON_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
