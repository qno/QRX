#include <cvwizard/model/ModuleMapping.hpp>

namespace qrx {
namespace cvwizard {
namespace model {

using namespace boundary::rack;
using namespace controller::mapping;

ModuleMapping::ModuleMapping(rack::ModuleWidget* widget)
   : _moduleWidget{widget}
{
   MappingControllable& c{*this};
   _controller = std::make_unique<sml::sm<MappingController>>(c);
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

void ModuleMapping::sendHoveredWidget(rack::Widget* widget)
{
   _hoveredWidget = widget;
   _controller->process_event(event::OnWidgetHovered{});
}

PortWidget* ModuleMapping::getIfIsInputPortWidget(Widget* widget) const
{
   PortWidget* result = nullptr;
   if (auto&& p = dynamic_cast<PortWidget*>(widget))
   {
      if (PortWidget::INPUT == p->type)
      {
         result = p;
      }
   }
   return result;
}

bool ModuleMapping::isInputPortWidgetHovered() const
{
   DEBUG("entered %s", __FUNCTION__);
   return nullptr != getIfIsInputPortWidget(_hoveredWidget);
}

void ModuleMapping::hoverWidget()
{
   _onHoverWidget = std::make_unique<ui::HoveredWidget>(_hoveredWidget);
   _hoveredWidget->addChild(_onHoverWidget.get());
}

}
}
}
