#include "pch.h"
#include "VertexArray.h"

bool ew::VertexArray::create(const std::string& name, void* null)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    return true;
}

void ew::VertexArray::destroy()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(vbos.size(), vbos.data());
}

void ew::VertexArray::CreateBuffer(GLsizei size, GLsizei count, void* data)
{
    this->count = count;
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    vbos.push_back(vbo);
}

void ew::VertexArray::SetAttribute(int index, GLint size, GLsizei stride, size_t offset)
{
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)(offset));
}

void ew::VertexArray::Draw(GLenum primitiveType)
{
    glBindVertexArray(vao);
    glDrawArrays(primitiveType, 0, count);
}
