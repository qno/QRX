#define CATCH_CONFIG_MAIN

#include <hippomocks.h>
#include <catch2/catch.hpp>

#include <string>

class MockInterface
{
public:
   MockInterface() = delete;
   virtual ~MockInterface() = default;
   virtual const int getInt666() = 0;
   virtual const std::string getStringMMM() = 0;
};

TEST_CASE("Test1", "[simple]")
{
   REQUIRE(1 == 1);
}

TEST_CASE("Mockup", "[hippomock]")
{
   MockRepository mockRepository;
   auto mock = mockRepository.Mock<MockInterface>();
   mockRepository.ExpectCall(mock, MockInterface::getInt666).Return(666);
   mockRepository.ExpectCall(mock, MockInterface::getStringMMM).Return(std::string{"MMM"});
   REQUIRE(666 == mock->getInt666());
   REQUIRE(std::string{"MMM"} == mock->getStringMMM());
}
