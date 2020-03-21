#include <CVWizard/CVWizardModule.hpp>

using namespace rack;

namespace qrx {

CVWizardModule::CVWizardModule()
   : Module()
{
   config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
}

void CVWizardModule::process(const ProcessArgs& args)
{

}

json_t* CVWizardModule::dataToJson()
{
   auto json = new json_t{};
   
   return json;
}

void CVWizardModule::dataFromJson(json_t* root)
{

}

}
