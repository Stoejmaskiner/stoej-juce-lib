#include <math.h>

float soft_sigmoid(float x)   { return std::tanhf(x); }
double soft_sigmoid(double x) { return std::tanh(x);  }

float soft_sigmoid(float x) {
    std::sqrtf(std::tanhf(x*x)) * 
}
