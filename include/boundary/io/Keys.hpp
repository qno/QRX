#pragma once

#include <GLFW/glfw3.h>
#include <widget/event.hpp>

namespace qrx::boundary::io::keys {

constexpr auto MOD_CTRL       = RACK_MOD_CTRL;
constexpr auto MOD_CTRL_NAME  = RACK_MOD_CTRL_NAME;
constexpr auto MOD_SHIFT_NAME = RACK_MOD_SHIFT_NAME;
constexpr auto MOD_ALT_NAME   = RACK_MOD_ALT_NAME;

constexpr auto ESCAPE = GLFW_KEY_ESCAPE;
constexpr auto M = GLFW_KEY_M;
constexpr auto T = GLFW_KEY_T;

}
