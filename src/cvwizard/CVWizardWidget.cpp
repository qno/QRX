#include <cvwizard/CVWizardWidget.hpp>

using namespace rack;

namespace qrx {
namespace cvwizard {

CVWizardWidget::CVWizardWidget(CVWizardModule* module)
   : ModuleWidget(), _module(module), _appWindow(APP->window)
{
   setModule(_module);
   
   setPanel(_appWindow->loadSvg(asset::plugin(pluginInstance, "res/CVWizard/Module_Rack.svg")));
   
   addChild(createWidget<rack::ScrewBlack>(Vec(RACK_GRID_WIDTH, 0)));
   addChild(createWidget<rack::ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
   addChild(createWidget<rack::ScrewBlack>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
   addChild(createWidget<rack::ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
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

void CVWizardWidget::onEnter(const rack::event::Enter& e)
{
   _tooltip = new rack::ui::Tooltip{};
   _tooltip->text = std::string{"this is a CVWizard main widget tooltip"};
   APP->scene->addChild(_tooltip);
}

void CVWizardWidget::onLeave(const rack::event::Leave& e)
{
   if (_tooltip)
   {
      APP->scene->removeChild(_tooltip);
      delete _tooltip;
      _tooltip = nullptr;
   }
}

void CVWizardWidget::onHover(const rack::event::Hover& e)
{
   rack::ModuleWidget::onHover(e);
   e.consume(this);
}


}
}
