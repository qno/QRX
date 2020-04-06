#include <sigslot/signal.hpp>
#include <catch2/catch.hpp>
#include <functional>
#include <iostream>

struct MyController
{
   using MySignalType = std::function<void()>;
   
   sigslot::connection connect(MySignalType signal)
   {
      return _signal.connect(signal);
   }
   
   void publish()
   {
      _signal();
   }
   
   sigslot::signal<> _signal;
};

struct MyView1
{
   void printThisOut()
   {
      std::cout << "MyView1 - this is called by a sigslot signal" << std::endl;
   }
};

struct MyView2
{
   void printThatOut()
   {
      std::cout << "MyView2 - this is called by a sigslot signal" << std::endl;
   }
};

TEST_CASE("SignalSlot playground", "[xxx]")
{
   auto ctrl = MyController{};
   auto view1 = MyView1{};
   auto view2 = MyView2{};
   
   ctrl.connect(std::bind(&MyView1::printThisOut, &view1));
   ctrl.connect(std::bind(&MyView2::printThatOut, &view2));
   
   ctrl.publish();
}

