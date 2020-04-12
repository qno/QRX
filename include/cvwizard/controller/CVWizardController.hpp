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
}

namespace guard {
const auto isTooltipsEnabled = [](const CVWizardControllable& c) { return c.isShowTooltipsEnabled(); };
const auto isCtrlKeyPressed  = [](const CVWizardControllable& c) { return c.isControlKeyPressed(); };
const auto isMappingKeyPressed  = [](const CVWizardControllable& c) { return c.isMappingKeyPressed(); };
const auto isMappingCancelKeyPressed  = [](const CVWizardControllable& c) { return c.isMappingCancelKeyPressed(); };
const auto isTooltipKeyPressed  = [](const CVWizardControllable& c) { return c.isTooltipKeyPressed(); };
}

namespace action {
const auto showWidgetTooltip   = [](CVWizardControllable& c) { c.showWidgetTooltip(); };
const auto removeWidgetTooltip = [](CVWizardControllable& c) { c.removeWidgetTooltip(); };

const auto showTooltip   = [](CVWizardControllable& c) { c.showTooltip(); };
const auto removeTooltip = [](CVWizardControllable& c) { c.removeTooltip(); };

const auto toogleTooltip = [](CVWizardControllable& c) { c.toogleTooltip(); };

const auto handleHoveredWidget = [](CVWizardControllable& c) { c.handleHoveredWidget(); };
}

namespace state {
class Idle;
class CtrlKeyPressed;
class MappingModeActive;
}

class CVWizardController
{
public:
   auto operator()() const
   {
      // clang-format off
      return sml::make_transition_table(
*sml::state<state::Idle> + sml::event<event::OnEnter> [guard::isTooltipsEnabled] / action::showWidgetTooltip   = sml::state<state::Idle>,
 sml::state<state::Idle> + sml::event<event::OnLeave> [guard::isTooltipsEnabled] / action::removeWidgetTooltip = sml::state<state::Idle>,
 sml::state<state::Idle> + sml::event<event::OnKeyPressed> [guard::isCtrlKeyPressed] = sml::state<state::CtrlKeyPressed>,
 sml::state<state::CtrlKeyPressed> + sml::event<event::OnKeyPressed> [guard::isMappingKeyPressed] / action::showTooltip = sml::state<state::MappingModeActive>,
 sml::state<state::MappingModeActive> + sml::event<event::OnKeyPressed> [guard::isMappingCancelKeyPressed] / action::removeTooltip = sml::state<state::Idle>,
 sml::state<state::MappingModeActive> + sml::event<event::OnWidgetHovered> / action::handleHoveredWidget = sml::state<state::MappingModeActive>
      );
      // clang-format on
   }

private:
};

}
}
}
