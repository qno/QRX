#pragma once

#include <cvwizard/sm/keyboard/KeyboardEvents.hpp>
#include <tinyfsm.hpp>

#include <iostream>

namespace qrx {
namespace cvwizard {
namespace sm {
namespace keyboard {

class Keyboard : public tinyfsm::Fsm<Keyboard>
{
public:
   Keyboard() = default;
   virtual ~Keyboard() noexcept = default;
   
   void react(const tinyfsm::Event&) { };
   virtual void react(const ControlKeyEvent& e) = 0;
   
   virtual void entry() { };  /* entry actions in some states */
   void         exit()  { };  /* no exit actions */
   
};

class ControlKeyPressed : public Keyboard
{
public:
   ControlKeyPressed() = default;
   ~ControlKeyPressed() override = default;
   void entry() override { std::cout << "* ControlKey pressed" << std::endl; };
   void react(const ControlKeyEvent& e) override { };// { transit<MappingModeActive>(); };
};

}
}
}
}

using namespace qrx::cvwizard::sm::keyboard;
FSM_INITIAL_STATE(Keyboard, ControlKeyPressed);
