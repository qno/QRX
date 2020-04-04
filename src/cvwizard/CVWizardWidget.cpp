#include <cvwizard/CVWizardWidget.hpp>

using namespace rack;

namespace qrx {
namespace cvwizard {

CVWizardWidget::CVWizardWidget(CVWizardModule* module)
   : ModuleWidget(), _module(module), _appWindow(APP->window)
{
   setModule(_module);
   
   setPanel(_appWindow->loadSvg(asset::plugin(pluginInstance, "res/CVWizard/Module_Rack.svg")));
   
   addChild(createWidget<WizScrew>(Vec(RACK_GRID_WIDTH, 0)));
   addChild(createWidget<WizScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
   addChild(createWidget<WizScrew>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
   addChild(createWidget<WizScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
}

void CVWizardWidget::step()
{
   if (_module && _module->isMasterModule())
   {
      if (!APP->event->heldKeys.empty())
      {
         _module->handleKeyboardInput();
      }
   }
   ModuleWidget::step();
}

void CVWizardWidget::draw(const DrawArgs& args)
{
   ModuleWidget::draw(args);
}

}
}
