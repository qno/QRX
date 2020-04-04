#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <cvwizard/controller/CVWizardController.hpp>

#include <catch2/catch.hpp>

using namespace qrx::cvwizard::controller;

TEST_CASE("CVWizard controller", "[cvwizard] [controller]")
{
   REQUIRE(&CVWizardController::instance() != nullptr);
   
   SECTION("start throws if KeyboardEventsProvider is not set")
   {
      REQUIRE_THROWS_AS(CVWizardController::instance().start(), CVWizardController::KeyboardEventsProviderNotSetException);
   }
}

#pragma GCC diagnostic pop
