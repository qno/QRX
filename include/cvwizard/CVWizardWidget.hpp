#pragma once

#include <boundary/rack/AppBoundary.hpp>
#include <cvwizard/CVWizardModule.hpp>
#include <cvwizard/CVWizard.hpp>

#include <memory>

namespace qrx::cvwizard {

using namespace boundary;

class CVWizardWidget final : public rack::ModuleWidget
                           , public rack::AppBoundary
{
public:
  
   explicit CVWizardWidget(CVWizardModule* module);
  
   ~CVWizardWidget() override;

private:
   
   rack::State* getEventState() const override;
   rack::Scene* getScene() const override;
   rack::Window* getWindow() const override;
   bool isKeyPressed(const int keyCode) const override;
   bool isModKeyPressed(const int modKeyCode) const override;
   
   void step() override;
   void draw(const rack::widget::DrawArgs& args) override;
   
   void onEnter(const rack::event::Enter& e) override;
   void onLeave(const rack::event::Leave& e) override;
   void onHover(const rack::event::Hover& e) override;
   
   void tooltipCallback(const CVWizard::TooltipCallbackKind kind);
   void showWidgetTooltip();
   void removeWidgetTooltip();
   void showTooltip();
   void removeTooltip();
   
   CVWizard _cvWizard;
   CVWizardModule* _module  = nullptr;
   
   std::unique_ptr<rack::ui::Tooltip> _widgetTooltip = nullptr;
   static std::unique_ptr<rack::ui::Tooltip> s_tooltip;
   
   sigslot::connection _tooltipsCallbackConnection;
};

}
