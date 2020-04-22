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

sigslot::connection CVWizard::connectTooltipsCallback(std::function<void(const TooltipCallbackKind)> callback)
{
   return _tooltipsCallback.connect(callback);
}

void CVWizard::showWidgetTooltip()
{
   DEBUG("showWidgetTooltip");
   _tooltipsCallback(TooltipCallbackKind::ShowWidgetTooltip);
}

void CVWizard::removeWidgetTooltip()
{
   DEBUG("removeWidgetTooltip");
   _tooltipsCallback(TooltipCallbackKind::RemoveWidgetTooltip);
}

void CVWizard::showTooltip()
{
   DEBUG("showTooltip");
   _tooltipsCallback(TooltipCallbackKind::ShowTooltip);
}

void CVWizard::removeTooltip()
{
   DEBUG("removeTooltip");
   _tooltipsCallback(TooltipCallbackKind::RemoveTooltip);
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
   const auto currentHovered = _model.getCurrentModuleMapping()->getModuleWidget();
   
   if (currentHovered == hovered)
   {
      result = true;
   }
   else
   {
      if (auto parent = hovered->parent)
      {
         while (parent)
         {
            if (parent == currentHovered)
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

void CVWizard::beginModuleMapping()
{
   if (auto moduleWidget = getIfIsModuleWidget(_appBoundary.getEventState()->getHoveredWidget()))
   {
      _model.beginModuleMapping(moduleWidget);
   }
}

void CVWizard::endModuleMapping()
{
   _model.endModuleMapping();
}

void CVWizard::sendHoveredWidget()
{
   _model.getCurrentModuleMapping()->sendHoveredWidget(_appBoundary.getEventState()->getHoveredWidget());
}

}
}
