#pragma once

#include <cvwizard/controller/KeyboardEventsProviding.hpp>

#include <exception>
#include <thread>

namespace qrx {
namespace cvwizard {
namespace controller {

class CVWizardController
{
public:
   
   class KeyboardEventsProviderNotSetException : public std::exception
   {
   public:
      KeyboardEventsProviderNotSetException()
         : std::exception() { }
      const char* what() const noexcept override
      {
         return "KeyboardEventsProvider is not set";
      }
   };
   
   static CVWizardController& instance();
   
   virtual ~CVWizardController() noexcept;
   
   void start();
   void stop() noexcept;
   
   void setKeyboardEventsProvider(KeyboardEventsProviding* provider);

private:
   
   CVWizardController();
   
   void run() noexcept;
   
   std::thread _controllerThread;
   
   bool _isMappingModeEnabled = false;
   bool _isStopped            = false;
   KeyboardEventsProviding* _keyboardEventsProvider;
};

}
}
}
