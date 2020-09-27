#pragma once

#include <boundary/rack/AppBoundary.hpp>
#include <cvwizard/controller/CVWizardController.hpp>
#include <cvwizard/model/CVWizardModel.hpp>
#include <cvwizard/ModuleSettings.hpp>
#include <sigslot/signal.hpp>

#include <functional>
#include <memory>

namespace qrx {
namespace cvwizard {

using namespace boundary;

class CVWizard final : public controller::CVWizardControllable
{
public:
  
   enum class TooltipCallbackKind
   {
      ShowWidgetTooltip,
      RemoveWidgetTooltip,
      ShowTooltip,
      RemoveTooltip
   };
   
   explicit CVWizard(const rack::AppBoundary& appBoundary);
   ~CVWizard();
   
   void addSettings(const std::shared_ptr<ModuleSettings>& settings);
   
   void process();
   
   void onEnter();
   void onLeave();
   
   sigslot::connection connectTooltipsCallback(std::function<void(const TooltipCallbackKind)> callback);
   
   void showWidgetTooltip() override;
   void removeWidgetTooltip() override;
   void showTooltip() override;
   void removeTooltip() override;
   bool isShowTooltipsEnabled() const override;
   void toggleTooltip() override ;
   
   bool isControlKeyPressed() const override;
   bool isMappingKeyPressed() const override;
   bool isMappingCancelKeyPressed() const override;
   bool isTooltipKeyPressed() const override;
   
   bool isModuleWidgetHovered() const override;
   bool isSameModuleWidgetHovered() const override;
   
   void beginModuleMapping() override;
   void endModuleMapping() override;
   
   void sendOnEnterModuleChildWidget() const override;
   void sendOnLeaveModuleChildWidget() const override;
   
   model::CVWizardModel _model;
   
private:

   const rack::AppBoundary& _appBoundary;
   std::unique_ptr<sml::sm<controller::CVWizardController>> _controller;
   std::shared_ptr<ModuleSettings> _settings;
   
   sigslot::signal<TooltipCallbackKind> _tooltipsCallback;
};

}
}
