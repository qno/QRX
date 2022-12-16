set(SOURCES QRXPlugin.cpp
            PluginSettings.cpp
            cvwizard/CVWizardRackModel.cpp
            cvwizard/CVWizardModule.cpp
            cvwizard/CVWizardWidget.cpp
            cvwizard/CVWizard.cpp
            cvwizard/utility/Widget.cpp
            cvwizard/model/CVWizardModel.cpp
            cvwizard/model/ModuleMapping.cpp
            cvwizard/model/CVParameterMapping.cpp
            cvwizard/ui/Tooltip.cpp)

target_sources(${RACK_PLUGIN_LIB} PRIVATE ${SOURCES})
target_include_directories(${RACK_PLUGIN_LIB} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${RACK_PLUGIN_LIB} PRIVATE RackSDK SML SigSlot)
