#include <math.h>

float soft_sigmoid(float x)   { return std::tanhf(x); }
double soft_sigmoid(double x) { return std::tanh(x);  }

float medium_sigmoid(float x)   { return std::sqrtf(std::tanhf(x*x)) * std::copysign(1.0f, x); }
double medium_sigmoid(double x) { return std::sqrt(std::tanh(x*x))   * std::copysign(1.0, x);  }

float firm_sigmoid(float x)   { return std::sqrtf(std::sqrtf(std::tanhf(x*x*x*x))) * std::copysign(1.0f, x); }
double firm_sigmoid(double x) { return std::sqrt(std::sqrt(std::tanh(x*x*x*x)))    * std::copysign(1.0, x);  }

