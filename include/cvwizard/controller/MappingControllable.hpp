#pragma once

namespace qrx::cvwizard::controller::mapping {

class MappingControllable
{
public:
   virtual bool isInputPortWidgetAndNotMapped() const = 0;
   virtual bool isKnobParamWidgetAndNotMapped() const = 0;
   virtual bool isSelectedHovered() const = 0;
   virtual void addSelectedInputPort() = 0;
   virtual void addSelectedKnobParamWidget() = 0;
   virtual void enableHoverWidget() = 0;
   virtual void disableHoverWidget() = 0;
};

}
