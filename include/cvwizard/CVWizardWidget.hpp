#pragma once

#include <QRXPlugin.hpp>
#include <boundary/RackAppBoundary.hpp>
#include <cvwizard/CVWizardModule.hpp>
#include <cvwizard/model/CVWizardModel.hpp>
#include <cvwizard/controller/CVWizardController.hpp>

#include <memory>

namespace qrx {
namespace cvwizard {

class CVWizardWidget final : public rack::ModuleWidget
                           , public controller::CVWizardControllable
{
public:
  
   explicit CVWizardWidget(CVWizardModule* module);
  
   ~CVWizardWidget() override;
   
   void setApp(const std::shared_ptr<boundary::RackAppBoundary>& app);

private:
   
   void step() override;
   void draw(const DrawArgs& args) override;
   
   void onEnter(const rack::event::Enter& e) override;
   void onLeave(const rack::event::Leave& e) override;
   void onHover(const rack::event::Hover& e) override;
   
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
#ifdef QRX_UNITTESTS
public:
   model::CVWizardModel& getModel() { return _model; }
#endif
   bool isSameModuleWidgetHovered() const override;
#ifdef QRX_UNITTESTS
private:
#endif
   //  bool isModuleWidgetSelected() const override;
   //   bool isParamWidgetHovered() const override;
   //   bool isParamWidgetSelected() const override;
   //   bool isInputPortWidgetHovered() const override;
   //   bool isInputPortWidgetSelected() const override;
   
   //   void addSelectedParamWidget() override;
   //  void addSelectedPortWidget() override;
   
   rack::ModuleWidget* getIfIsModuleWidget(rack::Widget* widget) const;
   //   rack::PortWidget* getIfIsInputPortWidget(rack::Widget* widget) const;
   // rack::ParamWidget* getIfIsParamWidget(rack::Widget* widget) const;
   
   std::shared_ptr<boundary::RackAppBoundary> _app = nullptr;
   CVWizardModule* _module  = nullptr;
   rack::Window* _appWindow = nullptr;
   
   std::unique_ptr<sml::sm<controller::CVWizardController>> _controller;
   static model::CVWizardModel _model;
   
   std::unique_ptr<rack::ui::Tooltip> _widgetTooltip = nullptr;
   static std::unique_ptr<rack::ui::Tooltip> s_tooltip;
};

}
}
