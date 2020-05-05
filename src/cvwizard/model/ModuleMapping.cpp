#include <cvwizard/model/ModuleMapping.hpp>
#include <cvwizard/utility/Widget.hpp>

namespace qrx {
namespace cvwizard {
namespace model {

using namespace boundary::rack;
using namespace controller::mapping;

ModuleMapping::ModuleMapping(rack::ModuleWidget* widget)
   : _moduleWidget{widget}
{
   DEBUG("entered %s", __FUNCTION__);
   MappingControllable& c{*this};
   _controller = std::make_unique<sml::sm<MappingController>>(c);
}

ModuleWidget* ModuleMapping::getModuleWidget() const
{
   return _moduleWidget;
}

void ModuleMapping::enableHover()
{
   DEBUG("entered %s", __FUNCTION__);
   _moduleOnHoverWidget = std::make_unique<ui::HoveredWidget>(_moduleWidget);
   _moduleWidget->addChild(_moduleOnHoverWidget.get());
}

void ModuleMapping::disableHover()
{
   DEBUG("entered %s", __FUNCTION__);
   _moduleOnHoverWidget = nullptr;
}

void ModuleMapping::onEnterWidget(rack::Widget* widget)
{
   DEBUG("entered %s, widget (#0x%0x)", __FUNCTION__, widget);
   _currentHoveredWidget = widget;
   _controller->process_event(event::OnEnterWidget{});
}

void ModuleMapping::onLeaveWidget()
{
   DEBUG("entered %s", __FUNCTION__);
   _controller->process_event(event::OnLeaveWidget{});
}

void ModuleMapping::OnSelectWidget(rack::Widget* widget)
{
   DEBUG("entered %s, widget (#0x%0x)", __FUNCTION__, widget);
   _selectedWidget = widget;
   _controller->process_event(event::OnWidgetSelected{});
}

bool ModuleMapping::isInputPortWidget() const
{
   DEBUG("entered %s, hovered=(#0x%0x)", __FUNCTION__, _currentHoveredWidget);
   return nullptr != utility::Widget::getIfIsInputPortWidget(_currentHoveredWidget);
}

bool ModuleMapping::isKnobParamWidget() const
{
   DEBUG("entered %s, hovered=(#0x%0x)", __FUNCTION__, _currentHoveredWidget);
   return nullptr != utility::Widget::getIfIsKnobParamWidget(_currentHoveredWidget);
}

bool ModuleMapping::isSelectedHovered() const
{
   DEBUG("entered %s, selected=(#0x%0x), hovered=(#0x%0x)", __FUNCTION__, _selectedWidget, _currentHoveredWidget);
   return _selectedWidget == _currentHoveredWidget;
}

void ModuleMapping::addSelectedInputPort()
{
   DEBUG("entered %s", __FUNCTION__);
   DEBUG("create _currentCVParamMapping");
   _currentCVParamMapping = std::make_shared<CVParameterMapping>();
   _currentCVParamMapping->setInputPort(utility::Widget::getIfIsInputPortWidget(_selectedWidget));
}

void ModuleMapping::addSelectedKnobParamWidget()
{
   DEBUG("entered %s", __FUNCTION__);
   _currentCVParamMapping->setCVParameter(utility::Widget::getIfIsKnobParamWidget(_selectedWidget));
   _cvParameterMappings.push_back(_currentCVParamMapping);
   _currentCVParamMapping = nullptr;
}

void ModuleMapping::enableHoverWidget()
{
   DEBUG("entered %s", __FUNCTION__);
   _onHoverWidget = std::make_unique<ui::HoveredWidget>(_currentHoveredWidget);
   _currentHoveredWidget->addChild(_onHoverWidget.get());
}

void ModuleMapping::disableHoverWidget()
{
   DEBUG("entered %s", __FUNCTION__);
   _onHoverWidget = nullptr;
}

bool ModuleMapping::hasMappedParameter() const
{
   DEBUG("entered %s", __FUNCTION__);
   DEBUG("_cvParameterMappings size is %d", _cvParameterMappings.size());
   return !_cvParameterMappings.empty();
}

}
}
}
