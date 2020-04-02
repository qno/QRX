#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <cvwizard/CVWizardModule.hpp>

#include <catch2/catch.hpp>
#include <fakeit.hpp>

using namespace qrx::cvwizard;

TEST_CASE("CVWizard SLUG", "[cvwizard] [module]")
{
   REQUIRE(std::string{CVWizardModule::SLUG} == std::string{"CVWizard"});
}

TEST_CASE("CVWizard Rack master module", "[cvwizard] [module]")
{
   SECTION("ensure that only first CVWizard instance becomes master module")
   {
      auto module1 = CVWizardModule{};
      auto module2 = CVWizardModule{};
      auto module3 = CVWizardModule{};
    
      REQUIRE(module1.isMasterModule());
      REQUIRE(!module2.isMasterModule());
      REQUIRE(!module3.isMasterModule());
   }
   
   SECTION("ensure that if master module deleted the next module becomes master")
   {
      auto module1 = std::make_unique<CVWizardModule>();
      auto module2 = std::make_unique<CVWizardModule>();
      auto module3 = std::make_unique<CVWizardModule>();
   
      const auto args = rack::engine::Module::ProcessArgs{};
      module1 = nullptr;
      module2->process(args);
      module3->process(args);
      
      REQUIRE(!module1);
      REQUIRE(module2->isMasterModule());
      REQUIRE(!module3->isMasterModule());
   }
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

TEST_CASE("CVWizard settings", "[cvwizard] [settings]")
{
   using namespace fakeit;
   using namespace qrx::cvwizard;
   
   auto defaultSettings = ModuleSettings::Settings{};
   
   auto pluginSettingsMock = Mock<ModuleSettings>();
   
   When(Method(pluginSettingsMock, getCVWizardSettings)).AlwaysReturn(defaultSettings);
   When(Method(pluginSettingsMock, dumpSettings).Using(_)).AlwaysReturn();
   
   // shared_ptr of mock -  https://github.com/eranpeer/FakeIt/issues/60
   auto pluginSettings = std::shared_ptr<ModuleSettings>(&pluginSettingsMock(), [](...) {});
   
   SECTION("ensure get settings returns added settings")
   {
      auto cvWizard = CVWizardModule{};
      cvWizard.addSettings(pluginSettings);
      REQUIRE(cvWizard.getSettings());
      REQUIRE(cvWizard.getSettings()->getCVWizardSettings() == defaultSettings);
   }
}

#pragma GCC diagnostic pop
