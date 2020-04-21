#pragma once

#include <boundary/rack/Types.hpp>
#include <cvwizard/ui/HoveredWidget.hpp>

#include <unordered_map>
#include <memory>

namespace qrx {
namespace cvwizard {
namespace model {

using namespace boundary;

class ModuleMapping final
{
//   using ParameterMappings = std::unordered_map<rack::ModuleWidget*, std::shared_ptr<ModuleMapping>>;

public:
   explicit ModuleMapping(rack::ModuleWidget* widget);
   ~ModuleMapping() noexcept = default;
   
   rack::ModuleWidget* getModuleWidget() const;
   
   void enableHover();
   void disableHover();

private:
   
   rack::ModuleWidget* _moduleWidget = nullptr;
   std::unique_ptr<ui::HoveredWidget> _moduleOnHoverWidget = nullptr;
   
   // _paramsMapping
};

}
}
}
