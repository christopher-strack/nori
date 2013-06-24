#ifndef NORI_SPRITE_H_
#define NORI_SPRITE_H_

#include "nori/detail/sprite_fwd.h"

#include <string>


namespace nori {

class sprite {
public:
    sprite(const std::string& image_file);

    const std::string& image_file() const;

private:
    std::string _image_file;
};


sprite_ptr make_sprite(const std::string& image_file);

} // namespace nori

#endif // NORI_SPRITE_H_
