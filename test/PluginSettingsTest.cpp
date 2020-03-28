#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <PluginSettings.hpp>

#include <catch2/catch.hpp>

using namespace qrx;

TEST_CASE("PluginSettings", "[plugin] [settings]")
{
   PluginSettings pluginSettings{};
   
   SECTION("ensure that slug is QRX")
   {
      REQUIRE(std::string{PluginSettings::SLUG} == std::string{"QRX"});
   }
}

#pragma GCC diagnostic pop
