#include <cvwizard/CVWizardModule.hpp>
#include <cvwizard/CVWizardWidget.hpp>
#include <PluginSettings.hpp>
#include <RackApp.hpp>

#include <memory>

using namespace qrx::cvwizard;

std::shared_ptr<qrx::boundary::RackAppBoundary> rackApp = std::make_shared<qrx::RackApp>();
auto pluginSettings = std::make_shared<qrx::PluginSettings>();
rack::Model* modelCVWizard = rack::createModel<CVWizardModule, CVWizardWidget>(CVWizardModule::SLUG);
