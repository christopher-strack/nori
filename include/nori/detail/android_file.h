#ifndef NORI_ANDROID_FILE_H_
#define NORI_ANDROID_FILE_H_


struct AAssetManager;
struct AAsset;


namespace nori {
namespace detail {

class android_file {
public:
    android_file();
    android_file(const char* filename);
    ~android_file();

    bool open(const char* filename);
    void close();
    bool is_open() const;

    unsigned int size();
    unsigned int read(char* buffer, unsigned int size);


    static AAssetManager* asset_manager;

private:
    AAsset* _asset;
};

} // namespace detail
} // namespace nori

#endif // NORI_ANDROID_FILE_H_
