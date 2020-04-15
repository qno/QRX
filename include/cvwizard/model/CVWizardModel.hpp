#pragma once

#include <app/ParamWidget.hpp>
#include <app/PortWidget.hpp>
#include <cvwizard/ui/HoveredWidget.hpp>
#include <cvwizard/ui/CVIndicatorWidget.hpp>

namespace qrx {
namespace cvwizard {
namespace model {

class CVWizardModel
{
public:
   
   ~CVWizardModel()
   {
      if (onHoverWidget)
      {
         delete onHoverWidget;
         onHoverWidget = nullptr;
      }
   }
   
   rack::widget::Widget* hoveredModuleWidget = nullptr;
   ui::HoveredWidget* onHoverModuleWidget = nullptr;
   rack::widget::Widget* hoveredWidget = nullptr;
   ui::HoveredWidget* onHoverWidget = nullptr;
   
   rack::app::ParamWidget* paramWidget = nullptr;
   rack::app::PortWidget* portWidget          = nullptr;
   ui::CVIndicatorWidget* selectedParamWidget = nullptr;
};

}
}
}
