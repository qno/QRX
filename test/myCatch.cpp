#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#define CATCH_CONFIG_MAIN

#include <fakeit.hpp>
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
   virtual int getInt666() = 0;
   virtual const std::string getStringMMM() = 0;
   virtual const MyParam getParam(const MyParam& p) = 0;
};


TEST_CASE("Test1", "[tag]")
{
   auto value = 1;
   auto expected = 1;
   REQUIRE(value == expected);
}

TEST_CASE("Use a simple Mockup with FakeIt", "[fakeit] [another tag]")
{
   using namespace fakeit;
   Mock<MockInterface> mock;
   
   auto s = std::string{"MMM"};
   auto p = MyParam{1,2};
   
   When(Method(mock,getInt666)).Return(666);
   When(Method(mock,getStringMMM)).Return(s);
   When(Method(mock,getParam).Using(p)).Return(p);
   
   auto& m = mock.get();
   REQUIRE(m.getInt666() == 666);
   REQUIRE(m.getStringMMM() == s);
   REQUIRE(m.getParam(p) == p);
   
   Verify(Method(mock,getInt666));
   Verify(Method(mock,getStringMMM));
   Verify(Method(mock,getParam).Using(p));
}

namespace rack {
namespace engine {
inline bool operator== (const Module::ProcessArgs& lhs, const Module::ProcessArgs& rhs)
{
   return (lhs.sampleRate == rhs.sampleRate) && (lhs.sampleTime == rhs.sampleTime);
}

Module::Module() { }
Module::~Module() { }
void Module::config(int, int, int, int) { }
}
}

TEST_CASE("FakIt stuff from Rack", "[rack] [fakeit]")
{
   using namespace fakeit;
   using namespace rack::engine;
   using namespace qrx;
   
   Mock<CVWizardModule> mock;
   Mock<Module> moduleMock;
   
   auto args = Module::ProcessArgs{111.f, 222.f};
   auto json = std::unique_ptr<json_t>(new json_t{JSON_INTEGER, 88});
   
   //When(Method(mock,process).Using(args));
   When(Method(mock,dataToJson)).Return(json.get());
   When(Method(mock,dataFromJson).Using(json.get()));
   
   auto& m = mock.get();
   
   //m.process(args);
   REQUIRE(m.dataToJson() == json.get());
   //REQUIRE(m.dataToJson()->type == json->type);
   //REQUIRE(m.dataToJson()->refcount == json->refcount);
   //m.dataFromJson(json.get());
   //m.dataFromJson(json.get());
   
   //Verify(Method(mock,process).Using(args)).Once();
   //Verify(Method(mock,dataToJson)).Exactly(3);
   //Verify(Method(mock,dataFromJson).Using(json.get())).Twice();
}

#pragma GCC diagnostic pop

