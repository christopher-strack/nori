#include "nori/detail/precompiled.h"
#include "nori/slicer.h"


namespace nori {

rectangle_list default_slicer::slice(const size& area_size) {
    rectangle_list slices;
    slices.push_back(rectangle(point(), area_size));
    return slices;
}


grid_slicer::grid_slicer(const size& cell_size)
    : _cell_size(cell_size)
{
}

grid_slicer::grid_slicer(int width, int height)
    : _cell_size(size(width, height))
{
}

rectangle_list grid_slicer::slice(const size& area_size) {
    rectangle_list slices;
    const int height = area_size.y - area_size.y % _cell_size.y;
    const int width  = area_size.x - area_size.x % _cell_size.x;
    for (int y = 0; y < height; y += _cell_size.y){
        for (int x = 0; x < width; x += _cell_size.x){
            slices.push_back(rectangle(point(x, y), _cell_size));
        }
    }
    return slices;
}

} // namespace nori
