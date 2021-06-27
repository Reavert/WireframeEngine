#include "WireframeObject.h"

WireframeObject::WireframeObject(vector<Vector4> vertices, Vector4 color)
{
    m_vertices = vertices;
    m_color = color;

    auto cArr = m_color.ToArray();
    for (auto v : m_vertices)
    {
        auto vArr = v.ToArray();
        m_verticesBuffer.insert(m_verticesBuffer.end(), vArr.begin(), vArr.end());
        m_colorBuffer.insert(m_colorBuffer.end(), cArr.begin(), cArr.end());
    }

    m_position = Vector3(0.0f, 0.0f, 0.0f);
    m_rotation = Vector3(0.0f, 0.0f, 0.0f);
    m_scale = Vector3(1.0f, 1.0f, 1.0f);
    CreateVBO();
    
}

WireframeObject::~WireframeObject(void)
{
    DestroyVBO();
}

void WireframeObject::CreateVBO(void)
{
    GLsizeiptr vboSize = m_verticesBuffer.size() * sizeof(GLfloat);
    GLsizeiptr colorBufferSize = m_colorBuffer.size() * sizeof(GLfloat);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vboSize, m_verticesBuffer.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &m_colorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBufferId);
    glBufferData(GL_ARRAY_BUFFER, colorBufferSize, m_colorBuffer.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
}

void WireframeObject::DestroyVBO(void)
{
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &m_colorBufferId);
    glDeleteBuffers(1, &m_vbo);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &m_vao);
}

void WireframeObject::Render(ShaderProgram* program)
{
    glPushMatrix();
    program->SetPosition(m_position.x, m_position.y, m_position.z);
    program->SetRotation(m_rotation.x, m_rotation.y, m_rotation.z);
    program->SetScale(m_scale.x, m_scale.y, m_scale.z);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_LINE_STRIP, 0, m_verticesBuffer.size());
    glPopMatrix();
}

void WireframeObject::SetRotation(GLfloat rotationX, GLfloat rotationY, GLfloat rotationZ)
{
    m_rotation.x = rotationX;
    m_rotation.y = rotationY;
    m_rotation.z = rotationZ;
}

void WireframeObject::SetRotation(Vector3 rotation)
{
    m_rotation = rotation;
}

void WireframeObject::SetPosition(GLfloat positionX, GLfloat positionY, GLfloat positionZ)
{
    m_position.x = positionX;
    m_position.y = positionY;
    m_position.z = positionZ;
}

void WireframeObject::SetPosition(Vector3 position)
{
    m_position = position;
}

void WireframeObject::SetScale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ)
{
    m_scale.x = scaleX;
    m_scale.y = scaleY;
    m_scale.z = scaleZ;
}

void WireframeObject::SetScale(Vector3 scale)
{
    m_scale = scale;
}
