add_library(FakeIt INTERFACE)
target_include_directories(FakeIt INTERFACE $<INSTALL_INTERFACE:include> FakeIt/include)
target_compile_options(FakeIt INTERFACE "-O0")
