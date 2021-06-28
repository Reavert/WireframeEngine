#pragma once
#include <glew.h>
#include "ShaderProgram.h"
#include "Vector3.h"

#define PI 3.1415926535

class Camera
{
public:
	Camera(GLfloat FOV, GLfloat width, GLfloat height, GLfloat nearZ, GLfloat farZ);

	void UpdateProjection(ShaderProgram* program);
	void UpdateView(ShaderProgram* program);
private:
	GLfloat m_aspectRatio;
	GLfloat m_near;
	GLfloat m_far;
	GLfloat m_range;
	GLfloat m_FOV;

	GLfloat m_projectionMatrix[4][4];

	Vector3 m_viewPosition;
};