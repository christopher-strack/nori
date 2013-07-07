#ifndef NORI_VECTOR2_H_
#define NORI_VECTOR2_H_

#include <stdexcept>


namespace nori {

template<typename T>
class vector2 {
public:
    vector2();
    vector2(T x, T y);

    vector2(const vector2<T>& other);
    vector2<T>& operator=(const vector2<T>& other);

    template<typename U>
    vector2(const vector2<U>& other)
        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))
    {
    }

    bool operator==(const vector2<T>& other) const;
    bool operator!=(const vector2<T>& other) const;

    T& operator[](int index);
    T operator[](int index) const;

    vector2<T> operator+(const vector2<T>& other) const;
    vector2<T> operator-(const vector2<T>& other) const;

    vector2<T> operator*(T scalar) const;
    vector2<T> operator/(T scalar) const;

    T x;
    T y;
};

typedef vector2<int> size;
typedef vector2<int> point;
typedef vector2<float> point_f;
typedef vector2<float> size_f;


template<typename T>
vector2<T>::vector2() : x(0), y(0) {
}

template<typename T>
vector2<T>::vector2(T x, T y) : x(x), y(y) {
}

template<typename T>
vector2<T>::vector2(const vector2<T>& other) {
    operator=(other);
}

template<typename T>
vector2<T>& vector2<T>::operator=(const vector2<T>& other) {
    x = other.x;
    y = other.y;
    return *this;
}

template<typename T>
bool nori::vector2<T>::operator==(const vector2<T>& other) const {
    return x == other.x && y == other.y;
}

template<typename T>
bool nori::vector2<T>::operator!=(const vector2<T>& other) const {
    return !operator==(other);
}

template<typename T>
T& nori::vector2<T>::operator[](int index) {
    if (index < 0 || index > 1) {
        throw std::out_of_range("Invalid element access.");
    }
    return index == 0 ? x : y;
}

template<typename T>
T nori::vector2<T>::operator[](int index) const {
    if (index < 0 || index > 1) {
        throw std::out_of_range("Invalid element access.");
    }
    return index == 0 ? x : y;
}

template<typename T>
vector2<T> nori::vector2<T>::operator+(const vector2<T>& other) const {
    return vector2<T>(x + other.x, y + other.y);
}

template<typename T>
vector2<T> nori::vector2<T>::operator-(const vector2<T>& other) const {
    return vector2<T>(x - other.x, y - other.y);
}

template<typename T>
vector2<T> nori::vector2<T>::operator*(T scalar) const {
    return vector2<T>(x * scalar, y * scalar);
}

template<typename T>
vector2<T> nori::vector2<T>::operator/(T scalar) const {
    return vector2<T>(x / scalar, y / scalar);
}

} // namespace nori


#endif // NORI_VECTOR2_H_
