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
   When(Method(controllableMock, toogleTooltip)).AlwaysReturn();
   
   When(Method(controllableMock, isControlKeyPressed)).AlwaysReturn(true);
   When(Method(controllableMock, isMappingKeyPressed)).AlwaysReturn(true);
   When(Method(controllableMock, isMappingCancelKeyPressed)).AlwaysReturn(false);
   When(Method(controllableMock, isTooltipKeyPressed)).AlwaysReturn(false);
   
   auto& m = controllableMock.get();
   
   SECTION("ensure initial state")
   {
      sml::sm<CVWizardController> controller{m};
      REQUIRE(controller.is(sml::state<state::Idle>));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state CtrlKeyPressed if Ctrl Key was pressed")
   {
      sml::sm<CVWizardController> controller{m};
      
      const auto e = event::OnKeyPressed{};
      controller.process_event(e);
      REQUIRE(controller.is(sml::state<state::CtrlKeyPressed>));
      Verify(Method(controllableMock, isControlKeyPressed));
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state MappingModeActive if Ctrl-M was pressed")
   {
      sml::sm<CVWizardController> controller{m};

      const auto e = event::OnKeyPressed{};
      controller.process_event(e);
      REQUIRE(controller.is(sml::state<state::CtrlKeyPressed>));
      Verify(Method(controllableMock, isControlKeyPressed));

      controller.process_event(e);
      REQUIRE(controller.is(sml::state<state::MappingModeActive>));
      Verify(Method(controllableMock, isMappingKeyPressed));
      Verify(Method(controllableMock, showTooltip));
      controllableMock.Reset();
   }
}
