#include <rack.hpp>

extern "C" {

int glfwGetKey(GLFWwindow*, int) { return {}; }

NVGcolor nvgRGB(unsigned char, unsigned char, unsigned char) { return {}; }
NVGcolor nvgRGBf(float, float, float){ return {}; }
NVGcolor nvgRGBAf(float, float, float, float) { return {}; }
NVGcolor nvgRGBA(unsigned char, unsigned char, unsigned char, unsigned char) { return {}; }
}

namespace rack {

App* appGet() { return{}; }

Window::Window() { }
Window::~Window() { }
std::shared_ptr<Svg> Window::loadSvg(const std::string&) { return{}; }
int Window::getMods() { return{}; }

namespace plugin {
Plugin::~Plugin()
{ }
void Plugin::addModel(Model* model)
{ models.push_back(model); }
Model* Plugin::getModel(std::string slug)
{
   for (auto m : models)
   {
      if (m->slug == slug)
      {
         return m;
      }
   }
   return nullptr;
}
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

SvgScrew::SvgScrew() { }
void SvgScrew::setSvg(std::shared_ptr<rack::Svg>) { }
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
}

}
