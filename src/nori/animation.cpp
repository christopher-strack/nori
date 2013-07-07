#include "nori/detail/precompiled.h"
#include "nori/animation.h"


namespace nori {

animation::animation()
    : _value(0), _elapsed_time(0), _speed(1)
{
}

animation::animation(const integer_range& range)
    : _range(range),
      _iterator(range.begin()),
      _value(0),
      _elapsed_time(0),
      _speed(1)
{
    if (!range.empty()) {
        _value = *range.begin();
    }
}

void animation::advance(float time) {
    if (!_range.empty()) {
        _elapsed_time += time;
        while (_elapsed_time >= _speed) {
            _iterator++;
            if (_iterator == _range.end()) {
                _iterator = _range.begin();
            }
            _value = *_iterator;
            _elapsed_time -= _speed;
        }
    }
}

int animation::value() const {
    return _value;
}

animation& animation::set_speed(float speed) {
    _speed = speed;
    return *this;
}

float animation::speed() const {
    return _speed;
}

} // namespace nori
