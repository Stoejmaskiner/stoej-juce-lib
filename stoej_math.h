#include <cmath>

namespace stoej {

    float sign(float x)   { return std::copysign(1.0f, x); }
    double sign(double x) { return std::copysign(1.0, x);  }

    // ref: https://stackoverflow.com/a/16659263
    float clamp(float x, float min, float max) {
        const float t = x < min ? min : x;
        return t > max ? max : t;
    }
    double clamp(double x, double min, double max) {
        const double t = x < min ? min : x;
        return t > max ? max : t;
    }
}
