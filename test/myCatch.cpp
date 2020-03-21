#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <catch2/catch.hpp>
#include <fakeit.hpp>
#include <TestOperators.hpp>

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

TEST_CASE("FakIt stuff from Rack", "[rack] [fakeit]")
{
   using namespace fakeit;
   using namespace rack::engine;
   using namespace qrx;
   
   Mock<CVWizardModule> mock;
   Mock<Module> moduleMock;
   
   auto args = Module::ProcessArgs{111.f, 222.f};
   auto json = std::unique_ptr<json_t>(new json_t{JSON_OBJECT, 88});
   
   When(Method(mock,process).Using(_)).AlwaysReturn();
   When(Method(mock,dataToJson)).AlwaysReturn(json.get());
   When(Method(mock,dataFromJson).Using(_)).AlwaysReturn();
   
   auto& m = mock.get();
   
   m.process(args);
   REQUIRE(m.dataToJson() == json.get());
   REQUIRE(m.dataToJson()->type == JSON_OBJECT);
   REQUIRE(m.dataToJson()->refcount == 88);
   m.dataFromJson(json.get());
   m.dataFromJson(json.get());
   
   Verify(Method(mock,process).Using(args)).Once();
   Verify(Method(mock,dataToJson)).Exactly(3);
   Verify(Method(mock,dataFromJson).Using(json.get())).Twice();
}

TEST_CASE("test a project class for coverage", "[rack] [coverage]")
{
   using namespace fakeit;
   using namespace rack::engine;
   using namespace qrx;
   
   CVWizardModule wiz;
   
   REQUIRE(wiz.dataToJson() == nullptr);
}

#pragma GCC diagnostic pop
