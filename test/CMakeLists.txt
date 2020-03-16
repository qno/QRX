find_package(Catch2 REQUIRED)

add_executable(catchTest myCatch.cpp)
target_link_libraries(catchTest Catch2::Catch2)

include_directories(catchTest ${PROJECT_SOURCE_DIR}/include)

# this is needed in Debug mode, otherwise linking will fail with too big obj file error
#if (${MINGW})
#  target_compile_options(catchTest PRIVATE "-Wa,-mbig-ob")
#endif ()

include(CTest)
enable_testing()
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(catchTest)
