#pragma once

#include <cvwizard/model/ModuleMapping.hpp>
#include <cvwizard/ui/OnHoverWidget.hpp>
#include <cvwizard/ui/CVIndicatorWidget.hpp>

#include <unordered_map>
#include <memory>

namespace qrx {
namespace cvwizard {
namespace model {

using namespace boundary;

class CVWizardModel final
{
   using ModuleMappings = std::unordered_map<rack::ModuleWidget*, std::shared_ptr<ModuleMapping>>;
public:
   
   ~CVWizardModel() noexcept;
   
   void beginModuleMapping(rack::ModuleWidget* widget);
   void endModuleMapping();
   
   std::shared_ptr<ModuleMapping> getCurrentModuleMapping() const;

private:
   ModuleMappings _moduleMappings;
   std::shared_ptr<ModuleMapping> _currentModuleMapping = nullptr;
};

}
}
}
