#include <cvwizard/model/ModuleMapping.hpp>
#include <cvwizard/utility/Widget.hpp>

#include <algorithm>

namespace qrx::cvwizard::model {

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
   _moduleOnHoverWidget = std::make_unique<ui::OnHoverWidget>(_moduleWidget);
   _moduleWidget->addChild(_moduleOnHoverWidget.get());
}

void ModuleMapping::disableHover()
{
   _moduleOnHoverWidget = nullptr;
}

void ModuleMapping::onEnterWidget(rack::Widget* widget)
{
   _currentHoveredWidget = widget;
   _controller->process_event(event::OnEnterWidget{});
}

void ModuleMapping::onLeaveWidget()
{
   _controller->process_event(event::OnLeaveWidget{});
}

bool ModuleMapping::hasMappedParameter() const
{
   return !_cvParameterMappings.empty();
}

void ModuleMapping::onClicked(boundary::rack::Widget* widget)
{
   _selectedWidget = widget;
   _controller->process_event(event::OnWidgetSelected{});
   _onHoverWidget = nullptr;
   _selectedWidget = nullptr;
}

bool ModuleMapping::isWidgetMapped(const boundary::rack::Widget* widget) const
{
   auto result = false;
   
   const auto it = std::find_if(_cvParameterMappings.begin(), _cvParameterMappings.end(),
                                [widget](const std::shared_ptr<CVParameterMapping>& pm)
                                { return pm->getInputPort() == widget || pm->getCVParameter() == widget; });
   
   if (_cvParameterMappings.end() != it)
   {
      result = true;
   }
   
   return result;
}

bool ModuleMapping::isInputPortWidgetAndNotMapped() const
{
   auto result = false;
   if (const auto widget = utility::Widget::getIfIsInputPortWidget(_currentHoveredWidget))
   {
      result = true;
      if (isWidgetMapped(widget))
      {
         result = false;
      }
   }
   return result;
}

bool ModuleMapping::isKnobParamWidgetAndNotMapped() const
{
   auto result = false;
   if (const auto widget = utility::Widget::getIfIsKnobParamWidget(_currentHoveredWidget))
   {
      result = true;
      if (isWidgetMapped(widget))
      {
         result = false;
      }
   }
   return result;
}

bool ModuleMapping::isSelectedHovered() const
{
   return _selectedWidget == _currentHoveredWidget;
}

void ModuleMapping::addSelectedInputPort()
{
   _currentCVParamMapping = std::make_shared<CVParameterMapping>();
   _currentCVParamMapping->setInputPort(utility::Widget::getIfIsInputPortWidget(_selectedWidget));
}

void ModuleMapping::addSelectedKnobParamWidget()
{
   _currentCVParamMapping->setCVParameter(utility::Widget::getIfIsKnobParamWidget(_selectedWidget));
   _cvParameterMappings.push_back(_currentCVParamMapping);
   _currentCVParamMapping = nullptr;
}

void ModuleMapping::enableHoverWidget()
{
   _onHoverWidget = std::make_unique<ui::ClickableOnHoverWidget>(_currentHoveredWidget);
   _currentHoveredWidget->addChild(_onHoverWidget.get());
   _onClickCallbackConnection = _onHoverWidget->connectOnClickCallback(std::bind(&ModuleMapping::onClicked, this, std::placeholders::_1));
}

void ModuleMapping::disableHoverWidget()
{
   _onHoverWidget = nullptr;
}

}
