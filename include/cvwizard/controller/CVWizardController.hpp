#pragma once

#include <cvwizard/controller/CVWizardControllable.hpp>

#include <boost/sml.hpp>

namespace sml = boost::sml;

namespace qrx {
namespace cvwizard {
namespace controller {

namespace event {
struct OnEnter{};
struct OnLeave{};
struct OnKeyPressed{};
struct OnWidgetHovered{};
struct OnWidgetSelected{};
}

namespace guard {
const auto isShowTooltipsEnabled = [](const CVWizardControllable& c) { return c.isShowTooltipsEnabled(); };
const auto isCtrlKeyPressed      = [](const CVWizardControllable& c) { return c.isControlKeyPressed(); };
const auto isMappingKeyPressed = [](const CVWizardControllable& c) { return c.isMappingKeyPressed(); };
const auto isMappingCancelKeyPressed = [](const CVWizardControllable& c) { return c.isMappingCancelKeyPressed(); };
const auto isTooltipKeyPressed = [](const CVWizardControllable& c) { return c.isTooltipKeyPressed(); };
const auto isModuleWidgetHovered = [](const CVWizardControllable& c) { return c.isModuleWidgetHovered(); };
const auto isNotSameModuleWidgetHovered = [](const CVWizardControllable& c) { return !c.isSameModuleWidgetHovered(); };
const auto isNotModuleWidgetHovered = [](const CVWizardControllable& c) { return !c.isModuleWidgetHovered(); };
const auto isSelectedWidgetValid  = [](const CVWizardControllable& c) { return !c.isModuleWidgetHovered() && c.isSelectedHovered(); };
}

namespace action {
const auto showWidgetTooltip   = [](CVWizardControllable& c) { c.showWidgetTooltip(); };
const auto removeWidgetTooltip = [](CVWizardControllable& c) { c.removeWidgetTooltip(); };
const auto showTooltip   = [](CVWizardControllable& c) { c.showTooltip(); };
const auto removeTooltip = [](CVWizardControllable& c) { c.removeTooltip(); };
const auto toggleTooltip = [](CVWizardControllable& c) { c.toggleTooltip(); };
const auto beginModuleMapping = [](CVWizardControllable& c) { c.beginModuleMapping(); };
const auto endModuleMapping = [](CVWizardControllable& c) { c.endModuleMapping(); };
const auto sendOnEnterWidget = [](CVWizardControllable& c) { c.sendOnEnterModuleChildWidget(); };
const auto sendOnLeaveWidget = [](CVWizardControllable& c) { c.sendOnLeaveModuleChildWidget(); };
const auto sendSelectedWidget = [](CVWizardControllable& c) { c.sendSelectedWidget(); };
}

namespace state {
class Idle;
class CtrlKeyPressed;
class MappingModeActive;
class ModuleHovered;
class ModuleChildHovered;
class ModuleChildSelected;
}

class CVWizardController
{
public:
   auto operator()() const
   {
      using namespace event;
      using namespace state;
      using namespace guard;
      using namespace action;
      // clang-format off
      return sml::make_transition_table(
*sml::state<Idle> + sml::event<OnEnter> [isShowTooltipsEnabled] / showWidgetTooltip = sml::state<Idle>,
 sml::state<Idle> + sml::event<OnLeave> [isShowTooltipsEnabled] / removeWidgetTooltip = sml::state<Idle>,
 sml::state<Idle> + sml::event<OnKeyPressed> [isCtrlKeyPressed] = sml::state<CtrlKeyPressed>,
 sml::state<CtrlKeyPressed> + sml::event<OnKeyPressed> [isMappingKeyPressed] / showTooltip = sml::state<MappingModeActive>,
 sml::state<MappingModeActive> + sml::event<OnKeyPressed> [isMappingCancelKeyPressed] / removeTooltip = sml::state<Idle>,
 sml::state<MappingModeActive> + sml::event<OnWidgetHovered> [isModuleWidgetHovered] / beginModuleMapping = sml::state<ModuleHovered>,
 sml::state<ModuleHovered> + sml::event<OnWidgetHovered> [isNotSameModuleWidgetHovered] / endModuleMapping = sml::state<MappingModeActive>,
 sml::state<ModuleHovered> + sml::event<OnWidgetHovered> [isNotModuleWidgetHovered] / sendOnEnterWidget = sml::state<ModuleChildHovered>,
 sml::state<ModuleChildHovered> + sml::event<OnWidgetHovered> [isModuleWidgetHovered] / sendOnLeaveWidget = sml::state<ModuleHovered>,
 sml::state<ModuleChildHovered> + sml::event<OnWidgetSelected> [isSelectedWidgetValid] / sendSelectedWidget = sml::state<ModuleChildSelected>,
 sml::state<ModuleChildSelected> + sml::event<OnWidgetHovered> [isModuleWidgetHovered] / sendOnLeaveWidget = sml::state<ModuleHovered>
      );
      // clang-format on
   }
};

}
}
}
