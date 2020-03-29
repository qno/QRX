#include <PluginSettings.hpp>
#include <jansson.h>
#include <asset.hpp>
#include <logger.hpp>

#include <memory>

namespace qrx {

PluginSettings::~PluginSettings()
{
   save();
}

void PluginSettings::load()
{
   const auto jsonFile = rack::asset::user(SLUG + std::string{".json"});
   INFO("Load %s plugin settings from '%s'", SLUG, jsonFile.c_str());
   
   auto jsonError = json_error_t{};
   auto pluginJson = std::unique_ptr<json_t>(json_load_file(jsonFile.c_str(), JSON_ENCODE_ANY, &jsonError));
   
   if (!pluginJson)
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
}

void PluginSettings::save() const
{
   INFO("Save %s plugin settings to '%s.json'", SLUG, SLUG);
}

cvwizard::ModuleSettings::Settings PluginSettings::getCVWizardSettings()
{
   return _cvWizardSettings;
}

void PluginSettings::dumpSettings(const cvwizard::ModuleSettings::Settings& settings)
{
   _cvWizardSettings = settings;
}

}
