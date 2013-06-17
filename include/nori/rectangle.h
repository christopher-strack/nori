#ifndef NORI_RECTANGLE_H_
#define NORI_RECTANGLE_H_

#include "nori/vector2.h"


namespace nori {

template<typename T>
class rectangle_t {
public:
    rectangle_t(T left, T top, T right, T bottom)
        : left(left), top(top), right(right), bottom(bottom)
    {
    }

    rectangle_t()
        : left(0), top(0), right(0), bottom(0)
    {
    }

    rectangle_t(const vector2<T>& position, const vector2<T>& size)
        : left(position.x), top(position.y),
        right(position.x + size.x), bottom(position.y + size.y)
    {
    }

    template<typename U>
    operator rectangle_t<U>() {
        return rectangle_t<U>(
            static_cast<U>(left), static_cast<U>(top),
            static_cast<U>(right), static_cast<U>(bottom));
    }

    bool operator==(const rectangle_t<T>& other) const {
      return left == other.left && top == other.top &&
          right == other.right && bottom == other.bottom;
    }

    bool operator!=(const rectangle_t<T>& other) const {
        return !operator==(other);
    }

    vector2<T> position() const {
        return vector2<T>(left, top);
    }

    vector2<T> size() const {
        return vector2<T>(right - left, bottom - top);
    }

    bool inside(const rectangle_t<T>& other) {
        return left >= other.left && top >= other.top
            && right <= other.right && bottom <= other.bottom;
    }

    T left, top, right, bottom;
};

typedef rectangle_t<int> rectangle;
typedef rectangle_t<float> rectangle_f;

} // namespace nori

#endif // NORI_RECTANGLE_H_
