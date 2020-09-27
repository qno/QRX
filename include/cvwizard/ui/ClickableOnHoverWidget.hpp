#pragma once

#include <boundary/rack/Types.hpp>
#include <cvwizard/ui/AnimatedValue.hpp>

#include <sigslot/signal.hpp>

#include <functional>

namespace qrx {
namespace cvwizard {
namespace ui {

class ClickableOnHoverWidget final : public boundary::rack::OpaqueWidget, public AnimatedValue
{
public:
   
   explicit ClickableOnHoverWidget(boundary::rack::Widget* w)
      : _hoveredWidget{w}
   {
      box.size = _hoveredWidget->box.size;
   }
   
   ~ClickableOnHoverWidget() override
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
      boundary::rack::OpaqueWidget::draw(args);
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
   void onEnter(const boundary::rack::event::Enter& e) override
   {
   }
   
   void onLeave(const boundary::rack::event::Leave& e) override
   {
   }
   
   void onHover(const boundary::rack::event::Hover& e) override
   {
   }
   
   void onButton(const boundary::rack::event::Button& e) override
   {
      _onClickCallback(_hoveredWidget);
   }
   
   void onSelect(const boundary::rack::event::Select& e) override
   {
   }
   
   sigslot::connection connectOnClickCallback(std::function<void(boundary::rack::Widget*)> callback)
   {
      return _onClickCallback.connect(callback);
   }
   
private:
   
   boundary::rack::Widget* _hoveredWidget = nullptr;
   sigslot::signal<boundary::rack::Widget*> _onClickCallback;
};

}
}
}
