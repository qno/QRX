#pragma once

#include <boundary/rack/AppBoundary.hpp>
#include <cvwizard/controller/CVWizardController.hpp>
#include <cvwizard/model/CVWizardModel.hpp>
#include <cvwizard/ModuleSettings.hpp>

#include <memory>

namespace qrx {
namespace cvwizard {

class CVWizard final : public controller::CVWizardControllable
{
public:
  
   explicit CVWizard(const boundary::rack::AppBoundary& appBoundary);
   ~CVWizard();
   
   void addSettings(const std::shared_ptr<ModuleSettings>& settings);
   
   void process();
   
   void onEnter();
   void onLeave();
   
   void showWidgetTooltip() override;
   void removeWidgetTooltip() override;
   void showTooltip() override;
   void removeTooltip() override;
   bool isShowTooltipsEnabled() const override;
   void toogleTooltip() override ;
   
   bool isControlKeyPressed() const override;
   bool isMappingKeyPressed() const override;
   bool isMappingCancelKeyPressed() const override;
   bool isTooltipKeyPressed() const override;
   
//   void handleHoveredWidget() override;
   void addHoveredModuleWidget() override;
   void clearHoveredModuleWidget() override;
   
   bool isModuleWidgetHovered() const override;

   bool isSameModuleWidgetHovered() const override;

   //bool isModuleWidgetSelected() const override;
   //bool isParamWidgetHovered() const override;
   //bool isParamWidgetSelected() const override;
   //bool isInputPortWidgetHovered() const override;
   //bool isInputPortWidgetSelected() const override;
   
   //void addSelectedParamWidget() override;
   //void addSelectedPortWidget() override;
   
   boundary::rack::ModuleWidget* getIfIsModuleWidget(boundary::rack::Widget* widget) const;
   //boundary::rack::PortWidget* getIfIsInputPortWidget(boundary::rackWidget* widget) const;
   //boundary::rack::ParamWidget* getIfIsParamWidget(boundary::rackWidget* widget) const;
   
   model::CVWizardModel _model;
   
private:

   const boundary::rack::AppBoundary& _appBoundary;
   std::unique_ptr<sml::sm<controller::CVWizardController>> _controller;
   std::shared_ptr<ModuleSettings> _settings;
};

}
}
