#include <sigslot/signal.hpp>
#include <catch2/catch.hpp>
#include <functional>
#include <iostream>

struct MyController
{
   using Callback1 = std::function<void()>;
   using Callback2 = std::function<void(int)>;
   
   sigslot::connection connect1(const Callback1& callback)
   {
      return _signals1.connect(callback);
   }
   
   sigslot::connection connect2(const Callback2& callback)
   {
      return _signals2.connect(callback);
   }
   
   void publish()
   {
      _signals1();
      for (int i=0; i < 10; ++i)
         _signals2(i);
   }
   
   sigslot::signal<> _signals1;
   sigslot::signal<int> _signals2;
};

struct MyView1
{
   void printThisOut()
   {
      std::cout << "MyView1 - this is called by a sigslot signal" << std::endl;
   }
   
   void printThisOutX(int x)
   {
      std::cout << "MyView1 - this is called by a sigslot signal - " << x << std::endl;
   }
};

struct MyView2
{
   void printThatOut()
   {
      std::cout << "MyView2 - this is called by a sigslot signal" << std::endl;
   }
   
   void printThatOutX(int x)
   {
      std::cout << "MyView2 - this is called by a sigslot signal - " << x << std::endl;
   }
};

TEST_CASE("SignalSlot playground", "[xxx]")
{
   auto ctrl = MyController{};
   auto view1 = MyView1{};
   auto view2 = MyView2{};
   
   ctrl.connect1(std::bind(&MyView1::printThisOut, &view1));
   ctrl.connect2(std::bind(&MyView1::printThisOutX, &view1, std::placeholders::_1));
   ctrl.connect1(std::bind(&MyView2::printThatOut, &view2));
   ctrl.connect2(std::bind(&MyView2::printThatOutX, &view2, std::placeholders::_1));
   
   ctrl.publish();
}

