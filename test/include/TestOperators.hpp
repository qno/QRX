#pragma once

#include <rack.hpp>

namespace rack {
namespace engine {
inline bool operator== (const Module::ProcessArgs& lhs, const Module::ProcessArgs& rhs)
{
   return (lhs.sampleRate == rhs.sampleRate) && (lhs.sampleTime == rhs.sampleTime);
}
}
}
