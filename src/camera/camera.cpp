#include "camera.h"

glm::mat4 Camera::getViewMatrix() {
    if (isInit) {
        isInit = false;
        updateCameraVectors();
    }

    return glm::lookAt(position, position + front, up);
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        else if (pitch < -89.f) {
            pitch = -89.0f;
        }
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset, float minZoom, float maxZoom) {
    if (minZoom > maxZoom) {
        float temp = minZoom;
        minZoom = maxZoom;
        maxZoom = temp;
    }

    if (zoom >= minZoom && zoom <= maxZoom) zoom -= yoffset;

    if (zoom <= minZoom) zoom = minZoom;
    else if (zoom >= maxZoom) zoom = maxZoom;
}

void Camera::updateCameraVectors() {
    // Calculate the new Front vector
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    // Also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
