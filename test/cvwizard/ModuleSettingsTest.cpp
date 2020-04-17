#include <cvwizard/ModuleSettings.hpp>
#include <GLFW/glfw3.h>

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
      REQUIRE(defaultSettings.MappingKey == GLFW_KEY_M);
      REQUIRE(defaultSettings.MappingCancelKey == GLFW_KEY_ESCAPE);
      REQUIRE(defaultSettings.MappingTooltipKey == GLFW_KEY_T);
      REQUIRE(defaultSettings.ShowMappingTooltips ==  true);
   }
}

