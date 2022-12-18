#pragma once

#include <boundary/rack/Types.hpp>

namespace qrx::cvwizard::utility {

class Widget final
{
public:
   static boundary::rack::ModuleWidget* getIfIsModuleWidget(boundary::rack::Widget* widget);

   static boundary::rack::ParamWidget* getIfIsKnobParamWidget(boundary::rack::Widget* widget);
   
   static boundary::rack::PortWidget* getIfIsInputPortWidget(boundary::rack::Widget* widget);
};

}
