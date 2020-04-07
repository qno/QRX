#pragma once

#include <cvwizard/sm/keyboard/KeyboardEvents.hpp>
#include <tinyfsm.hpp>
#include <sigslot/signal.hpp>

#include <logger.hpp>

#include <functional>

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
   
   static sigslot::connection connectActive(std::function<void()> callback)
   {
      return _mappingActiveSignal.connect(callback);
   }
   
   static sigslot::connection connectIdle(std::function<void()> callback)
   {
      return _idleSignal.connect(callback);
   }
   
protected:
   static sigslot::signal<> _mappingActiveSignal;
   static sigslot::signal<> _idleSignal;
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
   void entry() override { DEBUG("* idle state"); _idleSignal(); };
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
   void react(const ControlKeyPressedEvent& e) override { transit<ControlKeyPressed>(); };
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
   void entry() override { DEBUG("* MappingModeActive"); _mappingActiveSignal(); };
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

