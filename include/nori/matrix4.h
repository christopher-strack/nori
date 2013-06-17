#ifndef NORI_MATRIX4_H_
#define NORI_MATRIX4_H_

#include "nori/vector2.h"


namespace nori {

class matrix4 {
public:
    matrix4();
    matrix4(float elements[16]);

    static matrix4 make_orthogonal(const size& size);

    float elements[16];
};

} // namespace nori

#endif /* NORI_MATRIX4_H_ */
