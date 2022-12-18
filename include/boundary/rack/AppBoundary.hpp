#pragma once

#include <boundary/rack/Types.hpp>

namespace qrx::boundary::rack {

class AppBoundary
{
public:
   virtual State* getEventState() const = 0;
   virtual Scene* getScene() const = 0;
   virtual Window* getWindow() const = 0;
   
   virtual bool isKeyPressed(const int keyCode) const = 0;
   virtual bool isModKeyPressed(const int modKeyCode) const = 0;
};

}
