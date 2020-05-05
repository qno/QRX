#pragma once

#include <boundary/rack/Types.hpp>

#include <chrono>
#include <cmath>

namespace qrx {
namespace cvwizard {
namespace ui {

class CVIndicatorWidget final : public boundary::rack::TransparentWidget
{
public:
   
   CVIndicatorWidget(boundary::rack::Widget* w, boundary::rack::Module* module, int portId)
      : _selectedParamWidget{w}
      , _module{module}
      , _portId{portId}
   {
      box.size = _selectedParamWidget->box.size;
   }
   
   ~CVIndicatorWidget() override
   {
      if (_selectedParamWidget)
      {
         _selectedParamWidget->removeChild(this);
      }
   }
   
   void step() override
   {
   }
   
   void draw(const boundary::rack::widget::DrawArgs& args) override
   {
      boundary::rack::TransparentWidget::draw(args);
      auto* vg = args.vg;
      auto voltage = _module->inputs.at(_portId).getVoltage();
      auto c = box.size.x/2.f;
      auto r = c+2.f;
   
      auto openingArcDir = NVG_CW;
      auto closingArcDir = NVG_CCW;
   
      if (voltage < 0.f)
      {
         openingArcDir = NVG_CCW;
         closingArcDir = NVG_CW;
      }
   
      constexpr auto ARC_MAX = 5.f / 6.f * M_PI;
   
      nvgTranslate(vg, 0.f, box.size.y);
      nvgRotate(vg, -M_PI_2);
      nvgBeginPath(vg);
      nvgArc(vg, c, c, r, 0, ARC_MAX * voltage / 5.f, openingArcDir);
      nvgArc(vg, c, c, r+3.f, ARC_MAX * voltage / 5.f, 0, closingArcDir);
      nvgClosePath(vg);
      nvgFillColor(vg, nvgRGBA(12,166,78,200));
      nvgFill(vg);
   }

private:
   
   boundary::rack::Widget* _selectedParamWidget = nullptr;
   boundary::rack::Module* _module = nullptr;
   int _portId;
};

}
}
}
