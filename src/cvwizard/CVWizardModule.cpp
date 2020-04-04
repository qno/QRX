#include <cvwizard/CVWizardModule.hpp>
#include <PluginSettings.hpp>
#include <utility>

using namespace rack;

#ifndef QRX_UNITTESTS
extern std::shared_ptr<qrx::PluginSettings> pluginSettings;

std::shared_ptr<qrx::cvwizard::ModuleSettings> addPluginSettings()
{
   return std::dynamic_pointer_cast<qrx::cvwizard::ModuleSettings>(pluginSettings);
}
#endif

namespace qrx {
namespace cvwizard {

std::atomic_bool CVWizardModule::_isRackPluginMasterModule{false};

CVWizardModule::CVWizardModule()
   : Module()
   , controller::KeyboardEventsProviding()
#ifndef QRX_UNITTESTS
   , _settings{addPluginSettings()}
#endif
{
   determineMasterModuleStatus();
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
   _controller.setKeyboardEventsProvider(this);
   _controller.start();
}

CVWizardModule::~CVWizardModule() noexcept
{
   if (_isRackMasterModule)
   {
      _isRackPluginMasterModule = false;
      DEBUG("CVWizardModule (#%d) removed as master module instance", this);
   }
}

bool CVWizardModule::isMasterModule() const
{
   return _isRackMasterModule;
}

void CVWizardModule::process(const ProcessArgs& args)
{
   determineMasterModuleStatus();
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

void CVWizardModule::addSettings(std::shared_ptr<ModuleSettings> settings)
{
   _settings = std::move(settings);
}

std::shared_ptr<ModuleSettings> CVWizardModule::getSettings() const
{
   return _settings;
}

void CVWizardModule::determineMasterModuleStatus()
{
   if (!_isRackPluginMasterModule)
   {
      DEBUG("CVWizardModule (#%d) instance becomes master module", this);
      _isRackPluginMasterModule = true;
      _isRackMasterModule = true;
   }
}

bool CVWizardModule::isControlKeyPressed() const
{
   return (GLFW_MOD_CONTROL == (APP->window->getMods() & GLFW_MOD_CONTROL));
}

bool CVWizardModule::isMappingKeyPressed() const
{
   return (GLFW_PRESS == glfwGetKey(APP->window->win, _settings->getCVWizardSettings().MappingKey));
}

bool CVWizardModule::isMappingCancelKeyPressed() const
{
   return (GLFW_PRESS == glfwGetKey(APP->window->win, _settings->getCVWizardSettings().MappingCancelKey));
}

bool CVWizardModule::isTooltipKeyPressed() const
{
   return (GLFW_PRESS == glfwGetKey(APP->window->win, _settings->getCVWizardSettings().MappingTooltipKey));
}

}
}
