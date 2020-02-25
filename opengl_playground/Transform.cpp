#include"Transform.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;



glm::mat4 Transform::getTranslationMatrix() {
    auto T = identity<mat4>();
    T = translate(T, _pos);
    return T;
}

glm::mat4 Transform::getScaleMatrix() {
    auto S = identity<mat4>();
    S = scale(S, _scale);
    return S;
}

glm::mat4 Transform::getRotationMatrix() {
    // X rotation matrix
    auto x = vec3(1,0,0);
    auto Rx = identity<mat4>();
    Rx = rotate(Rx, _rotX, x); 

    // Y rotation matrix
    auto y = vec3(0,1,0);
    auto Ry = identity<mat4>();
    Ry = rotate(Ry, _rotY, y);
    
    // Z rotation matrix
    auto z = vec3(0, 0, 1);
    auto Rz = identity<mat4>();
    Rz = rotate(Rz,_rotZ, z);

    return Rx*Ry*Rz;
}

glm::mat4 Transform::getModelMatrix() {
    auto R = getRotationMatrix();
    auto S = getScaleMatrix();
    auto T = getTranslationMatrix();
    return T * R * S;
}