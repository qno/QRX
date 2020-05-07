#pragma once

#include <chrono>
#include <cmath>

namespace qrx {
namespace cvwizard {
namespace ui {

class AnimatedValue
{
public:
   ~AnimatedValue() = default;

protected:
   AnimatedValue() = default;
   
   void animate()
   {
      // https://stackoverflow.com/questions/14391327/how-to-get-duration-as-int-millis-and-float-seconds-from-chrono
      // https://gafferongames.com/post/fix_your_timestep
      const auto elapsed = std::chrono::steady_clock::now() - _start;
      const auto seconds = std::chrono::duration_cast<std::chrono::duration<float>>(elapsed).count();
   
      const auto x = (seconds * AnimationSpeed);
      const auto value = ((1.f + std::sin(x))/2.f * 255.f);
      
      if (value < 75.f)
      {
         _value = 75;
      }
      else
      {
         _value = static_cast<unsigned char>(value);
      }
   }
   
   static constexpr float AnimationSpeed = 2.f;
   unsigned char _value = 0;
   const std::chrono::time_point<std::chrono::steady_clock> _start = std::chrono::steady_clock::now();
};

}
}
}
