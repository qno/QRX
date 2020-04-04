#pragma once

#include <cvwizard/controller/KeyboardEventsProviding.hpp>

#include <thread>

namespace qrx {
namespace cvwizard {
namespace controller {

class CVWizardController
{
public:
   
   CVWizardController();
   virtual ~CVWizardController() noexcept;
   
   void start() noexcept;
   void stop() noexcept;
   
   void setKeyboardEventsProvider(KeyboardEventsProviding* provider);

private:
   
   void run() noexcept;
   
   std::thread _controllerThread;
   
   bool _isMappingModeEnabled = false;
   bool _isStopped            = false;
   KeyboardEventsProviding* _keyboardEventsProvider;
};

}
}
}
