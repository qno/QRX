#include <cvwizard/CVWizard.hpp>

#include <catch2/catch.hpp>
#include <fakeit.hpp>

using namespace qrx::boundary::rack;
using namespace qrx::cvwizard;
using namespace fakeit;

TEST_CASE("CVWizard isSameModuleWidgetHovered", "[cvwizard]")
{
   Mock<AppBoundary> rackBoundaryMock;
   
   When(Method(rackBoundaryMock, getEventState)).AlwaysReturn(nullptr);
   When(Method(rackBoundaryMock, getScene)).AlwaysReturn(nullptr);
   When(Method(rackBoundaryMock, getWindow)).AlwaysReturn(nullptr);
   
   auto& m = rackBoundaryMock.get();
   
   CVWizard cvWizard{m};
   auto& model = cvWizard._model;
   
   SECTION("ensure return false if hovered module widget is nullptr")
   {
      Widget appHoveredWidget;
      State state;
      state.hoveredWidget = &appHoveredWidget;
      
      When(Method(rackBoundaryMock, getEventState)).Return(&state);
      REQUIRE(cvWizard.isSameModuleWidgetHovered() == false);
      Verify(Method(rackBoundaryMock, getEventState));
      VerifyNoOtherInvocations(rackBoundaryMock);
      rackBoundaryMock.Reset();
   }
   
   SECTION("ensure return false if hovered module widget != app hovered widget")
   {
      Widget appHoveredWidget;
      State state;
      state.hoveredWidget = &appHoveredWidget;
      Widget hoveredWidget;
      model.hoveredModuleWidget = &hoveredWidget;
      
      When(Method(rackBoundaryMock, getEventState)).Return(&state);
      REQUIRE(cvWizard.isSameModuleWidgetHovered() == false);
      Verify(Method(rackBoundaryMock, getEventState));
      VerifyNoOtherInvocations(rackBoundaryMock);
      rackBoundaryMock.Reset();
   }
   
   SECTION("ensure return true if hovered module widget == app hovered widget")
   {
      Widget appHoveredWidget;
      State state;
      state.hoveredWidget = &appHoveredWidget;
      model.hoveredModuleWidget = &appHoveredWidget;
      
      When(Method(rackBoundaryMock, getEventState)).Return(&state);
      REQUIRE(cvWizard.isSameModuleWidgetHovered() == true);
      Verify(Method(rackBoundaryMock, getEventState));
      VerifyNoOtherInvocations(rackBoundaryMock);
      rackBoundaryMock.Reset();
   }
   
   SECTION("ensure return true if hovered module widget is a parent of app hovered widget")
   {
      Widget hoveredModuleWidget;
      Widget appHoveredWidget;
      appHoveredWidget.parent = &hoveredModuleWidget;
      
      State state;
      state.hoveredWidget = &appHoveredWidget;
      model.hoveredModuleWidget = &hoveredModuleWidget;
      
      When(Method(rackBoundaryMock, getEventState)).Return(&state);
      REQUIRE(cvWizard.isSameModuleWidgetHovered() == true);
      Verify(Method(rackBoundaryMock, getEventState));
      VerifyNoOtherInvocations(rackBoundaryMock);
      rackBoundaryMock.Reset();
   }
   
   SECTION("ensure return false if hovered module widget is not a parent of app hovered widget")
   {
      Widget hoveredModuleWidget;
      Widget appHoveredWidget;
      Widget appHoveredParentWidget;
      appHoveredWidget.parent = &appHoveredParentWidget;
      
      State state;
      state.hoveredWidget = &appHoveredWidget;
      model.hoveredModuleWidget = &hoveredModuleWidget;
      
      When(Method(rackBoundaryMock, getEventState)).Return(&state);
      REQUIRE(cvWizard.isSameModuleWidgetHovered() == false);
      Verify(Method(rackBoundaryMock, getEventState));
      VerifyNoOtherInvocations(rackBoundaryMock);
      rackBoundaryMock.Reset();
   }
}
