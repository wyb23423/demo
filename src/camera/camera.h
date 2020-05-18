#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>;
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	// Camera Attributes
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	// Euler Angles
	float yaw = -90.0f;
	float pitch = 0.0f;

	// Camera options
	float mouseSensitivity = 0.1f;
	float zoom = 45.0f;

	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 getViewMatrix();

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void processMouseScroll(float yoffset, float minZoom = 1.0f, float maxZoom = 45.0f);

private:
	bool isInit = true;
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

	void updateCameraVectors();
};

#endif
