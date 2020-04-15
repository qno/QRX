#pragma once

#include <event.hpp>
#include <app/Scene.hpp>
#include <window.hpp>

namespace qrx {
namespace boundary {

class RackAppBoundary
{
public:
   virtual rack::event::State* getEventState() const = 0;
   virtual rack::app::Scene* getScene() const = 0;
   virtual rack::Window* getWindow() const = 0;
};

}
}
