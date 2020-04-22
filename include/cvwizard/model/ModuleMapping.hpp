#pragma once

#include <boundary/rack/Types.hpp>
#include <cvwizard/controller/MappingController.hpp>
#include <cvwizard/model/CVParameterMapping.hpp>
#include <cvwizard/ui/HoveredWidget.hpp>

#include <list>
#include <memory>

namespace qrx {
namespace cvwizard {
namespace model {

using namespace boundary;

class ModuleMapping final : public controller::mapping::MappingControllable
{
   using CVParameterMappings = std::list<std::shared_ptr<CVParameterMapping>>;

public:
   explicit ModuleMapping(rack::ModuleWidget* widget);
   ~ModuleMapping() noexcept = default;
   
   rack::ModuleWidget* getModuleWidget() const;
   
   void enableHover();
   void disableHover();
   
   void sendHoveredWidget(rack::Widget* widget);

private:
   
   rack::PortWidget* getIfIsInputPortWidget(rack::Widget* widget) const;
   bool isInputPortWidgetHovered() const override;
   void hoverWidget() override;
   std::unique_ptr<sml::sm<controller::mapping::MappingController>> _controller;
   rack::ModuleWidget* _moduleWidget = nullptr;
   std::unique_ptr<ui::HoveredWidget> _moduleOnHoverWidget = nullptr;
   rack::Widget* _hoveredWidget = nullptr;
   std::unique_ptr<ui::HoveredWidget> _onHoverWidget = nullptr;
   std::shared_ptr<CVParameterMapping> _currentCVParamMapping;
   CVParameterMappings _cvParameterMappings;
};

}
}
}
