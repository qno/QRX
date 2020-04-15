#include <RackApp.hpp>

namespace qrx {

rack::event::State* RackApp::getEventState() const { return APP->event; }

rack::app::Scene* RackApp::getScene() const { return APP->scene; }

rack::Window* RackApp::getWindow() const { return APP->window; }

}
