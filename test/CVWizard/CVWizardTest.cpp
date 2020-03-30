#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <CVWizard/CVWizardModule.hpp>
#include <PluginSettings.hpp>

#include <catch2/catch.hpp>

using namespace qrx::cvwizard;

TEST_CASE("CVWizard SLUG", "[cvwizard] [module]")
{
   REQUIRE(std::string{CVWizardModule::SLUG} == std::string{"CVWizard"});
}

TEST_CASE("CVWizardModule dataToJson", "[cvwizard] [module]")
{
   CVWizardModule cvWizard;
   auto jsonResult = std::unique_ptr<json_t>(cvWizard.dataToJson());
   REQUIRE(jsonResult != nullptr);
   
   SECTION("json result type is JSON_OBJECT")
   {
      REQUIRE(jsonResult->type == JSON_OBJECT);
   }
   
   SECTION("check json content")
   {
      const auto jsonParam1 = json_object_get(jsonResult.get(), "param1");
      REQUIRE(jsonParam1 != nullptr);
      REQUIRE(std::string(json_string_value(jsonParam1)) == std::string("0815"));
      
      const auto jsonParam2 = json_object_get(jsonResult.get(), "param2");
      REQUIRE(jsonParam2 != nullptr);
      REQUIRE(json_integer_value(jsonParam2) == 2);
      
      const auto jsonParam3 = json_object_get(jsonResult.get(), "param3");
      REQUIRE(jsonParam3 != nullptr);
      REQUIRE(json_boolean_value(jsonParam3) == true);
   }
   
   //REQUIRE(json_dumps(jsonResult.get(), JSON_ENCODE_ANY) == "1");
}

TEST_CASE("CVWizardModule module settings", "[cvwizard] [module]")
{
   const auto defaultSettings = ModuleSettings::Settings{};
   
   SECTION("CVWizardModule get default settings")
   {
      auto pluginSettings = std::make_shared<qrx::PluginSettings>();
      CVWizardModule cvWizard;
      cvWizard.addSettings(pluginSettings);
      REQUIRE(cvWizard.getSettings().getCVWizardSettings() == defaultSettings);
   }
   
   SECTION("ensure CVWizardModule get settings from file with non default settings" )
   {
      auto pluginSettings = std::make_shared<qrx::PluginSettings>();
      pluginSettings->load("non-default-settings.json");
      CVWizardModule cvWizard;
      cvWizard.addSettings(pluginSettings);
      REQUIRE(!(cvWizard.getSettings().getCVWizardSettings() == defaultSettings));
   }
   
   SECTION("ensure CVWizardModule get default settings if corrupted settings file loaded" )
   {
      auto pluginSettings = std::make_shared<qrx::PluginSettings>();
      pluginSettings->load("corrupted-settings.json");
      CVWizardModule cvWizard;
      cvWizard.addSettings(pluginSettings);
      REQUIRE(cvWizard.getSettings().getCVWizardSettings() == defaultSettings);
   }
   SECTION("ensure CVWizardModule get default settings attribute if file with corrupted settings attribute loaded" )
   {
      auto pluginSettings = std::make_shared<qrx::PluginSettings>();
      pluginSettings->load("corrupted-attribute.json");
      CVWizardModule cvWizard;
      cvWizard.addSettings(pluginSettings);
      REQUIRE(!(cvWizard.getSettings().getCVWizardSettings() == defaultSettings));
      REQUIRE(cvWizard.getSettings().getCVWizardSettings().MappingTooltipKey == defaultSettings.MappingTooltipKey);
   }
}

#pragma GCC diagnostic pop
