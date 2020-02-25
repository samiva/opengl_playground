#include"vertexbuffer.h"
#include <glm/glm.hpp>

VertexBuffer::VertexBuffer() {
    _id = idcount;
    ++idcount;
 }

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &_id);
    --idcount;
}

void VertexBuffer::genBuffers(unsigned int count) {
    glGenBuffers(count, &_id);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setData(void * data, size_t size) {
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

unsigned int VertexBuffer::idcount = 1;
