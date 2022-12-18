#pragma once

#include <cvwizard/controller/MappingControllable.hpp>

#include <boost/sml.hpp>

namespace sml = boost::sml;

namespace qrx::cvwizard::controller::mapping {

namespace event {
struct OnEnterWidget {};
struct OnLeaveWidget {};
struct OnWidgetSelected {};
}

namespace guard {
const auto isInputPortWidgetAndNotMapped = [](const MappingControllable& c) { return c.isInputPortWidgetAndNotMapped(); };
const auto isKnobParamWidgetAndNotMapped = [](const MappingControllable& c) { return c.isKnobParamWidgetAndNotMapped(); };
const auto isSelectedHovered = [](const MappingControllable& c) { return c.isSelectedHovered(); };
}

namespace action {
const auto enableHoverWidget = [](MappingControllable& c) { c.enableHoverWidget(); };
const auto disableHoverWidget = [](MappingControllable& c) { c.disableHoverWidget(); };
const auto addSelectedInputPort = [](MappingControllable& c) { c.addSelectedInputPort(); };
const auto addSelectedKnobParamWidget = [](MappingControllable& c) { c.addSelectedKnobParamWidget(); };
}

namespace state {
class Idle;
class InputPortHovered;
class InputPortSelected;
class KnobParamHovered;
class KnobParamSelected;
}

class MappingController
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
*sml::state<Idle> + sml::event<OnEnterWidget> [isInputPortWidgetAndNotMapped] / enableHoverWidget = sml::state<InputPortHovered>,
 sml::state<InputPortHovered> + sml::event<OnLeaveWidget> / disableHoverWidget = sml::state<Idle>,
 sml::state<InputPortHovered> + sml::event<OnWidgetSelected> [isSelectedHovered] / addSelectedInputPort = sml::state<InputPortSelected>,
 sml::state<InputPortSelected> + sml::event<OnLeaveWidget> / disableHoverWidget = sml::state<InputPortSelected>,
 sml::state<InputPortSelected> + sml::event<OnEnterWidget> [isKnobParamWidgetAndNotMapped] / enableHoverWidget = sml::state<KnobParamHovered>,
 sml::state<KnobParamHovered> + sml::event<OnLeaveWidget> / disableHoverWidget = sml::state<InputPortSelected>,
 sml::state<KnobParamHovered> + sml::event<OnWidgetSelected> [isSelectedHovered] / addSelectedKnobParamWidget = sml::state<KnobParamSelected>,
 sml::state<KnobParamSelected> + sml::event<OnLeaveWidget> / disableHoverWidget = sml::state<Idle>
      );
      // clang-format on
   }
};

}
