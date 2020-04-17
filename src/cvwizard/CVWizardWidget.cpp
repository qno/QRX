#include <cvwizard/CVWizardWidget.hpp>
#include <cvwizard/ui/Tooltip.hpp>
#include <QRXPlugin.hpp>

#include <rack.hpp>

namespace qrx {
namespace cvwizard {

std::unique_ptr<boundary::rack::ui::Tooltip> CVWizardWidget::s_tooltip = nullptr;

using namespace boundary::rack;

CVWizardWidget::CVWizardWidget(CVWizardModule* module)
   : ModuleWidget{}
   , AppBoundary{}
   , _cvWizard{*this}
   , _module{module}
{
   using namespace ::rack;
   
   DEBUG("CVWizardWidget ctr (#0x%0x)", this);
   
   setModule(_module);
   _cvWizard.addSettings(_module->getSettings());
   
   setPanel(::rack::appGet()->window->loadSvg(::rack::asset::plugin(pluginInstance, "res/CVWizard/Module_Rack.svg")));

   addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, 0)));
   addChild(createWidget<ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
   addChild(createWidget<ScrewBlack>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
   addChild(createWidget<ScrewBlack>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
}

CVWizardWidget::~CVWizardWidget()
{
   DEBUG("CVWizardWidget dtr (#0x%0x)", this);
   removeWidgetTooltip();
   removeTooltip();
}

State* CVWizardWidget::getEventState() const
{
   return ::rack::appGet()->event;
}

Scene* CVWizardWidget::getScene() const
{
   return ::rack::appGet()->scene;
}

Window* CVWizardWidget::getWindow() const
{
   return ::rack::appGet()->window;
}

void CVWizardWidget::step()
{
   if (_module && _module->isMasterModule())
   {
       _cvWizard.process();
   }
   ModuleWidget::step();
}

void CVWizardWidget::draw(const widget::DrawArgs& args)
{
   ModuleWidget::draw(args);
}

void CVWizardWidget::onEnter(const event::Enter& e)
{
   _cvWizard.onEnter();
}

void CVWizardWidget::onLeave(const event::Leave& e)
{
   _cvWizard.onLeave();
}

void CVWizardWidget::onHover(const event::Hover& e)
{
   rack::ModuleWidget::onHover(e);
   e.consume(this);
}

void CVWizardWidget::showWidgetTooltip()
{
   DEBUG("showWidgetTooltip Widget #0x%0x", this);
   _widgetTooltip = std::make_unique<rack::ui::Tooltip>();
   _widgetTooltip->text = ui::Tooltip::getStartMappingText(_module->getSettings()->getSettings().MappingKey);
   ::rack::appGet()->scene->addChild(_widgetTooltip.get());
}

void CVWizardWidget::removeWidgetTooltip()
{
   DEBUG("removeWidgetTooltip Widget #0x%0x", this);
   if (_widgetTooltip)
   {
      ::rack::appGet()->scene->removeChild(_widgetTooltip.get());
      _widgetTooltip = nullptr;
   }
}

void CVWizardWidget::showTooltip()
{
   DEBUG("showTooltip Widget #0x%0x", this);
   if (_module && _module->isMasterModule())
   {
      removeWidgetTooltip();
      s_tooltip = std::make_unique<rack::ui::Tooltip>();
      s_tooltip->text = "Mapping mode is active (Press 'Esc' to cancel).\nClick now on a module input!";
      ::rack::appGet()->scene->addChild(s_tooltip.get());
   }
}

void CVWizardWidget::removeTooltip()
{
   DEBUG("removeTooltip Widget #0x%0x", this);
   if (_module && _module->isMasterModule())
   {
      if (s_tooltip)
      {
         ::rack::appGet()->scene->removeChild(s_tooltip.get());
         s_tooltip = nullptr;
      }
   }
}

bool CVWizardWidget::isShowTooltipsEnabled() const
{
   return _module->getSettings()->getSettings().ShowMappingTooltips;
}

}
}
