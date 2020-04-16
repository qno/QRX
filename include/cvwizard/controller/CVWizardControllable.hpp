#pragma once

namespace qrx {
namespace cvwizard {
namespace controller {

class CVWizardControllable
{
public:
   virtual void showWidgetTooltip() = 0;
   virtual void removeWidgetTooltip() = 0;
   virtual void showTooltip() = 0;
   virtual void removeTooltip() = 0;
   virtual bool isShowTooltipsEnabled() const = 0;
   virtual void toogleTooltip() = 0;
   
   virtual bool isControlKeyPressed() const = 0;
   virtual bool isMappingKeyPressed() const = 0;
   virtual bool isMappingCancelKeyPressed() const = 0;
   virtual bool isTooltipKeyPressed() const = 0;
   
   virtual void handleHoveredWidget() = 0;
   virtual void addHoveredModuleWidget() = 0;
   virtual void clearHoveredModuleWidget() = 0;
   
   virtual bool isModuleWidgetHovered() const = 0;
   virtual bool isSameModuleWidgetHovered() const = 0;
   virtual bool isModuleWidgetSelected() const = 0;
   virtual bool isParamWidgetHovered() const = 0;
   virtual bool isParamWidgetSelected() const = 0;
   virtual bool isInputPortWidgetHovered() const = 0;
   virtual bool isInputPortWidgetSelected() const = 0;
   
   virtual void addSelectedParamWidget() = 0;
   virtual void addSelectedPortWidget() = 0;
};

}
}
}
