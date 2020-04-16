#pragma once

#include <cvwizard/controller/CVWizardControllable.hpp>

#include <boost/sml.hpp>

#include <exception>
#include <memory>

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

struct OnPortWidgetHovered{};
struct OnParamWidgetHovered{};
struct OnPortWidgetSelected{};
struct OnParamWidgetSelected{};
}

namespace guard {
const auto isTooltipsEnabled = [](const CVWizardControllable& c) { return c.isShowTooltipsEnabled(); };
const auto isCtrlKeyPressed = [](const CVWizardControllable& c) { return c.isControlKeyPressed(); };
const auto isMappingKeyPressed = [](const CVWizardControllable& c) { return c.isMappingKeyPressed(); };
const auto isMappingCancelKeyPressed = [](const CVWizardControllable& c) { return c.isMappingCancelKeyPressed(); };
const auto isTooltipKeyPressed = [](const CVWizardControllable& c) { return c.isTooltipKeyPressed(); };

const auto isModuleWidgetHovered = [](const CVWizardControllable& c) { return c.isModuleWidgetHovered(); };
const auto isNotSameModuleWidgetHovered = [](const CVWizardControllable& c) { return !c.isSameModuleWidgetHovered(); };

const auto isParamWidgetHovered = [](const CVWizardControllable& c) { return c.isParamWidgetHovered(); };
const auto isParamWidgetSelected = [](const CVWizardControllable& c) { return c.isParamWidgetSelected(); };

const auto isInputPortWidgetHovered = [](const CVWizardControllable& c) { return c.isParamWidgetHovered(); };
const auto isInputPortWidgetSelected = [](const CVWizardControllable& c) { return c.isInputPortWidgetSelected(); };
}

namespace action {
const auto showWidgetTooltip   = [](CVWizardControllable& c) { c.showWidgetTooltip(); };
const auto removeWidgetTooltip = [](CVWizardControllable& c) { c.removeWidgetTooltip(); };

const auto showTooltip   = [](CVWizardControllable& c) { c.showTooltip(); };
const auto removeTooltip = [](CVWizardControllable& c) { c.removeTooltip(); };

const auto toogleTooltip = [](CVWizardControllable& c) { c.toogleTooltip(); };

const auto addHoveredModuleWidget = [](CVWizardControllable& c) { c.addHoveredModuleWidget(); };
const auto clearHoveredModuleWidget = [](CVWizardControllable& c) { c.clearHoveredModuleWidget(); };
const auto handleHoveredWidget = [](CVWizardControllable& c) { c.handleHoveredWidget(); };
const auto addSelectedPortWidget = [](CVWizardControllable& c) { c.addSelectedPortWidget(); };
const auto addSelectedParamWidget = [](CVWizardControllable& c) { c.addSelectedParamWidget(); };
}

namespace state {
class Idle;
class CtrlKeyPressed;
class MappingModeActive;
class ModuleHovered;
class InputPortHovered;
class InputPortSelected;
class InputParamSelected;
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
*sml::state<Idle> + sml::event<OnEnter> [isTooltipsEnabled] / showWidgetTooltip = sml::state<Idle>,
 sml::state<Idle> + sml::event<OnLeave> [isTooltipsEnabled] / removeWidgetTooltip = sml::state<Idle>,
 sml::state<Idle> + sml::event<OnKeyPressed> [isCtrlKeyPressed] = sml::state<CtrlKeyPressed>,
 sml::state<CtrlKeyPressed> + sml::event<OnKeyPressed> [isMappingKeyPressed] / showTooltip = sml::state<MappingModeActive>,
 sml::state<MappingModeActive> + sml::event<OnKeyPressed> [isMappingCancelKeyPressed] / removeTooltip = sml::state<Idle>,
 sml::state<MappingModeActive> + sml::event<OnWidgetHovered> [isModuleWidgetHovered] / addHoveredModuleWidget = sml::state<ModuleHovered>,
 sml::state<ModuleHovered> + sml::event<OnWidgetHovered> [isNotSameModuleWidgetHovered] / clearHoveredModuleWidget = sml::state<MappingModeActive>
////sml::state<ModuleHovered> + sml::event<OnWidgetHovered> [isModuleWidgetHovered] / addHoveredModuleWidget = sml::state<ModuleHovered>
// sml::state<ModuleHovered> + sml::event<OnWidgetHovered> [isInputPortWidgetHovered] / handleHoveredWidget = sml::state<InputPortHovered>,
// sml::state<InputPortHovered> + sml::event<OnWidgetSelected> [isInputPortWidgetSelected] / addSelectedPortWidget = sml::state<InputPortSelected>,
// sml::state<InputPortSelected> + sml::event<OnWidgetSelected> [isParamWidgetHovered] / addSelectedParamWidget = sml::state<InputParamSelected>
      );
      // clang-format on
   }
};

}
}
}
