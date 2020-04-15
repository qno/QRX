#include <cvwizard/CVWizardWidget.hpp>
#include <cvwizard/ui/HoveredWidget.hpp>
#include <cvwizard/ui/CVIndicatorWidget.hpp>
#include <cvwizard/ui/Tooltip.hpp>

using namespace rack;

#ifndef QRX_UNITTESTS
extern std::shared_ptr<qrx::boundary::RackAppBoundary> rackApp;
#endif

namespace qrx {
namespace cvwizard {

model::CVWizardModel CVWizardWidget::_model;
std::unique_ptr<rack::ui::Tooltip> CVWizardWidget::s_tooltip = nullptr;

CVWizardWidget::CVWizardWidget(CVWizardModule* module)
   : ModuleWidget()
#ifndef QRX_UNITTESTS
   , _app{rackApp}
#endif
   , _module(module)
   , _appWindow(_app->getWindow())
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

void CVWizardWidget::setApp(const std::shared_ptr<boundary::RackAppBoundary>& app)
{
   _app = app;
}

void CVWizardWidget::step()
{
   if (_module && _module->isMasterModule())
   {
      if (!_app->getEventState()->heldKeys.empty())
      {
         _controller->process_event(controller::event::OnKeyPressed{});
      }
      
      if (_app->getEventState()->getHoveredWidget())
      {
         _controller->process_event(controller::event::OnWidgetHovered{});
      }
   
      if (_app->getEventState()->getSelectedWidget())
      {
         _controller->process_event(controller::event::OnWidgetSelected{});
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
      _app->getScene()->removeChild(_widgetTooltip.get());
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
      _app->getScene()->addChild(s_tooltip.get());
   }
}

void CVWizardWidget::removeTooltip()
{
   DEBUG("removeTooltip Widget #0x%0x", this);
   if (_module && _module->isMasterModule())
   {
      if (s_tooltip)
      {
         _app->getScene()->removeChild(s_tooltip.get());
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
   return (RACK_MOD_CTRL  == (_app->getWindow()->getMods() & RACK_MOD_CTRL));
}

bool CVWizardWidget::isMappingKeyPressed() const
{
   return (GLFW_PRESS == glfwGetKey(_app->getWindow()->win, _module->getSettings()->getCVWizardSettings().MappingKey));
}

bool CVWizardWidget::isMappingCancelKeyPressed() const
{
   return (GLFW_PRESS == glfwGetKey(_app->getWindow()->win, _module->getSettings()->getCVWizardSettings().MappingCancelKey));
}

bool CVWizardWidget::isTooltipKeyPressed() const
{
   return (GLFW_PRESS == glfwGetKey(_app->getWindow()->win, _module->getSettings()->getCVWizardSettings().MappingTooltipKey));
}

bool CVWizardWidget::isModuleWidgetHovered () const
{
   return nullptr != getIfIsModuleWidget(_app->getEventState()->getHoveredWidget());
}

bool CVWizardWidget::isModuleWidgetSelected () const
{
   return nullptr != getIfIsModuleWidget(_app->getEventState()->getSelectedWidget());
}

bool CVWizardWidget::isParamWidgetHovered () const
{
   return nullptr != getIfIsParamWidget(_app->getEventState()->getHoveredWidget());
}

bool CVWizardWidget::isParamWidgetSelected () const
{
   return nullptr != getIfIsParamWidget(_app->getEventState()->getSelectedWidget());
}

bool CVWizardWidget::isInputPortWidgetHovered () const
{
   return nullptr != getIfIsInputPortWidget(_app->getEventState()->getHoveredWidget());
}

bool CVWizardWidget::isInputPortWidgetSelected () const
{
   return nullptr != getIfIsInputPortWidget(APP->event->getSelectedWidget());
}

void CVWizardWidget::addSelectedParamWidget()
{
   _model.paramWidget = getIfIsParamWidget(_app->getEventState()->getSelectedWidget());
   DEBUG("addSelectedParamWidget #0x%0x", _model.paramWidget);
   _model.selectedParamWidget = new ui::CVIndicatorWidget{_model.paramWidget, _model.portWidget->module, _model.portWidget->portId};
   _model.paramWidget->addChild(_model.selectedParamWidget);
}

void CVWizardWidget::addSelectedPortWidget()
{
   _model.portWidget = getIfIsInputPortWidget(_app->getEventState()->getSelectedWidget());
   DEBUG("addSelectedPortWidget #0x%0x", _model.portWidget);
}

rack::ModuleWidget* CVWizardWidget::getIfIsModuleWidget(rack::Widget* widget) const
{
   return dynamic_cast<rack::ModuleWidget*>(widget);
}

rack::PortWidget* CVWizardWidget::getIfIsInputPortWidget(rack::Widget* widget) const
{
   rack::PortWidget* result = nullptr;
   if (auto&& p = dynamic_cast<rack::PortWidget*>(widget))
   {
      if (rack::PortWidget::INPUT == p->type)
      {
         result = p;
      }
   }
   return result;
}

rack::ParamWidget* CVWizardWidget::getIfIsParamWidget(rack::Widget* widget) const
{
   rack::ParamWidget* result = nullptr;
   if (auto&& paramWidget = dynamic_cast<rack::ParamWidget*>(widget))
   {
      if (dynamic_cast<rack::Knob*>(paramWidget))
      {
         result = paramWidget;
      }
   }
   return result;
}

void CVWizardWidget::handleHoveredWidget()
{
   auto hovered = _app->getEventState()->getHoveredWidget();
   
   if (_model.hoveredWidget != hovered)
   {
      if (_model.hoveredWidget && _model.onHoverWidget)
      {
         delete _model.onHoverWidget;
         _model.onHoverWidget = nullptr;
      }
      if (auto&& inputPortWidget = getIfIsInputPortWidget(hovered))
      {
         DEBUG("handleHovered input port widget #0x%0x", hovered);
         _model.hoveredWidget = hovered;
         _model.onHoverWidget = new ui::HoveredWidget{inputPortWidget};
         hovered->addChild(_model.onHoverWidget);
      }
      else if (auto&& paramWidget = getIfIsParamWidget(hovered))
      {
         DEBUG("handleHovered param widget #0x%0x", hovered);
         _model.hoveredWidget = hovered;
         _model.onHoverWidget = new ui::HoveredWidget{paramWidget};
         hovered->addChild(_model.onHoverWidget);
      }
      else
      {
         _model.hoveredWidget = nullptr;
      }
   }
}

bool CVWizardWidget::isNotSameModuleWidgetHovered () const
{
   bool result = false;
   const auto hovered = _app->getEventState()->getHoveredWidget();
   
   DEBUG("isNotSameModuleWidgetHovered hovered widget #0x%0x", hovered);
   DEBUG("isNotSameModuleWidgetHovered _model.hoveredModuleWidget widget #0x%0x", _model.hoveredModuleWidget);
   if (_model.hoveredModuleWidget && _model.hoveredModuleWidget != hovered)
   {
//      DEBUG("isNotSameModuleWidgetHovered _model.hoveredModuleWidget != hovered");
//      if (auto&& parent = hovered->parent)
//      {
//         DEBUG("isNotSameModuleWidgetHovered hovered->parent widget #0x%0x", hovered->parent);
//         while (parent && parent != _model.hoveredModuleWidget)
//         {
//            if (parent == _model.hoveredModuleWidget)
//            {
//               DEBUG("parent == _model.hoveredModuleWidget - break");
//               result = true;
//               break;
//            }
//            else
//            {
//               DEBUG("isNotSameModuleWidgetHovered parent->parent widget #0x%0x", parent->parent);
//               parent = parent->parent;
//            }
//         }
//      }
   }
   
   return result;
}


void CVWizardWidget::addHoveredModuleWidget()
{
   auto hovered = _app->getEventState()->getHoveredWidget();
   if (auto&& moduleWidget = getIfIsModuleWidget(hovered))
   {
      DEBUG("addHoveredModuleWidget #0x%0x", hovered);
      _model.hoveredModuleWidget = hovered;
      _model.onHoverModuleWidget = new ui::HoveredWidget{moduleWidget};
      hovered->addChild(_model.onHoverModuleWidget);
   }
}

void CVWizardWidget::clearHoveredModuleWidget()
{
   DEBUG("clearHoveredModuleWidget #0x%0x", _model.hoveredModuleWidget);
   if (_model.hoveredModuleWidget && _model.onHoverModuleWidget)
   {
      delete _model.onHoverModuleWidget;
     _model.onHoverModuleWidget = nullptr;
   }
    _model.hoveredModuleWidget = nullptr;
}

}
}
