#pragma once

#include <boundary/rack/Types.hpp>
#include <cvwizard/ModuleSettings.hpp>

#include <atomic>
#include <memory>

namespace qrx::cvwizard {

using namespace boundary;

class CVWizardModule final : public rack::Module
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
   
   void process(const rack::engine::ProcessArgs& args) override;
   
   json_t* dataToJson() override;
   
   void dataFromJson(json_t* root) override;
   
   bool isMasterModule() const;
   
   void addSettings(std::shared_ptr<ModuleSettings> settings);
   
   std::shared_ptr<ModuleSettings> getSettings() const;
   
private:
   
   void determineMasterModuleStatus();
   
   static std::atomic_bool s_isRackPluginMasterModule;
   bool _isRackMasterModule = false;
   std::shared_ptr<ModuleSettings> _settings;
};

}
