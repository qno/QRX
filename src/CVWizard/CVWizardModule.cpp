#include <CVWizard/CVWizardModule.hpp>
#include <PluginSettings.hpp>

using namespace rack;

extern std::shared_ptr<qrx::PluginSettings> pluginSettings;

std::shared_ptr<qrx::cvwizard::ModuleSettings> addSettings()
{
   return std::dynamic_pointer_cast<qrx::cvwizard::ModuleSettings>(pluginSettings);
}

namespace qrx {
namespace cvwizard {

CVWizardModule::CVWizardModule()
   : Module()
   , _settings(addSettings())
{
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
}

void CVWizardModule::process(const ProcessArgs& args)
{

}

json_t* CVWizardModule::dataToJson()
{
   auto json = json_object();
   
   json_object_set_new(json, "param1", json_string("0815"));
   json_object_set_new(json, "param2", json_integer(2));
   json_object_set_new(json, "param3", json_boolean(true));
   
   return json;
}

void CVWizardModule::dataFromJson(json_t* root)
{

}

ModuleSettings& CVWizardModule::getSettings() const
{
   return *_settings;
}

}
}
