#include "mesh.h"
#include <iostream>

Mesh createMesh(const float* vertexData, const unsigned int* indices, bool genNormals) {
    // get list of vertex positions for each triangle
    std::vector<IndexedVertex> verts;
    for (int i = 0; i < 36; ++i) {
        std::cout << "Vertex:" << std::endl;
        int k = 0;
        auto indx = 3 * indices[i] + k;
        auto indy = 3 * indices[i] + k + 1;
        auto indz = 3 * indices[i] + k + 2;
        auto x = vertexData[indx];
        auto y = vertexData[indy];
        auto z = vertexData[indz];
        IndexedVertex vert;
        vert.pos = {x,y,z};
        vert.posIdx = i;
        verts.push_back(vert);
    }


    std::vector<Triangle> triangles;
    for (int i = 0; i < verts.size(); i+=3) {
        
        triangles.push_back(Triangle{ verts[i],verts[i + 1],verts[i + 2] });
    }

    // Normal order : front, left, back, right, top, bottom
    std::vector<glm::vec3> fnormals;
    for (int i = 0; i < verts.size();i+=6) {
        glm::vec3 v0 = verts[i].pos;
        glm::vec3 v1 = verts[i+1].pos;
        glm::vec3 v2 = verts[i+2].pos;

        glm::vec3 l0 = v1 - v0;
        glm::vec3 l1 = v2 - v0;
        fnormals.push_back(glm::cross(l0,l1));
    }

    int fndx=0;
    for (int i = 0; i < triangles.size(); i+=2) {
        triangles[i].v0.normal = fnormals[fndx];
        triangles[i].v1.normal = fnormals[fndx];
        triangles[i].v2.normal = fnormals[fndx];

        triangles[i+1].v0.normal = fnormals[fndx];
        triangles[i+1].v1.normal = fnormals[fndx];
        triangles[i+1].v2.normal = fnormals[fndx];
        fndx++;
    }
    
    std::vector<IndexedVertex> vdata;

    for (int i = 0; i < triangles.size(); i+=2) {
        vdata.push_back(triangles[i].v0);
        vdata.push_back(triangles[i].v1);
        vdata.push_back(triangles[i].v2);
        vdata.push_back(triangles[i + 1].v1);
    }

    /*
        CUBE INDICES:
        front   :     0 1 2
                :     0 3 2
        left    :     4 5 6
                :     4 7 6
        back    :     8 9 10
                :     8 11 10
        right   :     12 13 14
                      12 15 14
        top     :     16 17 18
                      16 19 18
        bottom  :     20 21 22
                      20 23 22
    */
    
    unsigned int newIndices[36];

    for (int i = 0, k = 0; i < 36; i += 6, k += 4) {
        newIndices[i]=k;
        newIndices[i+1] = k+1;
        newIndices[i+2] = k+2;

        newIndices[i+3] = k;
        newIndices[i+4] = k+3;
        newIndices[i+5] = k+2;

    }
	Mesh mesh(sizeof(newIndices)/sizeof(newIndices[0]));
	std::memcpy(mesh._indices, newIndices, sizeof(newIndices));
	// Mesh vdata std::vector<float> and vdata std::vector<IndexedVertex>
	for (auto iv : vdata) {
		//mesh._vdata = vdata;
		mesh._vdata.push_back(iv.pos.x);
		mesh._vdata.push_back(iv.pos.y);
		mesh._vdata.push_back(iv.pos.z);

		if (genNormals)
		{
			mesh._vdata.push_back(iv.normal.x);
			mesh._vdata.push_back(iv.normal.y);
			mesh._vdata.push_back(iv.normal.z);
		}
	}
	mesh._indiceCount = sizeof(newIndices)/sizeof(newIndices[0]);
    return mesh;
}

Mesh::Mesh(unsigned int numIndices) {
	_indices = new unsigned int[numIndices];	
}
