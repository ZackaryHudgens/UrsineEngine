#include "MeshComponent.hpp"

#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <cmrc/cmrc.hpp>

#include "Environment.hpp"
#include "GameObject.hpp"

CMRC_DECLARE(ShaderLib);

using UrsineRenderer::MeshComponent;

MeshComponent::MeshComponent()
  : mVAO(0)
  , mVBO(0)
  , mEBO(0)
{
  // Add the base model shader.
  auto fs = cmrc::ShaderLib::get_filesystem();
  auto vertexFile = fs.open("resources/shaders/DefaultShader.vert");
  auto fragmentFile = fs.open("resources/shaders/DefaultShader.frag");
  AddShader("default", Shader(vertexFile.begin(), fragmentFile.begin()));

  // Generate IDs for the vertex array, vertex buffer and element buffer.
  glGenVertexArrays(1, &mVAO);
  glGenBuffers(1, &mVBO);
  glGenBuffers(1, &mEBO);
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

void MeshComponent::PrivateRender() const
{
  for(const auto& shaderPair : GetShaderMap())
  {
    shaderPair.second.Activate();

    // Draw the mesh.
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
}
