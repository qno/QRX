#include <cvwizard/model/CVParameterMapping.hpp>

#include <catch2/catch.hpp>

using namespace qrx;
using namespace qrx::cvwizard::model;

TEST_CASE("CVParameterMapping", "[cvwizard] [cvparameter] [mapping]")
{
   SECTION("set get input port widget")
   {
      CVParameterMapping pm{};
      boundary::rack::PortWidget portWidget;
      pm.setInputPort(&portWidget);
      REQUIRE(pm.getInputPort() == &portWidget);
   }
   
   /*SECTION("set get cv parameter widget")
   {
      CVParameterMapping pm{};
      boundary::rack::ParamWidget paramWidget;
      pm.setCVParameter(&paramWidget);
      REQUIRE(pm.getCVParameter() == &paramWidget);
   }*/
}
