#include "Renderer.h"
#include "vertexarray.h"
#include "ElementBuffer.h"
#include "Shader.h"

void Renderer::draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) const {
    va.bind();
    ib.bind();
    shader.bind();
    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::clear() const {
    static const float color[] = { 1,0,0,1 };
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glClearBufferfv(GL_COLOR, GL_NONE, color);
}
