option(ENABLE_COVERAGE "Enable code coverage analysis" OFF)

find_package(Catch2 REQUIRED)

set(UT_EXE PluginUnittests)

file(GLOB TEST_SOURCES *Test.cpp)

add_library(RackSDKReferences STATIC RackSDKMissingReferences.cpp)

add_executable(${UT_EXE} CatchMain.cpp myCatch.cpp ${TEST_SOURCES} ${SOURCES})

target_link_libraries(${UT_EXE} RackSDKReferences ${CONAN_LIBS_JANSSON})

# -O0 is required for FakeIt!
target_compile_options(${UT_EXE} PRIVATE "-O0" "-fuse-ld=gold" "-flto")
target_link_libraries(${UT_EXE} Catch2::Catch2)

include_directories( ${PROJECT_SOURCE_DIR}/include include)

if (${ENABLE_COVERAGE})
  message (STATUS "code coverage analysis is enabled")
  target_compile_options(${UT_EXE} PRIVATE "--coverage" "-g")
  # target_link_options is only possible since CMake 3.13
  #target_link_options(catchTest PRIVATE "--coverage")
  set_target_properties(${UT_EXE} PROPERTIES LINK_FLAGS "--coverage")
endif ()

include(Catch)
catch_discover_tests(${UT_EXE})
