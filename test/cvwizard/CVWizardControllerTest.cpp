#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <cvwizard/CVWizardController.hpp>

#include <catch2/catch.hpp>

using namespace qrx::cvwizard;

TEST_CASE("CVWizard controller", "[cvwizard] [controller]")
{
   REQUIRE(std::make_shared<CVWizardController>());
}

#pragma GCC diagnostic pop
