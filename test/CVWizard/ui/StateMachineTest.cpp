#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-override"
#pragma GCC diagnostic ignored "-Wcast-function-type"

#include <tinyfsm.hpp>

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
   ~MyOnState() override = default;
   void entry() override { std::cout << "* MyState is ON" << std::endl; };
   void react(const MyToggleEvent&) override { transit<MyOffState>(); };
};

class MyOffState : public MySM
{
public:
   MyOffState() = default;
   ~MyOffState() override = default;
   void entry() override { std::cout << "* MyState is OFF" << std::endl; };
   void react(const MyToggleEvent&) override { transit<MyOnState>(); };
};
}

FSM_INITIAL_STATE(x::MySM, x::MyOffState);

TEST_CASE("TinyFSM playground", "[statemachine]")
{
   auto toggle = x::MyToggleEvent{};
   
   x::MySM::start();
   
   for (int i=0; i<7; ++i)
   {
      x::MySM::dispatch(toggle);
   }
}

namespace qrx
{
// Events
class KeyboardEvent : public tinyfsm::Event
{
public:

};

// Statemachine
class SM : public tinyfsm::Fsm<SM>
{
public:
   
   SM() = default;
   virtual ~SM() = default;
   
   /* default reaction for unhandled events */
   void react(const tinyfsm::Event&) { };
   
   virtual void react(const KeyboardEvent& e) = 0;
   
   virtual void entry() { };  /* entry actions in some states */
   void         exit()  { };  /* no exit actions */
};
// States
class MappingModeInactive;

class MappingModeActive : public SM
{
public:
   MappingModeActive() = default;
   ~MappingModeActive() override = default;
   void entry() override { std::cout << "* MappingMode is active " << std::endl; };
   void react(const KeyboardEvent& e) override { transit<MappingModeInactive>(); };
};

class MappingModeInactive : public SM
{
public:
   MappingModeInactive() = default;
   ~MappingModeInactive() override = default;
   void entry() override { std::cout << "* MappingMode is inactive" << std::endl; };
   void react(const KeyboardEvent& e) override { transit<MappingModeActive>(); };
};
}

FSM_INITIAL_STATE(qrx::SM, qrx::MappingModeInactive);

TEST_CASE("more advanced state machine example", "[statemachine]")
{
   auto event = qrx::KeyboardEvent{};
   
   qrx::SM::start();
   
   for (int i=0; i<7; ++i)
   {
      qrx::SM::dispatch(event);
   }
}


#pragma GCC diagnostic pop
