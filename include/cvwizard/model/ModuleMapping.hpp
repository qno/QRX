#pragma once

#include <boundary/rack/Types.hpp>
#include <cvwizard/ui/HoveredWidget.hpp>

#include <memory>

namespace qrx {
namespace cvwizard {
namespace model {

using namespace boundary;

class ModuleMapping final
{
public:
   explicit ModuleMapping(rack::ModuleWidget* widget);
   ~ModuleMapping() noexcept = default;
   
   const rack::ModuleWidget* getModuleWidget() const;
   
   void enableHover();
   void disableHover();

private:
   
   rack::ModuleWidget* _moduleWidget = nullptr;
   std::unique_ptr<ui::HoveredWidget> _moduleOnHoverWidget = nullptr;
};

}
}
}
