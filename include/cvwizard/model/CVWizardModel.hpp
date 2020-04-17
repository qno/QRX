#pragma once

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
   
   boundary::rack::Widget* hoveredModuleWidget = nullptr;
   std::unique_ptr<ui::HoveredWidget> onHoverModuleWidget = nullptr;
   
//   boundary::rack::ParamWidget* paramWidget = nullptr;
//   boundary::rack::PortWidget* portWidget = nullptr;
//   ui::CVIndicatorWidget* selectedParamWidget = nullptr;
};

}
}
}
