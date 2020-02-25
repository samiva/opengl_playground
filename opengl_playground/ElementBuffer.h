#ifndef __ELEMENTBUFFER_H__
#define __ELEMENTBUFFER_H__
#include<gl/gl3w.h>

class IndexBuffer {
public:
    IndexBuffer();
    ~IndexBuffer();
    void genBuffers(unsigned int count=1);
    void setData(void *data, size_t size, size_t count);
    void bind() const;
    void unbind() const;
    inline const unsigned int getCount() const { return _count; }
private:
    unsigned int _count;
    unsigned int _id{ 1 };
    static unsigned int idcount;
};

#endif //!__ELEMENTBUFFER_H__