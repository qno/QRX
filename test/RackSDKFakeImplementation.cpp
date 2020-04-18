#include <rack.hpp>

extern "C" {
NVGcolor nvgRGB(unsigned char, unsigned char, unsigned char) { return {}; }
NVGcolor nvgRGBf(float, float, float){ return {}; }
NVGcolor nvgRGBAf(float, float, float, float) { return {}; }
NVGcolor nvgRGBA(unsigned char, unsigned char, unsigned char, unsigned char) { return {}; }

void nvgLineTo(NVGcontext*, float, float) { }
void nvgMoveTo(NVGcontext*, float, float) { }
void nvgLineCap(NVGcontext*, int) { }
void nvgLineJoin(NVGcontext*, int) { }
void nvgStrokeWidth(NVGcontext*, float) { }
void nvgStrokeColor(NVGcontext*, NVGcolor) { }
void nvgBeginPath(NVGcontext*) { }
void nvgStroke(NVGcontext*) { }
void nvgCircle(NVGcontext*, float, float, float) { }
void nvgPathWinding(NVGcontext*, int) { }
void nvgFillColor(NVGcontext*, NVGcolor) { }
void nvgFill(NVGcontext*) { }
void nvgRect(NVGcontext*, float, float, float, float) { }
void nvgTranslate(NVGcontext*, float, float) { }
void nvgRotate(NVGcontext*, float) { }
void nvgArc(NVGcontext*, float , float , float, float, float, int) { }
void nvgArcTo(NVGcontext*, float, float, float, float, float) { }
void nvgClosePath(NVGcontext*) { }
}

namespace rack {

App* appGet() { return{}; }

Window::Window() { }
Window::~Window() { }
std::shared_ptr<Svg> Window::loadSvg(const std::string&) { return{}; }
int Window::getMods() { return{}; }

namespace plugin {
Plugin::~Plugin() { }
void Plugin::addModel(Model*) { }
Model* Plugin::getModel(std::string) { return{}; }
}
namespace app {
ModuleWidget::ModuleWidget() { }
ModuleWidget::~ModuleWidget() { }
void ModuleWidget::setModule(engine::Module*) { }
void ModuleWidget::setPanel(std::shared_ptr<rack::Svg>) { }
void ModuleWidget::draw(const widget::Widget::DrawArgs&) { }
void ModuleWidget::onButton(const event::Button&) { }
void ModuleWidget::onHoverKey(const event::HoverKey&) { }
void ModuleWidget::onDragStart(const event::DragStart&) { }
void ModuleWidget::onDragEnd(const event::DragEnd&) { }
void ModuleWidget::onDragMove(const event::DragMove&) { }
json_t*  ModuleWidget::toJson() { return{}; }
void ModuleWidget::fromJson(json_t*) { }

void ParamWidget::step() { }
void ParamWidget::draw(const DrawArgs&) { }
void ParamWidget::onButton(const event::Button&) { }
void ParamWidget::onDoubleClick(const event::DoubleClick&) { }
void ParamWidget::onEnter(const event::Enter&) { }
void ParamWidget::onLeave(const event::Leave&) { }

PortWidget::PortWidget() { }
PortWidget::~PortWidget() { }
void PortWidget::step() { }
void PortWidget::draw(const DrawArgs&) { }
void PortWidget::onButton(const event::Button&) { }
void PortWidget::onEnter(const event::Enter&) { }
void PortWidget::onLeave(const event::Leave&) { }
void PortWidget::onDragStart(const event::DragStart&) { }
void PortWidget::onDragEnd(const event::DragEnd&) { }
void PortWidget::onDragDrop(const event::DragDrop&) { }
void PortWidget::onDragEnter(const event::DragEnter&) { }
void PortWidget::onDragLeave(const event::DragLeave&) { }

SvgScrew::SvgScrew() { }
void SvgScrew::setSvg(std::shared_ptr<rack::Svg>) { }

void Knob::onHover(const event::Hover&) { }
void Knob::onButton(const event::Button&) { }
void Knob::onDragStart(const event::DragStart&) { }
void Knob::onDragEnd(const event::DragEnd&) { }
void Knob::onDragMove(const event::DragMove&) { }
void Knob::reset() { }
void Knob::randomize() { }
}

namespace logger {
void log(Level level, const char* file, int line, const char* msg, ...)
{
   static constexpr const char* const levelLabels[] = {
      "debug",
      "info",
      "warn",
      "fatal"
   };
   va_list args1;
   va_start(args1, msg);
   va_list args2;
   va_copy(args2, args1);
   std::vector<char> buf(1+std::vsnprintf(nullptr, 0, msg, args1));
   va_end(args1);
   std::vsnprintf(buf.data(), buf.size(), msg, args2);
   va_end(args2);
   std::cout << "[FakeRackSDK (" << levelLabels[level] << ") " << file << ":" << line << "] " << buf.data() << std::endl;
}
}

namespace asset {
std::string plugin(plugin::Plugin*, std::string) { return{}; }
std::string user(std::string s) { return std::string{TOSTRING(QRX_UNITTESTS_ASSET_DIR)} + "/" + s; }
std::string system(std::string) { return{}; }
}

namespace engine {

Module::Module() { }
Module::~Module() { }
void Module::config(int, int, int, int) { }
json_t* Module::toJson() { return{}; }
}

namespace widget {
Widget::~Widget() { }
void Widget::step() { }
math::Rect Widget::getChildrenBoundingBox() { return{}; }
math::Vec Widget::getRelativeOffset(math::Vec, Widget*) { return{}; }
math::Rect Widget::getViewport(math::Rect) { return{}; }

void Widget::draw(const Widget::DrawArgs&) { }
void Widget::addChild(Widget*) { }
void Widget::removeChild(rack::widget::Widget*) { }
}

namespace ui {
void Tooltip::step() { }
void Tooltip::draw(const DrawArgs&) { }
}

}
