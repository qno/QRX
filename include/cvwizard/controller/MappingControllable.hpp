#pragma once

namespace qrx {
namespace cvwizard {
namespace controller {
namespace mapping {

class MappingControllable
{
public:
   virtual bool isKnobParamWidget() const = 0;
   virtual bool isInputPortWidget() const = 0;
   virtual bool isSelectedHovered() const = 0;
   virtual void addSelectedInputPort() = 0;
   virtual void addSelectedKnobParamWidget() = 0;
   virtual void enableHoverWidget() = 0;
   virtual void disableHoverWidget() = 0;
};

}
}
}
}
