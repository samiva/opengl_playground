#ifndef __VERTEXBUFFER_H__
#define __VERTEXBUFFER_H__
#include <GL/gl3w.h>

class VertexBuffer {
public:
    VertexBuffer();
    ~VertexBuffer();
    void genBuffers(unsigned int count = 1);
    void bind() const;
    void unbind() const;
    void setData(void* data, size_t size);
private:
    unsigned int _id;
    static unsigned int idcount;
};
#endif //!__VERTEXBUFFER_H__