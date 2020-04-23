#include <cvwizard/utility/Widget.hpp>

namespace qrx {
namespace cvwizard {
namespace utility {

boundary::rack::ModuleWidget* Widget::getIfIsModuleWidget(boundary::rack::Widget* widget)
{
   return dynamic_cast<boundary::rack::ModuleWidget*>(widget);
}

boundary::rack::ParamWidget* Widget::getIfIsParamWidget(boundary::rack::Widget* widget)
{
   boundary::rack::ParamWidget* result = nullptr;
   if (auto&& paramWidget = dynamic_cast<boundary::rack::ParamWidget*>(widget))
   {
      if (dynamic_cast<boundary::rack::Knob*>(paramWidget))
      {
         result = paramWidget;
      }
   }
   return result;
}

boundary::rack::PortWidget* Widget::getIfIsInputPortWidget(boundary::rack::Widget* widget)
{
   boundary::rack::PortWidget* result = nullptr;
   if (auto&& p = dynamic_cast<boundary::rack::PortWidget*>(widget))
   {
      if (boundary::rack::PortWidget::INPUT == p->type)
      {
         result = p;
      }
   }
   return result;
}

}
}
}
