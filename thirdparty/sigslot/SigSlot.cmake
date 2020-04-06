add_library(SigSlot INTERFACE)
target_include_directories(SigSlot INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/thirdparty/sigslot/include>)
