#pragma once

#include <QRXPlugin.hpp>
#include <CVWizard/ModuleSettings.hpp>

#include <atomic>
#include <memory>

namespace qrx {
namespace cvwizard {

class CVWizardModule : public rack::engine::Module
{
public:
   
   static constexpr char const* SLUG = "CVWizard";
   
   enum ParamIds
   {
      NUM_PARAMS
   };
   
   enum InputIds
   {
      NUM_INPUTS
   };
   
   enum OutputIds
   {
      NUM_OUTPUTS
   };
   
   enum LightIds
   {
      NUM_LIGHTS
   };
   
   CVWizardModule();
   ~CVWizardModule() noexcept override;
   
   bool isMasterModule() const;
   
   void process(const ProcessArgs& args) override;
   
   json_t* dataToJson() override;
   
   void dataFromJson(json_t* root) override;
   
   void addSettings(std::shared_ptr<ModuleSettings> settings);
   
   std::shared_ptr<ModuleSettings> getSettings() const;
   
private:
   
   void determineMasterModuleStatus();
   
   static std::atomic_bool _isRackPluginMasterModule;
   bool _isRackMasterModule = false;
   std::shared_ptr<ModuleSettings> _settings;
};

}
}
