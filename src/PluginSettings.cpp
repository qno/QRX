#include <PluginSettings.hpp>
#include <jansson.h>
#include <logger.hpp>

namespace qrx {

PluginSettings::~PluginSettings()
{
   save();
}

void PluginSettings::load()
{
   INFO("load %s plugin settings from '%s.json'", SLUG, SLUG);
}

void PluginSettings::save() const
{
   INFO("save %s plugin settings to '%s.json'", SLUG, SLUG);
}

cvwizard::ModuleSettings::Settings PluginSettings::getCVWizardSettings()
{
   return{};
}

void PluginSettings::dumpSettings(const cvwizard::ModuleSettings::Settings& settings)
{

}

}
