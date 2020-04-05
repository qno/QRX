#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <cvwizard/sm/keyboard/Keyboard.hpp>

#include <catch2/catch.hpp>

using namespace qrx::cvwizard::sm::keyboard;

FSM_INITIAL_STATE(Keyboard, Idle);

TEST_CASE("Keyboard statemachine", "[keyboard] [statemachine]")
{
   Keyboard::start();
   Keyboard::dispatch(ControlKeyPressedEvent{});
   Keyboard::dispatch(MappingKeyEvent{});
   Keyboard::dispatch(MappingCancelKeyEvent{});
}

#pragma GCC diagnostic pop
