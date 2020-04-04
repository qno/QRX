#pragma once

#include <cvwizard/sm/keyboard/KeyboardEvents.hpp>
#include <tinyfsm.hpp>

#include <logger.hpp>

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
   virtual void react(const ControlKeyPressedEvent& e) { };
   virtual void react(const ControlKeyReleasedEvent& e) { };
   virtual void react(const MappingKeyEvent& e) { };
   virtual void react(const MappingCancelKeyEvent& e) { };
   
   virtual void entry() { };  /* entry actions in some states */
   void         exit()  { };  /* no exit actions */
   
};

class ControlKeyPressed;
class ControlKeyReleased;
class MappingModeActive;
class MappingCanceled;

class Idle : public Keyboard
{
public:
   Idle() = default;
   ~Idle() override = default;
   void entry() override { DEBUG("* idle state"); };
   void react(const ControlKeyPressedEvent& e) override { transit<ControlKeyPressed>(); };
};

class ControlKeyPressed : public Keyboard
{
public:
   ControlKeyPressed() = default;
   ~ControlKeyPressed() override = default;
   void entry() override { DEBUG("* ControlKey pressed"); };
   void react(const MappingKeyEvent& e) override { transit<MappingModeActive>(); };
   void react(const ControlKeyReleasedEvent& e) override { transit<Idle>(); };
};

class ControlKeyReleased : public Keyboard
{
public:
   ControlKeyReleased() = default;
   ~ControlKeyReleased() override = default;
   void entry() override { DEBUG("* ControlKey released"); };
   void react(const ControlKeyReleasedEvent& e) override { transit<Idle>(); };
};

class MappingModeActive : public Keyboard
{
public:
   MappingModeActive() = default;
   ~MappingModeActive() override = default;
   void entry() override { DEBUG("* MappingModeActive"); };
   void react(const MappingCancelKeyEvent& e) override { transit<Idle>(); };
};

class MappingCanceled : public Keyboard
{
public:
   MappingCanceled() = default;
   ~MappingCanceled() override = default;
   void entry() override { DEBUG("* MappingCanceled"); };
   void react(const MappingCancelKeyEvent& e) override { transit<Idle>(); };
};
}
}
}
}

using namespace qrx::cvwizard::sm::keyboard;
FSM_INITIAL_STATE(Keyboard, Idle);
