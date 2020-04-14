#pragma once

#include <widget/TransparentWidget.hpp>

#include <chrono>
#include <cmath>

namespace qrx {
namespace cvwizard {
namespace ui {

class CVIndicatorWidget final : public rack::TransparentWidget
{
public:
   
   CVIndicatorWidget(rack::Widget* w, rack::Module* module, int portId)
      : _selectedParamWidget{w}
      , _module{module}
      , _portId{portId}
   {
      box.size = _selectedParamWidget->box.size;
   }
   
   ~CVIndicatorWidget()
   {
      if (_selectedParamWidget)
      {
         _selectedParamWidget->removeChild(this);
      }
   }
   
   void step() override
   {
   }
   
   void draw(const DrawArgs& args) override
   {
      TransparentWidget::draw(args);
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
      nvgFillColor(vg, nvgRGBA(0,255,0,200));
      nvgFill(vg);
   }

private:
   
   rack::Widget* _selectedParamWidget = nullptr;
   rack::Module* _module = nullptr;
   int _portId;
};

}
}
}
