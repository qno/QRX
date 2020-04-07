#include <cvwizard/CVWizardWidget.hpp>
#include <cvwizard/ui/Tooltip.hpp>
#include <cvwizard/sm/keyboard/Keyboard.hpp>

using namespace rack;

namespace qrx {
namespace cvwizard {

rack::Tooltip* CVWizardWidget::_tooltip = nullptr;

CVWizardWidget::CVWizardWidget(CVWizardModule* module)
   : ModuleWidget(), _module(module), _appWindow(APP->window)
{
   setModule(_module);
   
   setPanel(_appWindow->loadSvg(asset::plugin(pluginInstance, "res/CVWizard/Module_Rack.svg")));
   
   addChild(createWidget<rack::ScrewBlack>(Vec(RACK_GRID_WIDTH, 0)));
   addChild(createWidget<rack::ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
   addChild(createWidget<rack::ScrewBlack>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
   addChild(createWidget<rack::ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
   
   if (_module)
   {
      _connection = sm::keyboard::Keyboard::connect(std::bind(&CVWizardWidget::onMappingModeActive, this));
   }
}

CVWizardWidget::~CVWizardWidget()
{
   if (_connection.connected())
      _connection.disconnect();
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
   _tooltip->text = ui::Tooltip::getStartMappingText(_module->getSettings()->getCVWizardSettings().MappingKey);
   APP->scene->addChild(_tooltip);
}

void CVWizardWidget::onLeave(const rack::event::Leave& e)
{
   if (_tooltip)
   {
      APP->scene->removeChild(_tooltip);
      delete _tooltip;
   }
}

void CVWizardWidget::onHover(const rack::event::Hover& e)
{
   rack::ModuleWidget::onHover(e);
   e.consume(this);
}

void CVWizardWidget::onMappingModeActive()
{
   INFO("onMappingModeActive Widget #%d", this);
}

}
}
