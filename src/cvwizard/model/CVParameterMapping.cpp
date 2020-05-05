#include <cvwizard/model/CVParameterMapping.hpp>

namespace qrx {
namespace cvwizard {
namespace model {

using namespace boundary::rack;

void CVParameterMapping::setInputPort(rack::PortWidget* widget)
{
   _inputPortWidget = widget;
}

void CVParameterMapping::setCVParameter(rack::ParamWidget* widget)
{
   _cvParamWidget = widget;
   _cvIndicatorWidget = std::make_unique<ui::CVIndicatorWidget>(_cvParamWidget, _inputPortWidget->module, _inputPortWidget->portId);
   _cvParamWidget->addChild(_cvIndicatorWidget.get());
}

}
}
}
