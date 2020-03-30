#include <PluginSettings.hpp>
#include <jansson.h>
#include <asset.hpp>
#include <logger.hpp>

#include <memory>
#include <iostream>
namespace qrx {

PluginSettings::~PluginSettings()
{
   save();
}

void PluginSettings::load(const std::string& file)
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

void PluginSettings::save(const std::string& file) const
{
   const auto jsonFile = rack::asset::user(file);
   INFO("Save %s plugin settings to '%s'", SLUG, jsonFile.c_str());
}

cvwizard::ModuleSettings::Settings PluginSettings::getCVWizardSettings()
{
   return _cvWizardSettings;
}

void PluginSettings::dumpSettings(const cvwizard::ModuleSettings::Settings& settings)
{
   _cvWizardSettings = settings;
}

void PluginSettings::loadCVWizardSettings(const json_t& json)
{
   const auto cvWizard = json_object_get(&json, "CVWizard");
   
   if (cvWizard)
   {
      const auto showTooltip = json_object_get(cvWizard, "ShowMappingTooltips");
      if (showTooltip)
      {
         _cvWizardSettings.ShowMappingTooltips = json_boolean_value(showTooltip);
      }
      const auto mappingKey = json_object_get(cvWizard, "MappingKey");
      if (mappingKey)
      {
         _cvWizardSettings.MappingKey = json_integer_value(mappingKey);
      }
      const auto mappingTooltipKey = json_object_get(cvWizard, "MappingTooltipKey");
      if (mappingTooltipKey)
      {
         _cvWizardSettings.MappingTooltipKey = json_integer_value(mappingTooltipKey);
      }
      const auto mappingCancelKey = json_object_get(cvWizard, "MappingCancelKey");
      if (mappingCancelKey)
      {
         _cvWizardSettings.MappingCancelKey = json_integer_value(mappingCancelKey);
      }
   }
}

}
