#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <CVWizard/CVWizardModule.hpp>

#include <TestOperators.hpp>
#include <catch2/catch.hpp>
#include <fakeit.hpp>


TEST_CASE("dataToJson", "[cvwizard] [module]")
{
   using namespace qrx;
   
   CVWizardModule wiz;
   auto expected = std::string{"{}"};
   auto jsonResult = std::unique_ptr<json_t>(wiz.dataToJson());
   
   REQUIRE(jsonResult != nullptr);
}

#pragma GCC diagnostic pop
