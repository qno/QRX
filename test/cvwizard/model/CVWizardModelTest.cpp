#include <cvwizard/model/CVWizardModel.hpp>

#include <catch2/catch.hpp>

using namespace qrx::cvwizard::model;
using namespace qrx::boundary::rack;

TEST_CASE("CVWizardModel", "[cvwizard] [model]")
{
   CVWizardModel model;
   
   SECTION("new model has no mapping")
   {
      REQUIRE(model.getCurrentModuleMapping() == nullptr);
   }
   
   SECTION("not finished mapping module")
   {
      ModuleWidget moduleWidget;
      model.beginModuleMapping(&moduleWidget);
      auto firstMapping = model.getCurrentModuleMapping();
      REQUIRE(firstMapping);
      REQUIRE(firstMapping->getModuleWidget() == &moduleWidget);
      model.endModuleMapping();
      REQUIRE(model.getCurrentModuleMapping() == nullptr);
      model.beginModuleMapping(&moduleWidget);
      auto secondMapping = model.getCurrentModuleMapping();
      REQUIRE(secondMapping);
      REQUIRE(secondMapping != firstMapping);
   }
}
