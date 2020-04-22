#include <cvwizard/model/CVWizardModel.hpp>

namespace qrx {
namespace cvwizard {
namespace model {

using namespace boundary::rack;

CVWizardModel::~CVWizardModel()
{
}

void CVWizardModel::beginModuleMapping(rack::ModuleWidget* widget)
{
   auto existingMapping = _moduleMappings.find(widget);
   if (_moduleMappings.end() != existingMapping)
   {
      _currentModuleMapping = existingMapping->second;
   }
   else
   {
      _currentModuleMapping = std::make_shared<ModuleMapping>(widget);
   }
   _currentModuleMapping->enableHover();
}

void CVWizardModel::endModuleMapping()
{
   _currentModuleMapping->disableHover();
   // if param mappings has been added do
   //_moduleMappings.insert(std::make_pair(widget, _currentModuleMapping));
   _currentModuleMapping = nullptr;
}

std::shared_ptr<ModuleMapping> CVWizardModel::getCurrentModuleMapping() const
{
   return _currentModuleMapping;
}

}
}
}
