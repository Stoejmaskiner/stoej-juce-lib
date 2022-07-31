#include <cmath>
#include <stoej_math.hpp>

namespace stoej {
    float soft_sigmoid(float x)   { return std::tanhf(x); }
    double soft_sigmoid(double x) { return std::tanh(x);  }

    float medium_sigmoid(float x)   { return std::sqrtf(std::tanhf(x*x)) * std::copysign(1.0f, x); }
    double medium_sigmoid(double x) { return std::sqrt(std::tanh(x*x))   * std::copysign(1.0, x);  }

    float firm_sigmoid(float x)   { return std::sqrtf(std::sqrtf(std::tanhf(x*x*x*x))) * std::copysign(1.0f, x); }
    double firm_sigmoid(double x) { return std::sqrt(std::sqrt(std::tanh(x*x*x*x)))    * std::copysign(1.0, x);  }

    float unity_clamp(float x)   { return stoej::clamp(x, -1.0f, 1.0f); }
    double unity_clamp(double x) { return stoej::clamp(x, -1.0, 1.0);   }
}
