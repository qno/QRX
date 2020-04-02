#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <cvwizard/sm/keyboard/Keyboard.hpp>

#include <catch2/catch.hpp>

using namespace qrx::cvwizard::sm::keyboard;

TEST_CASE("Keyboard statemachine", "[keyboard] [statemachine]")
{
   Keyboard::start();
   auto ctrlPressedEvent = ControlKeyEvent{};
   Keyboard::dispatch(ctrlPressedEvent);
}

#pragma GCC diagnostic pop
