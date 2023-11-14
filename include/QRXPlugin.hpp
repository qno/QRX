#pragma once

#include <plugin/Plugin.hpp>
#include <plugin/Model.hpp>

// Declare the Plugin, defined in plugin.cpp
extern ::rack::plugin::Plugin* pluginInstance;

// Declare each Model, defined in each module source file
extern ::rack::plugin::Model* modelCVWizard;
