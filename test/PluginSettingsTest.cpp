#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <PluginSettings.hpp>

#include <catch2/catch.hpp>

using namespace qrx;

TEST_CASE("PluginSettings", "[plugin] [settings]")
{
   SECTION("ensure that slug is QRX")
   {
      REQUIRE(std::string{PluginSettings::SLUG} == std::string{"QRX"});
   }
   
   SECTION("ensure that created PluginSettings instance returns CVWizard default settings")
   {
      const auto defaultCVWizardSettings = cvwizard::ModuleSettings::Settings{};
      PluginSettings pluginSettings{};
      REQUIRE(pluginSettings.getCVWizardSettings() == defaultCVWizardSettings);
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

TEST_CASE("load PluginSettings", "[plugin] [settings]")
{
   const auto defaultCVWizardSettings = cvwizard::ModuleSettings::Settings{};
   
   SECTION("ensure that PluginSettings load for non existing json file returns CVWizard default settings")
   {
      PluginSettings pluginSettings{};
      pluginSettings.load("this-file-does-not-exist.json");
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
   
   SECTION("ensure PluginSettings get default settings attribute if file with corrupted settings attribute loaded" )
   {
      PluginSettings pluginSettings{};
      pluginSettings.load("corrupted-attribute.json");
      REQUIRE(!(pluginSettings.getCVWizardSettings() == defaultCVWizardSettings));
      REQUIRE(pluginSettings.getCVWizardSettings().MappingTooltipKey == defaultCVWizardSettings.MappingTooltipKey);
   }
}

TEST_CASE("save PluginSettings", "[plugin] [settings]")
{
   const auto defaultCVWizardSettings = cvwizard::ModuleSettings::Settings{};
   
   SECTION("ensure that PluginSettings save default settings to JSON file")
   {
      const auto savedSettingsFile = std::string{"saved-defaults.json"};
      
      PluginSettings pluginSettingsSaver{};
      pluginSettingsSaver.save(savedSettingsFile);
      
      PluginSettings pluginSettingsLoader{};
      pluginSettingsLoader.load(savedSettingsFile);
      
      REQUIRE(pluginSettingsLoader.getCVWizardSettings() == defaultCVWizardSettings);
   }
   
   SECTION("ensure that PluginSettings save dumped settings to JSON file")
   {
      const auto savedSettingsFile = std::string{"saved-dumped.json"};
      
      auto settingsToDump = cvwizard::ModuleSettings::Settings{};
      settingsToDump.MappingTooltipKey = 1111;
      settingsToDump.MappingCancelKey = 2222;
      settingsToDump.MappingKey = 3333;
      settingsToDump.ShowMappingTooltips = false;
      
      PluginSettings pluginSettingsSaver{};
      pluginSettingsSaver.dumpSettings(settingsToDump);
      pluginSettingsSaver.save(savedSettingsFile);
   
      PluginSettings pluginSettingsLoader{};
      pluginSettingsLoader.load(savedSettingsFile);
      
      REQUIRE(pluginSettingsLoader.getCVWizardSettings() == settingsToDump);
   }
}

#pragma GCC diagnostic pop
