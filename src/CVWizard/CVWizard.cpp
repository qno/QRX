#include <CVWizard/CVWizardModule.hpp>
#include <CVWizard/CVWizardWidget.hpp>
#include <PluginSettings.hpp>
using namespace qrx::cvwizard;

auto pluginSettings = std::make_shared<qrx::PluginSettings>();
rack::Model* modelCVWizard = rack::createModel<CVWizardModule, CVWizardWidget>(CVWizardModule::SLUG);
