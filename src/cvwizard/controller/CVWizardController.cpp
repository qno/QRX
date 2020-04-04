#include <cvwizard/controller/CVWizardController.hpp>

#include <logger.hpp>

namespace qrx {
namespace cvwizard {
namespace controller {

CVWizardController::CVWizardController()
{

}

CVWizardController::~CVWizardController() noexcept
{
   stop();
}

void CVWizardController::start() noexcept
{
   INFO("start CVWizardController now ...");
   _controllerThread = std::thread{[this] { run(); }};
}

void CVWizardController::stop() noexcept
{
   INFO("stop CVWizardController now ...");
   _isStopped = true;
   _controllerThread.join();
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
      std::this_thread::sleep_for(std::chrono::seconds(5));
   }
   
   INFO("exit CVWizardController thread");
}

}
}
}
