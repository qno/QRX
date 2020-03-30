#pragma once

#include <CVWizard/ModuleSettings.hpp>

#include <string>

struct json_t;

namespace qrx {

class PluginSettings : public cvwizard::ModuleSettings
{
public:
   static constexpr char const* SLUG = "QRX";
   
   PluginSettings() = default;
   ~PluginSettings() override;
   PluginSettings(const PluginSettings&) = delete;
   PluginSettings& operator= (const PluginSettings&) = delete;
  
   void load(const std::string& file = std::string{SLUG} + ".json");
   void save(const std::string& file = std::string{SLUG} + ".json") const;
   
   cvwizard::ModuleSettings::Settings getCVWizardSettings() override;
   void dumpSettings(const cvwizard::ModuleSettings::Settings& settings) override;
   
private:
   
   void loadCVWizardSettings(const json_t& json);
   
   cvwizard::ModuleSettings::Settings _cvWizardSettings;
};

}
