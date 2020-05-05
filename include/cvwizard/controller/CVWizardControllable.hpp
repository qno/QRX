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
   virtual void toggleTooltip() = 0;
   
   virtual bool isControlKeyPressed() const = 0;
   virtual bool isMappingKeyPressed() const = 0;
   virtual bool isMappingCancelKeyPressed() const = 0;
   virtual bool isTooltipKeyPressed() const = 0;
   
   virtual void beginModuleMapping() = 0;
   virtual void endModuleMapping() = 0;
   
   virtual bool isModuleWidgetHovered() const = 0;
   virtual bool isSameModuleWidgetHovered() const = 0;
   virtual bool isSelectedHovered() const = 0;
   
   virtual void sendOnEnterModuleChildWidget() const = 0;
   virtual void sendOnLeaveModuleChildWidget() const = 0;
   virtual void sendSelectedWidget() const = 0;
};

}
}
}
