#include <boost/sml.hpp>
#include <catch2/catch.hpp>
#include <iostream>

namespace sml = boost::sml;

struct WidgetControllable
{
   virtual void showTooltip() = 0;
   virtual void removeTooltip() = 0;
   virtual bool showTooltips() const = 0;
};

struct HoverEvent {};
struct LeaveEvent {};

// guards
const auto ifTooltipEnabled = [] (const WidgetControllable& w) { return w.showTooltips(); };

// actions
const auto showTooltip = [] (WidgetControllable& w) { w.showTooltip(); };
const auto removeTooltip = [] (WidgetControllable& w) { w.removeTooltip(); };

class Idle;

struct WidgetSM {
   auto operator()() const {
      return sml::make_transition_table(
         *sml::state<Idle> + sml::event<HoverEvent> [ifTooltipEnabled] / showTooltip = sml::state<Idle>,
          sml::state<Idle> + sml::event<LeaveEvent> [ifTooltipEnabled] / removeTooltip = sml::state<Idle>
      );
   }
};

struct Widget : public WidgetControllable
{
   void showTooltip() override
   {
      std::cout << "show onHover Tooltip" << std::endl;
   }
   
   void removeTooltip() override
   {
      std::cout << "remove onHover Tooltip" << std::endl;
   }
   
   bool showTooltips() const override
   {
      return _showTooltips == true;
   }
   
   void onHover()
   {
      _sm->process_event(HoverEvent{});
   }
   
   void onLeave()
   {
      _sm->process_event(LeaveEvent{});
   }
   
   Widget()
   {
      WidgetControllable& wc{*this};
      _sm = std::make_unique<sml::sm<WidgetSM>>(wc);
   }
   
   bool _showTooltips = false;
   
private:
   std::unique_ptr<sml::sm<WidgetSM>> _sm;
};


TEST_CASE("Sml playground", "[xxx]")
{
   Widget w{};
   w._showTooltips = true;
   w.onHover();
   w.onLeave();
}
