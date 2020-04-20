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
   
   SECTION("begin mapping module")
   {
      ModuleWidget moduleWidget;
      model.beginModuleMapping(&moduleWidget);
      auto&& currentMapping = model.getCurrentModuleMapping();
      REQUIRE(currentMapping);
      REQUIRE(currentMapping->getModuleWidget() == &moduleWidget);
   }
}
