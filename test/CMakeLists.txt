option(ENABLE_COVERAGE "Enable code coverage analysis" OFF)

find_package(Catch2 REQUIRED)

set(UT_EXE PluginUnittests)

file(GLOB TEST_SOURCES *Test.cpp)

add_library(TEST_HEADERS INTERFACE)
target_include_directories(TEST_HEADERS INTERFACE ${PROJECT_SOURCE_DIR}/include INTERFACE include)
target_compile_options(TEST_HEADERS INTERFACE "-O0") # -O0 is required for FakeIt!

add_library(RackSDKFakeImplementation STATIC RackSDKFakeImplementation.cpp)

add_executable(${UT_EXE} CatchMain.cpp myCatch.cpp ${TEST_SOURCES} ${SOURCES})
target_compile_options(${UT_EXE} PRIVATE "-fuse-ld=gold" "-flto")
target_compile_definitions(${UT_EXE} PRIVATE PLUGIN_JSON_FILE=${PROJECT_SOURCE_DIR}/plugin.json)
target_link_libraries(${UT_EXE} TEST_HEADERS RackSDKFakeImplementation ${CONAN_LIBS_JANSSON} Catch2::Catch2)


if (ENABLE_COVERAGE)
  message (STATUS "code coverage analysis is enabled")
  target_compile_options(${UT_EXE} PRIVATE "--coverage" "-g")
  #target_link_options(${UT_EXE} PRIVATE "--coverage") # only possible since CMake 3.13
  set_target_properties(${UT_EXE} PROPERTIES LINK_FLAGS "--coverage")
endif ()

include(Catch)
catch_discover_tests(${UT_EXE})
