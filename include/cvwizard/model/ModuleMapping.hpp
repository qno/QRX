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
   
   void onEnterWidget(rack::Widget* widget);
   void onLeaveWidget();
   void OnSelectWidget(rack::Widget* widget);
   
   bool hasMappedParameter() const;
   
private:
   
   bool isInputPortWidget() const override;
   bool isKnobParamWidget() const override;
   bool isSelectedHovered() const override;
   void addSelectedInputPort() override;
   void addSelectedKnobParamWidget() override;
   void enableHoverWidget() override;
   virtual void disableHoverWidget() override;
   std::unique_ptr<sml::sm<controller::mapping::MappingController>> _controller;
   rack::ModuleWidget* _moduleWidget = nullptr;
   std::unique_ptr<ui::HoveredWidget> _moduleOnHoverWidget = nullptr;
   rack::Widget* _currentHoveredWidget = nullptr;
   rack::Widget* _selectedWidget = nullptr;
   std::unique_ptr<ui::HoveredWidget> _onHoverWidget = nullptr;
   std::shared_ptr<CVParameterMapping> _currentCVParamMapping;
   CVParameterMappings _cvParameterMappings;
};

}
}
}
