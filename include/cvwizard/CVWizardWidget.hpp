#pragma once

#include <QRXPlugin.hpp>
#include <cvwizard/CVWizardModule.hpp>
#include <cvwizard/controller/CVWizardController.hpp>

namespace qrx {
namespace cvwizard {

class WizScrew : public rack::app::SvgScrew
{
public:
  
   WizScrew()
   {
      setSvg(APP->window->loadSvg(rack::asset::plugin(pluginInstance, "res/CVWizard/Screw.svg")));
   }
};

class CVWizardWidget : public rack::ModuleWidget
{
public:
  
   explicit CVWizardWidget(CVWizardModule* module);
  
   ~CVWizardWidget() override = default;
  
   void step() override;
  
   void draw(const DrawArgs& args) override;

private:
  
   CVWizardModule* _module  = nullptr;
   rack::Window* _appWindow = nullptr;
   GLFWwindow* _glfwWindow  = nullptr;
   
   controller::CVWizardController _controller;
  
   bool m_mappingModeActive = false;
};

}
}
