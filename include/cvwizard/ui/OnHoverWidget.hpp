#pragma once

#include <widget/TransparentWidget.hpp>

#include <chrono>

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
   
   void draw(const DrawArgs& args) override
   {
      // https://stackoverflow.com/questions/14391327/how-to-get-duration-as-int-millis-and-float-seconds-from-chrono
      const auto elapsed = std::chrono::steady_clock::now() - _start;
      const auto seconds = std::chrono::duration_cast<std::chrono::duration<float>>(elapsed).count();
      
      constexpr auto alphaSpeed = 200.f;
      const auto alpha = static_cast<char>((seconds*alphaSpeed))%255;
      
      TransparentWidget::draw(args);
      auto vg = args.vg;
      const auto v = box.size.x / 2.f;
      nvgBeginPath(vg);
      nvgCircle(vg, v, v, v + 3.f);
      nvgCircle(vg, v, v, v);
      nvgPathWinding(vg, NVG_HOLE);
      nvgFillColor(vg, nvgRGBA(255, 0, 0, alpha));
      nvgFill(vg);
   }

private:
   Widget* _hoveredWidget = nullptr;
   const std::chrono::time_point<std::chrono::steady_clock> _start = std::chrono::steady_clock::now();
};

}
}
}
