#include <cvwizard/CVWizard.hpp>
#include <cvwizard/ui/HoveredWidget.hpp>
#include <cvwizard/ui/CVIndicatorWidget.hpp>
#include <cvwizard/ui/Tooltip.hpp>
#include <boundary/io/Keys.hpp>

namespace qrx {
namespace cvwizard {

using namespace boundary::rack;

CVWizard::CVWizard(const AppBoundary& appBoundary)
   : controller::CVWizardControllable{}
   , _appBoundary{appBoundary}
{
   DEBUG("CVWizard ctr (#0x%0x)", this);
   controller::CVWizardControllable& c{*this};
   _controller = std::make_unique<sml::sm<controller::CVWizardController>>(c);
}

CVWizard::~CVWizard()
{
   DEBUG("CVWizardWidget dtr (#0x%0x)", this);
}

void CVWizard::addSettings(const std::shared_ptr<ModuleSettings>& settings)
{
   _settings = settings;
}

void CVWizard::process()
{
   if (!_appBoundary.getEventState()->heldKeys.empty())
   {
      _controller->process_event(controller::event::OnKeyPressed{});
   }

   if (_appBoundary.getEventState()->getHoveredWidget())
   {
      _controller->process_event(controller::event::OnWidgetHovered{});
   }

   if (_appBoundary.getEventState()->getSelectedWidget())
   {
      _controller->process_event(controller::event::OnWidgetSelected{});
   }
}

void CVWizard::onEnter()
{
   _controller->process_event(controller::event::OnEnter{});
}

void CVWizard::onLeave()
{
   _controller->process_event(controller::event::OnLeave{});
}

sigslot::connection CVWizard::connectShowWidgetTooltip(std::function<void()> callback)
{
   return _showWidgetTooltip.connect(callback);
}

sigslot::connection CVWizard::connectRemoveWidgetTooltip(std::function<void()> callback)
{
   return _removeWidgetTooltip.connect(callback);
}

sigslot::connection CVWizard::connectShowTooltip(std::function<void()> callback)
{
   return _showTooltip.connect(callback);
}

sigslot::connection CVWizard::connectRemoveTooltip(std::function<void()> callback)
{
   return _removeTooltip.connect(callback);
}

void CVWizard::showWidgetTooltip()
{
   DEBUG("showWidgetTooltip");
   _showWidgetTooltip();
}

void CVWizard::removeWidgetTooltip()
{
   DEBUG("removeWidgetTooltip");
   _removeWidgetTooltip();
}

void CVWizard::showTooltip()
{
   DEBUG("showTooltip");
   _showTooltip();
}

void CVWizard::removeTooltip()
{
   DEBUG("removeTooltip");
   _removeTooltip();
}

bool CVWizard::isShowTooltipsEnabled() const
{
   return _settings->getSettings().ShowMappingTooltips;
}

void CVWizard::toggleTooltip()
{

}

bool CVWizard::isControlKeyPressed() const
{
   return _appBoundary.isModKeyPressed(io::keys::MOD_CTRL);
}

bool CVWizard::isMappingKeyPressed() const
{
   return _appBoundary.isKeyPressed(_settings->getSettings().MappingKey);
}

bool CVWizard::isMappingCancelKeyPressed() const
{
   return _appBoundary.isKeyPressed(_settings->getSettings().MappingCancelKey);
}

bool CVWizard::isTooltipKeyPressed() const
{
   return _appBoundary.isKeyPressed(_settings->getSettings().MappingTooltipKey);
}

bool CVWizard::isModuleWidgetHovered() const
{
   return nullptr != getIfIsModuleWidget(_appBoundary.getEventState()->getHoveredWidget());
}

/*bool CVWizard::isModuleWidgetSelected () const
{
   DEBUG("entered %s", __FUNCTION__);
   return nullptr != getIfIsModuleWidget(_appBoundary.getEventState()->getSelectedWidget());
}*/

/*bool CVWizard::isParamWidgetHovered () const
{
   DEBUG("entered %s", __FUNCTION__);
   return nullptr != getIfIsParamWidget(_appBoundary.getEventState()->getHoveredWidget());
}*/

/*bool CVWizard::isParamWidgetSelected () const
{
   DEBUG("entered %s", __FUNCTION__);
   return nullptr != getIfIsParamWidget(_appBoundary.getEventState()->getSelectedWidget());
}*/

/*bool CVWizard::isInputPortWidgetHovered () const
{
   DEBUG("entered %s", __FUNCTION__);
   return nullptr != getIfIsInputPortWidget(_appBoundary.getEventState()->getHoveredWidget());
}*/

/*bool CVWizard::isInputPortWidgetSelected () const
{
   DEBUG("entered %s", __FUNCTION__);
   return nullptr != getIfIsInputPortWidget(_appBoundary.getEventState()->getSelectedWidget());
}*/

/*void CVWizard::addSelectedParamWidget()
{
   DEBUG("entered %s", __FUNCTION__);
   _model.paramWidget = getIfIsParamWidget(_appBoundary.getEventState()->getSelectedWidget());
   DEBUG("addSelectedParamWidget #0x%0x", _model.paramWidget);
   _model.selectedParamWidget = new ui::CVIndicatorWidget{_model.paramWidget, _model.portWidget->module, _model.portWidget->portId};
   _model.paramWidget->addChild(_model.selectedParamWidget);
}*/

/*void CVWizard::addSelectedPortWidget()
{
   DEBUG("entered %s", __FUNCTION__);
   _model.portWidget = getIfIsInputPortWidget(_appBoundary.getEventState()->getSelectedWidget());
   DEBUG("addSelectedPortWidget #0x%0x", _model.portWidget);
}*/

ModuleWidget* CVWizard::getIfIsModuleWidget(Widget* widget) const
{
   return dynamic_cast<ModuleWidget*>(widget);
}

/*PortWidget* CVWizard::getIfIsInputPortWidget(Widget* widget) const
{
   PortWidget* result = nullptr;
   if (auto&& p = dynamic_cast<PortWidget*>(widget))
   {
      if (PortWidget::INPUT == p->type)
      {
         result = p;
      }
   }
   return result;
}*/

/*ParamWidget* CVWizard::getIfIsParamWidget(Widget* widget) const
{
   ParamWidget* result = nullptr;
   if (auto&& paramWidget = dynamic_cast<ParamWidget*>(widget))
   {
      if (dynamic_cast<Knob*>(paramWidget))
      {
         result = paramWidget;
      }
   }
   return result;
}*/

/*void CVWizard::handleHoveredWidget()
{
   auto hovered = _appBoundary->getEventState()->getHoveredWidget();

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
}*/

bool CVWizard::isSameModuleWidgetHovered() const
{
   bool result = false;
   const auto hovered = _appBoundary.getEventState()->getHoveredWidget();
   
   if (_model.hoveredModuleWidget == hovered)
   {
      result = true;
   }
   else
   {
      if (auto parent = hovered->parent)
      {
         while (parent)
         {
            if (parent == _model.hoveredModuleWidget)
            {
               result = true;
               break;
            }
            else
            {
               parent = parent->parent;
            }
         }
      }
   }
   return result;
}

void CVWizard::addHoveredModuleWidget()
{
   auto hovered = _appBoundary.getEventState()->getHoveredWidget();
   if (auto&& moduleWidget = getIfIsModuleWidget(hovered))
   {
      _model.hoveredModuleWidget = hovered;
      _model.onHoverModuleWidget = std::make_unique<ui::HoveredWidget>(moduleWidget);
      moduleWidget->addChild(_model.onHoverModuleWidget.get());
   }
}

void CVWizard::clearHoveredModuleWidget()
{
   _model.onHoverModuleWidget = nullptr;
   _model.hoveredModuleWidget = nullptr;
}

}
}
