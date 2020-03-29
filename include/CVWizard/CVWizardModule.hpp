#pragma once

#include <QRXPlugin.hpp>
#include <CVWizard/ModuleSettings.hpp>

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
   ~CVWizardModule() override = default;
   
   void process(const ProcessArgs& args) override;
   
   json_t* dataToJson() override;
   
   void dataFromJson(json_t* root) override;
   
   ModuleSettings& getSettings() const;
   
private:
   std::shared_ptr<ModuleSettings> _settings;
};

}
}
