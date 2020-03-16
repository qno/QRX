#define CATCH_CONFIG_MAIN

#include <hippomocks.h>
#include <catch2/catch.hpp>

#include <string>

#include <CVWizard/CVWizardModule.hpp>

struct MyParam
{
   int x;
   int y;
};

bool operator== (const MyParam& lhs, const MyParam& rhs)
{
   return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

class MockInterface
{
public:
   MockInterface() = delete;
   virtual ~MockInterface() = default;
   virtual const int getInt666() = 0;
   virtual const std::string getStringMMM() = 0;
   virtual const MyParam getParam(const MyParam& p) = 0;
};


TEST_CASE("Test1", "[tag]")
{
   auto value = 1;
   auto expected = 1;
   REQUIRE(value == expected);
}

TEST_CASE("Use a simple Mockup", "[hippomocks] [another tag]")
{
   MockRepository mockRepository;
   auto mock = mockRepository.Mock<MockInterface>();
   mockRepository.ExpectCall(mock, MockInterface::getInt666).Return(666);
   mockRepository.ExpectCall(mock, MockInterface::getStringMMM).Return(std::string{"MMM"});
   REQUIRE(mock->getInt666() == 666);
   REQUIRE(mock->getStringMMM() == std::string{"MMM"});
   
   auto p = MyParam{1,2};
   mockRepository.ExpectCall(mock, MockInterface::getParam).With(p).Return(p);
   REQUIRE(mock->getParam(p) == p);
}

namespace rack {
namespace engine {
inline bool operator== (const Module::ProcessArgs& lhs, const Module::ProcessArgs& rhs)
{
   return (lhs.sampleRate == rhs.sampleRate) && (lhs.sampleTime == rhs.sampleTime);
}
}
}

TEST_CASE("Mock stuff from Rack", "[rack] [hippomocks]")
{
   using namespace rack::engine;
   using namespace qrx;
   MockRepository mockRepository;
   auto mock = mockRepository.Mock<CVWizardModule>();
   
   auto args = Module::ProcessArgs{111.f, 222.f};
   auto json = std::unique_ptr<json_t>(new json_t{JSON_INTEGER, 88});
   
   mockRepository.ExpectCall(mock, CVWizardModule::process);
   mockRepository.ExpectCalls(mock, CVWizardModule::dataToJson, 3).Return(json.get());
   mockRepository.ExpectCalls(mock, CVWizardModule::dataFromJson, 2);
   
   mock->process(args);
   REQUIRE(mock->dataToJson() == json.get());
   REQUIRE(mock->dataToJson()->type == json->type);
   REQUIRE(mock->dataToJson()->refcount == json->refcount);
   mock->dataFromJson(json.get());
   mock->dataFromJson(json.get());
}
