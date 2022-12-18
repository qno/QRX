#include <cvwizard/CVWizardModule.hpp>
#include <PluginSettings.hpp>

#include <mutex>

#ifndef QRX_UNITTESTS
extern std::shared_ptr<qrx::PluginSettings> pluginSettings;

std::shared_ptr<qrx::cvwizard::ModuleSettings> addPluginSettings()
{
   return std::dynamic_pointer_cast<qrx::cvwizard::ModuleSettings>(pluginSettings);
}
#endif

namespace qrx::cvwizard {

using namespace boundary::rack;

static std::mutex s_MasterModuleStatusMutex;
std::atomic_bool CVWizardModule::s_isRackPluginMasterModule{false};

CVWizardModule::CVWizardModule()
 : Module{}
#ifndef QRX_UNITTESTS
   , _settings{addPluginSettings()}
#endif
{
   DEBUG("CVWizardModule ctr (#0x%0x)", this);
   determineMasterModuleStatus();
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
}

CVWizardModule::~CVWizardModule() noexcept
{
   DEBUG("CVWizardModule dtr (#0x%0x)", this);
   if (_isRackMasterModule)
   {
      s_isRackPluginMasterModule = false;
      DEBUG("CVWizardModule (#%0x) removed as master module instance", this);
   }
}

bool CVWizardModule::isMasterModule() const
{
   return _isRackMasterModule;
}

void CVWizardModule::process(const engine::ProcessArgs& args)
{
   determineMasterModuleStatus();
}

json_t* CVWizardModule::dataToJson()
{
   json_t* json = nullptr;
   if (_isRackMasterModule)
   {
      json = json_object();
      json_object_set_new(json, "param1", json_string("0815"));
      json_object_set_new(json, "param2", json_integer(2));
      json_object_set_new(json, "param3", json_boolean(true));
   }
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
   if (s_MasterModuleStatusMutex.try_lock())
   {
      if (!s_isRackPluginMasterModule)
      {
         DEBUG("CVWizardModule (#0x%0x) instance becomes master module", this);
         s_isRackPluginMasterModule = true;
         _isRackMasterModule        = true;
      }
      s_MasterModuleStatusMutex.unlock();
   }
}

}
