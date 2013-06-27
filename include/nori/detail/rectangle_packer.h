#ifndef NORI_RECTANGLE_PACKER_H_
#define NORI_RECTANGLE_PACKER_H_

#include "nori/rectangle.h"
#include "nori/vector2.h"

#include <boost/optional.hpp>

#include <memory>


namespace nori {
namespace detail {

class rectangle_packer {
public:
    rectangle_packer(const size& size);

    boost::optional<rectangle> pack(const size& rectangle_size);

private:
    class node {
    public:
        node(const rectangle& rectangle);
        node* add(const size& size);
        const rectangle& region() const;

    private:
        typedef std::shared_ptr<node> node_ptr;
        node_ptr _left;
        node_ptr _right;
        rectangle _region;
        bool _free;
    };

    node _root;
};

} // namespace detail
} // namespace nori

#endif // NORI_RECTANGLE_PACKER_H_
