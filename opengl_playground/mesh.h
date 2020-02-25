#ifndef __MESH_H__
#define __MESH_H__
#include <glm/glm.hpp>
#include <vector>


struct IndexedVertex {
    glm::vec3 pos;
    glm::vec3 normal;

    unsigned int posIdx;
    //unsigned  int normalIdx;

    bool operator==(const IndexedVertex& other) const {
        return pos == other.pos;
    }
};

struct Triangle {
    IndexedVertex v0, v1, v2;

    bool adjacentToVertex(const IndexedVertex& v) const {
        if (v == v0 || v == v1 || v == v2) return true;
        return false;
    }
};



class Mesh {
private:
public:
	Mesh() = default;
	Mesh(unsigned int numIndices);
	unsigned int* _indices;
	std::vector<float> _vdata;
	unsigned int _indiceCount;

};

Mesh createMesh(const float* vertexData, const unsigned int* indices, bool genNormals =false);
#endif // !__MESH_H__
