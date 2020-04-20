#include <cvwizard/model/CVWizardModel.hpp>
#include <app/ModuleWidget.hpp>

namespace qrx {
namespace cvwizard {
namespace model {

using namespace boundary::rack;

CVWizardModel::~CVWizardModel()
{
}

void CVWizardModel::beginModuleMapping(rack::ModuleWidget* widget)
{
   _currentModuleMapping = std::make_shared<ModuleMapping>(widget);
   _moduleMappings.insert(std::make_pair(widget, _currentModuleMapping));
}

void CVWizardModel::endModuleMapping()
{
   _currentModuleMapping->disableHover();
}

std::shared_ptr<ModuleMapping> CVWizardModel::getCurrentModuleMapping() const
{
   return _currentModuleMapping;
}

}
}
}
