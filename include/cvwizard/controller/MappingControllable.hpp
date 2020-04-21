#pragma once

namespace qrx {
namespace cvwizard {
namespace controller {

class MappingControllable
{
public:
   //   virtual bool isModuleWidgetSelected() const = 0;
   //   virtual bool isParamWidgetHovered() const = 0;
   //virtual bool isParamWidgetSelected() const = 0;
   virtual bool isInputPortWidgetHovered() const = 0;
   //virtual bool isInputPortWidgetSelected() const = 0;
   
   //virtual void addSelectedParamWidget() = 0;
   //virtual void addSelectedPortWidget() = 0;
};

}
}
}
