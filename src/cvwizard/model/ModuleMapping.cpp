#include <cvwizard/model/ModuleMapping.hpp>

namespace qrx {
namespace cvwizard {
namespace model {

using namespace boundary::rack;

ModuleMapping::ModuleMapping(rack::ModuleWidget* widget)
   : _moduleWidget{widget}
{
}

ModuleWidget* ModuleMapping::getModuleWidget() const
{
   return _moduleWidget;
}

void ModuleMapping::enableHover()
{
   _moduleOnHoverWidget = std::make_unique<ui::HoveredWidget>(_moduleWidget);
   _moduleWidget->addChild(_moduleOnHoverWidget.get());
}

void ModuleMapping::disableHover()
{
   _moduleOnHoverWidget = nullptr;
}

}
}
}
