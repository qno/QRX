find_package(Catch2 REQUIRED)

if (NOT MINGW)
  set(TEST_SOURCES ${PROJECT_SOURCE_DIR}/src/CVWizard/CVWizardModule.cpp)
endif ()

add_executable(catchTest myCatch.cpp ${TEST_SOURCES})
target_link_libraries(catchTest Catch2::Catch2)

include_directories(catchTest ${PROJECT_SOURCE_DIR}/include)

# this is needed in Debug mode, otherwise linking will fail with too big obj file error
#if (${MINGW})
#  target_compile_options(catchTest PRIVATE "-Wa,-mbig-ob")
#endif ()

include(CTest)
enable_testing()
include(Catch)
catch_discover_tests(catchTest)
