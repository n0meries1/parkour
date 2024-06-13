#include "camera.h"

camera::camera(glm::vec3 Position, glm::vec3 Up, float Yaw, float Pitch)
	: m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_movementspeed(movementspeed), m_sensitivity(sensitivity), m_zoom(zoom)
{
	m_position = Position;
	m_worldup = Up;
	m_yaw = Yaw;
	m_pitch = Pitch;
	updateCameraVectors();
}

void camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainpitch = true)
{
	xoffset *= m_sensitivity;
	yoffset *= m_sensitivity;

	m_yaw += xoffset;
	m_pitch += yoffset;

	if (constrainpitch)
	{
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;
	}

	updateCameraVectors();
}

void camera::ProcessKeyboardMovement(Camera_Movement direction, float deltatime)
{
	float velocity = m_movementspeed * deltatime;
	if (direction == FORWARD)
		m_position += movementfront * velocity;
	if (direction == BACKWARD)
		m_position -= movementfront * velocity;
	if (direction == LEFT)
		m_position += movementright * velocity;
	if (direction == RIGHT)
		m_position -= movementright * velocity;
}

void camera::ProcessScrollMovement(float scrolloffset)
{
	if (m_zoom >= 1.0f && m_zoom <= 45.0f)
		m_zoom -= scrolloffset;
	if (m_zoom < 1.0f)
		m_zoom = 1.0f;
	if (m_zoom > 45.0f)
		m_zoom = 45.0f;

}
void camera::UpdateCamera(const glm::vec3& playerposition)
{
	m_position = playerposition - m_front * 10.0f + glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 camera::GetViewMatrix()
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);
	m_right = glm::normalize(glm::cross(m_front, m_worldup));
	m_up = glm::normalize(glm::cross(m_right, m_front));
	
}
