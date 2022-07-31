#include <cmath>

namespace stoej {

    inline float sign(float x) { return std::copysign(1.0f, x); }
    inline double sign(double x) { return std::copysign(1.0, x); }

    // ref: https://stackoverflow.com/a/16659263
    inline float clamp(float x, float min, float max) {
        const float t = x < min ? min : x;
        return t > max ? max : t;
    }
    inline double clamp(double x, double min, double max) {
        const double t = x < min ? min : x;
        return t > max ? max : t;
    }

    inline float clamp_min(float x, float min) { return x < min ? min : x; }
    inline double clamp_min(double x, double min) { return x < min ? min : x; }

    inline float clamp_max(float x, float max) { return x > max ? max : x; }
    inline double clamp_max(double x, double max) { return x > max ? max : x; }

    inline float clamp_abs(float x, float limit) { return clamp(x, -limit, limit); }
    inline double clamp_abs(double x, double limit) { return clamp(x, -limit, limit); }

    inline float clamp_unity(float x) { return clamp(x, -1.f, 1.f); }
    inline double clamp_unity(double x) { return clamp(x, -1., 1.); }
}
