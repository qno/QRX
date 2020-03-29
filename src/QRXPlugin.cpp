#include <QRXPlugin.hpp>
#include <PluginSettings.hpp>

rack::plugin::Plugin* pluginInstance;
std::shared_ptr<qrx::PluginSettings> pluginSettings;

void init(rack::plugin::Plugin* p)
{
   pluginSettings = std::make_shared<qrx::PluginSettings>();
   pluginSettings->load();
   
   pluginInstance = p;
   
   p->addModel(modelCVWizard);
}
