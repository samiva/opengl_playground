#ifndef __VERTEX_H__
#define __VERTEX_H__
#include <glm/glm.hpp>
class Vertex {
public:
    Vertex(glm::vec3 pos);
private:
    glm::vec3 _pos;
};
#endif // !__VERTEX_H__
