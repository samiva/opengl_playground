#include "vertexarray.h"
#include "vertexbuffer.h"


VertexArray::VertexArray() {
    _id = idcount;
    ++idcount;
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &_id);
}

void VertexArray::genVertexArrays(unsigned int count) {
    glGenVertexArrays(count, &_id);
}

void VertexArray::bind() const {
    glBindVertexArray(_id);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::addBufferLayout(const VertexBuffer& vb, const BufferLayout & layout) {
    vb.bind();
    unsigned char offset{ 0 };
    for (unsigned int i = 0; i < layout.getElements().size(); ++i) {
        const auto& elem = layout.getElements()[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, elem.count, elem.type, elem.normalized, layout.getStride(), reinterpret_cast<void*>(offset));
        offset += elem.count * BufferLayoutElement::getSizeOfType(elem.type);
    }
}

unsigned int VertexArray::idcount = 1;

