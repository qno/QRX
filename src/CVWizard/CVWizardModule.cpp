#include <CVWizard/CVWizardModule.hpp>

using namespace rack;

namespace qrx {

CVWizardModule::CVWizardModule()
    : Module() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
}

void CVWizardModule::process(const ProcessArgs& args) {

}

}
