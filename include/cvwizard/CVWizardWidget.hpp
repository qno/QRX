#pragma once

#include <QRXPlugin.hpp>
#include <cvwizard/CVWizardModule.hpp>
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
   
   bool isControlKeyPressed () const override;
   bool isMappingKeyPressed () const override;
   bool isMappingCancelKeyPressed () const override;
   bool isTooltipKeyPressed () const override;
   
   std::unique_ptr<sml::sm<controller::CVWizardController>> _controller;
   
   CVWizardModule* _module  = nullptr;
   rack::Window* _appWindow = nullptr;
   
   std::unique_ptr<rack::ui::Tooltip> _widgetTooltip = nullptr;
   static std::unique_ptr<rack::ui::Tooltip> s_tooltip;
};

}
}
