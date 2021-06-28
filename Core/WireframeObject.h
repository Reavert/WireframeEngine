#pragma once

#include "glew.h"
#include "Utils.h"
#include "ShaderProgram.h"
#include <vector>
#include "Vector4.h"
#include "Vector3.h"
#include "ObjectInfo.h"

class WireframeObject
{
public:
	WireframeObject(ObjectInfo info, Vector4 color);
	~WireframeObject(void);

	void Render(ShaderProgram* program);

	void SetRotation(GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ);
	void SetRotation(Vector3 rotation);
	Vector3 GetRotation();

	void SetPosition(GLfloat positionX, GLfloat positionY, GLfloat positionZ);
	void SetPosition(Vector3 position);
	Vector3 GetPosition();

	void SetScale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ);
	void SetScale(Vector3 scale);
	Vector3 GetScale();

private:
	vector<Vector4> m_vertices;
	vector<GLuint> m_indices;
	Vector4 m_color;

	vector<GLfloat> m_verticesBuffer;
	vector<GLfloat> m_colorBuffer;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_colorBufferId;
	GLuint m_elementBufferId;

	Vector3 m_rotation;
	Vector3 m_position;
	Vector3 m_scale;

	void CreateVBO(void);
	void DestroyVBO(void);
};

