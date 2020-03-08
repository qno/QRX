find_package(Catch2 REQUIRED)

add_executable(catchTest myCatch.cpp)
target_link_libraries(catchTest Catch2::Catch2)
