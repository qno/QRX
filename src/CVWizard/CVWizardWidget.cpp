#include <CVWizard/CVWizardWidget.hpp>

using namespace rack;

namespace qrx {

CVWizardWidget::CVWizardWidget(CVWizardModule *module)
   : ModuleWidget()
   , m_module(module)
{
  setModule(module);
  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CVWizard/Module_Rack.svg")));
   
   _glfwWindow = APP->window->win;

  addChild(createWidget<WizScrew>(Vec(RACK_GRID_WIDTH, 0)));
  addChild(createWidget<WizScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
  addChild(createWidget<WizScrew>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
  addChild(createWidget<WizScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
}

void CVWizardWidget::step()
{
  if (!m_mappingModeActive) {
    if (GLFW_MOD_CONTROL == (APP->window->getMods() & GLFW_MOD_CONTROL)) {

      const auto x = glfwGetKey(_glfwWindow, GLFW_KEY_M);

      if (GLFW_PRESS == x) {
        INFO("key CTRL-M pressed");
        m_mappingModeActive = true;
      }
    }
  }
  else {
    INFO("Mapping mode is active");
    const auto e = glfwGetKey(_glfwWindow, GLFW_KEY_ESCAPE);

    if (GLFW_PRESS == e) {
      m_mappingModeActive = false;
      INFO("Mapping mode is deactived");
    }
  }

  ModuleWidget::step();
}

void CVWizardWidget::draw(const DrawArgs &args)
{
  ModuleWidget::draw(args);
}

}
