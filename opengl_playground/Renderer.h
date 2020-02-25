#ifndef __RENDERER_H__
#define __RENDERER_H__
#include <GL/gl3w.h>

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer {
public:
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void clear() const;
};
#endif // !__RENDERER_H__