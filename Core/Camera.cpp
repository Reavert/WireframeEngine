#include "Camera.h"
#include <math.h>

Camera::Camera(GLfloat FOV, GLfloat width, GLfloat height, GLfloat nearZ, GLfloat farZ)
{
	m_aspectRatio = width / height;
	m_near = nearZ;
	m_far = farZ;

	m_range = nearZ - farZ;
	m_FOV = FOV;

	const GLfloat tanHalfFOV = tanf((m_FOV / 2.0) * PI / 180.0);
	
	m_projectionMatrix[0][0] = 1.0f / (tanHalfFOV * m_aspectRatio);
	m_projectionMatrix[0][1] = 0.0f;
	m_projectionMatrix[0][2] = 0.0f;
	m_projectionMatrix[0][3] = 0.0f;

	m_projectionMatrix[1][0] = 0.0f;
	m_projectionMatrix[1][1] = 1.0f / tanHalfFOV;
	m_projectionMatrix[1][2] = 0.0f;
	m_projectionMatrix[1][3] = 0.0f;

	m_projectionMatrix[2][0] = 0.0f;
	m_projectionMatrix[2][1] = 0.0f;
	m_projectionMatrix[2][2] = (-m_near - m_far) / m_range;
	m_projectionMatrix[2][3] = 2.0f * m_far * m_near / m_range;

	m_projectionMatrix[3][0] = 0.0f;
	m_projectionMatrix[3][1] = 0.0f;
	m_projectionMatrix[3][2] = 1.0f;
	m_projectionMatrix[3][3] = 0.0f;
}

void Camera::UpdateProjection(ShaderProgram* program)
{
	program->SetProjection(m_projectionMatrix[0]);
}

void Camera::UpdateView(ShaderProgram* program)
{
	// Not implemented yet
}