#ifndef NORI_VECTOR2_H_
#define NORI_VECTOR2_H_


namespace nori {

template<typename T>
class vector2 {
public:
    vector2();
    vector2(T x, T y);

    vector2(const vector2<T>& other);
    vector2<T>& operator=(const vector2<T>& other);

    bool operator==(const vector2<T>& other) const;
    bool operator!=(const vector2<T>& other) const;

    vector2<T> operator*(T scalar) {
        return vector2<T>(x * scalar, y * scalar);
    }

    vector2<T> operator/(T scalar) {
        return vector2<T>(x / scalar, y / scalar);
    }

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

} // namespace nori


#endif // NORI_VECTOR2_H_
