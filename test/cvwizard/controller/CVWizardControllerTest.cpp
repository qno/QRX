#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <cvwizard/controller/CVWizardController.hpp>

#include <catch2/catch.hpp>

using namespace qrx::cvwizard::controller;

TEST_CASE("CVWizard controller", "[cvwizard] [controller]")
{
   CVWizardController::instance().start();
   std::this_thread::sleep_for(std::chrono::seconds(20));
}

#pragma GCC diagnostic pop
