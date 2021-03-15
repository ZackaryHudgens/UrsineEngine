#include "MeshComponent.hpp"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include "Environment.hpp"
#include "GameObject.hpp"

using UrsineRenderer::MeshComponent;

MeshComponent::MeshComponent()
  : mVAO(0)
  , mVBO(0)
  , mEBO(0)
{
  // Generate IDs for the vertex array, vertex buffer and element buffer.
  glGenVertexArrays(1, &mVAO);
  glGenBuffers(1, &mVBO);
  glGenBuffers(1, &mEBO);
}

void MeshComponent::Render() const
{
  if(GetCurrentShader() != nullptr)
  {
    GetCurrentShader()->Activate();

    // Draw the mesh.
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
}

void MeshComponent::SetVertices(const VertexList& aVertices)
{
  mVertices = aVertices;

  // Bind the vertex array.
  glBindVertexArray(mVAO);

  // Load the vertex data.
  glBindBuffer(GL_ARRAY_BUFFER, mVBO);
  glBufferData(GL_ARRAY_BUFFER,
               mVertices.size() * sizeof(MeshVertex),
               &mVertices[0],
               GL_STATIC_DRAW);

  // Set the vertex position attributes.
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(MeshVertex),
                        (void*)(0));

  // Set the vertex color attributes.
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(MeshVertex),
                        (void*)(offsetof(MeshVertex, mColor)));

  // Set the vertex texture coordinates.
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2,
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(MeshVertex),
                        (void*)(offsetof(MeshVertex, mTexCoords)));

  // Unbind the vertex array.
  glBindVertexArray(0);
}

void MeshComponent::SetIndices(const IndexList& aIndices)
{
  mIndices = aIndices;

  // Bind the vertex array.
  glBindVertexArray(mVAO);

  // Load the element data.
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               mIndices.size() * sizeof(unsigned int),
               &mIndices[0],
               GL_STATIC_DRAW);

  // Unbind the vertex array.
  glBindVertexArray(0);
}
