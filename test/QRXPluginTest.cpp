#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <QRXPlugin.hpp>
#include <CVWizard/CVWizardModule.hpp>

#include <catch2/catch.hpp>

TEST_CASE("create QRXPlugin", "[plugin]")
{
   auto plugin = rack::plugin::Plugin{};
   init(&plugin);
   
   SECTION("create CVWizard model")
   {
      const auto model = plugin.getModel(qrx::cvwizard::CVWizardModule::SLUG);
      REQUIRE(model != nullptr);
      REQUIRE(model->slug == std::string{qrx::cvwizard::CVWizardModule::SLUG});
   }
}

#pragma GCC diagnostic pop
