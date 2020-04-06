#include <cvwizard/ui/Tooltip.hpp>

#include <locale>
#include <sstream>

namespace qrx {
namespace cvwizard {
namespace ui {

namespace {

#ifdef ARCH_MAC
static constexpr char const* MOD_KEY = "Cmd";
#else
static constexpr char const* MOD_KEY = "Ctrl";
#endif

std::locale locale;

}

char Tooltip::_mappingKey = 0;
std::string Tooltip::_startMappingText = std::string{};

std::string Tooltip::getStartMappingText(const char mappingKey)
{
   if (_mappingKey != mappingKey)
   {
      _mappingKey = mappingKey;
      auto text = std::stringstream{};
      text << "Press '" << MOD_KEY;
      text << "-" << std::toupper(mappingKey, locale) << "' to activate Mapping mode";
      _startMappingText = text.str();
   }
   return _startMappingText;
}

}
}
}
