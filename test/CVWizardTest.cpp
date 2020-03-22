#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <CVWizard/CVWizardModule.hpp>

#include <TestOperators.hpp>
#include <catch2/catch.hpp>
#include <fakeit.hpp>

using namespace fakeit;
using namespace qrx;

TEST_CASE("CVWizardModule dataToJson", "[cvwizard] [module]")
{
   CVWizardModule wiz;
   auto jsonResult = std::unique_ptr<json_t>(wiz.dataToJson());
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

#pragma GCC diagnostic pop
