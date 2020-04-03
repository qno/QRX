#pragma once

namespace qrx {
namespace cvwizard {

class CVWizardController
{
public:
   
   CVWizardController() = default;
   virtual ~CVWizardController() noexcept = default;
   
   void process();
   
private:
   bool _isMappingModeEnabled = false;
};

}
}
