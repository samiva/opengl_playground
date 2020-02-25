#include"Camera.h"

Camera::Camera() {
}

Camera::Camera(glm::vec3 pos, glm::vec3 target) : _pos(pos) {
    _forward = glm::normalize( target-_pos);
    glm::vec3 up(0,1,0);
    _right = glm::normalize(glm::cross(_forward, up));
    _up = -(glm::normalize(glm::cross(_forward, _right)));
}

// TODO: Fix rotation
void Camera::rotateYaw(float angle) {
    _yawAngle += angle;
    if (_yawAngle > 359.0f) {
        _yawAngle = 0.0f;
    }
    else if (_yawAngle < 0) {
        _yawAngle = 359.0f;
    }

    //_forward = glm::normalize(glm::vec3(glm::sin(_yawAngle), _forward.y, glm::cos(_yawAngle)));
    //_left = glm::normalize(glm::cross(_up, _forward));
    calculateForward(glm::radians(_pitchAngle), glm::radians(_yawAngle));
    auto R = glm::identity<glm::mat4>();
    auto up = glm::vec3(0.0f,1.0f,0.0f);
    R = glm::rotate(R, _yawAngle, up);
    _right = glm::normalize(glm::cross(_forward, _up));
    //_forward *= R;
}

// TODO: Fix rotation
void Camera::rotatePitch(float angle) {
    _pitchAngle += angle;
    if (_pitchAngle > 89.0f) {
        _pitchAngle=89.0f;
    } else if(_pitchAngle<0) {
        _pitchAngle = 0;
    }
    //_forward = glm::normalize(glm::vec3(_forward.x, glm::sin(_pitchAngle), glm::cos(_pitchAngle)));
    calculateForward(glm::radians(_pitchAngle), glm::radians(_yawAngle));
    //_up = glm::normalize(glm::cross(_forward, _right));
}

void Camera::calculateForward(float pitch, float yaw) {
    _forward = glm::normalize(glm::vec3(glm::cos(pitch)*glm::cos(yaw), glm::sin(pitch), glm::cos(pitch)*glm::sin(yaw)));
}