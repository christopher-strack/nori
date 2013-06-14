#ifndef NORI_RECTANGLE_H_
#define NORI_RECTANGLE_H_

#include "nori/vector2.h"


namespace nori {

template<typename T>
class rectangle_t {
public:
    rectangle_t(const vector2<T>& position, const vector2<T>& size)
        : left(position.x),
          top(position.y),
          right(position.x + size.x),
          bottom(position.y + size.y)
    {
    }

    T left, top, right, bottom;
};

typedef rectangle_t<int> rectangle;
typedef rectangle_t<float> rectangle_f;

} /* namespace nori */

#endif /* NORI_RECTANGLE_H_ */
