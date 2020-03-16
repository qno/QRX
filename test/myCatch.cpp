#define CATCH_CONFIG_MAIN

#include <hippomocks.h>
#include <catch2/catch.hpp>

#include <string>

#include <engine/Module.hpp>

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

TEST_CASE("ModuleMockup", "[rack]")
{
   using namespace rack::engine;
   MockRepository mockRepository;
   auto mock = mockRepository.Mock<Module>();
   
   auto args = Module::ProcessArgs{111.f, 222.f};
   auto json = std::unique_ptr<json_t>(new json_t{JSON_INTEGER, 88});
   
   mockRepository.ExpectCall(mock, Module::process);
   mockRepository.OnCall(mock, Module::onSampleRateChange);
   mockRepository.OnCall(mock, Module::onReset);
   mockRepository.OnCall(mock, Module::onRandomize);
   mockRepository.OnCall(mock, Module::onAdd);
   mockRepository.OnCall(mock, Module::onRemove);
   mockRepository.ExpectCalls(mock, Module::dataToJson, 3).Return(json.get());
   mockRepository.ExpectCalls(mock, Module::dataFromJson, 2);
   
   mock->process(args);
   mock->onSampleRateChange();
   REQUIRE(mock->dataToJson() == json.get());
   REQUIRE(mock->dataToJson()->type == json->type);
   REQUIRE(mock->dataToJson()->refcount == json->refcount);
   mock->dataFromJson(json.get());
   mock->dataFromJson(json.get());
}
