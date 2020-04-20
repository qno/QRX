#include <cvwizard/CVWizard.hpp>

#include <catch2/catch.hpp>
#include <fakeit.hpp>

using namespace qrx::boundary::rack;
using namespace qrx::cvwizard;
using namespace fakeit;

TEST_CASE("CVWizard isModuleWidgetHovered", "[cvwizard]")
{
   Mock<AppBoundary> rackBoundaryMock;
   When(Method(rackBoundaryMock, getEventState)).AlwaysReturn(nullptr);
   When(Method(rackBoundaryMock, getScene)).AlwaysReturn(nullptr);
   When(Method(rackBoundaryMock, getWindow)).AlwaysReturn(nullptr);
   When(Method(rackBoundaryMock, isKeyPressed)).AlwaysReturn(false);
   When(Method(rackBoundaryMock, isModKeyPressed)).AlwaysReturn(false);
   
   auto& m = rackBoundaryMock.get();
   CVWizard cvWizard{m};
   
   SECTION("ensure return false if hovered module widget is nullptr")
   {
      State state;
      REQUIRE(state.getHoveredWidget() == nullptr);
      
      When(Method(rackBoundaryMock, getEventState)).AlwaysReturn(&state);
      REQUIRE(cvWizard.isModuleWidgetHovered() == false);
      Verify(Method(rackBoundaryMock, getEventState));
      VerifyNoOtherInvocations(rackBoundaryMock);
      rackBoundaryMock.Reset();
   }
   
   // This test causes segfault in `CVWizard::getIfIsModuleWidget(Widget* widget)` dynamic_cast
   /*SECTION("ensure return true if hovered widget is module widget")
   {
      ModuleWidget moduleWidget;
      State state;
      state.hoveredWidget = &moduleWidget;
      
      REQUIRE(state.getHoveredWidget() == &moduleWidget);
      REQUIRE(dynamic_cast<ModuleWidget*>(state.getHoveredWidget()));
      
      When(Method(rackBoundaryMock, getEventState)).AlwaysReturn(&state);
      REQUIRE(m.getEventState() == &state);
      REQUIRE(cvWizard.isModuleWidgetHovered() == true);
      Verify(Method(rackBoundaryMock, getEventState));
      VerifyNoOtherInvocations(rackBoundaryMock);
      rackBoundaryMock.Reset();
   }*/
}

TEST_CASE("CVWizard isSameModuleWidgetHovered", "[cvwizard]")
{
   Mock<AppBoundary> rackBoundaryMock;
   When(Method(rackBoundaryMock, getEventState)).AlwaysReturn(nullptr);
   When(Method(rackBoundaryMock, getScene)).AlwaysReturn(nullptr);
   When(Method(rackBoundaryMock, getWindow)).AlwaysReturn(nullptr);
   When(Method(rackBoundaryMock, isKeyPressed)).AlwaysReturn(false);
   When(Method(rackBoundaryMock, isModKeyPressed)).AlwaysReturn(false);
   
   auto& m = rackBoundaryMock.get();
   CVWizard cvWizard{m};
   auto& model = cvWizard._model;

   SECTION("ensure return false if hovered module widget != app hovered widget")
   {
      Widget appHoveredWidget;
      State state;
      state.hoveredWidget = &appHoveredWidget;
      ModuleWidget hoveredModuleWidget;
      model.beginModuleMapping(&hoveredModuleWidget);
      
      When(Method(rackBoundaryMock, getEventState)).Return(&state);
      REQUIRE(cvWizard.isSameModuleWidgetHovered() == false);
      Verify(Method(rackBoundaryMock, getEventState));
      VerifyNoOtherInvocations(rackBoundaryMock);
      rackBoundaryMock.Reset();
   }
   
   SECTION("ensure return true if hovered module widget == app hovered widget")
   {
      ModuleWidget appHoveredModuleWidget;
      State state;
      state.hoveredWidget = &appHoveredModuleWidget;
      model.beginModuleMapping(&appHoveredModuleWidget);
      
      When(Method(rackBoundaryMock, getEventState)).Return(&state);
      REQUIRE(cvWizard.isSameModuleWidgetHovered() == true);
      Verify(Method(rackBoundaryMock, getEventState));
      VerifyNoOtherInvocations(rackBoundaryMock);
      rackBoundaryMock.Reset();
   }
   
   SECTION("ensure return true if hovered module widget is a parent of app hovered widget")
   {
      ModuleWidget hoveredModuleWidget;
      Widget appHoveredWidget;
      appHoveredWidget.parent = &hoveredModuleWidget;
      
      State state;
      state.hoveredWidget = &appHoveredWidget;
      model.beginModuleMapping(&hoveredModuleWidget);
      
      When(Method(rackBoundaryMock, getEventState)).Return(&state);
      REQUIRE(cvWizard.isSameModuleWidgetHovered() == true);
      Verify(Method(rackBoundaryMock, getEventState));
      VerifyNoOtherInvocations(rackBoundaryMock);
      rackBoundaryMock.Reset();
   }
   
   SECTION("ensure return false if hovered module widget is not a parent of app hovered widget")
   {
      ModuleWidget hoveredModuleWidget;
      Widget appHoveredWidget;
      Widget appHoveredParentWidget;
      appHoveredWidget.parent = &appHoveredParentWidget;
      
      State state;
      state.hoveredWidget = &appHoveredWidget;
      model.beginModuleMapping(&hoveredModuleWidget);
      
      When(Method(rackBoundaryMock, getEventState)).Return(&state);
      REQUIRE(cvWizard.isSameModuleWidgetHovered() == false);
      Verify(Method(rackBoundaryMock, getEventState));
      VerifyNoOtherInvocations(rackBoundaryMock);
      rackBoundaryMock.Reset();
   }
}
