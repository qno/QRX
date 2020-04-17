#pragma once

#include <boundary/rack/Types.hpp>

namespace qrx {
namespace boundary {
namespace rack {

class AppBoundary
{
public:
   virtual State* getEventState() const = 0;
   virtual Scene* getScene() const = 0;
   virtual Window* getWindow() const = 0;
};

}
}
}
