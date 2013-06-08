#include "nori/image.h"
#include "nori/file.h"
#include "nori/log.h"

#include "lodepng/lodepng.h"


namespace nori {

image::image(const char* filename) {
    nori::file file(filename);
    if (file.is_open()) {
        unsigned int file_size = file.size();
        image_buffer file_buffer(file_size);
        file.read((char*)&file_buffer[0], file_size);

        lodepng::State state;
        unsigned int width, height;
        unsigned error = lodepng::decode(_data, width, height, state, file_buffer);

        if (!error) {
            _size.x = width;
            _size.y = height;
        }
        else {
            log_error(
                "Error loading image '%s': %s",
                filename,
                lodepng_error_text(error));
        }
    }
    else {
        log_error("Couldn't load image. File '%s' doesn't exist.", filename);
    }
}

nori::size image::size() const {
    return _size;
}

image::image_buffer image::data() const {
    return _data;
}

} /* namespace nori */
