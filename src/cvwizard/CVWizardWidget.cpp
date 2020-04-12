#include <cvwizard/CVWizardWidget.hpp>
#include <cvwizard/ui/OnHoverWidget.hpp>
#include <cvwizard/ui/Tooltip.hpp>

using namespace rack;

namespace qrx {
namespace cvwizard {

model::CVWizardModel CVWizardWidget::_model;
std::unique_ptr<rack::ui::Tooltip> CVWizardWidget::s_tooltip = nullptr;

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
   
   controller::CVWizardControllable& c{*this};
   _controller = std::make_unique<sml::sm<controller::CVWizardController>>(c);
}

CVWizardWidget::~CVWizardWidget()
{
   DEBUG("CVWizardWidget dtr (#0x%0x)", this);
   removeWidgetTooltip();
   removeTooltip();
}

void CVWizardWidget::step()
{
   if (_module && _module->isMasterModule())
   {
      if (!APP->event->heldKeys.empty())
      {
         _controller->process_event(controller::event::OnKeyPressed{});
      }
      
      if (APP->event->getHoveredWidget())
      {
         _controller->process_event(controller::event::OnWidgetHovered{});
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
   _controller->process_event(controller::event::OnEnter{});
}

void CVWizardWidget::onLeave(const rack::event::Leave& e)
{
   DEBUG("onLeave Widget #0x%0x", this);
   _controller->process_event(controller::event::OnLeave{});
}

void CVWizardWidget::onHover(const rack::event::Hover& e)
{
   rack::ModuleWidget::onHover(e);
   e.consume(this);
}

void CVWizardWidget::showWidgetTooltip()
{
   DEBUG("showWidgetTooltip Widget #0x%0x", this);
   _widgetTooltip = std::make_unique<rack::ui::Tooltip>();
   _widgetTooltip->text = ui::Tooltip::getStartMappingText(_module->getSettings()->getCVWizardSettings().MappingKey);
   APP->scene->addChild(_widgetTooltip.get());
}

void CVWizardWidget::removeWidgetTooltip()
{
   DEBUG("removeWidgetTooltip Widget #0x%0x", this);
   if (_widgetTooltip)
   {
      APP->scene->removeChild(_widgetTooltip.get());
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
      APP->scene->addChild(s_tooltip.get());
   }
}

void CVWizardWidget::removeTooltip()
{
   DEBUG("removeTooltip Widget #0x%0x", this);
   if (_module && _module->isMasterModule())
   {
      if (s_tooltip)
      {
         APP->scene->removeChild(s_tooltip.get());
         s_tooltip = nullptr;
      }
   }
}

bool CVWizardWidget::isShowTooltipsEnabled() const
{
   return _module->getSettings()->getCVWizardSettings().ShowMappingTooltips;
}

void CVWizardWidget::toogleTooltip()
{
   DEBUG("toogleTooltip Widget #0x%0x", this);
}

bool CVWizardWidget::isControlKeyPressed() const
{
   return (RACK_MOD_CTRL  == (APP->window->getMods() & RACK_MOD_CTRL));
}

bool CVWizardWidget::isMappingKeyPressed() const
{
   return (GLFW_PRESS == glfwGetKey(APP->window->win, _module->getSettings()->getCVWizardSettings().MappingKey));
}

bool CVWizardWidget::isMappingCancelKeyPressed() const
{
   return (GLFW_PRESS == glfwGetKey(APP->window->win, _module->getSettings()->getCVWizardSettings().MappingCancelKey));
}

bool CVWizardWidget::isTooltipKeyPressed() const
{
   return (GLFW_PRESS == glfwGetKey(APP->window->win, _module->getSettings()->getCVWizardSettings().MappingTooltipKey));
}

void CVWizardWidget::handleHoveredWidget()
{
   auto hovered = APP->event->getHoveredWidget();
   
   if (_model.hoveredWidget != hovered)
   {
      if (_model.hoveredWidget && _model.onHoverWidget)
      {
         _model.hoveredWidget->removeChild(_model.onHoverWidget);
         delete _model.onHoverWidget;
         _model.onHoverWidget = nullptr;
      }
      if (auto&& p = dynamic_cast<rack::PortWidget*>(hovered))
      {
         if (rack::PortWidget::INPUT == p->type)
         {
            DEBUG("handleHoveredWidget Widget #0x%0x", hovered);
            _model.hoveredWidget = hovered;
            _model.onHoverWidget = new ui::OnHoverWidget{p};
            hovered->addChild(_model.onHoverWidget);
         }
      }
   }
}

}
}
