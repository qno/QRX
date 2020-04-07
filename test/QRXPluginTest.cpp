#include <QRXPlugin.hpp>
#include <cvwizard/CVWizardModule.hpp>

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
