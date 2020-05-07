#include <cvwizard/ModuleSettings.hpp>
#include <boundary/io/Keys.hpp>

#include <catch2/catch.hpp>
#include <fakeit.hpp>

TEST_CASE("CVWizard ModuleSettings", "[cvwizard] [settings]")
{
   using namespace fakeit;
   using namespace qrx::cvwizard;
   
   Mock<ModuleSettings> pluginSettingsMock;
   
   auto settings = ModuleSettings::Settings{};
   
   When(Method(pluginSettingsMock, getSettings)).AlwaysReturn(settings);
   When(Method(pluginSettingsMock, dumpSettings).Using(_)).AlwaysReturn();
   
   auto& m = pluginSettingsMock.get();
   
   SECTION("ensure default settings")
   {
      const auto defaultSettings = m.getSettings();
      REQUIRE(defaultSettings.MappingKey == qrx::boundary::io::keys::M);
      REQUIRE(defaultSettings.MappingTooltipKey == qrx::boundary::io::keys::T);
      REQUIRE(defaultSettings.ShowMappingTooltips ==  true);
   }
}
