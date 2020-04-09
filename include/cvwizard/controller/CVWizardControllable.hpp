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
};

}
}
}
