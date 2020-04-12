#pragma once

namespace qrx {
namespace cvwizard {
namespace ui {

class OnHoverWidget : public rack::TransparentWidget
{
public:
   
   OnHoverWidget(Widget* w)
   {
      _hoveredWidget = w;
      box.size = _hoveredWidget->box.size;
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
      nvgFillColor(vg, nvgRGBA(255, 0, 0, 200));
      nvgFill(vg);
   }

private:
   Widget* _hoveredWidget;
};

}
}
}
