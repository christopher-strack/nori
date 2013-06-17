#include "nori/matrix4.h"

#include <algorithm>


namespace nori {

matrix4::matrix4()
{
    std::fill(elements, elements+16, 0.0f);
}

matrix4::matrix4(float elements_[16]) {
    std::copy(elements_, elements_ + 16, elements);
}

matrix4 matrix4::make_orthogonal(const size& size) {
    float ratioX = 2.0f / (float)size.x;
    float ratioY = 2.0f / (float)size.y;

    float elements[] = {
      ratioX,    0.0f, 0.0f,   -1,
        0.0f, -ratioY, 0.0f,    1,
        0.0f,    0.0f, 1.0f, 0.0f,
        0.0f,    0.0f, 0.0f, 1.0f
    };

    return matrix4(elements);
}

} // namespace nori
