#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <iostream>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float yaw = -90.0f;
const float pitch = 0.0f;
const float movementspeed = 2.5f;
const float sensitivity = 0.1f;
const float zoom = 45.0f;


class camera
{
public:
	float m_yaw;
	float m_pitch;
	float m_movementspeed;
	float m_sensitivity;
	float m_zoom;
	glm::vec3 m_front;
	glm::vec3 m_right;
	glm::vec3 m_up;
	glm::vec3 m_worldup;
	glm::vec3 m_position;
	glm::vec3 movementfront;
	glm::vec3 movementright;
	camera(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f), float Yaw = yaw, float Pitch = pitch);
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainpitch);
	void ProcessKeyboardMovement(Camera_Movement direction, float deltatime);
	void ProcessScrollMovement(float scrolloffset);
	void UpdateCamera(const glm::vec3& playerposition);
	glm::mat4 GetViewMatrix();
private:
	void updateCameraVectors();
};
#endif // !CAMERA_H


