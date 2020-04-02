#include <CVWizard/CVWizardModule.hpp>
#include <PluginSettings.hpp>

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
#ifndef QRX_UNITTESTS
   , _settings{addPluginSettings()}
#endif
{
   if (!_isRackPluginMasterModule)
   {
      INFO("ctr CVWizardModule #%d becomes master module", this);
      _isRackPluginMasterModule = true;
      _isRackMasterModule = true;
   }
   else
   {
      INFO("ctr CVWizardModule #%d doesn't become master module", this);
   }
   
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
}

CVWizardModule::~CVWizardModule() noexcept
{
   if (_isRackMasterModule)
   {
      _isRackPluginMasterModule = false;
   }
}

bool CVWizardModule::isMasterModule() const
{
   return _isRackMasterModule;
}

void CVWizardModule::process(const ProcessArgs& args)
{
   if (_isRackMasterModule)
   {
      // do processing stuff here
   }
   else
   {
      if (!_isRackPluginMasterModule)
      {
         _isRackPluginMasterModule = true;
         _isRackMasterModule = true;
      }
   }
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
   _settings = settings;
}

std::shared_ptr<ModuleSettings> CVWizardModule::getSettings() const
{
   return _settings;
}

}
}
