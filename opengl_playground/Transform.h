#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include<glm/glm.hpp>
class Transform {
public:
    glm::mat4 getTranslationMatrix();
    glm::mat4 getScaleMatrix();
    glm::mat4 getRotationMatrix();
    glm::mat4 getModelMatrix();

    inline void setPos(glm::vec3 pos) { _pos = pos; }
    inline void move(glm::vec3 dir) { _pos += dir; }
    inline void setScale(glm::vec3 s) { _scale = s; }

    inline void rotX(float factor) { _rotX += factor; }
    inline void rotY(float factor) { _rotY += factor; }
    inline void rotZ(float factor) { _rotZ += factor; }

private:
    glm::vec3 _pos{0.0f};
    
    glm::vec3 _scale{1.0f};
    float _angle{ 0.0f };
    float _rotX{ 0.0f }, _rotY{ 0.0f }, _rotZ{ 0.0f };
};
#endif