#include "Camera.h"

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

	m_viewPosition = Vector3(0.0f, 0.0f, 0.0f);
	m_viewRotation = Vector3(0.0f, 0.0f, 0.0f);
}

void Camera::SetPosition(GLfloat posX, GLfloat posY, GLfloat posZ)
{
	m_viewPosition.x = posX;
	m_viewPosition.y = posY;
	m_viewPosition.z = posZ;
}

void Camera::SetPosition(Vector3 position)
{
	SetPosition(position.x, position.y, position.z);
}

void Camera::SetRotation(GLfloat rotX, GLfloat rotY, GLfloat rotZ)
{
	m_viewRotation.x = rotX;
	m_viewRotation.y = rotY;
	m_viewRotation.z = rotZ;

	GLfloat _forwardX, _forwardY, _forwardZ;
	GLfloat forwardX, forwardY, forwardZ;

	GLfloat _upX, _upY, _upZ;
	GLfloat upX, upY, upZ;

	_forwardY = sinf(rotX * PI / 180.0f);
	_forwardZ = cosf(rotX * PI / 180.0f);

	_forwardX = _forwardZ * sinf(rotY * PI / 180.0f);
	forwardZ = _forwardZ * cosf(rotY * PI / 180.0f);

	forwardX = _forwardX * cosf(rotZ * PI / 180.0f) + _forwardY * sinf(rotZ * PI / 180.0f);
	forwardY = _forwardX * sinf(rotZ * PI / 180.0f) - _forwardY * cosf(rotZ * PI / 180.0f);

	m_viewForward.x = forwardX;
	m_viewForward.y = forwardY;
	m_viewForward.z = forwardZ;

	_upY = -cosf(rotX * PI / 180.0f);
	_upZ = sinf(rotX * PI / 180.0f);

	_upX = _upZ * sinf(rotY * PI / 180.0f);
	upZ = _upZ * cosf(rotY * PI / 180.0f);

	upX = _upX * cosf(rotZ * PI / 180.0f) + _upY * sinf(rotZ * PI / 180.0f);
	upY = _upX * sinf(rotZ * PI / 180.0f) - _upY * cosf(rotZ * PI / 180.0f);

	m_viewUp.x = upX;
	m_viewUp.y = upY;
	m_viewUp.z = upZ;
}

void Camera::SetRotation(Vector3 rotation)
{
	SetRotation(rotation.x, rotation.y, rotation.z);
}

Vector3 Camera::GetForwardVector()
{
	return m_viewForward;
}

Vector3 Camera::GetUpVector()
{
	return m_viewUp;
}

void Camera::UpdateProjection(ShaderProgram* program)
{
	program->SetProjection(m_projectionMatrix[0]);
}

void Camera::UpdateView(ShaderProgram* program)
{
	program->SetViewPosition(m_viewPosition.x, m_viewPosition.y, m_viewPosition.z);
	program->SetViewRotation(m_viewRotation.x, m_viewRotation.y, m_viewRotation.z);
}