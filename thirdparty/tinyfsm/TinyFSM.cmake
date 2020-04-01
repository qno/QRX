add_library(TinyFSM INTERFACE)
target_include_directories(TinyFSM INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/thirdparty/tinyfsm/include>)
