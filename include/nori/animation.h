#ifndef NORI_ANIMATION_H_
#define NORI_ANIMATION_H_

#include <boost/range/any_range.hpp>


namespace nori {

typedef boost::any_range<
    int, boost::forward_traversal_tag,
    int, std::ptrdiff_t>
integer_range;


class animation {
public:
    animation();
    animation(const integer_range& range);

    void advance(float time);
    int value() const;

    animation& set_speed(float speed);
    float speed() const;

private:
    int _value;
    float _elapsed_time;
    float _speed;
    integer_range _range;
    integer_range::const_iterator _iterator;
};

} // namespace nori

#endif // NORI_ANIMATION_H_
