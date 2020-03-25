add_library(FakeIt::FakeIt INTERFACE IMPORTED)
target_include_directories(FakeIt::FakeIt INTERFACE include)
target_compile_options(FakeIt::FakeIt INTERFACE "-O0")
