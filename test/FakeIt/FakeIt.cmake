add_library(FakeIt INTERFACE)
target_include_directories(FakeIt INTERFACE include)
target_compile_options(FakeIt INTERFACE "-O0")
