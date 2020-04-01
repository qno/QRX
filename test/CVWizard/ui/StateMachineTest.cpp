#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <CVWizard/ui/StateMachine.hpp>

#include <catch2/catch.hpp>
//#include <fakeit.hpp>

#include <iostream>

namespace x
{
// Events
class MyToggleEvent : public tinyfsm::Event
{
public:
   int x;
};

// Statemachine
class MySM : public tinyfsm::Fsm<MySM>
{
public:
   
   MySM() = default;
   virtual ~MySM() = default;
   
   /* default reaction for unhandled events */
   void react(const tinyfsm::Event&) { };
   
   virtual void react(const MyToggleEvent&) = 0;
   
   virtual void entry() { };  /* entry actions in some states */
   void         exit()  { };  /* no exit actions */
};
// States
class MyOffState;

class MyOnState : public MySM
{
public:
   MyOnState() = default;
   virtual ~MyOnState() = default;
   void entry() override { std::cout << "* MyState is ON" << std::endl; };
   void react(const MyToggleEvent&) override { transit<MyOffState>(); };
};

class MyOffState : public MySM
{
public:
   MyOffState() = default;
   virtual ~MyOffState() = default;
   void entry() override { std::cout << "* MyState is OFF" << std::endl; };
   void react(const MyToggleEvent&) override { transit<MyOnState>(); };
};
}

FSM_INITIAL_STATE(x::MySM, x::MyOffState);

using namespace qrx::cvwizard::ui;

TEST_CASE("StateMachine", "[ui] [statemachine]")
{
   auto sm = std::make_shared<StateMachine>();
   REQUIRE(sm);
}

TEST_CASE("TinyFSM playground", "[statemachine]")
{
   auto toggle = x::MyToggleEvent{};
   
   x::MySM::start();
   
   for (int i=0; i<7; ++i)
   {
      x::MySM::dispatch(toggle);
   }
}

#pragma GCC diagnostic pop
