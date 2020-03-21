find_package(Catch2 REQUIRED)

if (NOT MINGW)
  set(TEST_SOURCES ${PROJECT_SOURCE_DIR}/src/CVWizard/CVWizardModule.cpp)
endif ()

add_executable(catchTest myCatch.cpp ${TEST_SOURCES})

# -O0 is required for FakeIt!
target_compile_options(catchTest PRIVATE "-O0" "--coverage" "-g")
# target_link_options is only possible since CMake 3.13
#target_link_options(catchTest PRIVATE "--coverage")
set_target_properties(catchTest PROPERTIES LINK_FLAGS "--coverage")
target_link_libraries(catchTest Catch2::Catch2)

include_directories( ${PROJECT_SOURCE_DIR}/include include)

if (MINGW)
  # avoid linking failure with too big obj file error
  target_compile_options(catchTest PRIVATE "-Wa,-mbig-ob")
endif ()

include(Catch)
catch_discover_tests(catchTest)
