#pragma once

namespace qrx {
namespace cvwizard {
namespace controller {

class KeyboardEventsProviding
{
public:
   virtual bool isControlKeyPressed () const = 0;
   virtual bool isMappingKeyPressed () const = 0;
   virtual bool isMappingCancelKeyPressed () const = 0;
   virtual bool isTooltipKeyPressed () const = 0;
};

}
}
}
