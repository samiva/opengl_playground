#include "objloader.h"
#include "mesh.h"

ObjModel::ObjModel(const std::string & fname) {
    loadOBJ(fname);
}

Mesh* ObjModel::loadMesh(const std::string& fname) {
    return nullptr;
}

void ObjModel::loadOBJ(const std::string& fname) {
    std::ifstream ifs(fname);
    std::stringstream stream;
    while (!ifs.eof()) {
        stream.str("");
        stream.clear();
        std::string str;
        std::getline(ifs, str);
        stream.str(str);
        char c;
        stream.get(c);
        switch (c) {
        case 'v':
        {
            stream.get(c);
            switch (c) {
            case 't':
            {
                // texture coordinates
                float u, v;
                stream >> u;
                stream >> v;
                textCoords.push_back(glm::vec2(u, v));
            }
            break;
            case 'n':
            {
                float x, y, z;
                // read vertex normals
                stream >> x;
                stream >> y;
                stream >> z;
                normals.push_back(glm::vec3(x,y,z));
            }
            break;
            case ' ':
            {
                float x, y, z;
                // read vertex positions
                stream >> x;
                stream >> y;
                stream >> z;
                vertices.push_back(glm::vec3(x, y, z));
            }
            break;
            }
        }
        break;
        case 'f':
        {
            // read index
            parseVertIndex(stream);
        }
        break;
        }
    }
}

void ObjModel::parseVertIndex(std::stringstream& stream) {
    int c;
    while (!stream.eof()) {
        c = stream.get();
        if (isalnum(c)) {
            stream.unget();
            int i;
            stream >> i;
            i -= 1;
            indices.push_back(i);
            stream.ignore(256, ' ');
        }
    }
}