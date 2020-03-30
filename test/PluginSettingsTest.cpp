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
   
   SECTION("ensure that not calling load returns CVWizard default settings")
   {
      PluginSettings pluginSettings{};
      REQUIRE(pluginSettings.getCVWizardSettings() == defaultCVWizardSettings);
   }
   
   SECTION("ensure that non existing QRX.json returns CVWizard default settings")
   {
      PluginSettings pluginSettings{};
      pluginSettings.load();
      REQUIRE(pluginSettings.getCVWizardSettings() == defaultCVWizardSettings);
   }
   
   SECTION("ensure that getCVWizardSettings after dumpSettings returns dumped settings")
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
