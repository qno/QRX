#pragma once

#include <QRXPlugin.hpp>

#include <CVWizard/CVWizardModule.hpp>

namespace qrx {

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
  
   CVWizardWidget(CVWizardModule* module);
  
   virtual ~CVWizardWidget() = default;
  
   void step() override;
  
   void draw(const DrawArgs& args) override;

private:
  
   CVWizardModule* _module;
   GLFWwindow* _glfwWindow;
  
   bool m_mappingModeActive = false;
};

}
