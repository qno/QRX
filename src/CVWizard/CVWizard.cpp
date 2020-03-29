#include <CVWizard/CVWizardModule.hpp>
#include <CVWizard/CVWizardWidget.hpp>

using namespace qrx::cvwizard;

rack::Model* modelCVWizard = rack::createModel<CVWizardModule, CVWizardWidget>(CVWizardModule::SLUG);
