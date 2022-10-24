//
//  Camera.cpp
//  LeanOpenGL
//
//  Created by 李涵旭 on 2022/10/24.
//

#include "Camera.hpp"


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
: _front(glm::vec3(0.0f, 0.0f, -1.0f)),
_movementSpeed(CAMERA_SPEED),
_mouseSensitivity(CAMERA_SENSITIVITY),
_zoom(CAMERA_ZOOM)
{
    _position = position;
    _worldUp = up;
    _yaw = yaw;
    _pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
: _front(glm::vec3(0.0f, 0.0f, -1.0f)),
_movementSpeed(CAMERA_SPEED),
_mouseSensitivity(CAMERA_SENSITIVITY),
_zoom(CAMERA_ZOOM)
{
    _position = glm::vec3(posX, posY, posZ);
    _worldUp = glm::vec3(upX, upY, upZ);
    _yaw = yaw;
    _pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(_position, _position + _front, _up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float offset)
{
    if (direction == FORWARD)
        _position += _front * offset;
    if (direction == BACKWARD)
        _position -= _front * offset;
    if (direction == LEFT)
        _position -= _right * offset;
    if (direction == RIGHT)
        _position += _right * offset;
}

void Camera::ProcessKeyboard2(Camera_Movement direction, float deltaTime)
{
    float velocity = _movementSpeed * deltaTime;
    if (direction == FORWARD)
        _position += _front * velocity;
    if (direction == BACKWARD)
        _position -= _front * velocity;
    if (direction == LEFT)
        _position -= _right * velocity;
    if (direction == RIGHT)
        _position += _right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= _mouseSensitivity;
    yoffset *= _mouseSensitivity;
    
    _yaw   += xoffset;
    _pitch += yoffset;
    
    // 确保当滚动角超出界限时，屏幕不会翻转
    if (constrainPitch)
    {
        if (_pitch > 89.0f)
            _pitch = 89.0f;
        if (_pitch < -89.0f)
            _pitch = -89.0f;
    }
    
    // 使用更新后的欧拉角更新_front， _right和_up向量
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    _zoom -= (float)yoffset;
    if (_zoom < 1.0f)
        _zoom = 1.0f;
    if (_zoom > 45.0f)
        _zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    // 计算新的_front向量
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);
    // 还要重新计算_right和_up向量
    _right = glm::normalize(glm::cross(_front, _worldUp));
    // 将这些向量归一化，因为你越往上或往下看，它们的长度就越接近于0，这就会导致运动变慢。
    _up    = glm::normalize(glm::cross(_right, _front));
}
