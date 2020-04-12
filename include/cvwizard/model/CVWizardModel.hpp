#pragma once

#include <widget/Widget.hpp>

namespace qrx {
namespace cvwizard {
namespace model {

class CVWizardModel
{
public:
   rack::widget::Widget* hoveredWidget = nullptr;
   rack::widget::Widget* onHoverWidget = nullptr;
};

}
}
}
