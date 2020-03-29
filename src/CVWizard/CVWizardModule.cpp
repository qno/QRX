#include <CVWizard/CVWizardModule.hpp>

using namespace rack;

namespace qrx {
namespace cvwizard {

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
   auto json = json_object();
   
   json_object_set_new(json, "param1", json_string("0815"));
   json_object_set_new(json, "param2", json_integer(2));
   json_object_set_new(json, "param3", json_boolean(true));
   
   return json;
}

void CVWizardModule::dataFromJson(json_t* root)
{

}

}
}
