find_package(Threads REQUIRED)
add_library(SigSlot INTERFACE)
target_include_directories(SigSlot INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/thirdparty/sigslot/include>)
target_link_libraries(SigSlot INTERFACE Threads::Threads)
