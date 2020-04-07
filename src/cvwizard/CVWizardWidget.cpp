#include <cvwizard/CVWizardWidget.hpp>
#include <cvwizard/ui/Tooltip.hpp>
#include <cvwizard/sm/keyboard/Keyboard.hpp>

using namespace rack;

namespace qrx {
namespace cvwizard {

rack::Tooltip* CVWizardWidget::_tooltip = nullptr;
rack::Tooltip* CVWizardWidget::_modeTooltip = nullptr;

CVWizardWidget::CVWizardWidget(CVWizardModule* module)
   : ModuleWidget(), _module(module), _appWindow(APP->window)
{
   DEBUG("CVWizardWidget ctr (#0x%0x)", this);
   setModule(_module);
   
   setPanel(_appWindow->loadSvg(asset::plugin(pluginInstance, "res/CVWizard/Module_Rack.svg")));
   
   addChild(createWidget<rack::ScrewBlack>(Vec(RACK_GRID_WIDTH, 0)));
   addChild(createWidget<rack::ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
   addChild(createWidget<rack::ScrewBlack>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
   addChild(createWidget<rack::ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
   
   if (_module)
   {
      _mappingActiveConnection = sm::keyboard::Keyboard::connectActive(std::bind(&CVWizardWidget::onMappingModeActive, this));
      _idleConnection = sm::keyboard::Keyboard::connectIdle(std::bind(&CVWizardWidget::onIdle, this));
      onIdle();
   }
}

CVWizardWidget::~CVWizardWidget()
{
   DEBUG("CVWizardWidget dtr (#0x%0x)", this);
   if (_mappingActiveConnection.connected())
   {
      _mappingActiveConnection.disconnect();
   }
   
   if (_idleConnection.connected())
   {
      _idleConnection.disconnect();
   }
   
   if (_module)
   {
      onIdle();
   }
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
   DEBUG("onEnter Widget #0x%0x", this);
   _tooltip = new rack::ui::Tooltip{};
   _tooltip->text = ui::Tooltip::getStartMappingText(_module->getSettings()->getCVWizardSettings().MappingKey);
   APP->scene->addChild(_tooltip);
}

void CVWizardWidget::onLeave(const rack::event::Leave& e)
{
   DEBUG("onLeave Widget #0x%0x", this);
   if (_tooltip)
   {
      APP->scene->removeChild(_tooltip);
      delete _tooltip;
      _tooltip = nullptr;
   }
}

void CVWizardWidget::onHover(const rack::event::Hover& e)
{
   DEBUG("onHover Widget #0x%0x", this);
   rack::ModuleWidget::onHover(e);
   e.consume(this);
}

void CVWizardWidget::onMappingModeActive()
{
   DEBUG("onMappingModeActive Widget #0x%0x", this);
   if (_module->isMasterModule())
   {
      _modeTooltip = new rack::ui::Tooltip{};
      _modeTooltip->text = "Mapping mode is active (Press 'Esc' to cancel).\nClick now on a module input!";
      APP->scene->addChild(_modeTooltip);
   }
}

void CVWizardWidget::onIdle()
{
   DEBUG("onIdle Widget #0x%0x", this);
   if (_module->isMasterModule())
   {
      if (_modeTooltip)
      {
         APP->scene->removeChild(_modeTooltip);
         delete _modeTooltip;
         _modeTooltip = nullptr;
      }
   }
}

}
}
