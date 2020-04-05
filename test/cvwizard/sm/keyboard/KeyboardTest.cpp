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
   REQUIRE(Keyboard::is_in_state<Idle>());
   Keyboard::dispatch(ControlKeyPressedEvent{});
   REQUIRE(Keyboard::is_in_state<ControlKeyPressed>());
   Keyboard::dispatch(ControlKeyPressedEvent{});
   REQUIRE(Keyboard::is_in_state<ControlKeyPressed>());
   Keyboard::dispatch(ControlKeyReleasedEvent{});
   REQUIRE(Keyboard::is_in_state<Idle>());
   Keyboard::dispatch(ControlKeyPressedEvent{});
   REQUIRE(Keyboard::is_in_state<ControlKeyPressed>());
   Keyboard::dispatch(MappingKeyEvent{});
   REQUIRE(Keyboard::is_in_state<MappingModeActive>());
   Keyboard::dispatch(MappingCancelKeyEvent{});
   REQUIRE(Keyboard::is_in_state<Idle>());
}

#pragma GCC diagnostic pop
