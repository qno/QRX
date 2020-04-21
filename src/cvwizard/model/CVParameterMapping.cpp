#include <cvwizard/model/CVParameterMapping.hpp>

namespace qrx {
namespace cvwizard {
namespace model {

using namespace boundary::rack;

CVParameterMapping::CVParameterMapping()
{
}

void CVParameterMapping::setInputPort(rack::PortWidget* widget)
{
   _inputPortWidget = widget;
}

void CVParameterMapping::setInputPort(rack::ParamWidget* widget)
{
   _cvParamWidget = widget;
}


void CVParameterMapping::enableHover()
{
}

void CVParameterMapping::disableHover()
{
}

}
}
}
