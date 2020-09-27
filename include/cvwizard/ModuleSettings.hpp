#pragma once

#include <boundary/io/Keys.hpp>

namespace qrx {
namespace cvwizard {

using namespace boundary;

class ModuleSettings
{
protected:
   static constexpr char const* MappingKey          = "MappingKey";
   static constexpr char const* MappingTooltipKey   = "MappingTooltipKey";
   static constexpr char const* ShowMappingTooltips = "ShowMappingTooltips";

public:
   
   struct Settings
   {
      int  MappingKey          = io::keys::M;
      int  MappingTooltipKey   = io::keys::T;
      bool ShowMappingTooltips = true;
      
      bool operator== (const Settings& other) const
      {
         return MappingKey == other.MappingKey &&
                MappingTooltipKey == other.MappingTooltipKey &&
                ShowMappingTooltips == other.ShowMappingTooltips;
      }
   };
   
   ModuleSettings() = default;
   virtual ~ModuleSettings() = default;
   ModuleSettings(const ModuleSettings&) = delete;
   ModuleSettings& operator=(const ModuleSettings&) = delete;
   
   virtual Settings getSettings() = 0;
   virtual void dumpSettings(const Settings& settings) = 0;
};

}
}
