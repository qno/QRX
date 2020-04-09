#include <cvwizard/controller/CVWizardController.hpp>

#include <catch2/catch.hpp>
#include <fakeit.hpp>

using namespace qrx::cvwizard::controller;
using namespace fakeit;

Mock<CVWizardControllable> controllableMock;

TEST_CASE("CVWizard controller", "[cvwizard] [controller]")
{
   When(Method(controllableMock, showWidgetTooltip));
   When(Method(controllableMock, removeWidgetTooltip));
   When(Method(controllableMock, showTooltip));
   When(Method(controllableMock, removeTooltip));
   When(Method(controllableMock, isShowTooltipsEnabled)).AlwaysReturn(true);
   When(Method(controllableMock, toogleTooltip));
   
   When(Method(controllableMock, isControlKeyPressed)).Return(false);
   When(Method(controllableMock, isMappingKeyPressed)).AlwaysReturn(false);
   When(Method(controllableMock, isMappingCancelKeyPressed)).AlwaysReturn(false);
   When(Method(controllableMock, isTooltipKeyPressed)).AlwaysReturn(false);
   
   SECTION("ensure state CtrlKeyPressed if Ctrl Key was pressed")
   {
      controllableMock.Reset();
      auto& m = controllableMock.get();
      sml::sm<CVWizardController> controller{m};
      REQUIRE(controller.is(sml::state<state::Idle>));
   }
   
   SECTION("ensure controller is in state CtrlKeyPressed if Ctrl Key was pressed")
   {
      controllableMock.Reset();
      When(Method(controllableMock, isControlKeyPressed)).Return(true);
   
      auto& m = controllableMock.get();
      sml::sm<CVWizardController> controller{m};
      
      const auto e = event::OnKeyPressed{};
      controller.process_event(e);
      REQUIRE(controller.is(sml::state<state::CtrlKeyPressed>));
   }
   
//   SECTION("ensure controller is in state MappingModeActive if Ctrl-M was pressed")
//   {
//      controllableMock.Reset();
//      When(Method(controllableMock, isControlKeyPressed)).Return(true);
//      When(Method(controllableMock, isMappingKeyPressed)).Return(true);
//      When(Method(controllableMock, showTooltip));
//
//      auto& m = controllableMock.get();
//      sml::sm<CVWizardController> controller{m};
//
//      const auto e = event::OnKeyPressed{};
//      controller.process_event(e);
//      REQUIRE(controller.is(sml::state<state::CtrlKeyPressed>));
//
//      controller.process_event(e);
//      REQUIRE(controller.is(sml::state<state::MappingModeActive>));
//      Verify(Method(controllableMock, showTooltip)).;
//   }
}
