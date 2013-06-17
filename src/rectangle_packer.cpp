#include "nori/detail/rectangle_packer.h"

#include <boost/make_shared.hpp>


namespace nori {
namespace detail {

rectangle_packer::rectangle_packer(const size& size)
    : _root(rectangle(point(), size))
{
}

bool rectangle_packer::pack(const size& rectangle_size, rectangle& packed_region) {
    if (rectangle_size.x > 0 && rectangle_size.y > 0) {
        node* node = _root.add(rectangle_size);
        if (node) {
            packed_region = node->region();
            return true;
        }
    }
    return false;
}


rectangle_packer::node::node(const rectangle& region)
    : _region(region), _free(true)
{
}

rectangle_packer::node* rectangle_packer::node::add(const size& size) {
    if (_left != 0 && _right != 0) {
        rectangle_packer::node* new_node = _left->add(size);
        if (new_node != 0) {
            return new_node;
        }

        return _right->add(size);
    } else {
        if (!_free) {
            return 0;
        }

        rectangle requested_region(_region.position(), size);
        if (!requested_region.inside(_region)) {
            return 0;
        }
        if (requested_region == _region) {
            _free = false;
            return this;
        }

        if (_region.size().x - size.x > _region.size().y - size.y) {
            _left = boost::make_shared<node>(rectangle(
                _region.left, _region.top,
                _region.left + size.x, _region.bottom));
            _right = boost::make_shared<node>(rectangle(
                _region.left + size.x, _region.top,
                _region.right, _region.bottom));
        } else {
            _left = boost::make_shared<node>(rectangle(
                _region.left, _region.top,
                _region.right, _region.top + size.y));
            _right = boost::make_shared<node>(rectangle(
                _region.left, _region.top + size.y,
                _region.right, _region.bottom));
        }

        return _left->add(size);
    }
}

const rectangle& rectangle_packer::node::region() const {
    return _region;
}

} /* namespace detail */
} /* namespace nori */
