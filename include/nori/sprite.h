#ifndef NORI_SPRITE_H_
#define NORI_SPRITE_H_

#include "nori/vector2.h"
#include "nori/detail/sprite_fwd.h"

#include <string>


namespace nori {

class sprite {
public:
    sprite(const std::string& image_file);
    sprite(const std::string& image_file, const size& slice_size);

    const size slice_size() const;
    const std::string& image_file() const;

private:
    size _slice_size;
    std::string _image_file;
};


sprite_ptr make_sprite(const std::string& image_file);
sprite_ptr make_sprite(const std::string& image_file, const size& slice_size);

} // namespace nori

#endif // NORI_SPRITE_H_
