#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <PluginSettings.hpp>

#include <catch2/catch.hpp>

using namespace qrx;

TEST_CASE("PluginSettings", "[plugin] [settings]")
{
   const auto defaultCVWizardSettings = cvwizard::ModuleSettings::Settings{};
   
   SECTION("ensure that slug is QRX")
   {
      REQUIRE(std::string{PluginSettings::SLUG} == std::string{"QRX"});
   }
   
   SECTION("ensure that created PluginSettings instance returns CVWizard default settings")
   {
      PluginSettings pluginSettings{};
      REQUIRE(pluginSettings.getCVWizardSettings() == defaultCVWizardSettings);
   }
   
   SECTION("ensure that PluginSettings load for non existing QRX.json returns CVWizard default settings")
   {
      PluginSettings pluginSettings{};
      pluginSettings.load();
      REQUIRE(pluginSettings.getCVWizardSettings() == defaultCVWizardSettings);
   }
   
   SECTION("ensure PluginSettings returns settings from file with non default settings" )
   {
      PluginSettings pluginSettings{};
      pluginSettings.load("non-default-settings.json");
      REQUIRE(!(pluginSettings.getCVWizardSettings() == defaultCVWizardSettings));
   }
   
   SECTION("ensure PluginSettings return default settings if corrupted settings file was loaded" )
   {
      PluginSettings pluginSettings{};
      pluginSettings.load("corrupted-settings.json");
      REQUIRE(pluginSettings.getCVWizardSettings() == defaultCVWizardSettings);
   }
   
   SECTION("ensure CVWizardModule get default settings attribute if file with corrupted settings attribute loaded" )
   {
      PluginSettings pluginSettings{};
      pluginSettings.load("corrupted-attribute.json");
      REQUIRE(!(pluginSettings.getCVWizardSettings() == defaultCVWizardSettings));
      REQUIRE(pluginSettings.getCVWizardSettings().MappingTooltipKey == defaultCVWizardSettings.MappingTooltipKey);
   }
   
   SECTION("ensure that PluginSettings getCVWizardSettings returns dumped settings after dumpSettings called")
   {
      PluginSettings pluginSettings{};
      auto dumpedSettings = cvwizard::ModuleSettings::Settings{};
      dumpedSettings.ShowMappingTooltips = false;
      dumpedSettings.MappingKey = 22;
      dumpedSettings.MappingCancelKey = 33;
      dumpedSettings.MappingTooltipKey = 44;
      pluginSettings.dumpSettings(dumpedSettings);
      REQUIRE(pluginSettings.getCVWizardSettings() == dumpedSettings);
   }
}

#pragma GCC diagnostic pop
