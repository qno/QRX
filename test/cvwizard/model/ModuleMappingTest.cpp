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
}
