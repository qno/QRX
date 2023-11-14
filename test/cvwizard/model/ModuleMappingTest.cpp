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
      REQUIRE(mapping.hasMappedParameter() == false);
   }
   
   SECTION("mapping complete parameter tuple")
   {
      ModuleWidget moduleWidget;
      PortWidget inputPortWidget;
      inputPortWidget.type = Port::INPUT;
      Knob knobWidget;
      ModuleMapping mapping{&moduleWidget};
      mapping.onEnterWidget(&inputPortWidget);
      mapping.onClicked(&inputPortWidget);
      mapping.onLeaveWidget();
      REQUIRE(mapping.hasMappedParameter() == false);
      mapping.onEnterWidget(&knobWidget);
      mapping.onClicked(&knobWidget);
      REQUIRE(mapping.hasMappedParameter() == true);
      mapping.onLeaveWidget();
      REQUIRE(mapping.hasMappedParameter() == true);
   }
}
