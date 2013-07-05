#ifndef NORI_SLICER_H_
#define NORI_SLICER_H_

#include "nori/vector2.h"
#include "nori/rectangle.h"

#include <vector>


namespace nori {

typedef std::vector<rectangle> rectangle_list;


class slicer_base {
public:
    virtual rectangle_list slice(const size& area_size) = 0;
};


class default_slicer : public slicer_base {
public:
    virtual rectangle_list slice(const size& area_size);
};


class grid_slicer : public slicer_base {
public:
    grid_slicer(int width, int height);
    grid_slicer(const size& cell_size);

    virtual rectangle_list slice(const size& area_size);

private:
    size _cell_size;
};

} // namespace nori

#endif // NORI_SPRITE_H_
