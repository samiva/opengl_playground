#ifndef __TEXTURE_H__ 
#define __TEXTURE_H__
#include <GL/gl3w.h>
#include <string>
#include <vector>

class Texture {
public:
    Texture();
    ~Texture();
    void createCubemap(std::vector<std::string> filePaths);
    void createTexture2D(const std::string& filePath);
    void bind() const;
    void unbind() const;
private:
    unsigned char* loadImage(std::string filepath, int& w, int& h, int& nChannels);
    unsigned int _id;
    static unsigned int idcount;

};
#endif // !__TEXTURE_H__ 