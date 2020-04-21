#include <cvwizard/model/ModuleMapping.hpp>

#include <catch2/catch.hpp>

using namespace qrx::boundary::rack;
using namespace qrx::cvwizard::model;
using namespace qrx::cvwizard::ui;

TEST_CASE("ModuleMapping", "[cvwizard] [model] [mapping]")
{
   SECTION("create mapping object")
   {
      ModuleWidget widget;
      ModuleMapping mapping{&widget};
      REQUIRE(mapping.getModuleWidget() == &widget);
   }
   
   SECTION("ensure enableHover attaches hover widget to mapped module widget")
   {
      ModuleWidget widget;
      ModuleMapping mapping{&widget};
      mapping.enableHover();
      REQUIRE(!mapping.getModuleWidget()->children.empty());
      //REQUIRE(mapping.getModuleWidget()->getFirstDescendantOfType<HoveredWidget>() != nullptr);
   }
   
   SECTION("ensure disableHover removed hover widget from mapped module widget")
   {
      ModuleWidget widget;
      ModuleMapping mapping{&widget};
      mapping.enableHover();
      mapping.disableHover();
      REQUIRE(mapping.getModuleWidget()->children.empty());
      //REQUIRE(mapping.getModuleWidget()->getFirstDescendantOfType<HoveredWidget>() == nullptr);
   }
}
