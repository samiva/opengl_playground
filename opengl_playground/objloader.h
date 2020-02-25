#ifndef __OBJLOADER_H__
#define __OBJLOADER_H__
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

/*
TODO: 
    * Read vertex normals from the model
*/

class Mesh;
class ObjModel {
public:
    ObjModel() = default;
    ~ObjModel() = default;
    ObjModel(const ObjModel &) = default;
    ObjModel(ObjModel&&) = default;
    ObjModel& operator=(const ObjModel&) = default;
    ObjModel& operator=(ObjModel&&) = default;

    ObjModel(const std::string& fname);

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textCoords;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;
    
private:
    Mesh* loadMesh(const std::string& fname);

    void loadOBJ(const std::string& fname);
    void parseVertIndex(std::stringstream& stream);

};
#endif