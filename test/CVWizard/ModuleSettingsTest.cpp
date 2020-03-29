#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <CVWizard/ModuleSettings.hpp>
#include <GLFW/glfw3.h>

#include <catch2/catch.hpp>
#include <fakeit.hpp>


TEST_CASE("CVWizard ModuleSettings", "[cvwizard] [settings]")
{
   using namespace fakeit;
   using namespace qrx::cvwizard;
   
   Mock<ModuleSettings> pluginSettingsMock;
   
   auto settings = ModuleSettings::Settings{};
   
   When(Method(pluginSettingsMock, getCVWizardSettings)).AlwaysReturn(settings);
   When(Method(pluginSettingsMock,dumpSettings).Using(_)).AlwaysReturn();
   
   auto& m = pluginSettingsMock.get();
   
   SECTION("ensure default settings")
   {
      const auto defaultSettings = m.getCVWizardSettings();
      REQUIRE(defaultSettings.MappingKey == GLFW_KEY_M);
      REQUIRE(defaultSettings.MappingCancelKey == GLFW_KEY_ESCAPE);
      REQUIRE(defaultSettings.MappingTooltipKey == GLFW_KEY_T);
      REQUIRE(defaultSettings.ShowMappingTooltips ==  false);
   }
   
   /*
   Verify(Method(mock,process).Using(args)).Once();
   Verify(Method(mock,dataToJson)).Exactly(3);
   Verify(Method(mock,dataFromJson).Using(json.get())).Twice();
    */
}

#pragma GCC diagnostic pop
