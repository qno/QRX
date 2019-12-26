#pragma once

#include <QRXPlugin.hpp>

namespace qrx {

class CVWizardModule : public rack::Module {
 public:
  
  enum ParamIds {
    NUM_PARAMS
  };
  
  enum InputIds {
    NUM_INPUTS
  };
  
  enum OutputIds {
    NUM_OUTPUTS
  };
  
  enum LightIds {
    NUM_LIGHTS
  };
  
  CVWizardModule();
  
  virtual ~CVWizardModule() = default;
  
  void process(const ProcessArgs& args) override;
};

}
