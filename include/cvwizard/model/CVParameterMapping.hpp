#pragma once

#include <boundary/rack/Types.hpp>
#include <cvwizard/ui/CVIndicatorWidget.hpp>

#include <memory>

namespace qrx {
namespace cvwizard {
namespace model {

using namespace boundary;

class CVParameterMapping final
{
public:
   CVParameterMapping() = default;
   ~CVParameterMapping() noexcept = default;
   
   void setInputPort(rack::PortWidget* widget);
   void setCVParameter(rack::ParamWidget* widget);

private:
   
   rack::PortWidget* _inputPortWidget = nullptr;
   rack::ParamWidget* _cvParamWidget = nullptr;
   rack::ParamWidget* _cvAttenuatorWidget = nullptr;
   
   std::unique_ptr<ui::CVIndicatorWidget> _cvIndicatorWidget = nullptr;
};

}
}
}
