add_library(FakeIt INTERFACE)
target_include_directories(FakeIt INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/thirdparty/fakeit/include>)
target_compile_options(FakeIt INTERFACE "-O0")
