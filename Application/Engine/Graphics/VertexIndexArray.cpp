#include "pch.h"
#include "VertexIndexArray.h"

bool ew::VertexIndexArray::create(const std::string& name, void* null)
{
    VertexArray::create(name, null);

    return true;
}

void ew::VertexIndexArray::destroy()
{
    VertexArray::destroy();
    glDeleteBuffers(1, &ibo);
}

void ew::VertexIndexArray::createIndexBuffer(GLenum indexType, GLsizei count, void* data)
{
    this->indexType = indexType;
    this->indexCount = count;

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    size_t indexSize = (indexType == GL_UNSIGNED_SHORT) ? sizeof(GLushort) : sizeof(GLuint);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * indexSize, data, GL_STATIC_DRAW);

}

void ew::VertexIndexArray::draw(GLenum primitiveType)
{
    glBindVertexArray(vao);
    glDrawElements(primitiveType, indexCount, indexType, 0);
}
