#pragma once

#include <string>

namespace qrx {
namespace cvwizard {
namespace ui {

class Tooltip
{
public:
   static std::string getStartMappingText(const char mappingKey);
   
private:
   static char _mappingKey;
   static std::string _startMappingText;
};

}
}
}
