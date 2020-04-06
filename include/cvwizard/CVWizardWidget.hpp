#pragma once

#include <QRXPlugin.hpp>
#include <cvwizard/CVWizardModule.hpp>

namespace qrx {
namespace cvwizard {


class CVWizardWidget : public rack::ModuleWidget
{
public:
  
   explicit CVWizardWidget(CVWizardModule* module);
  
   ~CVWizardWidget() override = default;
  
   void step() override;
  
   void draw(const DrawArgs& args) override;
   
   void onEnter(const rack::event::Enter& e) override;
   void onLeave(const rack::event::Leave& e) override;
   void onHover(const rack::event::Hover& e) override;

private:
   
   CVWizardModule* _module  = nullptr;
   rack::Window* _appWindow = nullptr;
   
   static rack::Tooltip* _tooltip;
};

}
}
