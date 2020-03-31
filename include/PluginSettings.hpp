#pragma once

#include <CVWizard/ModuleSettings.hpp>

#include <memory>
#include <string>

struct json_t;

namespace qrx {

class PluginSettings : public cvwizard::ModuleSettings
{
public:
   static constexpr char const* SLUG = "QRX";
   
   PluginSettings() = default;
   ~PluginSettings() noexcept override;
  
   void load(const std::string& file = std::string{SLUG} + ".json") noexcept;
   void save(const std::string& file = std::string{SLUG} + ".json") const noexcept;
   
   cvwizard::ModuleSettings::Settings getCVWizardSettings() override;
   void dumpSettings(const cvwizard::ModuleSettings::Settings& settings) override;
   
private:
   
   void loadCVWizardSettings(const json_t& json);
   std::unique_ptr<json_t> dumpCVWizardSettings() const;
   
   cvwizard::ModuleSettings::Settings _cvWizardSettings{};
};

}
