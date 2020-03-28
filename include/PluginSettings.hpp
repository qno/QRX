#pragma once

namespace qrx {

class PluginSettings
{
public:
   
   static constexpr char const* SLUG = "QRX";
   
   PluginSettings() = default;
   virtual ~PluginSettings() = default;
   PluginSettings(const PluginSettings&) = delete;
   PluginSettings& operator= (const PluginSettings&) = delete;
  
   void load();
   void save() const;
};

}
