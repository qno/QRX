#include <cvwizard/controller/MappingController.hpp>

#include <catch2/catch.hpp>
#include <fakeit.hpp>

using namespace qrx::cvwizard::controller::mapping;
using namespace fakeit;

TEST_CASE("Mapping controller", "[mapping] [controller]")
{
   Mock<MappingControllable> controllableMock;
   When(Method(controllableMock, isInputPortWidget)).AlwaysReturn(false);
   When(Method(controllableMock, isKnobParamWidget)).AlwaysReturn(false);
   When(Method(controllableMock, isSelectedHovered)).AlwaysReturn(false);
   When(Method(controllableMock, enableHoverWidget)).AlwaysReturn();
   When(Method(controllableMock, disableHoverWidget)).AlwaysReturn();
   When(Method(controllableMock, addSelectedInputPort)).AlwaysReturn();
   When(Method(controllableMock, addSelectedKnobParamWidget)).AlwaysReturn();
   
   auto& m = controllableMock.get();
   sml::sm<MappingController, sml::testing> controller{m};
   
   SECTION("ensure initial state")
   {
      REQUIRE(controller.is(sml::state<state::Idle>));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state InputPortHovered if input port widget is hovered")
   {
      When(Method(controllableMock, isInputPortWidget)).Return(true);
      controller.process_event(event::OnEnterWidget{});
      REQUIRE(controller.is(sml::state<state::InputPortHovered>));
      Verify(Method(controllableMock, isInputPortWidget));
      Verify(Method(controllableMock, enableHoverWidget));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state Idle on event OnLeaveWidget")
   {
      controller.set_current_states(sml::state<state::InputPortHovered>);
      controller.process_event(event::OnLeaveWidget{});
      REQUIRE(controller.is(sml::state<state::Idle>));
      Verify(Method(controllableMock, disableHoverWidget));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state InputPortSelected if input port widget is selected")
   {
      When(Method(controllableMock, isSelectedHovered)).Return(true);
      controller.set_current_states(sml::state<state::InputPortHovered>);
      controller.process_event(event::OnWidgetSelected{});
      REQUIRE(controller.is(sml::state<state::InputPortSelected>));
      Verify(Method(controllableMock, addSelectedInputPort));
      Verify(Method(controllableMock, isSelectedHovered));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state InputPortSelected on event OnLeaveWidget")
   {
      controller.set_current_states(sml::state<state::InputPortSelected>);
      controller.process_event(event::OnLeaveWidget{});
      REQUIRE(controller.is(sml::state<state::InputPortSelected>));
      Verify(Method(controllableMock, disableHoverWidget));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state KnobParamHovered if knob param widget is hovered")
   {
      When(Method(controllableMock, isKnobParamWidget)).Return(true);
      controller.set_current_states(sml::state<state::InputPortSelected>);
      controller.process_event(event::OnEnterWidget{});
      REQUIRE(controller.is(sml::state<state::KnobParamHovered>));
      Verify(Method(controllableMock, isKnobParamWidget));
      Verify(Method(controllableMock, enableHoverWidget));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state InputPortSelected on event OnLeaveWidget if state was KnobParamHovered")
   {
      controller.set_current_states(sml::state<state::KnobParamHovered>);
      controller.process_event(event::OnLeaveWidget{});
      REQUIRE(controller.is(sml::state<state::InputPortSelected>));
      Verify(Method(controllableMock, disableHoverWidget));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state KnobParamSelected if knob param widget is selected")
   {
      When(Method(controllableMock, isSelectedHovered)).Return(true);
      controller.set_current_states(sml::state<state::KnobParamHovered>);
      controller.process_event(event::OnWidgetSelected{});
      REQUIRE(controller.is(sml::state<state::KnobParamSelected>));
      Verify(Method(controllableMock, addSelectedKnobParamWidget));
      Verify(Method(controllableMock, isSelectedHovered));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state Idle on event OnLeaveWidget")
   {
      controller.set_current_states(sml::state<state::KnobParamSelected>);
      controller.process_event(event::OnLeaveWidget{});
      REQUIRE(controller.is(sml::state<state::Idle>));
      Verify(Method(controllableMock, disableHoverWidget));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
}
