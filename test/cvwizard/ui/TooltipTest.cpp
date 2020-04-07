#include <cvwizard/ui/Tooltip.hpp>

#include <catch2/catch.hpp>

#include <sstream>

using namespace qrx::cvwizard::ui;

TEST_CASE("Tooltip", "[ui] [tooltip]")
{
   SECTION("ensure Mapping mode tooltip text")
   {
      auto tooltipText = std::stringstream{};
      tooltipText << "Press '" << Tooltip::MOD_KEY << "-M' to activate Mapping mode";
      REQUIRE(Tooltip::getStartMappingText('m') == tooltipText.str());
   }
   
   SECTION("ensure Mapping mode tooltip text after mapping key has changed")
   {
      auto tooltipText = std::stringstream{};
      tooltipText << "Press '" << Tooltip::MOD_KEY << "-Q' to activate Mapping mode";
      REQUIRE(Tooltip::getStartMappingText('q') == tooltipText.str());
   }
}
