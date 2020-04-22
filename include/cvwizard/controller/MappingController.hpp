#pragma once

#include <cvwizard/controller/MappingControllable.hpp>

#include <boost/sml.hpp>

namespace sml = boost::sml;

namespace qrx {
namespace cvwizard {
namespace controller {
namespace mapping {

namespace event {
struct OnWidgetHovered {};
struct OnWidgetSelected {};
struct OnPortWidgetHovered {};
struct OnParamWidgetHovered {};
struct OnPortWidgetSelected {};
struct OnParamWidgetSelected {};
}

namespace guard {
//const auto isParamWidgetHovered = [](const MappingControllable& c) { return c.isParamWidgetHovered(); };
//const auto isParamWidgetSelected = [](const MappingControllable& c) { return c.isParamWidgetSelected(); };

const auto isInputPortWidgetHovered = [](const MappingControllable& c) { return c.isInputPortWidgetHovered(); };
//const auto isInputPortWidgetSelected = [](const MappingControllable& c) { return c.isInputPortWidgetSelected(); };
}

namespace action {
const auto hoverWidget = [](MappingControllable& c) { c.hoverWidget(); };
//const auto handleHoveredWidget = [](MappingControllable& c) { c.handleHoveredWidget(); };
//const auto addSelectedPortWidget = [](MappingControllable& c) { c.addSelectedPortWidget(); };
//const auto addSelectedParamWidget = [](MappingControllable& c) { c.addSelectedParamWidget(); };
}

namespace state {
class Idle;
class InputPortHovered;
class InputPortSelected;
class InputParamHovered;
class InputParamSelected;
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
         *sml::state<Idle> + sml::event<OnWidgetHovered> [isInputPortWidgetHovered] / hoverWidget = sml::state<InputPortHovered>
         // sml::state<InputPortHovered> + sml::event<OnWidgetSelected> [isInputPortWidgetSelected] / addSelectedPortWidget = sml::state<InputPortSelected>,
         // sml::state<InputPortSelected> + sml::event<OnWidgetSelected> [isParamWidgetHovered] / addSelectedParamWidget = sml::state<InputParamSelected>
      );
      // clang-format on
   }
};

}
}
}
}
