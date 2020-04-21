#include <cvwizard/controller/MappingController.hpp>

#include <catch2/catch.hpp>
#include <fakeit.hpp>

using namespace qrx::cvwizard::controller;
using namespace fakeit;

TEST_CASE("Mapping controller", "[mapping] [controller]")
{
   Mock<MappingControllable> controllableMock;
   
   auto& m = controllableMock.get();
   sml::sm<MappingController, sml::testing> controller{m};
   
   SECTION("ensure initial state")
   {
      REQUIRE(controller.is(sml::X));
      VerifyNoOtherInvocations(controllableMock);
      controllableMock.Reset();
   }
}
