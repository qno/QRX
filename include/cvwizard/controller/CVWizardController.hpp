#pragma once

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

private:
   
   void run() noexcept;
   
   std::thread _controllerThread;
   
   bool _isMappingModeEnabled = false;
   bool _isStopped            = false;
};

}
}
}
