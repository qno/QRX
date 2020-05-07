#include <cvwizard/CVWizard.hpp>
#include <cvwizard/utility/Widget.hpp>
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
   return nullptr != utility::Widget::getIfIsModuleWidget(_appBoundary.getEventState()->getHoveredWidget());
}

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
   if (auto moduleWidget = utility::Widget::getIfIsModuleWidget(_appBoundary.getEventState()->getHoveredWidget()))
   {
      _model.beginModuleMapping(moduleWidget);
   }
}

void CVWizard::endModuleMapping()
{
   _model.endModuleMapping();
}

void CVWizard::sendOnEnterModuleChildWidget() const
{
   _model.getCurrentModuleMapping()->onEnterWidget(_appBoundary.getEventState()->getHoveredWidget());
}
void CVWizard::sendOnLeaveModuleChildWidget() const
{
   _model.getCurrentModuleMapping()->onLeaveWidget();
}

}
}
