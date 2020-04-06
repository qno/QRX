#pragma once

#include <string>

namespace qrx {
namespace cvwizard {
namespace ui {

class Tooltip
{
public:

#ifdef ARCH_MAC
   static constexpr char const* MOD_KEY = "Cmd";
#else
   static constexpr char const* MOD_KEY = "Ctrl";
#endif
   
   static std::string getStartMappingText(const char mappingKey);
   
private:
   static char _mappingKey;
   static std::string _startMappingText;
};

}
}
}
