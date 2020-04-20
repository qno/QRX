#include <cvwizard/controller/CVWizardController.hpp>

#include <catch2/catch.hpp>
#include <fakeit.hpp>

using namespace qrx::cvwizard::controller;
using namespace fakeit;

TEST_CASE("CVWizard controller", "[cvwizard] [controller]")
{
   Mock<CVWizardControllable> controllableMock;
   
   When(Method(controllableMock, showWidgetTooltip)).AlwaysReturn();
   When(Method(controllableMock, removeWidgetTooltip)).AlwaysReturn();
   When(Method(controllableMock, showTooltip)).AlwaysReturn();
   When(Method(controllableMock, removeTooltip)).AlwaysReturn();
   When(Method(controllableMock, isShowTooltipsEnabled)).AlwaysReturn(true);
   When(Method(controllableMock, toggleTooltip)).AlwaysReturn();
   
   When(Method(controllableMock, isControlKeyPressed)).AlwaysReturn(false);
   When(Method(controllableMock, isMappingKeyPressed)).AlwaysReturn(false);
   When(Method(controllableMock, isMappingCancelKeyPressed)).AlwaysReturn(false);
   When(Method(controllableMock, isTooltipKeyPressed)).AlwaysReturn(false);
   
   //   When(Method(controllableMock, handleHoveredWidget)).AlwaysReturn();
   When(Method(controllableMock, beginModuleMapping)).AlwaysReturn();
   When(Method(controllableMock, endModuleMapping)).AlwaysReturn();
   When(Method(controllableMock, isModuleWidgetHovered)).AlwaysReturn(false);
   When(Method(controllableMock, isSameModuleWidgetHovered)).AlwaysReturn(false);
   //   When(Method(controllableMock, isModuleWidgetSelected)).AlwaysReturn(false);
   //   When(Method(controllableMock, isParamWidgetHovered)).AlwaysReturn(false);
   //   When(Method(controllableMock, isParamWidgetSelected)).AlwaysReturn(false);
   //   When(Method(controllableMock, isInputPortWidgetHovered)).AlwaysReturn(false);
   //   When(Method(controllableMock, isInputPortWidgetSelected)).AlwaysReturn(false);
   //   When(Method(controllableMock, addSelectedParamWidget)).AlwaysReturn();
   //   When(Method(controllableMock, addSelectedPortWidget)).AlwaysReturn();
   
   auto& m = controllableMock.get();
   sml::sm<CVWizardController, sml::testing> controller{m};
   
   SECTION("ensure initial state")
   {
      REQUIRE(controller.is(sml::state<state::Idle>));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure show widget tooltip on OnEnter event")
   {
      controller.process_event(event::OnEnter{});
      REQUIRE(controller.is(sml::state<state::Idle>));
      Verify(Method(controllableMock, isShowTooltipsEnabled));
      Verify(Method(controllableMock, showWidgetTooltip));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }

   SECTION("ensure remove widget tooltip on OnLeave event")
   {
      controller.process_event(event::OnLeave{});
      REQUIRE(controller.is(sml::state<state::Idle>));
      Verify(Method(controllableMock, isShowTooltipsEnabled));
      Verify(Method(controllableMock, removeWidgetTooltip));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state CtrlKeyPressed if Ctrl key was pressed")
   {
      When(Method(controllableMock, isControlKeyPressed)).Return(true);
   
      REQUIRE(controller.is(sml::state<state::Idle>));
      controller.process_event(event::OnKeyPressed{});
      REQUIRE(controller.is(sml::state<state::CtrlKeyPressed>));
      Verify(Method(controllableMock, isControlKeyPressed));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state MappingModeActive if Ctrl + MappingKey was pressed")
   {
      controller.set_current_states(sml::state<state::CtrlKeyPressed>);
      When(Method(controllableMock, isMappingKeyPressed)).Return(true);

      controller.process_event(event::OnKeyPressed{});
      REQUIRE(controller.is(sml::state<state::MappingModeActive>));
      Verify(Method(controllableMock, isMappingKeyPressed));
      Verify(Method(controllableMock, showTooltip));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state Idle if MappingCancelKey key was pressed")
   {
      controller.set_current_states(sml::state<state::MappingModeActive>);
      When(Method(controllableMock, isMappingCancelKeyPressed)).Return(true);
      
      controller.process_event(event::OnKeyPressed{});
      REQUIRE(controller.is(sml::state<state::Idle>));
      Verify(Method(controllableMock, isMappingCancelKeyPressed));
      Verify(Method(controllableMock, removeTooltip));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state ModuleHovered if module widget is hovered")
   {
      controller.set_current_states(sml::state<state::MappingModeActive>);
      When(Method(controllableMock, isModuleWidgetHovered)).Return(true);
      
      controller.process_event(event::OnWidgetHovered{});
      REQUIRE(controller.is(sml::state<state::ModuleHovered>));
      Verify(Method(controllableMock, isModuleWidgetHovered));
      Verify(Method(controllableMock, beginModuleMapping));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state MappingModeActive if not same module widget is hovered")
   {
      controller.set_current_states(sml::state<state::ModuleHovered>);
      When(Method(controllableMock, isSameModuleWidgetHovered)).Return(false);
      
      controller.process_event(event::OnWidgetHovered{});
      REQUIRE(controller.is(sml::state<state::MappingModeActive>));
      Verify(Method(controllableMock, isSameModuleWidgetHovered));
      Verify(Method(controllableMock, endModuleMapping));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
}
