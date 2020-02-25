#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__
#include<GL/gl3w.h>
#include<vector>

class VertexBuffer;

struct BufferLayoutElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    static unsigned int getSizeOfType(unsigned int type) {
        switch (type) 
        {
            case GL_FLOAT:      return sizeof(float);
        }
        return 0;
    }
};

class BufferLayout {
public:
    const std::vector<BufferLayoutElement>& getElements() const { return _elements; }
    const unsigned int getStride() const { return _stride; }

    template<typename T>
    void push(unsigned int count){}

    template<>
    void push<float>(unsigned int count) {
        _elements.push_back({GL_FLOAT, count, GL_FALSE});
        _stride += count * BufferLayoutElement::getSizeOfType(GL_FLOAT);
    }

private:
    std::vector<BufferLayoutElement> _elements;
    unsigned int _stride{ 0 };
};

class VertexArray {

public:
    VertexArray();
    ~VertexArray();
    void genVertexArrays(unsigned int count = 1);
    void bind() const;
    void unbind() const;
    void addBufferLayout(const VertexBuffer& vb, const BufferLayout& layout);
    
private:
    unsigned int _id;
    static unsigned int idcount;
};
#endif //!__VERTEXARRAY_H__