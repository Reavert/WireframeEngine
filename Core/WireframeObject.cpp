#include "WireframeObject.h"
#include <stdio.h>

WireframeObject::WireframeObject(vector<GLfloat> vertices, vector<GLfloat> colors)
{
	m_vertices = vertices;
	m_colors.clear();
    for (GLfloat v : m_vertices)
    {
        m_colors.push_back(1.0f);
    }
    m_shaderProgram = new ShaderProgram("vertex.glsl", "fragment.glsl");
    CreateVBO();
    
}

WireframeObject::~WireframeObject(void)
{
    DestroyVBO();
}

void WireframeObject::CreateVBO(void)
{
    GLsizeiptr vboSize = m_vertices.size() * sizeof(GLfloat);
    GLsizeiptr colorBufferSize = m_colors.size() * sizeof(GLfloat);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vboSize, m_vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &m_colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colorBufferSize, m_colors.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
}

void WireframeObject::DestroyVBO(void)
{
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &m_colorBuffer);
    glDeleteBuffers(1, &m_vbo);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &m_vao);
}

void WireframeObject::Render(void)
{
    m_shaderProgram->Use();
    glBindVertexArray(m_vao);
    glDrawArrays(GL_LINE_STRIP, 0, m_vertices.size());
}

void WireframeObject::SetRotation(GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ)
{
    m_shaderProgram->SetRotation(rotationX, rotationY, rotationZ);
}