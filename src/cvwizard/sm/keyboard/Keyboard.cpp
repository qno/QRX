#include <cvwizard/sm/keyboard/Keyboard.hpp>

namespace qrx {
namespace cvwizard {
namespace sm {
namespace keyboard {

sigslot::signal<> Keyboard::_mappingActiveSignal;
sigslot::signal<> Keyboard::_idleSignal;

}
}
}
}

using namespace qrx::cvwizard::sm::keyboard;
FSM_INITIAL_STATE(Keyboard, Idle);
