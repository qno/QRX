#include <CVWizard/CVWizardModule.hpp>
#include <CVWizard/CVWizardWidget.hpp>

rack::Model* modelCVWizard = rack::createModel<qrx::CVWizardModule, qrx::CVWizardWidget>(qrx::CVWizardModule::SLUG);
