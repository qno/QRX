add_library(SML INTERFACE)
if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    target_compile_options(SML INTERFACE -Wno-subobject-linkage)
endif ()
target_include_directories(SML INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/thirdparty/sml/include>)
