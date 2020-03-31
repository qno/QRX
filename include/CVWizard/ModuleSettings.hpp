#pragma once

namespace qrx {
namespace cvwizard {

class ModuleSettings
{
protected:
   // correspond to GLFW_KEY values
   static constexpr int KEY_M   = 77;
   static constexpr int KEY_T   = 84;
   static constexpr int KEY_ESC = 256;
   
   static constexpr char const* MappingKey          = "MappingKey";
   static constexpr char const* MappingCancelKey    = "MappingCancelKey";
   static constexpr char const* MappingTooltipKey   = "MappingTooltipKey";
   static constexpr char const* ShowMappingTooltips = "ShowMappingTooltips";

public:
   
   struct Settings
   {
      int  MappingKey          = KEY_M;
      int  MappingCancelKey    = KEY_ESC;
      int  MappingTooltipKey   = KEY_T;
      bool ShowMappingTooltips = true;
      
      bool operator== (const Settings& other) const
      {
         return MappingKey == other.MappingKey &&
                MappingCancelKey == other.MappingCancelKey &&
                MappingTooltipKey == other.MappingTooltipKey &&
                ShowMappingTooltips == other.ShowMappingTooltips;
      }
   };
   
   ModuleSettings() = default;
   virtual ~ModuleSettings() = default;
   ModuleSettings(const ModuleSettings&) = delete;
   ModuleSettings& operator=(const ModuleSettings&) = delete;
   
   virtual Settings getCVWizardSettings() = 0;
   virtual void dumpSettings(const Settings& settings) = 0;
};

}
}
