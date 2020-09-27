#pragma once

#include <boundary/rack/Types.hpp>
#include <cvwizard/ui/AnimatedValue.hpp>

namespace qrx {
namespace cvwizard {
namespace ui {

class OnHoverWidget final : public boundary::rack::TransparentWidget, public AnimatedValue
{
public:
   
   explicit OnHoverWidget(boundary::rack::Widget* w)
      : _hoveredWidget{w}
   {
      box.size = _hoveredWidget->box.size;
   }
   
   ~OnHoverWidget() override
   {
      if (_hoveredWidget)
      {
         _hoveredWidget->removeChild(this);
      }
   }
   
   void step() override
   {
      animate();
   }
   
   void draw(const boundary::rack::widget::DrawArgs& args) override
   {
      boundary::rack::TransparentWidget::draw(args);
      auto vg = args.vg;
      
      if (std::abs(box.size.x - box.size.y) < 5.f)
      {
         const auto v = box.size.x / 2.f;
         nvgBeginPath(vg);
         nvgCircle(vg, v, v, v + 3.f);
         nvgCircle(vg, v, v, v);
         nvgPathWinding(vg, NVG_HOLE);
         nvgFillColor(vg, nvgRGBA(255, 0, 0, _value));
         nvgFill(vg);
      }
      else
      {
         nvgLineCap(vg, NVG_ROUND);
         nvgLineJoin(vg, NVG_BEVEL);
         nvgStrokeWidth(vg, 5.f);
         nvgStrokeColor(vg, nvgRGBA(255, 0, 0, _value));
         nvgBeginPath(vg);
         nvgMoveTo(vg, 0, 0);
         nvgLineTo(vg, box.size.x, 0);
         nvgMoveTo(vg, box.size.x, 0);
         nvgLineTo(vg, box.size.x, box.size.y);
         nvgMoveTo(vg, box.size.x, box.size.y);
         nvgLineTo(vg, 0, box.size.y);
         nvgMoveTo(vg, 0, box.size.y);
         nvgLineTo(vg, 0, 0);
         nvgStroke(vg);
      }
   }

private:
   
   boundary::rack::Widget* _hoveredWidget = nullptr;
};

}
}
}
