#include <cvwizard/controller/CVWizardController.hpp>
#include <cvwizard/sm/keyboard/Keyboard.hpp>

#include <logger.hpp>

namespace qrx {
namespace cvwizard {
namespace controller {

CVWizardController::CVWizardController()
: _keyboardEventsProvider(nullptr)
{

}

CVWizardController::~CVWizardController() noexcept
{
   if(!_isStopped)
   {
      stop();
   }
}

CVWizardController& CVWizardController::instance()
{
   static CVWizardController instance;
   return instance;
}

void CVWizardController::start()
{
   DEBUG("start CVWizardController");
   if (nullptr == _keyboardEventsProvider)
   {
      throw KeyboardEventsProviderNotSetException{};
   }
   sm::keyboard::Keyboard::start();
   _isStopped = false;
   _controllerThread = std::thread{[this] { run(); }};
}

void CVWizardController::stop() noexcept
{
   DEBUG("stop CVWizardController");
   _isStopped = true;
   sm::keyboard::Keyboard::reset();
   if (_controllerThread.joinable())
   {
      _controllerThread.join();
   }
}

void CVWizardController::setKeyboardEventsProvider(KeyboardEventsProviding* provider)
{
   _keyboardEventsProvider = provider;
}

void CVWizardController::run() noexcept
{
   DEBUG("enter CVWizardController thread #%d", std::this_thread::get_id());
   
   while (!_isStopped)
   {
      INFO("took a round now ...");
      std::this_thread::sleep_for(std::chrono::seconds(1));
   }
   
   DEBUG("exit CVWizardController thread #%d", std::this_thread::get_id());
}

void CVWizardController::handleKeyboardInput()
{
   if (_keyboardEventsProvider)
   {
      if (_keyboardEventsProvider->isControlKeyPressed())
      {
         sm::keyboard::Keyboard::dispatch(sm::keyboard::ControlKeyPressedEvent{});
      }
      else
      {
         sm::keyboard::Keyboard::dispatch(sm::keyboard::ControlKeyReleasedEvent{});
      }
   
      if (_keyboardEventsProvider->isMappingKeyPressed())
      {
         sm::keyboard::Keyboard::dispatch(sm::keyboard::MappingKeyEvent{});
      }
   
      if (_keyboardEventsProvider->isMappingCancelKeyPressed())
      {
         sm::keyboard::Keyboard::dispatch(sm::keyboard::MappingCancelKeyEvent{});
      }
   }
   else
   {
      FATAL("KeyboardEventsProvider is nullptr");
   }
}

}
}
}
