#include <cvwizard/ui/Tooltip.hpp>
#include <boundary/io/Keys.hpp>

#include <locale>
#include <sstream>

namespace qrx {
namespace cvwizard {
namespace ui {

namespace {
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
      text << "Press '" << boundary::io::keys::MOD_CTRL_NAME;
      text << "-" << std::toupper(mappingKey, locale) << "' to activate Mapping mode";
      _startMappingText = text.str();
   }
   return _startMappingText;
}

std::string Tooltip::getMappingInputText()
{
   return std::string{"Mapping mode is active (Press 'Esc' to cancel).\nClick now on a module input!"};
}


}
}
}
