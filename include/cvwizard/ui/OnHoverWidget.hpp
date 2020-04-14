#pragma once

#include <widget/TransparentWidget.hpp>

#include <chrono>
#include <cmath>

namespace qrx {
namespace cvwizard {
namespace ui {

class OnHoverWidget final : public rack::TransparentWidget
{
public:
   
   OnHoverWidget(Widget* w)
      : _hoveredWidget{w}
   {
      box.size = _hoveredWidget->box.size;
   }
   
   ~OnHoverWidget()
   {
      if (_hoveredWidget)
      {
         _hoveredWidget->removeChild(this);
      }
   }
   
   void step() override
   {
      // https://stackoverflow.com/questions/14391327/how-to-get-duration-as-int-millis-and-float-seconds-from-chrono
      // https://gafferongames.com/post/fix_your_timestep
      const auto elapsed = std::chrono::steady_clock::now() - _start;
      const auto seconds = std::chrono::duration_cast<std::chrono::duration<float>>(elapsed).count();
   
      const auto x = (seconds * AlphaSpeed);
      const auto alpha = ((1.f + std::sin(x))/2.f * 255.f);
      
      if (alpha < 75.f)
      {
         _alpha = 75;
      }
      else
      {
         _alpha = static_cast<unsigned char>(alpha);
      }
   }
   
   void draw(const DrawArgs& args) override
   {
      TransparentWidget::draw(args);
      auto vg = args.vg;
      const auto v = box.size.x / 2.f;
      nvgBeginPath(vg);
      nvgCircle(vg, v, v, v + 3.f);
      nvgCircle(vg, v, v, v);
      nvgPathWinding(vg, NVG_HOLE);
      nvgFillColor(vg, nvgRGBA(255, 0, 0, _alpha));
      nvgFill(vg);
   }

private:
   
   static constexpr float AlphaSpeed = 2.f;
   unsigned char _alpha = 0;
   
   Widget* _hoveredWidget = nullptr;
   const std::chrono::time_point<std::chrono::steady_clock> _start = std::chrono::steady_clock::now();
};

}
}
}
