#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <CVWizard/CVWizardModule.hpp>

#include <jansson.h>
#include <catch2/catch.hpp>

#define GETSTRING(s) STR(s)
#define STR(s) #s

// see https://vcvrack.com/manual/Manifest
TEST_CASE("plugin.json", "[plugin] [json]")
{
   const auto QRX = std::string{"QRX"};
   const auto URL = std::string{"https://github.com/qno"};
   const auto LicenseGPLv3 = std::string{"GPL-3.0-or-later"};
   const auto Author = std::string{"Silvio Kunaschk"};
   const auto AuthorUrl = std::string{URL};
   const auto PluginUrl = std::string{URL + "/QRX"};
   const auto ManualUrl = std::string{PluginUrl + "/wiki"};
   const auto CVWizardManualUrl = std::string{ManualUrl + "/CVWizard-Module"};
   
   const auto jsonFile = std::string{GETSTRING(PLUGIN_JSON_FILE)};
   REQUIRE(!jsonFile.empty());
   
   auto pluginJson = std::unique_ptr<json_t>(json_load_file(jsonFile.c_str(), JSON_ENCODE_ANY, nullptr));
   
   SECTION("ensure that plugin.json exists")
   {
      REQUIRE(pluginJson != nullptr);
   }
   
   SECTION("ensure that plugin slug is QRX")
   {
      const auto slug = json_object_get(pluginJson.get(), "slug");
      REQUIRE(slug != nullptr);
      REQUIRE(std::string(json_string_value(slug)) == QRX);
   }
   
   SECTION("ensure that plugin name is QRX")
   {
      const auto name = json_object_get(pluginJson.get(), "name");
      REQUIRE(name != nullptr);
      REQUIRE(std::string(json_string_value(name)) == QRX);
   }
   
   SECTION("ensure that version is not empty")
   {
      const auto version = json_object_get(pluginJson.get(), "version");
      REQUIRE(version != nullptr);
      REQUIRE(!std::string(json_string_value(version)).empty());
   }
   
   SECTION("ensure that license is GPLv3")
   {
      const auto license = json_object_get(pluginJson.get(), "license");
      REQUIRE(license != nullptr);
      REQUIRE(std::string(json_string_value(license)) == LicenseGPLv3);
   }
   
   SECTION("ensure that brand is QRX")
   {
      const auto brand = json_object_get(pluginJson.get(), "brand");
      REQUIRE(brand != nullptr);
      REQUIRE(std::string(json_string_value(brand)) == QRX);
   }
   
   SECTION("ensure that author is correct")
   {
      const auto author = json_object_get(pluginJson.get(), "author");
      REQUIRE(author != nullptr);
      REQUIRE(std::string(json_string_value(author)) == Author);
   }
   
   SECTION("ensure that pluginUrl is correct")
   {
      const auto pluginUrl = json_object_get(pluginJson.get(), "pluginUrl");
      REQUIRE(pluginUrl != nullptr);
      REQUIRE(std::string(json_string_value(pluginUrl)) == PluginUrl);
   }
   
   SECTION("ensure that manualUrl is correct")
   {
      const auto manualUrl = json_object_get(pluginJson.get(), "manualUrl");
      REQUIRE(manualUrl != nullptr);
      REQUIRE(std::string(json_string_value(manualUrl)) == ManualUrl);
   }
   
   const auto modules = json_object_get(pluginJson.get(), "modules");
   REQUIRE(modules != nullptr);
   
   size_t index;
   json_t* value = nullptr;
   
   json_array_foreach(modules, index, value)
   {
      SECTION("ensure CVWizard module slug is CVWizard")
      {
         const auto slug = json_object_get(value, "slug");
         REQUIRE(slug != nullptr);
         REQUIRE(std::string(json_string_value(slug)) == qrx::CVWizardModule::SLUG);
      }
      SECTION("ensure CVWizard module name is CVWizard")
      {
         const auto name = json_object_get(value, "name");
         REQUIRE(name != nullptr);
         REQUIRE(std::string(json_string_value(name)) == qrx::CVWizardModule::SLUG);
      }
      SECTION("ensure that CVWizard module description is not empty")
      {
         const auto description = json_object_get(value, "description");
         REQUIRE(description != nullptr);
         REQUIRE(!std::string(json_string_value(description)).empty());
      }
      SECTION("ensure that CVWizard module manualUrl is correct")
      {
         const auto manualUrl = json_object_get(value, "manualUrl");
         REQUIRE(manualUrl != nullptr);
         REQUIRE(std::string(json_string_value(manualUrl)) == CVWizardManualUrl);
      }
      SECTION("ensure that CVWizard module tags are not empty")
      {
         const auto tags = json_object_get(value, "tags");
         REQUIRE(tags != nullptr);
         REQUIRE(json_array_size(tags) > 0);
      }
   }
}

#pragma GCC diagnostic pop
