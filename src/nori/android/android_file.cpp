#include "nori/detail/precompiled.h"
#include "nori/detail/android_file.h"
#include "nori/log.h"

#include <android/asset_manager.h>

#include <boost/algorithm/string/predicate.hpp>

#include <string>
#include <stdexcept>


namespace nori {
namespace detail {

AAssetManager* android_file::asset_manager = 0;


android_file::android_file()
    : _asset(0)
{
}

android_file::android_file(const char* filename) {
    open(filename);
}

android_file::~android_file() {
    close();
}

bool android_file::open(const char* filename) {
    static const std::string asset_folder = "assets/";
    if (boost::starts_with(filename, asset_folder)) {
        std::string asset_filename = std::string(filename).substr(asset_folder.size());

        _asset = ::AAssetManager_open(
            asset_manager,
            asset_filename.c_str(),
            AASSET_MODE_STREAMING);
    }
    else {
        throw std::runtime_error("not implemented");
    }

    return is_open();
}

void android_file::close() {
    if (_asset) {
        ::AAsset_close(_asset);
        _asset = 0;
    }
}

bool android_file::is_open() const {
    return _asset != 0;
}

unsigned int android_file::size() {
    return _asset != 0 ? static_cast<unsigned int>(::AAsset_getLength(_asset)) : 0;
}

unsigned int android_file::read(char* buffer, unsigned int size) {
    unsigned int bytes_read = 0;
    if (_asset) {
        bytes_read = ::AAsset_read(_asset, buffer, size);
    }
    return bytes_read;
}

} // namespace detail
} // namespace nori
