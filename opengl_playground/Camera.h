#ifndef __CAMERA_H__
#define __CAMERA_H__
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<iostream>

class Camera {
public:
    Camera();
    Camera(glm::vec3 pos, glm::vec3 target);
    inline void move(glm::vec3 dir) { _pos += dir; }
    inline void moveForward(float speed) { _pos += _forward * speed; }
    inline void moveBackward(float speed) { _pos -= _forward * speed; }
    inline void moveLeft(float speed) { _pos -= _right * speed; }
    inline void moveRight(float speed) { _pos += _right * speed; }

    inline glm::mat4 getViewMatrix() { return glm::lookAt(_pos, _pos + _forward * 10.0f, _up); }
    inline glm::mat4 getProjMatrix(float width, float height) { return glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f); }
    void rotateYaw(float angle);
    void rotatePitch(float angle);
private:
    glm::vec3 _pos{ 0.0f };
    glm::vec3 _up{ 0.0f,1.0f,0.0f };
    glm::vec3 _right;
    glm::vec3 _forward{ 0.0f,0.0f,-1.0f };

    float _yawAngle = 0.0f;
    float _pitchAngle = 0.0f;

    void calculateForward(float pitch, float yaw);
};
#endif