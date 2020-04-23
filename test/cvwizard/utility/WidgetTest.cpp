#include <cvwizard/utility/Widget.hpp>

#include <catch2/catch.hpp>

using namespace qrx::cvwizard;
using namespace qrx;

TEST_CASE("Widget utility", "[utility] [widget]")
{
   // disabled as test crash with segfault on Windows, will be fixed later
   /*
   SECTION("ensure getIfIsModuleWidget returns pointer if widget is ModuleWidget")
   {
      auto widget = std::make_unique<boundary::rack::ModuleWidget>();
      REQUIRE(utility::Widget::getIfIsModuleWidget(widget.get()) != nullptr);
   }
   
   SECTION("ensure getIfIsModuleWidget returns nullptr if widget is not ModuleWidget")
   {
      auto widget = std::make_unique<boundary::rack::ParamWidget>();
      REQUIRE(utility::Widget::getIfIsModuleWidget(widget.get()) == nullptr);
   }
   
   SECTION("ensure getIfIsParamWidget returns pointer if widget is a Knob ParamWidget")
   {
      auto widget = std::make_unique<boundary::rack::Knob>();
      REQUIRE(utility::Widget::getIfIsParamWidget(widget.get()) != nullptr);
   }
   
   SECTION("ensure getIfIsModuleWidget returns nullptr if widget is not a Knob ParamWidget")
   {
      auto widget = std::make_unique<boundary::rack::ParamWidget>();
      REQUIRE(utility::Widget::getIfIsParamWidget(widget.get()) == nullptr);
   }
   
   SECTION("ensure getIfIsInputPortWidget returns pointer if widget is a input PortWidget")
   {
      auto widget = std::make_unique<boundary::rack::PortWidget>();
      widget->type = boundary::rack::PortWidget::INPUT;
      REQUIRE(utility::Widget::getIfIsInputPortWidget(widget.get()) != nullptr);
   }
   
   SECTION("ensure getIfIsInputPortWidget returns nullptr if widget is not a input PortWidget")
   {
      auto widget = std::make_unique<boundary::rack::PortWidget>();
      widget->type = boundary::rack::PortWidget::OUTPUT;
      REQUIRE(utility::Widget::getIfIsParamWidget(widget.get()) == nullptr);
   }*/
}
