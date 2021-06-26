#include "glew.h"
#include "Utils.h"
#include "ShaderProgram.h"
#include <vector>
#include "Vector4.h"
#include "Vector3.h"

#pragma once
class WireframeObject
{
public:
	WireframeObject(vector<Vector4> vertices, Vector4 color);
	~WireframeObject(void);

	void Render(ShaderProgram* program);
	void SetRotation(GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ);
	void SetRotation(Vector3 rotation);
	Vector3 GetRotation();

	void SetPosition(GLfloat positionX, GLfloat positionY, GLfloat positionZ);
	void SetPosition(Vector3 position);
	Vector3 GetPosition();
private:
	vector<Vector4> m_vertices;
	Vector4 m_color;

	vector<GLfloat> m_verticesBuffer;
	vector<GLfloat> m_colorBuffer;

	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_colorBufferId;

	Vector3 m_rotation;
	Vector3 m_position;

	void CreateVBO(void);
	void DestroyVBO(void);
};

