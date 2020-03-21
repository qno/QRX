option(ENABLE_COVERAGE "Enable code coverage analysis" OFF)

find_package(Catch2 REQUIRED)

add_library(RackSDKReferences STATIC RackSDKMissingReferences)
add_executable(catchTest myCatch.cpp CatchMain.cpp ${SOURCES})

target_link_libraries(catchTest RackSDKReferences)

# -O0 is required for FakeIt!
target_compile_options(catchTest PRIVATE "-O0")
target_link_libraries(catchTest Catch2::Catch2)

include_directories( ${PROJECT_SOURCE_DIR}/include include)

if (MINGW)
  # avoid linking failure with too big obj file error
  target_compile_options(catchTest PRIVATE "-Wa,-mbig-ob")
endif ()

if (${ENABLE_COVERAGE})
  message (STATUS "code coverage analysis is enabled")
  target_compile_options(catchTest PRIVATE "--coverage" "-g")
  # target_link_options is only possible since CMake 3.13
  #target_link_options(catchTest PRIVATE "--coverage")
  set_target_properties(catchTest PROPERTIES LINK_FLAGS "--coverage")
endif ()

include(Catch)
catch_discover_tests(catchTest)
