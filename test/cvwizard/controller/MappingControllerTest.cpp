#include <cvwizard/controller/MappingController.hpp>

#include <catch2/catch.hpp>
#include <fakeit.hpp>

using namespace qrx::cvwizard::controller::mapping;
using namespace fakeit;

TEST_CASE("Mapping controller", "[mapping] [controller]")
{
   Mock<MappingControllable> controllableMock;
   When(Method(controllableMock, isInputPortWidgetHovered)).AlwaysReturn(false);
   When(Method(controllableMock, hoverWidget)).AlwaysReturn();
   
   auto& m = controllableMock.get();
   sml::sm<MappingController, sml::testing> controller{m};
   
   SECTION("ensure initial state")
   {
      REQUIRE(controller.is(sml::state<state::Idle>));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
   
   SECTION("ensure controller is in state InputParamHovered if input param is hovered")
   {
      When(Method(controllableMock, isInputPortWidgetHovered)).Return(true);
      controller.process_event(event::OnWidgetHovered{});
      REQUIRE(controller.is(sml::state<state::InputPortHovered>));
      Verify(Method(controllableMock, isInputPortWidgetHovered));
      Verify(Method(controllableMock, hoverWidget));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
}
