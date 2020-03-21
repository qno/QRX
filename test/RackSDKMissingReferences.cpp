#include <rack.hpp>

extern "C" {

int glfwGetKey(GLFWwindow* window, int key) { return {}; }

NVGcolor nvgRGB(unsigned char r, unsigned char g, unsigned char b) { return {}; }
NVGcolor nvgRGBf(float r, float g, float b){ return {}; }
NVGcolor nvgRGBAf(float r, float g, float b, float a) { return {}; }
NVGcolor nvgRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a) { return {}; }
}

namespace rack {

struct App;
App* appGet() { return{}; }

//rack::Window::loadSvg(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)'
//rack::Window::getMods()'
//undefined reference to `pluginInstance'

namespace app {
//rack::app::ModuleWidget::ModuleWidget()'
//rack::app::ModuleWidget::~ModuleWidget()'
//rack::app::ModuleWidget::setModule(rack::engine::Module*)'
//rack::app::ModuleWidget::setPanel(std::shared_ptr<rack::Svg>)'
//rack::app::ModuleWidget::draw(rack::widget::Widget::DrawArgs const&)'
//rack::app::SvgScrew::SvgScrew()'
//rack::app::SvgScrew::setSvg(std::shared_ptr<rack::Svg>)'
//rack::app::ModuleWidget::onButton(rack::event::Button const&)'
//rack::app::ModuleWidget::onHoverKey(rack::event::HoverKey const&)'
//rack::app::ModuleWidget::onDragStart(rack::event::DragStart const&)'
//rack::app::ModuleWidget::onDragEnd(rack::event::DragEnd const&)'
//rack::app::ModuleWidget::onDragMove(rack::event::DragMove const&)'
//rack::app::ModuleWidget::toJson()'
//rack::app::ModuleWidget::fromJson(json_t*)'
}

namespace logger {
//rack::logger::log(rack::logger::Level, char const*, int, char const*, ...)'
}

namespace asset {
//rack::asset::plugin(rack::plugin::Plugin*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)'
}

namespace engine {

Module::Module() { }
Module::~Module() { }
void Module::config(int, int, int, int) { }
}

namespace widget {
//rack::widget::Widget::step()'
//rack::widget::Widget::~Widget()'
//rack::widget::Widget::getChildrenBoundingBox()'
//rack::widget::Widget::getRelativeOffset(rack::math::Vec, rack::widget::Widget*)'
//rack::widget::Widget::getViewport(rack::math::Rect)'
//rack::widget::Widget::draw(rack::widget::Widget::DrawArgs const&)'
//rack::widget::Widget::addChild(rack::widget::Widget*)'
}

}
