#pragma once

#include <app/ParamWidget.hpp>
#include <app/PortWidget.hpp>
#include <cvwizard/ui/HoveredWidget.hpp>
#include <cvwizard/ui/CVIndicatorWidget.hpp>

#include <memory>

namespace qrx {
namespace cvwizard {
namespace model {

class CVWizardModel
{
public:
   
   ~CVWizardModel()
   {
   }
   
   rack::widget::Widget* hoveredModuleWidget = nullptr;
   std::unique_ptr<ui::HoveredWidget> onHoverModuleWidget = nullptr;
   
//   rack::app::ParamWidget* paramWidget = nullptr;
//   rack::app::PortWidget* portWidget = nullptr;
//   ui::CVIndicatorWidget* selectedParamWidget = nullptr;
};

}
}
}
