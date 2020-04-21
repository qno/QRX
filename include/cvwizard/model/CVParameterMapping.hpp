#pragma once

#include <boundary/rack/Types.hpp>
#include <cvwizard/ui/HoveredWidget.hpp>

#include <unordered_map>
#include <memory>

namespace qrx {
namespace cvwizard {
namespace model {

using namespace boundary;

class CVParameterMapping final
{
//   using ParameterMappings = std::unordered_map<rack::ModuleWidget*, std::shared_ptr<ModuleMapping>>;

public:
   explicit CVParameterMapping();
   ~CVParameterMapping() noexcept = default;
   
   void setInputPort(rack::PortWidget* widget);
   void setInputPort(rack::ParamWidget* widget);
   
   void enableHover();
   void disableHover();

private:
   
   rack::PortWidget* _inputPortWidget = nullptr;
   rack::ParamWidget* _cvParamWidget = nullptr;
   rack::ParamWidget* _cvAttenuatorWidget = nullptr;
   
   std::unique_ptr<ui::HoveredWidget> _inputPortOnHoverWidget = nullptr;
   std::unique_ptr<ui::HoveredWidget> _paramOnHoverWidget = nullptr;
};

}
}
}
