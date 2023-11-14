#include <cvwizard/ui/Tooltip.hpp>
#include <boundary/io/Keys.hpp>

#include <catch2/catch.hpp>

#include <sstream>

using namespace qrx::cvwizard::ui;

TEST_CASE("Tooltip", "[ui] [tooltip]")
{
   SECTION("ensure mapping mode tooltip text")
   {
      auto tooltipText = std::stringstream{};
      tooltipText << "Press '" << qrx::boundary::io::keys::MOD_CTRL_NAME << "-M' to activate Mapping mode";
      REQUIRE(Tooltip::getStartMappingText('m') == tooltipText.str());
   }
   
   SECTION("ensure mapping mode tooltip text after mapping key has changed")
   {
      auto tooltipText = std::stringstream{};
      tooltipText << "Press '" << qrx::boundary::io::keys::MOD_CTRL_NAME << "-Q' to activate Mapping mode";
      REQUIRE(Tooltip::getStartMappingText('q') == tooltipText.str());
   }
   
   SECTION("ensure mapping input port tooltip text")
   {
      const auto tooltipText = std::string{"Mapping mode is active (Press 'Esc' to cancel).\nClick now on a module input!"};
      REQUIRE(Tooltip::getMappingInputText() == tooltipText);
   }
}
