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
   
   When(Method(controllableMock, beginModuleMapping)).AlwaysReturn();
   When(Method(controllableMock, endModuleMapping)).AlwaysReturn();
   When(Method(controllableMock, isModuleWidgetHovered)).AlwaysReturn(false);
   When(Method(controllableMock, isSameModuleWidgetHovered)).AlwaysReturn(false);
   When(Method(controllableMock, isSelectedHovered)).AlwaysReturn(false);
   
   When(Method(controllableMock, sendOnEnterModuleChildWidget)).AlwaysReturn();
   When(Method(controllableMock, sendOnLeaveModuleChildWidget)).AlwaysReturn();
   When(Method(controllableMock, sendSelectedWidget)).AlwaysReturn();
   
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
      When(Method(controllableMock, isMappingKeyPressed)).Return(true);
      controller.set_current_states(sml::state<state::CtrlKeyPressed>);
      controller.process_event(event::OnKeyPressed{});
      REQUIRE(controller.is(sml::state<state::MappingModeActive>));
      Verify(Method(controllableMock, isMappingKeyPressed));
      Verify(Method(controllableMock, showTooltip));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state Idle if MappingCancelKey key was pressed")
   {
      When(Method(controllableMock, isMappingCancelKeyPressed)).Return(true);
      controller.set_current_states(sml::state<state::MappingModeActive>);
      controller.process_event(event::OnKeyPressed{});
      REQUIRE(controller.is(sml::state<state::Idle>));
      Verify(Method(controllableMock, isMappingCancelKeyPressed));
      Verify(Method(controllableMock, removeTooltip));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state ModuleHovered if module widget is hovered")
   {
      When(Method(controllableMock, isModuleWidgetHovered)).Return(true);
      controller.set_current_states(sml::state<state::MappingModeActive>);
      controller.process_event(event::OnWidgetHovered{});
      REQUIRE(controller.is(sml::state<state::ModuleHovered>));
      Verify(Method(controllableMock, isModuleWidgetHovered));
      Verify(Method(controllableMock, beginModuleMapping));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state MappingModeActive if not same module widget is hovered")
   {
      When(Method(controllableMock, isSameModuleWidgetHovered)).Return(false);
      controller.set_current_states(sml::state<state::ModuleHovered>);
      controller.process_event(event::OnWidgetHovered{});
      REQUIRE(controller.is(sml::state<state::MappingModeActive>));
      Verify(Method(controllableMock, isSameModuleWidgetHovered));
      Verify(Method(controllableMock, endModuleMapping));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state ModuleChildHovered if module child widget is hovered")
   {
      When(Method(controllableMock, isSameModuleWidgetHovered)).Return(true);
      When(Method(controllableMock, isModuleWidgetHovered)).Return(false);
      controller.set_current_states(sml::state<state::ModuleHovered>);
      controller.process_event(event::OnWidgetHovered{});
      REQUIRE(controller.is(sml::state<state::ModuleChildHovered>));
      Verify(Method(controllableMock, isSameModuleWidgetHovered));
      Verify(Method(controllableMock, isModuleWidgetHovered));
      Verify(Method(controllableMock, sendOnEnterModuleChildWidget));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state ModuleHovered if module child widget is not hovered anymore")
   {
      When(Method(controllableMock, isModuleWidgetHovered)).Return(true);
      controller.set_current_states(sml::state<state::ModuleChildHovered>);
      controller.process_event(event::OnWidgetHovered{});
      REQUIRE(controller.is(sml::state<state::ModuleHovered>));
      Verify(Method(controllableMock, isModuleWidgetHovered));
      Verify(Method(controllableMock, sendOnLeaveModuleChildWidget));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state ModuleChildSelected if module child widget is selected")
   {
      When(Method(controllableMock, isModuleWidgetHovered)).Return(false);
      When(Method(controllableMock, isSelectedHovered)).Return(true);
      controller.set_current_states(sml::state<state::ModuleChildHovered>);
      controller.process_event(event::OnWidgetSelected{});
      REQUIRE(controller.is(sml::state<state::ModuleChildSelected>));
      Verify(Method(controllableMock, isModuleWidgetHovered));
      Verify(Method(controllableMock, isSelectedHovered));
      Verify(Method(controllableMock, sendSelectedWidget));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller stays in state ModuleChildHovered if hovered is  selected not widget")
   {
      When(Method(controllableMock, isModuleWidgetHovered)).Return(false);
      When(Method(controllableMock, isSelectedHovered)).Return(false);
      controller.set_current_states(sml::state<state::ModuleChildHovered>);
      controller.process_event(event::OnWidgetSelected{});
      REQUIRE(controller.is(sml::state<state::ModuleChildHovered>));
      Verify(Method(controllableMock, isModuleWidgetHovered));
      Verify(Method(controllableMock, isSelectedHovered));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state ModuleHovered if selected module child widget is not hovered anymore")
   {
      When(Method(controllableMock, isModuleWidgetHovered)).Return(true);
      controller.set_current_states(sml::state<state::ModuleChildHovered>);
      controller.process_event(event::OnWidgetHovered{});
      REQUIRE(controller.is(sml::state<state::ModuleHovered>));
      Verify(Method(controllableMock, sendOnLeaveModuleChildWidget));
      Verify(Method(controllableMock, isModuleWidgetHovered));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
}
