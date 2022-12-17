option(ENABLE_COVERAGE "Enable code coverage analysis" OFF)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(UT_EXE PluginUnittests)

set(SRC ${PROJECT_SOURCE_DIR}/src)
set(SOURCES ${SRC}/PluginSettings.cpp
            ${SRC}/cvwizard/CVWizardModule.cpp
            ${SRC}/cvwizard/CVWizard.cpp
            ${SRC}/cvwizard/utility/Widget.cpp
            ${SRC}/cvwizard/model/CVWizardModel.cpp
            ${SRC}/cvwizard/model/ModuleMapping.cpp
            ${SRC}/cvwizard/model/CVParameterMapping.cpp
            ${SRC}/cvwizard/ui/Tooltip.cpp)

set(TESTS_SOURCES PluginJsonTest.cpp
                  PluginSettingsTest.cpp
                  cvwizard/CVWizardModuleTest.cpp
                  cvwizard/CVWizardTest.cpp
                  cvwizard/ModuleSettingsTest.cpp
                  cvwizard/utility/WidgetTest.cpp
                  cvwizard/controller/CVWizardControllerTest.cpp
                  cvwizard/controller/MappingControllerTest.cpp
                  cvwizard/model/CVWizardModelTest.cpp
                  cvwizard/model/ModuleMappingTest.cpp
                  cvwizard/model/CVParameterMappingTest.cpp
                  cvwizard/ui/TooltipTest.cpp)

add_library(RackSDKMissingSymbols STATIC RackSDKMissingSymbols.cpp)
target_link_libraries(RackSDKMissingSymbols PUBLIC RackSDK)
target_compile_definitions(RackSDKMissingSymbols PRIVATE QRX_UNITTESTS_ASSET_DIR=${CMAKE_CURRENT_BINARY_DIR})

add_executable(${UT_EXE} CatchMain.cpp ${TESTS_SOURCES} ${SOURCES})
target_include_directories(${UT_EXE} PRIVATE include ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(${UT_EXE} PRIVATE QRX_UNITTESTS
                                     PRIVATE PLUGIN_JSON_FILE=${PROJECT_SOURCE_DIR}/plugin.json)
target_link_libraries(${UT_EXE} PRIVATE RackSDK
  SML
  SigSlot
  FakeIt
  CONAN_PKG::catch2)

if (ENABLE_COVERAGE)
  message (STATUS "code coverage analysis is enabled")
  target_link_options(${UT_EXE} PRIVATE "--coverage")
  set_target_properties(${UT_EXE} PROPERTIES LINK_FLAGS "--coverage")
endif ()

include(Catch)
catch_discover_tests(${UT_EXE})

file(GLOB JSON_FILES fixtures/*.json)
file(INSTALL ${JSON_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
