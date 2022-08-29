#include <cmath>
#include <utils/stoej_math.h>

namespace stoej {
    float soft_sigmoid(float x)   { return std::tanhf(x); }
    double soft_sigmoid(double x) { return std::tanh(x);  }

    float medium_sigmoid(float x)   { return std::sqrtf(std::tanhf(x*x)) * std::copysign(1.0f, x); }
    double medium_sigmoid(double x) { return std::sqrt(std::tanh(x*x))   * std::copysign(1.0, x);  }

    float firm_sigmoid(float x)   { return std::sqrtf(std::sqrtf(std::tanhf(x*x*x*x))) * std::copysign(1.0f, x); }
    double firm_sigmoid(double x) { return std::sqrt(std::sqrt(std::tanh(x*x*x*x)))    * std::copysign(1.0, x);  }

    float bipolar_pow(float x, float a) { return std::pow(std::abs(x), a) * stoej::sign(x); }
    double bipolar_pow(double x, double a) { return std::pow(std::abs(x), a) * stoej::sign(x); }

    float rectified_pow(float x, float a) { return std::pow(std::abs(x), a); }
    double rectified_pow(double x, double a) { return std::pow(std::abs(x), a); }

    // TODO: fast approximations
}
