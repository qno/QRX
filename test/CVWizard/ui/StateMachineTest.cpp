#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <CVWizard/ui/StateMachine.hpp>

#include <catch2/catch.hpp>
#include <fakeit.hpp>

using namespace qrx::cvwizard::ui;

TEST_CASE("StateMachine", "[ui] [statemachine]")
{
   auto sm = std::make_shared<StateMachine>();
   REQUIRE(sm);
}

#pragma GCC diagnostic pop
