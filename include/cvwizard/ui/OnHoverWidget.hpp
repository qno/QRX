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
      nvgLineCap(vg, NVG_BUTT);
      nvgLineJoin(vg, NVG_BEVEL);
      nvgStrokeWidth(vg, 3.0f);
      nvgStrokeColor(vg, nvgRGBA(255, 0, 0, 255));
      nvgBeginPath(vg);
      nvgLineTo(vg, box.pos.x + box.size.x, box.pos.y + box.size.y);
      nvgMoveTo(vg, 0, 0);
      nvgLineTo(vg, box.size.x, box.size.y);
      nvgMoveTo(vg, box.size.x, 0);
      nvgLineTo(vg, 0, box.size.y);
      nvgStroke(vg);
   }

private:
   Widget* _hoveredWidget;
};

}
}
}
