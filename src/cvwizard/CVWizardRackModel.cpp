#include <cvwizard/CVWizardModule.hpp>
#include <cvwizard/CVWizardWidget.hpp>
#include <PluginSettings.hpp>

#include <helpers.hpp>

#include <memory>

using namespace qrx::cvwizard;

auto pluginSettings = std::make_shared<qrx::PluginSettings>();
::rack::plugin::Model* modelCVWizard = ::rack::createModel<CVWizardModule, CVWizardWidget>(CVWizardModule::SLUG);
