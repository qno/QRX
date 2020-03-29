#pragma once

#include <CVWizard/ModuleSettings.hpp>

namespace qrx {

class PluginSettings : public cvwizard::ModuleSettings
{
public:
   static constexpr char const* SLUG = "QRX";
   
   PluginSettings() = default;
   ~PluginSettings() override;
   PluginSettings(const PluginSettings&) = delete;
   PluginSettings& operator= (const PluginSettings&) = delete;
  
   void load();
   void save() const;
   
   cvwizard::ModuleSettings::Settings getCVWizardSettings() override;
   void dumpSettings(const cvwizard::ModuleSettings::Settings& settings) override;
   
private:
   cvwizard::ModuleSettings::Settings _cvWizardSettings;
};

}
