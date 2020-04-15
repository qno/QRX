#pragma once

#include <boundary/RackAppBoundary.hpp>
#include <app.hpp>

namespace qrx {

class RackApp final : public boundary::RackAppBoundary
{
public:
   rack::event::State* getEventState() const override;
   rack::app::Scene* getScene() const override;
   rack::Window* getWindow() const override;
};

}
