#pragma once
#include <cmath>
#include <utils/stoej_math.h>

namespace stoej {
	inline float soft_sigmoid(float x)   { return std::tanhf(x); }
	inline double soft_sigmoid(double x) { return std::tanh(x);  }

	inline float medium_sigmoid(float x)   { return std::sqrtf(std::tanhf(x*x)) * std::copysign(1.0f, x); }
	inline double medium_sigmoid(double x) { return std::sqrt(std::tanh(x*x))   * std::copysign(1.0, x);  }

	inline float firm_sigmoid(float x)   { return std::sqrtf(std::sqrtf(std::tanhf(x*x*x*x))) * std::copysign(1.0f, x); }
	inline double firm_sigmoid(double x) { return std::sqrt(std::sqrt(std::tanh(x*x*x*x)))    * std::copysign(1.0, x);  }

	inline float symmetric_pow(float x, float a) { return std::pow(std::abs(x), a) * stoej::sign(x); }
	inline double symmetric_pow(double x, double a) { return std::pow(std::abs(x), a) * stoej::sign(x); }

	inline float asymmetric_pow(float x, float a) { return std::pow(std::abs(x), a); }
	inline double asymmetric_pow(double x, double a) { return std::pow(std::abs(x), a); }

    // TODO: fast approximations
}
