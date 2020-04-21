set(SOURCES QRXPlugin.cpp
            PluginSettings.cpp
            cvwizard/CVWizardRackModel.cpp
            cvwizard/CVWizardModule.cpp
            cvwizard/CVWizardWidget.cpp
            cvwizard/CVWizard.cpp
            cvwizard/model/CVWizardModel.cpp
            cvwizard/model/ModuleMapping.cpp
            cvwizard/model/CVParameterMapping.cpp
            cvwizard/ui/Tooltip.cpp)

add_library(${LIB_NAME} MODULE ${SOURCES})

target_compile_options(${LIB_NAME} PRIVATE "-fuse-ld=gold" "-flto")
target_include_directories(${LIB_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${LIB_NAME} ${CONAN_LIBS} SML SigSlot)

if (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  set_target_properties(${LIB_NAME} PROPERTIES SUFFIX ".dylib")
endif ()

set_target_properties(${LIB_NAME} PROPERTIES PREFIX "")
