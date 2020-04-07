add_library(SML INTERFACE)
target_include_directories(SML INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/thirdparty/sml/include>)
