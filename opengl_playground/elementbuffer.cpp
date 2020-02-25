#include "ElementBuffer.h"

IndexBuffer::IndexBuffer() {
    _id = idcount;
    ++idcount;
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &_id);
}

void IndexBuffer::genBuffers(unsigned int count) {
    glGenBuffers(count, &_id);
}

void IndexBuffer::setData(void * data, size_t size, size_t count) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    _count = count;
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::idcount = 1;
