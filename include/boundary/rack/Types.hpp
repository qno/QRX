#pragma once

#include <widget/event.hpp>
#include <app/Scene.hpp>
#include <window/Window.hpp>
#include <engine/Module.hpp>
#include <widget/Widget.hpp>
#include <widget/TransparentWidget.hpp>
#include <app/ModuleWidget.hpp>
#include <app/ParamWidget.hpp>
#include <app/PortWidget.hpp>
#include <app/Knob.hpp>
#include <ui/Tooltip.hpp>
#include <logger.hpp>

namespace qrx {
namespace boundary {
namespace rack {

using State = ::rack::widget::EventState;
using Scene = ::rack::app::Scene;
using Window = ::rack::window::Window;

using Module = ::rack::engine::Module;
using Widget = ::rack::widget::Widget;
using OpaqueWidget = ::rack::widget::OpaqueWidget;
using TransparentWidget = ::rack::widget::TransparentWidget;
using ModuleWidget = ::rack::app::ModuleWidget;
using ParamWidget = ::rack::app::ParamWidget;
using PortWidget = ::rack::app::PortWidget;
using Knob = ::rack::app::Knob;
using Port = ::rack::engine::Port;

namespace ui {
using Tooltip = ::rack::ui::Tooltip;
}

namespace engine {
using ProcessArgs = ::rack::engine::Module::ProcessArgs;
}

namespace widget {
using DrawArgs = ::rack::widget::Widget::DrawArgs;
}

namespace event {
using Enter = ::rack::event::Enter;
using Leave = ::rack::event::Leave;
using Hover = ::rack::event::Hover;
using Button = ::rack::event::Button;
using Select = ::rack::event::Select;
}

namespace logger = ::rack::logger;

}
}
}
