#pragma once

#include <boundary/rack/AppBoundary.hpp>
#include <cvwizard/CVWizardModule.hpp>
#include <cvwizard/CVWizard.hpp>

#include <memory>

namespace qrx {
namespace cvwizard {

class CVWizardWidget final : public boundary::rack::ModuleWidget
                           , public boundary::rack::AppBoundary
{
public:
  
   explicit CVWizardWidget(CVWizardModule* module);
  
   ~CVWizardWidget() override;

private:
   
   boundary::rack::State* getEventState() const override;
   boundary::rack::Scene* getScene() const override;
   boundary::rack::Window* getWindow() const override;
   
   void step() override;
   void draw(const boundary::rack::widget::DrawArgs& args) override;
   
   void onEnter(const boundary::rack::event::Enter& e) override;
   void onLeave(const boundary::rack::event::Leave& e) override;
   void onHover(const boundary::rack::event::Hover& e) override;
   
   void showWidgetTooltip();
   void removeWidgetTooltip();
   void showTooltip();
   void removeTooltip();
   bool isShowTooltipsEnabled() const;
   
   CVWizard _cvWizard;
   CVWizardModule* _module  = nullptr;
   
   std::unique_ptr<boundary::rack::ui::Tooltip> _widgetTooltip = nullptr;
   static std::unique_ptr<boundary::rack::ui::Tooltip> s_tooltip;
};

}
}
