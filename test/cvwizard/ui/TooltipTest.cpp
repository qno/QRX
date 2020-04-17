#include <cvwizard/ui/Tooltip.hpp>
#include <boundary/io/Keys.hpp>

#include <catch2/catch.hpp>

#include <sstream>

using namespace qrx::cvwizard::ui;

TEST_CASE("Tooltip", "[ui] [tooltip]")
{
   SECTION("ensure Mapping mode tooltip text")
   {
      auto tooltipText = std::stringstream{};
      tooltipText << "Press '" << qrx::boundary::io::keys::MOD_CTRL_NAME << "-M' to activate Mapping mode";
      REQUIRE(Tooltip::getStartMappingText('m') == tooltipText.str());
   }
   
   SECTION("ensure Mapping mode tooltip text after mapping key has changed")
   {
      auto tooltipText = std::stringstream{};
      tooltipText << "Press '" << qrx::boundary::io::keys::MOD_CTRL_NAME << "-Q' to activate Mapping mode";
      REQUIRE(Tooltip::getStartMappingText('q') == tooltipText.str());
   }
}
