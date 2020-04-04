#include <cvwizard/controller/CVWizardController.hpp>

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
   if (nullptr == _keyboardEventsProvider)
   {
      throw KeyboardEventsProviderNotSetException{};
   }
   
   INFO("start CVWizardController now ...");
   _controllerThread = std::thread{[this] { run(); }};
}

void CVWizardController::stop() noexcept
{
   INFO("stop CVWizardController now ...");
   _isStopped = true;
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
   INFO("CVWizardController thread is running");
   
   while (!_isStopped)
   {
      INFO("took a round now ...");
      std::this_thread::sleep_for(std::chrono::seconds(1));
   }
   
   INFO("exit CVWizardController thread");
}

}
}
}
