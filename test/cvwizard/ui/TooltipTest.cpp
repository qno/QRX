#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <cvwizard/ui/Tooltip.hpp>

#include <catch2/catch.hpp>

#include <sstream>

using namespace qrx::cvwizard::ui;

TEST_CASE("Tooltip", "[ui] [tooltip]")
{
#ifdef ARCH_MAC
   static constexpr char const* MOD_KEY = "Cmd";
#else
   static constexpr char const* MOD_KEY = "Ctrl";
#endif
   
   SECTION("ensure Mapping mode tooltip text")
   {
      auto tooltipText = std::stringstream{};
      tooltipText << "Press '" << MOD_KEY << "-M' to activate Mapping mode";
      REQUIRE(Tooltip::getStartMappingText('m') == tooltipText.str());
   }
   
   SECTION("ensure Mapping mode tooltip text after mapping key has changed")
   {
      auto tooltipText = std::stringstream{};
      tooltipText << "Press '" << MOD_KEY << "-Q' to activate Mapping mode";
      REQUIRE(Tooltip::getStartMappingText('q') == tooltipText.str());
   }
}

#pragma GCC diagnostic pop
