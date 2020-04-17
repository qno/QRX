#include <PluginSettings.hpp>
#include <jansson.h>
#include <asset.hpp>
#include <logger.hpp>

#include <fstream>

namespace qrx {

PluginSettings::~PluginSettings() noexcept
{
   save();
}

void PluginSettings::load(const std::string& file) noexcept
{
   const auto jsonFile = rack::asset::user(file);
   INFO("Load %s plugin settings from '%s'", SLUG, jsonFile.c_str());
   
   auto jsonError = json_error_t{};
   auto pluginSettings = std::unique_ptr<json_t>(json_load_file(jsonFile.c_str(), JSON_ENCODE_ANY, &jsonError));
   
   if (!pluginSettings)
   {
      const auto error = json_error_code(&jsonError);
      if (json_error_cannot_open_file == error)
      {
         INFO("Couldn't open plugin settings file '%s', use default settings", jsonFile.c_str());
      }
      else
      {
         WARN("Error loading '%s' (%s), use default settings", jsonFile.c_str(), jsonError.text);
      }
   }
   else
   {
      loadCVWizardSettings(*pluginSettings);
   }
}

void PluginSettings::save(const std::string& file) const noexcept
{
   const auto jsonFile = rack::asset::user(file);
   INFO("Save %s plugin settings to '%s'", SLUG, jsonFile.c_str());
   
   auto json = std::unique_ptr<json_t>(json_object());
   const auto cvWizardSettingsJson = dumpCVWizardSettings();
   json_object_set_new(json.get(), "CVWizard", cvWizardSettingsJson.get());
   
   std::ofstream settingsFile(jsonFile, std::ofstream::trunc);
   settingsFile << json_dumps(json.get(), JSON_ENCODE_ANY | JSON_INDENT(2));
   settingsFile.close();
   
   if (settingsFile.fail())
   {
      WARN("saving '%s' has failed", jsonFile.c_str());
   }
}

cvwizard::ModuleSettings::Settings PluginSettings::getSettings()
{
   return _cvWizardSettings;
}

void PluginSettings::dumpSettings(const cvwizard::ModuleSettings::Settings& settings)
{
   _cvWizardSettings = settings;
}

void PluginSettings::loadCVWizardSettings(const json_t& json)
{
   using namespace qrx::cvwizard;
   
   const auto cvWizard = json_object_get(&json, "CVWizard");
   
   if (cvWizard)
   {
      const auto mappingKey = json_object_get(cvWizard, MappingKey);
      if (mappingKey)
      {
         _cvWizardSettings.MappingKey = json_integer_value(mappingKey);
      }
      const auto mappingCancelKey = json_object_get(cvWizard, MappingCancelKey);
      if (mappingCancelKey)
      {
         _cvWizardSettings.MappingCancelKey = json_integer_value(mappingCancelKey);
      }
      const auto mappingTooltipKey = json_object_get(cvWizard, MappingTooltipKey);
      if (mappingTooltipKey)
      {
         _cvWizardSettings.MappingTooltipKey = json_integer_value(mappingTooltipKey);
      }
      const auto showMappingTooltips = json_object_get(cvWizard, ShowMappingTooltips);
      if (showMappingTooltips)
      {
         _cvWizardSettings.ShowMappingTooltips = json_boolean_value(showMappingTooltips);
      }
   }
}

std::unique_ptr<json_t> PluginSettings::dumpCVWizardSettings() const
{
   using namespace qrx::cvwizard;
   
   auto cvWizardSettingsJson = std::unique_ptr<json_t>(json_object());
   
   json_object_set_new(cvWizardSettingsJson.get(), MappingKey, json_integer(_cvWizardSettings.MappingKey));
   json_object_set_new(cvWizardSettingsJson.get(), MappingCancelKey, json_integer(_cvWizardSettings.MappingCancelKey));
   json_object_set_new(cvWizardSettingsJson.get(), MappingTooltipKey, json_integer(_cvWizardSettings.MappingTooltipKey));
   json_object_set_new(cvWizardSettingsJson.get(), ShowMappingTooltips, json_boolean(_cvWizardSettings.ShowMappingTooltips));
   
   return cvWizardSettingsJson;
}

}
