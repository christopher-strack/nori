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

    T x;
    T y;
};

typedef vector2<int> size;



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

} /* namespace nori */


#endif /* NORI_VECTOR2_H_ */
