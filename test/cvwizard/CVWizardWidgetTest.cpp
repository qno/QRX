#include <cvwizard/CVWizardWidget.hpp>

#include <catch2/catch.hpp>
#include <fakeit.hpp>

using namespace qrx::cvwizard;
using namespace fakeit;

TEST_CASE("CVWizardWidget isSameModuleWidgetHovered", "[cvwizard] [widget]")
{
   Mock<qrx::boundary::RackAppBoundary> rackBoundaryMock;
   
   When(Method(rackBoundaryMock, getEventState)).AlwaysReturn(nullptr);
   When(Method(rackBoundaryMock, getScene)).AlwaysReturn(nullptr);
   When(Method(rackBoundaryMock, getWindow)).AlwaysReturn(nullptr);
   
   auto rackBoundary = std::shared_ptr<qrx::boundary::RackAppBoundary>(&rackBoundaryMock(), [](...) {});
   CVWizardWidget cvWizardWidget{nullptr};
   auto& model = cvWizardWidget.getModel();
   cvWizardWidget.setApp(rackBoundary);
   
   SECTION("ensure return false if hovered module widget is nullptr")
   {
      rack::Widget appHoveredWidget;
      rack::event::State state;
      state.hoveredWidget = &appHoveredWidget;
      
      When(Method(rackBoundaryMock, getEventState)).Return(&state);
      REQUIRE(cvWizardWidget.isSameModuleWidgetHovered() == false);
      Verify(Method(rackBoundaryMock, getEventState));
      VerifyNoOtherInvocations(rackBoundaryMock);
      rackBoundaryMock.Reset();
   }
   
   SECTION("ensure return false if hovered module widget != app hovered widget")
   {
      rack::Widget appHoveredWidget;
      rack::event::State state;
      state.hoveredWidget = &appHoveredWidget;
      rack::Widget hoveredWidget;
      model.hoveredModuleWidget = &hoveredWidget;
      
      When(Method(rackBoundaryMock, getEventState)).Return(&state);
      REQUIRE(cvWizardWidget.isSameModuleWidgetHovered() == false);
      Verify(Method(rackBoundaryMock, getEventState));
      VerifyNoOtherInvocations(rackBoundaryMock);
      rackBoundaryMock.Reset();
   }
   
   SECTION("ensure return true if hovered module widget == app hovered widget")
   {
      rack::Widget appHoveredWidget;
      rack::event::State state;
      state.hoveredWidget = &appHoveredWidget;
      model.hoveredModuleWidget = &appHoveredWidget;
      
      When(Method(rackBoundaryMock, getEventState)).Return(&state);
      REQUIRE(cvWizardWidget.isSameModuleWidgetHovered() == true);
      Verify(Method(rackBoundaryMock, getEventState));
      VerifyNoOtherInvocations(rackBoundaryMock);
      rackBoundaryMock.Reset();
   }
   
   SECTION("ensure return true if hovered module widget is a parent of app hovered widget")
   {
      rack::Widget hoveredModuleWidget;
      rack::Widget appHoveredWidget;
      appHoveredWidget.parent = &hoveredModuleWidget;
      
      rack::event::State state;
      state.hoveredWidget = &appHoveredWidget;
      model.hoveredModuleWidget = &hoveredModuleWidget;
      
      When(Method(rackBoundaryMock, getEventState)).Return(&state);
      REQUIRE(cvWizardWidget.isSameModuleWidgetHovered() == true);
      Verify(Method(rackBoundaryMock, getEventState));
      VerifyNoOtherInvocations(rackBoundaryMock);
      rackBoundaryMock.Reset();
   }
   
   SECTION("ensure return false if hovered module widget is not a parent of app hovered widget")
   {
      rack::Widget hoveredModuleWidget;
      rack::Widget appHoveredWidget;
      rack::Widget appHoveredParentWidget;
      appHoveredWidget.parent = &appHoveredParentWidget;
      
      rack::event::State state;
      state.hoveredWidget = &appHoveredWidget;
      model.hoveredModuleWidget = &hoveredModuleWidget;
      
      When(Method(rackBoundaryMock, getEventState)).Return(&state);
      REQUIRE(cvWizardWidget.isSameModuleWidgetHovered() == false);
      Verify(Method(rackBoundaryMock, getEventState));
      VerifyNoOtherInvocations(rackBoundaryMock);
      rackBoundaryMock.Reset();
   }
}
