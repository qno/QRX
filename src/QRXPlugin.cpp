#include <QRXPlugin.hpp>
#include <PluginSettings.hpp>

rack::plugin::Plugin* pluginInstance;
extern std::shared_ptr<qrx::PluginSettings> pluginSettings;

void init(rack::plugin::Plugin* p)
{
   pluginInstance = p;
   
   p->addModel(modelCVWizard);
   
   if (pluginSettings)
   {
      pluginSettings->load();
   }
   else
   {
      WARN("Failed to load plugin settings");
   }
}
