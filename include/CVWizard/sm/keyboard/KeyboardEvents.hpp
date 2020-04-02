#pragma once

#include <tinyfsm.hpp>

namespace qrx {
namespace cvwizard {
namespace sm {
namespace keyboard {

struct ControlKeyEvent : public tinyfsm::Event
{ };

struct MappingKeyEvent : public tinyfsm::Event
{ };

struct MappingCancelKeyEvent : public tinyfsm::Event
{ };

struct MappingTooltipKeyEvent : public tinyfsm::Event
{ };

}
}
}
}
